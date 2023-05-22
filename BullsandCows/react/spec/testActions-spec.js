import {playerActions} from "../src/actions/player" 
import { playerConstants } from "../src//constants/playerConstants";
describe('Actions tests', function() 
{
    it('it should be xxx player added', function() 
    {
        let actions = [];
        let action = playerActions.register({name:"xxx",score:0});
        action((result)=>{actions.push(result)});
        expect(actions[0].payload.name).toEqual("xxx");
        expect(actions[0].type).toEqual(playerConstants.REGISTER_REQUEST);
    });

    it('it should be yyy player scored', function() 
    {
        let actions=[];
        let actionF = playerActions.updatePlayerScore("yyy",10)
        actionF((result)=>{actions.push(result);});
        console.log(actions);
        expect(actions[0].payload.name).toEqual("yyy");
        expect(actions[0].type).toEqual(playerConstants.UPDATE_REQUEST);
    });
  });
  