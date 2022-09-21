import Immutable from 'immutable';
import { symbols as gameSymbols } from '../actions/bullscowsgame';
import AutoPlay from '../auto/autoplay'
import {playerConstants} from "../../../../constants/playerConstants";

const autoPlay = new AutoPlay();
const initialState = Immutable.fromJS(
    {
        gamingNow: false,
        heap: autoPlay.getInitialSet(),
        secret: [0, 0, 0, 0],
        vsComputer: false,
        results: []
    }
);

function newGame(state = initialState, secret, vsComputer) {
    return initialState.set("gamingNow", true).set("secret", secret).set("vsComputer", vsComputer).set();
}


function skip(state) {
    let results = state.get("results");
    let vsComputer = state.get("vsComputer");
    let heap=[...state.get("heap")];
    if (vsComputer) 
    {
        let num = [...heap[Math.floor(Math.random() * heap.length)]];
        let secret = [...state.get("secret")]
        let filter = autoPlay.calculate(secret, num)
        heap = autoPlay.prune(heap, filter, num);
        let result = Immutable.fromJS(
            {
                guess: num,
                exist: filter.exist,
                matches: filter.matches
            }

        )
        results = results.push(result);
        
    }
    else {
        let result = Immutable.fromJS(
            {
                guess: 'skip',
                exist: "-",
                matches: "-"
            }

        )
        results = results.push(result);
    }
    return state.set("heap",heap).set("results", results);
}


function play(state, guess) {
    let secret = [...state.get("secret")]
    let filter = autoPlay.calculate(secret, guess)
    let results = state.get("results");
    let result = Immutable.fromJS(
        {
            guess: guess,
            exist: filter.exist,
            matches: filter.matches
        }
    )
    results = results.push(result);
    return state.set("results", results);
}

export function reducer(state = initialState, action) {
    switch (action.type) {
        case playerConstants.LOGIN_REQUEST:
        case playerConstants.LOGOUT:
        case gameSymbols.stop:
            return state.set("gamingNow", false);
        case gameSymbols.play:
            return play(state, action.payload);
        case gameSymbols.newGame:
            return newGame(state, action.payload.secret, action.payload.vsSomputer);
        case gameSymbols.skip:
            return skip(state);
        default:
            return state;
    }
}
