import React from 'react';
import {NavLink as Link, Route,Switch} from 'react-router-dom';
import Home from './components/home';
import Highscore from './components/highscore';
export default class App extends React.Component {
  render() {
    const { match } = this.props;
    console.log("###################");
    console.log(match.path);
    console.log(match.url);
    console.log("###################");
    return (
      <div className="px-2">
        <div><h1>Bulls and Cows</h1></div>
        <div>
          <nav className="mb-1 nav nav-pills">
            <Link to="/" exact={true} className="nav-link" activeClassName="active">Home</Link>
            <Link to="/highscore" className="nav-link" activeClassName="active">Highscore</Link>
            <Link to="/login" className="nav-link" activeClassName="active">Logout</Link>
          </nav>
          <Switch>
            <Route exact path="/" component={Home} />
            <Route path="/highscore" component={Highscore}/>
          </Switch>
        </div>
      </div>
    );
  }
};
