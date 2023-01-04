import React from 'react';
import '../../css/App.css';
import BullsAndCows from '../games/bullsandcows/components/home'
import { useLocation } from 'react-router-dom'

export default function Game(props) {
  let  location = useLocation();
  const game = () =>  {
    if (location.pathname==='/games/bullsandcows')
    {
      return  <BullsAndCows navigate={props.navigate}/>
    }
    else{
      props.navigate("/");
    }
    return <></>;
  }
  return <>
    <div className='sign-up'>
        <div className="fs-6 row text-left w-100">
          <div className="col-sm-12 my-auto">
            {game()}
           </div> 
        </div>
    </div>
  </>
}
