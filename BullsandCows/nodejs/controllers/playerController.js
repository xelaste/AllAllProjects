var express = require('express');
const Logger = require('../logger');
const logger = Logger.createLogger("server");
var playerService = require('../models/player.js');
const router = express.Router();

router.get('/', function (req, res,next) 
{
    logger.debug(req.body);
    res.set({ 'content-type': 'application/json;charset=utf-8' })
    playerService.getPlayers(1000).then(players=> {
        logger.debug("Players: ");
        logger.debug(players)
        res.send(players)
    }).catch(err=>{
        logger.debug("**************************");
        logger.error(err);
        logger.debug("**************************");
        next(err);
    });
})

router.get('/winners', function (req, res,next) 
{
    logger.debug(req.body);
    res.set({ 'content-type': 'application/json;charset=utf-8' })
    playerService.getWinners(3).then(players=> {
        logger.debug("Players: ");
        logger.debug(players)
        res.send(players)
    }).catch(err=>{
        logger.debug("**************************");
        logger.error(err);
        logger.debug("**************************");
        next(err);
    });
})

router.post('/authenticate/:username', function (req, res,next) 
{
    res.set({ 'content-type': 'application/json;charset=utf-8' });
    playerService.login(req.body.username,req.body.password).then(player=>
        {
            logger.debug("**************************");
            logger.debug(player);
            logger.debug("**************************");
            (player) ? res.json(player) : res.status(400).json({ message: 'Username or password is incorrect' });    
        }
        ).catch(err=>{
            if(!(typeof err === 'string'))
            {
                logger.error(err.stack);
                res.status(500).json({ message: "Internal server error"});
            }
            else
            {
                logger.error(err);
                res.status(500).json({ message: err });
            }
    });
});

router.post('/register', function (req, res,next) 
{
    res.set({ 'content-type': 'application/json;charset=utf-8' });
    var newPlayer = {
        name: req.body.name,
        score: 0,
        email: "",
        username: req.body.name,
        password:req.body.password,
        hash: '',
        profileImage: 'noimage.png'
    };
    playerService.createPlayer(newPlayer).then(player=>{
        logger.debug("**************************");
        logger.debug(player);
        logger.debug("**************************");
        res.json(player)}).catch(err=>{
        logger.debug("**************************");
        logger.error(err);
        logger.debug("**************************");
        res.status(500).json({ message: err });
    });
});
        
router.put('/', function (req, res,next) 
{
    logger.debug(req.body);
    res.set({ 'content-type': 'application/json;charset=utf-8' });
    let updatedPlayer = {
        name: req.body.name,
        score: req.body.score,
        email: "",
        username: req.body.name,
        password: '',
        profileImage: 'noimage.png'
    };
    playerService.updatePlayer(updatedPlayer).then(player=>{
        logger.debug("**************************");
        logger.debug(player);
        logger.debug("**************************");
        res.json(player)}).catch(err=>{
        logger.debug("**************************");
        logger.error(err);
        logger.debug("**************************");
        next(err)});
})

module.exports = router;