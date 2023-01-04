import React from 'react';
import '../../css/App.css';
import BullsAndCows from '../games/bullsandcows/components/home'
import { useLocation } from 'react-router-dom'

export default function Game(props) {
  let location = useLocation();
  const game = () => {
    if (location.pathname === '/games/bullsandcows') {
      return <BullsAndCows navigate={props.navigate} />
    }
    else {
      props.navigate("/");
    }
    return <></>;
  }

  return (
    <>
      <div className='home'>
        <div className='container-fluid m-5'>
          <div className='row text-center'>
            <h3 className="display-4 text-primary">{props.name}</h3>
          </div>
          <div className="row h-100 fs-6">
              {game()}
          </div>
        </div>
      </div>
    </>
  );

}
