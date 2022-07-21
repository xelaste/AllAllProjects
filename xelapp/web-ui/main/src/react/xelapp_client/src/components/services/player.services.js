import config from 'config';
import {authHeader} from '../util/auth-header';

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
    return fetch(`${config.apiUrl}/players/authenticate/` + username , requestOptions)
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

    return fetch(`${config.apiUrl}/players/register`, requestOptions).then(handleResponse);
}


function update(player) {
    const requestOptions = {
        method: 'PUT',
        headers: { ...authHeader(), 'Content-Type': 'application/json' },
        body: JSON.stringify(player)
    };
    return fetch(`${config.apiUrl}/players`, requestOptions).then(handleResponse);
}


function getAll() 
{
    const requestOptions = {
        method: 'GET',
        headers: { ...authHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${config.apiUrl}/players`, requestOptions).then(handleResponse);
}

function getWinners() 
{
    const requestOptions = {
        method: 'GET',
        headers: { ...authHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${config.apiUrl}/players/winners`, requestOptions).then(handleResponse);
}
// prefixed function name with underscore because delete is a reserved word in javascript
function _delete(name) 
{
    const requestOptions = {
        method: 'DELETE',
        headers: { ...authHeader(), 'Content-Type': 'application/json' },
    };
    return fetch(`${config.apiUrl}/players/${name}`, requestOptions).then(handleResponse);
}
function handleResponse(response) {
    return response.text().then(text => {
        const data = text && JSON.parse(text);
        if (!response.ok) {
            if (response.status === 401) {
                // auto logout if 401 response returned from api
                logout();
                location.reload(true);
            }
            const error = (data && data.message) || response.statusText;
            return Promise.reject(error);
        }
        return data;
    });
}
