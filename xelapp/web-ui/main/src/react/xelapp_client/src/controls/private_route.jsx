import React from 'react';
import {Navigate ,Outlet} from 'react-router-dom';

class PrivateRoute extends React.Component {
    render() {
      const { component: Component, ...rest } = this.props
      return  sessionStorage.getItem('player') ? (
                <Outlet/>
              ):(
                <Navigate to="/login"/>
              )
        } 
    }
export default PrivateRoute