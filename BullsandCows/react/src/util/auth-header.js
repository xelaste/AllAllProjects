export const authHeader = function () {
    // return authorization header with jwt token
    let user = JSON.parse(sessionStorage.getItem('player'));
    if (user && user.token) {
        return { 'Authorization': 'Bearer ' + user.token };
    } else {
        return {};
    }
}