const players = require ("../models/playerLoki");
const logger=require("../logger").createLogger("PlayerLokyTest");;
var collection = null;
beforeEach(() => {
    collection = players.init();
    collection.clear();
  });
test('add new player aa', () => {
    player = players.createPlayer({name: "aa" ,    score: 0})
    var tyrfing = collection.findOne({'name': 'aa'});
    expect(tyrfing).not.toBeNull();
    expect(tyrfing.score).toBe(0);
    logger.debug(tyrfing);
  });
  test('find all the players', () => {
    players.createPlayer({name: "bb" ,    score: 0});
    players.createPlayer({name: "cc" ,    score: 0});
    var tyrfing = collection.find();
    logger.debug(tyrfing);
    expect(tyrfing.length).toBeGreaterThan(0);
  });

  test('find all the winners', () => {
    players.createPlayer({name: "bb" ,    score: 0});
    players.createPlayer({name: "cc" ,    score: 1});
    players.createPlayer({name: "dd" ,    score: 10});
    players.createPlayer({name: "xx" ,    score: 100});
    var tyrfing = players.getWinners(3)
    expect.assertions(2);
    return tyrfing.then(data=>{
      logger.debug(data);
      expect(data.length).toBeGreaterThan(0);
      expect(data[0].name).toBe("xx")
    });
  });

  test('Update the player', async () => {
    let tyrfing = {name: "bb" ,   score: 0};
    players.createPlayer(tyrfing);
    logger.debug(tyrfing.score);
    let score = tyrfing.score
    score++;
    await players.updatePlayer({name: "bb" ,   score: score});
    tyrfing = collection.findOne({'name': 'bb'});
    logger.debug("@=================================");
    logger.debug(tyrfing);
    logger.debug("==================================");
    expect(tyrfing.score).toEqual(score);
    logger.debug(tyrfing);
  });
