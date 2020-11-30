const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const Logger = require('../logger');
const config = require('config');
const  httpService = require('got');
const logger = Logger.createLogger("playerStitch");
const secret = config.dbConfig.stitch.secret;
const bullsandcowsURL=config.dbConfig.stitch.url;

if (process.env.HTTP_PROXY) 
{
    process.env["GLOBAL_AGENT_HTTP_PROXY"]="http://" + process.env.HTTPS_PROXY;
    require('global-agent/bootstrap');
}

module.exports = new Object();
module.exports.getPlayers = async function (limit) 
{
    let playerListURL = bullsandcowsURL + "/BullsAndCows_getPlayers"
    let url = playerListURL + "?secret=" + secret + "&limit=" + limit;
    logger.debug(url);
    return await httpService.get(url).then((response)=> {
         logger.debug(response.body);
         let players=JSON.parse(response.body);
         if (Array.isArray(players))
         {
            players=players.map(e=>{
                return {"_id":e._id.$oid,
                "name":e.name,
                "username":e.username,
                "score":parseInt(e.score.$numberDouble)
                }
            });
         }
         return players
    });
};
module.exports.createPlayer = async function (data) 
{
    let url=bullsandcowsURL + "/BullsAndCows_createPlayer?secret=" + secret;
    let newPlayer = {};
    newPlayer.name=data.name;
    newPlayer.score=data.score;
    newPlayer.username=data.username,
    newPlayer.profileImage='noimage.png';
    if (data.password) {
        newPlayer.hash = bcrypt.hashSync(data.password, 10);   
    }
    console.debug(data);
    let result=await httpService.post(url, 
    {
        json: newPlayer,
        responseType: 'json',
        resolveBodyOnly: true
    }).then((player)=> 
    {
        logger.debug(player);
        return {
            "_id":player._id.$oid,
            "name":player.name,
            "username":player.username,
            "score":parseInt(player.score.$numberDouble)
            };
    }).catch(e=>{
        if (e.response && e.response.body)
        {
            logger.error(e.response.body);
            throw e.response.body.error;
        }
        throw e;
    })
    return result;
};

module.exports.updatePlayer = async function (data) 
{
    logger.debug("updatePlayer in -->");
    logger.debug(data);
    let url=bullsandcowsURL + "/BullsAndCows_updatePlayer?secret=" + secret;
    return await httpService.post(url, 
        {
            json: data,
            responseType: 'json',
            resolveBodyOnly: true
        }).then(function (player) 
    {
        logger.debug(player);
        if (!player.username)
        {
            player.username=palyer.name;
        }
        logger.debug("updatePlayer out <--");
        return {
            "_id":player._id.$oid,
            "name":player.name,
            "username":player.username,
            "score":parseInt(player.score.$numberDouble)
            };
    }).catch(e=>{logger.error(e);
        throw e.error.error;
    })
};

module.exports.getWinners = async function (limit) 
{
    let playerListURL = bullsandcowsURL + "/BullsAndCows_getWinners";
    let url = playerListURL + "?secret=" + secret + "&limit=" + limit;
    logger.debug(url);
    return await httpService.get(url).then((response)=> {
         logger.debug(response);
         let players=JSON.parse(response.body);
         if (Array.isArray(players))
         {
            players=players.map(e=>{
                return {"_id":e._id.$oid,
                "name":e.name,
                "username":e.username,
                "score":parseInt(e.score.$numberDouble)
                }
            });
         }
         return players
    });
};

module.exports.login = async function (username,password) 
{
    logger.debug("login in -->");
    let playerListURL = bullsandcowsURL + "/BullsAndCows_login";
    let url = playerListURL + "?secret=" + secret + "&username=" + username;
    logger.debug(url);
    let player =  await httpService.get(url).then((response)=> {
         logger.debug(response.body);
         let responsePlayer=JSON.parse(response.body);
         if (responsePlayer)
         return  {
                "_id":responsePlayer._id.$oid,
                "name":responsePlayer.name,
                "username":responsePlayer.username,
                "hash":responsePlayer.hash,
                "score":parseInt(responsePlayer.score.$numberDouble)
                }
        });
    logger.debug(player);
    if (player && bcrypt.compareSync(password, player.hash)) 
    {
        const token = jwt.sign({ sub: player.id }, config.jwt.secret);
        return {
            ...player,
            token
        };
    }
};
