/**
 * Use this file to define and implement game components
 *
 * At minimum you should create a container called Game
 * for the gameplay page, and you'll probably want to define
 * some helper components for Game to use.
 *
 * All components used for Game container should also
 * be defined and implemented in this file.
 */
import React from 'react';
import * as gameActions from "../actions/bullscowsgame";
import { connect } from 'react-redux';
import { getFormValues, isPristine, isSubmitting, reset, submit } from 'redux-form';
import PropTypes from 'prop-types';
import GameForm from './game_form';
import _ from 'underscore';
import { generateSecretArray } from '../util/secretGenerator';
import { playerActions } from './../actions/player';

function mapStateToProps(state) {
  return {
    players: [...state.player.get('players')],
    currentPlayer: state.player.get('currentPlayer'),
    secret: [...state.game.get('secret')],
    gamingNow: state.game.get('gamingNow'),
    results: [...state.game.get("results")],
    vsComputer: state.game.get("vsComputer"),
    heap: state.game.get("heap"),
    values: getFormValues('gameForm')(state)
  }
}
function withTimer(Component) {
  return class Timer extends React.Component {
    constructor(props) {
      super(props);
      this.state = { ticks: 0, start: (new Date()).getTime(),period:props.period };
      this.reset = this.reset.bind(this);
      if (props.subscribe)
      {
        props.subscribe (this.reset);
      }
    }

    reset ()
    {
      this.state = { ticks: 0, start: (new Date()).getTime(),period:this.state.period };
    }
    componentDidMount() {
      this.reset();
      this.timer = setInterval(this.tick, 1000);
    }

    componentWillUnmount() {
      this.reset();
      clearInterval(this.timer);
    }

    tick = () => {
        let ticks = Math.floor(((new Date()).getTime() - this.state.start) / 1000)
        if (ticks != this.state.ticks) {
          this.setState(state => ({ ticks: ticks }));
          if (this.state.ticks > 0 && this.state.ticks % this.state.period == 0) {
            store.dispatch(gameActions.skip());
          }
      }
    };
    render() {
      return (
        <Component {...this.props} ticks={this.state.ticks} />
      );
    }
  }
}
class Clock extends React.Component {
  render() {
    let percent = Math.floor(100 * ((this.props.ticks % this.props.period)/this.props.period));
    let style={};
    style.width=percent + "%";
    return <div className="progress" style={{height: "1.5em"}}>
            <div className="progress-bar" style={style}><strong><span className="pl-3">Elapsed Time:</span>{this.props.period - this.props.ticks % this.props.period}</strong></div>
          </div>
  
  }
}

Clock = withTimer(Clock);

class Game extends React.Component {
  static propTypes = {
    players: PropTypes.array,
    secret: PropTypes.array,
    currentPlayer: PropTypes.string,
    dispatch: PropTypes.func,
    pristine: PropTypes.bool,
    submitting: PropTypes.bool,
    gamingNow: PropTypes.bool,
    error: PropTypes.string,
    results: PropTypes.array,
    vsComputer: PropTypes.bool,
    heap: PropTypes.array
  };
  constructor(props) 
  {
    super(props);
    this.subscribeToTimer = this.subscribeToTimer.bind(this);
  }

  resetTimer=null;

  subscribeToTimer( handler )
  {
    this.resetTimer = handler;
  }  
  isWin() {
    return this.props.results.filter(item => parseInt(item.get("matches")) === 4).length > 0
  }
  isLost() {
    return this.props.results.length >= 10 && !this.isWin();
  }
  vsComputer() {
    return this.props.vsComputer;
  }

  fillGuesses() {
    let guesses = [];
    for (let i = 0; i < this.props.results.length; i++) {
      guesses.push({ guess: this.props.results[i].get("guess"), exists: this.props.results[i].get("exist"), match: this.props.results[i].get("matches") });
    }
    for (let i = guesses.length - 1; i < 10; i++) {
      guesses.push({ guess: "", exists: "", match: "" })
    }
    return guesses.slice(0, 10);
  }
  restart() {
    if (this.resetTimer)
    {
        this.resetTimer();
    } 
    this.props.dispatch(gameActions.newGame(generateSecretArray(),this.vsComputer()));
    this.props.dispatch(reset('gameForm'));
  }

  render() {
    return (<div className="panel h-100 p-0 m-0">
    < div className="row m-1">
        {!this.vsComputer() && <h4>Player: {this.props.currentPlayer}</h4>}
     </div> 
      {this.isWin() && <div className="alert alert-success w-25">Winner</div>}
      {this.isLost() && <div className="alert alert-danger w-25">Game is lost</div>}
      <div className="ml-2 row w-50">
      <div style={{backgroundColor: 'yellow'}} className="col-sm-6">
        <table   className="table table-sm table-striped" >
            <thead>
              <tr>
                <th style={{width:'3vw'}}>#</th>
                <th style={{width:'5vw'}}>Guess</th>
                <th style={{width:'5vw'}}>Cows</th>
                <th style={{width:'5vw'}}>Bulls</th>
              </tr>
            </thead>
        </table>
        <div className="overflow-auto" style={{height:"40vh"}}>
          <table className="table table-striped table-sm" >
            <tbody>
              {this.fillGuesses().map((item, idx) =>
                <tr key={idx} className="px-0">
                  <td style={{width:'2vw',textAlign:'center'}}>{idx + 1}</td>
                  <td style={{width:'5vw',textAlign:'center'}} >{item.guess}</td>
                  <td style={{width:'5vw',textAlign:'center'}}>{item.exists}</td>
                  <td style={{width:'5vw',textAlign:'center'}}>{item.match}</td>
                </tr>
              )}
            </tbody>
          </table>
        </div>
        </div>
        <div className="col-sm-4 ml-2" style={{ backgroundColor: "pink" ,height:"50vh"}}>
          <GameForm isLost={this.isLost()} isWin={this.isWin()} vsComputer={this.vsComputer()} heap={this.props.heap} secret={this.props.secret} playerName={this.props.currentPlayer} />
        </div>
      </div>
      {!this.isWin() && !this.isLost() &&
        <div className="mt-3 col-sm-3">
          <Clock subscribe={this.subscribeToTimer} ticks={0} period={this.vsComputer()?2:30}/>
        </div>
      }
      <div className="panel fixed-bottom">
        <button className="btn btn-primary btn-sm col-md-1 ml-1"
          type="button" disabled={this.vsComputer() || !this.props.values || this.props.values && !(parseInt(this.props.values.d1) && parseInt(this.props.values.d2) && parseInt(this.props.values.d3) && parseInt(this.props.values.d4))}
          onClick={() => {
            let guess = [parseInt(this.props.values.d1), parseInt(this.props.values.d2), parseInt(this.props.values.d3), parseInt(this.props.values.d4)];
            if (_.isEqual(guess, this.props.secret)) {
              this.props.dispatch(playerActions.updatePlayerScore(this.props.currentPlayer, 10 - this.props.results.length));
            }
            this.props.dispatch(gameActions.play([parseInt(this.props.values.d1), parseInt(this.props.values.d2), parseInt(this.props.values.d3), parseInt(this.props.values.d4)]))
            this.props.values.d1="";
            this.props.values.d2="";
            this.props.values.d3="";
            this.props.values.d4="";
            this.resetTimer ();
          }
          }>
          Check
      </button>
        <button className="btn btn-primary btn-sm col-md-1 ml-1"
          type="button"
          onClick={this.restart.bind(this)}>
          New
      </button>
        <button className="btn btn-primary btn-sm col-md-1 ml-1"
          type="button"
          onClick={() => this.props.dispatch(gameActions.stopGame(this.props.currentPlayer))}>
          Back
      </button>
      </div>
    </div >);
  }
};

export default connect(mapStateToProps)(Game);
