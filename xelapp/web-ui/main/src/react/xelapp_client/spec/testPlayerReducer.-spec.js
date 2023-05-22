import Immutable from 'immutable';
import { playerConstants } from "../src//constants/playerConstants";
import { reducer } from "../src/reducers/player"
const initialState = Immutable.fromJS(
    {
        players: [],
        currentPlayer: ''
    }
);
describe('Reducer tests', function () {
    it('add players', function () {
        let action = { type: playerConstants.REGISTER_SUCCESS, payload: "xxx" }
        let state = reducer(initialState, action);
        expect(state.get('players').size).toEqual(1);
        expect(state.get('players').get(0).get('name')).toEqual(action.payload);
        action = { type: playerConstants.REGISTER_SUCCESS, payload: "yyy" }
        state = reducer(state, action);
        expect(state.get('players').size).toEqual(2);
        expect(state.get('players').get(1).get('name')).toEqual(action.payload);
    });

    it('Update players score', function () {
        let action = { type: playerConstants.REGISTER_SUCCESS, payload: "xxx" }
        let state = reducer(initialState, action);
        expect(state.get('players').size).toEqual(1);
        expect(state.get('players').get(0).get('name')).toEqual(action.payload);
        action = { type: playerConstants.REGISTER_SUCCESS, payload: "yyy" }
        state = reducer(state, action);
        expect(state.get('players').size).toEqual(2);
        expect(state.get('players').get(1).get('name')).toEqual(action.payload);
        action = { type: playerConstants.UPDATE_SUCCESS, payload: { name: "yyy", score: 10 } };
        state = reducer(state, action);
        let player = state.get('players').find((player) => player.get('name') == "yyy");
        let score = player.get('score');
        expect(state.get('players').size).toEqual(2);
        expect(score).toEqual(10);
        state = reducer(state, action);
        player = state.get('players').find((player) => player.get('name') == "yyy");
        score = player.get('score');
        expect(score).toEqual(20);
        player = state.get('players').find((player) => player.get('name') == "xxx");
        score = player.get('score');
        expect(score).toEqual(0);
    });
}
);
