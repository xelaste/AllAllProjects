export const symbols = {
  newGame: '@@bullscowsgame/newGame',
  play: '@@bullscowsgame/play',
  skip: '@@bullscowsgame/skip',
  win: '@@bullscowsgame/win',
  stop: '@@bullscowsgame/stop',
  lose: '@@bullscowsgame/lose'
};

export function skip() 
{
  return {
    type: symbols.skip,
  };
}

export function play(guess) {
  return {
    type: symbols.play,
    payload: guess
  };
}

export function newGame(secret,vsSomputer=false) 
{
  return {
    type: symbols.newGame,
    payload: { secret: secret,vsSomputer:vsSomputer },
  };
}

export function winGame(player,score) 
{
  return {
    type: symbols.win,
    payload: { player: player,score:score },
  };
}

export function loseGame(player) {
  return {
    type: symbols.lose,
    payload: { player: player },
  };
}
export function stopGame(player) {
  return {
    type: symbols.stop,
    payload: { player: player },
  };
}


