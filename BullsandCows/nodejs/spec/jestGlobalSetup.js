module.exports = async () => 
{
   console.log("###### Jest Global Settings Start #######");
   process.env.LOG_LEVEL="debug";
   process.env.HTTP_PROXY="genproxy:8080";
   process.env.HTTPS_PROXY="genproxy:8080";
   process.env["GLOBAL_AGENT_HTTP_PROXY"]="http://genproxy:8080";
   console.log(process.env);
   console.log("########################");
};
