const Logger=require("../logger");
const logger=Logger.createLogger("playerStitch.test");
const playersDAO=require ("../models/playerStitch");
test('retrieve Players Stitch', async () => {
    let players = await playersDAO.getPlayers(10);
   logger.debug(players);
  });

test('create Player Stitch', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  let player = await playersDAO.createPlayer({name: name , username:name , score: 0,profileImage:'noimage.png'});
  logger.debug(player);
  expect(player.username).toBe(name)
  expect.assertions(2);
  return playersDAO.createPlayer({name: name , username:name , score: 0,profileImage:'noimage.png'})
   .then(()=>expect(true).toBe(false)).catch(e=>{
                                                  logger.error(e);                                              
                                                  expect(e).not.toBeNull()
                                                 }
                                            );
});

test('update Player Stitch', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  let player = await playersDAO.createPlayer({name: name , username:name ,password:name, score: 0,profileImage:'noimage.png'});
  logger.debug(player);
  expect(player.username).toBe(name)
  player.score=1;
  player = await playersDAO.updatePlayer(player);
  logger.debug(player);
});


test('login', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  let player = await playersDAO.createPlayer({name: name , username:name,password:name , score: 0,profileImage:'noimage.png'});
  logger.debug(player);
  expect(player.username).toBe(name)
  player = await playersDAO.login(name,name);
  logger.debug(player);
});