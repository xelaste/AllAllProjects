const got = require('got');
//const axios=require ('axios');

process.env["GLOBAL_AGENT_HTTP_PROXY"]="http://genproxy:8080";
//process.env["HTTP_PROXY"]="http://genproxy:8080";
//process.env["HTTPS_PROXY"]="http://genproxy:8080";

//process.env.GLOBAL_AGENT_HTTPS_PROXY='http://genproxy:8080';
//process.env.ROARR_LOG=true
require('global-agent/bootstrap');
/*
var tunnel = require('tunnel');
var tunnelingAgent = tunnel.httpsOverHttp({
  proxy: {
    host: 'genproxy',
    port: 8080
  },
  headers: {
    'User-Agent': 'Node'
  }
});
(async () => {
    const response = await axios(
        {
            method:'get',
            url:'http://webhooks.mongodb-stitch.com/api/client/v2.0/app/bullsandcows-pepdu/service/BullsAndCows/incoming_webhook/BullsAndCows_getPlayers?secret=[qwerty123456]&limit=10'
        }
    );
    console.log(response.data);
    })();

(async ()=>
{
    const response = await axios({
        url:'https://webhooks.mongodb-stitch.com/api/client/v2.0/app/bullsandcows-pepdu/service/BullsAndCows/incoming_webhook/BullsAndCows_createPlayer?secret=[qwerty123456]', 
        method:'post',
        proxy:false,
        data:{
        name: 'aaaa bbbb',
        score: 0,
        email: '',
        username: '__dhhhhx',
        password: '1234',
        hash: '',
        profileImage: 'noimage.png'            
    }
}).catch(function (error) {
        console.log(error);
        return error;
      });
    console.log("*********************************")   
    console.log(response);
} 
)();


    
/*
   (async () => {
    try {
        const response = await got.get('https://webhooks.mongodb-stitch.com/api/client/v2.0/app/bullsandcows-pepdu/service/BullsAndCows/incoming_webhook/BullsAndCows_getPlayers?secret=[qwerty123456]&limit=10');
       
        console.log(response.body);
        //=> '<!doctype html> ...'
    } catch (error) {
        console.log(error.response.body);
        //=> 'Internal server error ...'
    }
})();
*/
(async () => {
    const response = await got.post('https://webhooks.mongodb-stitch.com/api/client/v2.0/app/bullsandcows-pepdu/service/BullsAndCows/incoming_webhook/BullsAndCows_createPlayer?secret=[qwerty123456]', 
    {
        //agent: { https: tunnelingAgent},
        json: {
            name: 'aaggyyy bbbbeee',
            score: 0,
            email: 'dddd@fff.com',
            username: '__$ssxxff$__ggx',
            password: '1234',
            hash: '1234',
            profileImage: 'noimage.png'            
        },
        responseType: 'json',
        resolveBodyOnly: true
    }).catch((e)=>console.log(e.response.body));
    console.log("**********************************");
    console.log(response);
})();
 

