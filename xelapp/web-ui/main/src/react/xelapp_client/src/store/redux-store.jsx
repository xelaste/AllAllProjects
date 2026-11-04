import { createStore, combineReducers ,applyMiddleware ,compose } from 'redux';
import {reducer as playerReducer} from '../modules/login/reducers/player';
import {reducer as bullscowsgameReducer} from '../modules/games/bullsandcows/reducers/bullscowsgame';
import {authentication} from "../modules/login/reducers/authentication.reducer";
import {registration} from "../modules/login/reducers/registration.reducer";
import { thunk } from 'redux-thunk'; // Fixed named import
import { createLogger } from 'redux-logger';

const loggerMiddleware = createLogger(
  {
    collapsed:true,
  } 
);


const reducer = combineReducers({
  player: playerReducer,
  game: bullscowsgameReducer,
  authentication:authentication,
  registration:registration
});

const store = createStore(
  reducer, /* preloadedState, */
  compose (
    applyMiddleware( thunk, loggerMiddleware),
    (window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__()) || compose
  )
);
window.store = store;
export default store;

