import Immutable from 'immutable';
import {symbols as gameSymbols,play,newGame } from '../src/actions/bullscowsgame';
import {reducer} from "../src/reducers/bullscowsgame"

describe('Reducer tests', function() 
{
    const initialState = Immutable.fromJS(
        {
            secret: [0,0,0,0],
            results:[]
        }
    );
    it('new game', function() 
    {
        let action = newGame([1,2,3,4],"xxxx");
        expect(action.type).toEqual( gameSymbols.newGame);
        console.log(action.payload);
        let state = reducer (initialState,action); 
        console.log(state.get("secret"));
        expect(state.get("secret")).toEqual([1,2,3,4]);
        expect(state.get("results").size).toEqual(0);
    });

    it('play', function() 
    {
        let newGameAction = newGame([1,2,3,4],"xxxx");
        expect(newGameAction.type).toEqual( gameSymbols.newGame);
        console.log(newGameAction.payload);
        let newGameState = reducer (initialState,newGameAction); 
        let action = play([1,2,3,4]);
        expect(action.type).toEqual(gameSymbols.play);
        console.log("#########" + action.payload);
        let state = reducer (newGameState,action); 
        console.log(state.get("secret"));
        expect(state.get("secret")).toEqual([1,2,3,4]);
        expect(state.get("results").size).toEqual(1);
        expect(state.get("results").get(0).get("exist")).toEqual(0);
        expect(state.get("results").get(0).get("matches")).toEqual(4);
        let actionX = play([4,2,3,9]);
        expect(action.type).toEqual(gameSymbols.play);
        let stateX = reducer (state,actionX); 
        expect(stateX.get("secret")).toEqual([1,2,3,4]);
        expect(stateX.get("results").size).toEqual(2);
        expect(stateX.get("results").get(1).get("exist")).toEqual(1);
        expect(stateX.get("results").get(1).get("matches")).toEqual(2);

    });


});
  