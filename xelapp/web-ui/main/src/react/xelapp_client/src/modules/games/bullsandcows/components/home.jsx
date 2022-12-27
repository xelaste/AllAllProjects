/**
 * Use this file to define and implement the main menu home page.
 *
 * At minimum you should create a container called Home
 * for the menu home page. You may also define helper components.
 *
 * All components used for Home container should also
 * be defined and implemented in this file.
 */


import React from 'react';
import { connect } from 'react-redux';
import PropTypes from 'prop-types';
import { playerActions } from "../actions/player";
import * as gameActions from "../actions/bullscowsgame";
import { getFormValues, isPristine, isSubmitting, reset, submit } from 'redux-form';
import Game from './game';
import { generateSecretArray } from '../util/secretGenerator';


function mapStateToProps(state) {
  return {
    players: [...state.player.get('players')],
    currentPlayer: state.player.get('currentPlayer'),
    values: getFormValues('homeForm')(state),
    pristine: isPristine('homeForm')(state),
    submitting: isSubmitting('homeForm')(state),
    error: state.player.get('error'),
    gamingNow: state.game.get('gamingNow')
  }
}


class Home extends React.Component {
  static propTypes = {
    players: PropTypes.array,
    currentPlayer: PropTypes.string,
    dispatch: PropTypes.func,
    pristine: PropTypes.bool,
    submitting: PropTypes.bool,
    gamingNow: PropTypes.bool,
    error: PropTypes.string
  };

  playersList() 
  {
    return <div className="w-75" >
      <h4>List Of Players</h4>
      <div style={{"height":"90%"}}className="w-100 overflow-auto" >
        <ul className="list-group">
          {this.props.players.map((item, idx) => {
            return <li key={idx} className="list-group-item d-flex justify-content-between mx-0">
              <span className="d-flex justify-content-end">
                <input className="mt-2" id={'radio_player_' + idx} name="player" type="radio" 
                  onClick={() => this.updateCurrentPlayer(item.get("name"))} onChange={() => { }} 
                  checked={(item.get("name") === this.props.currentPlayer)} />
                <span className="px-1" >{item.get("name")}</span>
              </span>
              <span className="badge-primary badge-pill">{item.get("score")}</span></li>
          })}
        </ul>
      </div>
    </div>
  }
  updateCurrentPlayer(player) {
    const { dispatch } = this.props;
    dispatch(playerActions.updateCurrentPlayer(player));
  }
  componentDidMount() {
    const { dispatch } = this.props;
    dispatch(playerActions.getAll());
  }
  handleSubmit(e) 
  {
    console.log("enter handleSubmit");
    let playerName = this.props.values.playerName;
    this.props.dispatch(playerActions.register({ name: playerName, score: 0 }));
    console.log("exit handleSubmit");
  }
  render() {
    if (this.props.gamingNow) {
      return (<Game />);
    }
    else
      return (
        <div>
          {this.props.error && <div className="mt-10 px-2 col-sm-6 alert alert-danger">{this.props.error}</div>}
            <div className="h-50 px-0 ml-0 container">
              <div className="ml-1 row h-100  w-100">
                {this.playersList()}
              </div>
              <div className="ml-1 row">
                <button className="btn btn-primary btn-sm col-md-2 ml-1"
                  type="button" disabled={(this.props.pristine && !this.props.currentPlayer) || this.props.submiting}
                  onClick={() => { this.updateCurrentPlayer("");}}>
                  Clear Values
                </button>
                
                <button className="btn col-md-2 ml-3 btn-primary"
                  type="button" disabled={!this.props.currentPlayer}
                  onClick={() => this.props.dispatch(gameActions.newGame(generateSecretArray()))}>
                  Play
                </button>
                
                <button className="btn col-md-2 ml-3 btn-primary"
                  type="button"
                  onClick={() => this.props.dispatch(gameActions.newGame(generateSecretArray(), true))}>
                  Play Vs Computer
                </button>
              </div>
          </div>
        </div>
      )
  };

}
export default connect(mapStateToProps)(Home);

