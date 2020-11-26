const Logger=require("../logger");
const logger=Logger.createLogger("playerStitch.test");
const playersDAO=require ("../models/playerStitch");
test('retrieve Players Stitch', async () => {
    let players = await playersDAO.getPlayers(10);
   logger.debug(players);
  });

test('create Player Stitch', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  expect.assertions(1);
  return playersDAO.createPlayer({name: name , username:name , score: 0,profileImage:'noimage.png'})
   .then((player)=>expect(player.username).toBe(name)).catch(e=>{
                                                  logger.error(e);                                              
                                                  expect(e).not.toBeNull()
                                                 }
                                            );
});

test('update Player Stitch', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  let player = await playersDAO.createPlayer({name: name , username:name ,password:name, score: 0,profileImage:'noimage.png'});
  logger.debug(player);
  player.score=1;
  expect.assertions(2);
  return playersDAO.updatePlayer(player).then(player=>{expect(player.username).toBe(name);expect(player.score).toBe(1)});
});


test('login', async () => {
  let name=Math.random().toString(36).substring(2, 15)
  let player = await playersDAO.createPlayer({name: name , username:name,password:name , score: 0,profileImage:'noimage.png'});
  logger.debug(player);
  expect.assertions(1);
  return playersDAO.login(name,name).then((player)=>expect(player.username).toBe(name)).catch(e=>{
    logger.error(e);                                              
    expect(e).not.toBeNull()
   }
  );
  
});