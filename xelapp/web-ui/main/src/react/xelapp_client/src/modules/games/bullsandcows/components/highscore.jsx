/**
 * Use this file to define and implement hiscore components
 *
 * At minimum you should create a container called HiScore
 * for the hiscore page, and you'll probably want to define
 * some helper components for HiScore to use.
 *
 * All components used for HiScore container should also
 * be defined and implemented in this file.
 */

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
import { connect } from 'react-redux';
import PropTypes from 'prop-types';
import { playerActions } from "../actions/player";
function mapStateToProps(state) 
{
  return {
    winners: [...state.player.get('winners')],
    currentPlayer: state.player.get('currentPlayer'),
    error: state.player.get('error')
  }
}

// Cows Bulls Game
class Highscore extends React.Component {
  static propTypes = {
    players: PropTypes.array,
    winners: PropTypes.array,
    currentPlayer: PropTypes.string,
    dispatch: PropTypes.func,
    pristine: PropTypes.bool,
    submitting: PropTypes.bool,
    error: PropTypes.string
  };
  
  componentDidMount() {
    const { dispatch } = this.props;
    dispatch(playerActions.getWinners());
  }
  playersList() 
  {
    let sortedPlayers = this.props.winners;
    return <div className="panel panel-default h-100">
      <label><h4>Winners's List</h4></label>
      <div className="pl-2 h-100 w-50"  >
        <ul className="list-group">
          {sortedPlayers.map((item, idx) => (
            <li key={idx} className="list-group-item d-flex justify-content-between">
              <span className="d-flex justify-content-end">
                <span className="px-2" >{item.get("name")}</span>
              </span>
              <span className="badge-primary badge-pill">{item.get("score")}</span>
            </li>

          ))}
        </ul>
      </div>
    </div>
  }
  render() {
    return <div>
      {this.playersList()}
    </div>
  }
};

export default connect(mapStateToProps)(Highscore);



