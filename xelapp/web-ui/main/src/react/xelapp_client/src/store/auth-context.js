import React, { useState, useEffect, useCallback } from 'react';

let logoutTimer;


const calculateRemainingTime = (expirationTime) => {
  const currentTime = new Date().getTime();
  const adjExpirationTime = new Date(expirationTime).getTime();

  const remainingDuration = adjExpirationTime - currentTime;

  return remainingDuration;
};

export const retrieveStoredToken = () => {
  let strUser = sessionStorage.getItem('player');
  let user = strUser ? JSON.parse(strUser) : {};
  const storedToken = user && user.token ? user.token : '';
  const storedAuthHeader = ()=> {return user && user.token ? {'Authorization': 'Bearer ' + user.token} : {};};
  const storedExpirationDate = sessionStorage.getItem('expirationTime');
  const remainingTime = calculateRemainingTime(storedExpirationDate);

  if (remainingTime <= 3600) {
    sessionStorage.removeItem('player');
    sessionStorage.removeItem('expirationTime');
    return null;
  }
  return {
    token: storedToken,
    authHeader:storedAuthHeader,
    duration: remainingTime,
    isLoggedIn: () => {return !!storedToken}
  };
};

let storedValues = retrieveStoredToken();
const AuthContext = React.createContext(
  {
    ...storedValues,
    login: (token)=>{},
    logout: ()=>{}
  }
);

export const AuthContextProvider = (props) => {
  const tokenData = retrieveStoredToken();
  
  let initialToken;
  if (tokenData) {
    initialToken = tokenData.token;
  }

  const [token, setToken] = useState(initialToken);

  const logoutHandler = useCallback(() => {
    setToken(null);
    document.cookie = "authorization=; expires=Thu, 01 Jan 1964 00:00:00 UTC; path=/;"
    sessionStorage.removeItem('token');
    sessionStorage.removeItem('expirationTime');

    if (logoutTimer) {
      clearTimeout(logoutTimer);
    }
  }, []);

  const isLoggedIn  = () => {return !!token}
  const authHeader = () => {return retrieveStoredToken().authHeader}
  const loginHandler = (token, expirationTime) => {
    setToken(token);
    if (!expirationTime)
    {
      const today = new Date()
      let tomorrow =  new Date()
      tomorrow.setDate(today.getDate() + 1)
      expirationTime = tomorrow.toISOString()
    }
    sessionStorage.setItem('token', token);
    sessionStorage.setItem('expirationTime', expirationTime);
    sessionStorage.setItem('authHeader',retrieveStoredToken().authHeader);
    const remainingTime = calculateRemainingTime(expirationTime);
    document.cookie = "authorization=Bearer " + token;
    logoutTimer = setTimeout(logoutHandler, remainingTime);
  };

  useEffect(() => {
    if (tokenData) {
      logoutTimer = setTimeout(logoutHandler, tokenData.duration);
    }
  }, [tokenData, logoutHandler]);

  const contextValue = {
    token: token,
    authHeader: authHeader,
    isLoggedIn: isLoggedIn,
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
