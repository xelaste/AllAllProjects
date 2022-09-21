import { useContext } from 'react';
import AuthContext from '../../store/auth-context'

const AuthHeader = ()=>{
    const authCtx = useContext(AuthContext);
    return authCtx.authHeader;
}
export const playerService = 
{
    login,
    logout,
    register,
    getAll,
    getWinners,
    update,
    delete: _delete
};
function login(username,password) 
{
    const player={username:username,password:password}
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(player)
    };
    return fetch(`${process.env.REACT_APP_API_URL}/players/authenticate/` + username , requestOptions)
    .then(handleResponse)
    .then(player => {
            sessionStorage.setItem('player', JSON.stringify(player));
            return player;
        }
    );
}
function logout() 
{
    sessionStorage.removeItem('player');
}
    

function register(player) {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json'},
        body: JSON.stringify(player)

    };

    return fetch(`${process.env.REACT_APP_API_URL}/players/register`, requestOptions).then(handleResponse);
}


function update(player) {
    const requestOptions = {
        method: 'PUT',
        headers: { ...AuthHeader(), 'Content-Type': 'application/json' },
        body: JSON.stringify(player)
    };
    return fetch(`${process.env.REACT_APP_API_URL}/players`, requestOptions).then(handleResponse);
}


function getAll() 
{
    const requestOptions = {
        method: 'GET',
        headers: { ...AuthHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${process.env.REACT_APP_API_URL}/players`, requestOptions).then(handleResponse);
}

function getWinners() 
{
    const requestOptions = {
        method: 'GET',
        headers: { ...AuthHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${process.env.REACT_APP_API_URL}/players/winners`, requestOptions).then(handleResponse);
}
// prefixed function name with underscore because delete is a reserved word in javascript
function _delete(name) 
{
    const requestOptions = {
        method: 'DELETE',
        headers: { ...AuthHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${process.env.REACT_APP_API_URL}/players/${name}`, requestOptions).then(handleResponse);
}
function handleResponse(response) {
    return response.text().then(text => {
        const data = text && JSON.parse(text);
        if (!response.ok) {
            if (response.status === 401) {
                // auto logout if 401 response returned from api
                logout();
                window.location.reload(true);
            }
            const error = (data && data.message) || response.statusText;
            return Promise.reject(error);
        }
        return data;
    });
}
