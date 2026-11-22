export const symbols = {
  newGame: '@@bullscowsgame/newGame',
  play: '@@bullscowsgame/play',
  skip: '@@bullscowsgame/skip',
  win: '@@bullscowsgame/win',
  stop: '@@bullscowsgame/stop',
  lose: '@@bullscowsgame/lose',
  guess_changed: '@@bullscowsgame/guess_changed'
};

export function skip() 
{
  return {
    type: symbols.skip,
  };
}

export function guessChanged(guess, valid) {
  return {
    type: symbols.guess_changed,
    payload: {digits: guess, valid: valid}
  }
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


