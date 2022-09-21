import { playerConstants } from '../../../constants/playerConstants';

const initialState =  {
      registering:false,
      done: false,
      fail:false,
  }

export function registration(state = initialState, action) 
{
  switch (action.type) {
    case playerConstants.LOGOUT:
      return initialState;  
    case playerConstants.REGISTER_REQUEST:
      return { registering: true ,done:false,failed:false};
    case playerConstants.REGISTER_SUCCESS:
      return { registering: false ,done:true,failed:false};
    case playerConstants.REGISTER_FAILURE:
      return { registering: false ,done:false,failed:true};
    default:
      return state
  }
}