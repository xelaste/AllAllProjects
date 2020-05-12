import { createStore, combineReducers ,applyMiddleware ,compose } from 'redux';
import { reducer as reduxFormReducer } from 'redux-form';
import {reducer as playerReducer} from './reducers/player';
import {reducer as bullscowsgameReducer} from './reducers/bullscowsgame';
import {authentication} from "./reducers/authentication.reducer";
import {registration} from "./reducers/registration.reducer";
import thunkMiddleware from 'redux-thunk';
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
  registration:registration,
  form: reduxFormReducer
});

const store = createStore(
  reducer, /* preloadedState, */
  compose (
    applyMiddleware( thunkMiddleware, loggerMiddleware),
    (window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__()) || compose
  )
);
window.store = store;
export default store;

