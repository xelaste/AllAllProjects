import React from 'react';
import { Navigate, Outlet } from 'react-router-dom';
import AuthContext from '../store/auth-context';
class PrivateRoute extends React.Component {
  static contextType = AuthContext
  render() {
    const authCtx = this.context
    return authCtx.isLoggedIn() ? (
      <Outlet />
    ) : (
      <Navigate to="/login" />
    )
  }
}
export default PrivateRoute