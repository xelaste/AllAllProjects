var assert = require('assert').strict;
const Logger=require("../logger");
const logger=Logger.createLogger("playerStitch.test");
const playersDAO=require ("../models/playerStitch");

describe('playerStitch', function() {
  describe('#getPlayers()', function() {
    it('should return players list', async function() {
        let players = await playersDAO.getPlayers(10);
        logger.debug("returned " + players.length + " players");
        assert.notStrictEqual(players,null);
        assert(players.length>0);
    });
  });
    describe('#createPlayerStitch()',  () => {
        it('should return new player', async function() {  
            let name=Math.random().toString(36).substring(2, 15)
            let newPlayer= await playersDAO.createPlayer({name: name , username:name , score: 0,profileImage:'noimage.png'});
            logger.debug(newPlayer);
            assert.equal(newPlayer.username,name);
            assert(newPlayer._id!==null);
        });
    })
});