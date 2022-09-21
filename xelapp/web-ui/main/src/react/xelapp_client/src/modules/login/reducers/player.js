import Immutable from 'immutable';
import {playerConstants} from "../../../constants/playerConstants";


const EMPTY_LIST = Immutable.fromJS([]);
const initialState = Immutable.fromJS(
    {
        players: EMPTY_LIST,
        winners: EMPTY_LIST,
        currentPlayer: '',
        error: ''
    }
);

const playerReducer = (state = initialState, action) => {
    return reducer(state, action);
}
export default playerReducer;

function addPlayer(state) 
{
    return state;
}

function updatePlayerScore(state, playerName, score) {
    let player = state.get('players').find((player) => player.get('name') === playerName);
    if (player) {
        player = player.set('score', player.get('score') + score);
        let players = state.get('players');
        players = players.filter((o) => o.get('name') !== playerName);
        return state.set('players', players.push(player));
    }
    return state;
}

function isNewPlayer(state, playerName) {
    let player = state.get('players').filter((o) => o.get('name') === playerName);
    return (player.size === 0);
}
function updateCurrentPlayer(state, playerName) {
    if (playerName) {
        if (isNewPlayer(state, playerName)) {
            state = addPlayer(state, playerName);
        }
    }
    return state.set('currentPlayer', playerName)
}

function fetchPlayers(state, data) {
    state = state.update('players',()=>EMPTY_LIST);
    state = state.update('players', (val) => val.push(...data.map(item => Immutable.Map(item))));
    return state;
}

function fetchWinners(state, data) {
    state = state.update('winners',()=>EMPTY_LIST);
    state = state.update('winners', (val) => val.push(...data.map(item => Immutable.Map(item))));
    return state;
}

export function reducer(state = initialState, action) {
    switch (action.type) {
        case "@@redux-form/CHANGE":
        case "@@redux-form/RESET":
        case playerConstants.LOGIN_REQUEST:
        case playerConstants.LOGOUT:
            return state.set("error","");  
        case playerConstants.GETALL_SUCCESS:
            return fetchPlayers(state, action.payload);
        case playerConstants.GETWINNERS_SUCCESS:    
            return fetchWinners(state, action.payload);
        case playerConstants.REGISTER_FAILURE:
             return state.set("error",action.payload);  
        case playerConstants.REGISTER_SUCCESS:
            return addPlayer(state, action.payload);
        case playerConstants.UPDATE_SUCCESS:
            return updatePlayerScore(state, action.payload.name, action.payload.score);
        case playerConstants.SET_CURRENT_PLAYER:
             return updateCurrentPlayer(state, action.payload);
        case playerConstants.LOGIN_FAILURE:
             let error = action.payload.error?action.payload.error:action.payload;   
             return state.set("error",error);  
        default:
            return state;
    }
}
