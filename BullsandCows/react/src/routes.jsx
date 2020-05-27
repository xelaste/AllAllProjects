import React from 'react';
import { BrowserRouter as Router, Route} from "react-router-dom";

import App from './app';
import { Provider } from 'react-redux';
import store from './store';
import PrivateRoute from './components/private_route';
import {LoginPage} from './components/login_page';
import {RegisterPage} from './components/register_page';



export default class Routes extends React.Component {
  render() {
    return (
      <Provider store={store}>
        <Router>
          <div className="h-100">
            <PrivateRoute exact path="/" component={App} />
            <PrivateRoute exact path="/highscore" component={App} />
            <Route path="/login" component={LoginPage} />
            <Route path="/register" component={RegisterPage} />
          </div>
        </Router>
      </Provider>
    );
};
}