import React, { useState, useEffect, useCallback } from 'react';
import logger from 'redux-logger';

let logoutTimer;

const AuthContext = React.createContext({
  token: '',
  authHeader: {},
  isLoggedIn: false,
  login: (token) => {},
  logout: () => {},
});

const calculateRemainingTime = (expirationTime) => {
  const currentTime = new Date().getTime();
  const adjExpirationTime = new Date(expirationTime).getTime();

  const remainingDuration = adjExpirationTime - currentTime;

  return remainingDuration;
};

const retrieveStoredToken = () => {
  let user = JSON.parse(sessionStorage.getItem('player'));
  /*
  if (user && user.token) {
    return { 'Authorization': 'Bearer ' + user.token };
} else {
    return {};
}
*/
  const storedToken = user && user.token ? user.token : '';
  const storedAuthHeader = user && user.token ? {'Authorization': 'Bearer ' + user.token} : {}; 
  const storedExpirationDate = localStorage.getItem('expirationTime');
  const remainingTime = calculateRemainingTime(storedExpirationDate);

  if (remainingTime <= 3600) {
    localStorage.removeItem('player');
    localStorage.removeItem('expirationTime');
    return null;
  }
  logger.log (storedToken,remainingTime);
  return {
    token: storedToken,
    authHeader:storedAuthHeader,
    duration: remainingTime
  };
};

export const AuthContextProvider = (props) => {
  const tokenData = retrieveStoredToken();
  
  let initialToken;
  if (tokenData) {
    initialToken = tokenData.token;
  }

  const [token, setToken] = useState(initialToken);

  const userIsLoggedIn = !!token;

  const logoutHandler = useCallback(() => {
    setToken(null);
    localStorage.removeItem('token');
    localStorage.removeItem('expirationTime');

    if (logoutTimer) {
      clearTimeout(logoutTimer);
    }
  }, []);

  const loginHandler = (token, expirationTime) => {
    setToken(token);
    localStorage.setItem('token', token);
    localStorage.setItem('expirationTime', expirationTime);

    const remainingTime = calculateRemainingTime(expirationTime);

    logoutTimer = setTimeout(logoutHandler, remainingTime);
  };

  useEffect(() => {
    if (tokenData) {
      console.log(tokenData.duration);
      logoutTimer = setTimeout(logoutHandler, tokenData.duration);
    }
  }, [tokenData, logoutHandler]);

  const contextValue = {
    token: token,
    isLoggedIn: userIsLoggedIn,
    login: loginHandler,
    logout: logoutHandler,
  };

  return (
    <AuthContext.Provider value={contextValue}>
      {props.children}
    </AuthContext.Provider>
  );
};

export default AuthContext;
