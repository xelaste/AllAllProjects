import React from 'react';
import { Route, Redirect } from 'react-router-dom';

class PrivateRoute extends React.Component {
    render() {
      const { component: Component, ...rest } = this.props
      return (
        <Route {...rest}  render={(props) => {
            return sessionStorage.getItem('player') ? (
                <Component {...props} />
              ):(
                <Redirect to={{
                  pathname: '/login',
                  state: { from: this.props.location }
                }} />
              )
          }
        } >
        </Route>
      )
    }
  }
export default PrivateRoute