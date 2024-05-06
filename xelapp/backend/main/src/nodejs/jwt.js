const expressJwt = require('express-jwt');
const config = require('config');

function jwt() {
    const secret = config.jwt.secret;
    const algorithms=config.jwt.algorithms;
    return expressJwt({ secret:secret,
                        algorithms:algorithms, 
                        isRevoked:isRevoked, 
                        getToken:getToken}).unless({
        path: [
            // public routes that don't require authentication
            /\/login/,
            /\/register/,
            /\/players\/authenticate*/,
            /\/players\/register*/,
        ]
    });
}
function getToken (req) {
    if (req.headers.authorization) {
        return req.headers.authorization.replace("Bearer","").trim();
    } else {
        return req.cookies.authorization ? req.cookies.authorization.replace("Bearer","").trim():"";
    }    
}
async function isRevoked(req, payload, done) {
   // const user = await userService.getById(payload.sub);
    // revoke token if user no longer exists
   // if (!user) {
    //    return done(null, true);
    //}
    done();
};

module.exports = jwt;