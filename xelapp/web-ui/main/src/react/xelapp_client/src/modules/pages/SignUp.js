import React from 'react';
import '../../css/App.css';
import { LoginPage } from '../login/components/login_page';
export default function SignUp() {
  return <>
    <div className='sign-up'>
        <div className="fs-6 row text-left">
          <div class="col-sm-12 my-auto">
            <LoginPage />
           </div> 
        </div>
    </div>
  </>

}
