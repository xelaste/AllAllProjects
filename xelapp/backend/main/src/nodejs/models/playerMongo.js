var mongoose = require('mongoose');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const Logger = require('../logger');
const config = require('config');
const logger = Logger.createLogger("playerMongo");

mongoose.Promise = require('bluebird');
mongoose.connect( config.dbConfig.mongodb.connectionString, { useMongoClient: true });
// User Schema
var PlayerSchema = mongoose.Schema({
    loginname: {
        type: String,
        index: true
    },
    hash: {
        type: String,
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

var player = module.exports = mongoose.model('Player', PlayerSchema);

module.exports.createPlayer = async function (data) 
{
    let newPlayer = new player();
    newPlayer.name=data.name;
    newPlayer.score=data.score;
    newPlayer.username=data.username,
    newPlayer.profileImage='noimage.png';
    if (data.password) {
        newPlayer.hash = bcrypt.hashSync(data.password, 10);
    }
    if ( (await player.findOne({ name: data.name })) === null)
    {
        await newPlayer.save();
        return await player.findOne({ name: newPlayer.name });
    }   
    else
    {
        throw 'Player name "' + data.name + '" is already taken';
    }
    
};

// Fetch All Classes
module.exports.getPlayers = async function (limit) {
    let players = await player.find().limit(limit);
    return players;
};

// Fetch All Winners
module.exports.getWinners = async function (limit) 
{
    let players = await player.find({ score: { $gt: 0 } }).sort( { score: -1 } ).limit(limit);
    return players;
};

module.exports.updatePlayer = async function (data) 
{
    await player.findOneAndUpdate(
        { name: data.name },
        {
            $inc: { "score": data.score }
        },
        {save: true, upsert: true}
    )
};

module.exports.login = async function (username,password) 
{
    logger.debug("login in -->");
    return await player.findOne({ name: username }).then((response)=> {
        if (response && bcrypt.compareSync(password, response.hash)) 
        {
            logger.debug(response);
            const token = jwt.sign({ sub: response.id }, config.jwt.secret);
            return {
                ...response,
                token
            };
        }
        else return false;
      })
};
