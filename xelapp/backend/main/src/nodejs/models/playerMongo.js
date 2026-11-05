const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const Logger = require('../logger');
const config = require('config');
const logger = Logger.createLogger("playerMongo");

// Connect (Mongoose 6+: no options needed, native promises)
mongoose.connect(config.get('dbConfig.mongodb.connectionString'))
    .then(() => logger.info('Connected to MongoDB'))
    .catch(err => {
        logger.error('MongoDB connection error: ' + err.message);
        process.exit(1);
    });

// Player Schema
const PlayerSchema = new mongoose.Schema({
    loginname: {
        type: String,
        index: true
    },
    hash: {
        type: String
    },
    email: {
        type: String
    },
    name: {
        type: String
    },
    score: {
        type: Number
    },
    profileimage: {
        type: String
    }
});

const player = module.exports = mongoose.model('Player', PlayerSchema);

module.exports.createPlayer = async function (data) {
    if (await player.findOne({ name: data.name }) !== null) {
        throw 'Player name "' + data.name + '" is already taken';
    }

    const newPlayer = new player({
        name: data.name,
        score: data.score,
        loginname: data.username,       // schema field is "loginname"
        profileimage: 'noimage.png'     // schema field is lowercase "profileimage"
    });
    if (data.password) {
        newPlayer.hash = await bcrypt.hash(data.password, 10);
    }

    await newPlayer.save();
    return newPlayer;
};

// Fetch all players
module.exports.getPlayers = async function (limit) {
    return await player.find().limit(limit);
};

// Fetch all winners
module.exports.getWinners = async function (limit) {
    return await player.find({ score: { $gt: 0 } }).sort({ score: -1 }).limit(limit);
};

module.exports.updatePlayer = async function (data) {
    return await player.findOneAndUpdate(
        { name: data.name },
        { $inc: { score: data.score } },
        { new: true, upsert: true }
    );
};

module.exports.login = async function (username, password) {
    logger.debug("login in -->");
    const response = await player.findOne({ name: username });

    if (response && response.hash && await bcrypt.compare(password, response.hash)) {
        const { hash, ...user } = response.toObject();   // plain object, password hash excluded
        logger.debug(user);
        const token = jwt.sign({ sub: response.id }, config.get('jwt.secret'), { algorithm: 'HS256' });
        return { ...user, token };
    }
    return false;
};