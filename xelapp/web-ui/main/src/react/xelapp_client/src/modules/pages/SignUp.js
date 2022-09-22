import React from 'react';
import '../../css/App.css';
import { LoginPage } from '../login/components/login_page';
import { RegisterPage } from '../login/components/register_page';
import { useLocation } from 'react-router-dom'
export default function SignUp() {
  let  location = useLocation();
  console.log("&&&&&&&&" + location )
  console.log( location )
  return <>
    <div className='sign-up'>
        <div className="fs-6 row text-left w-100">
          <div class="col-sm-12 my-auto">
              {(location.pathname==='/register')? <RegisterPage/> :<LoginPage />}
           </div> 
        </div>
    </div>
  </>

}
