console.log("Set working directory to:    ", __dirname); 
process.chdir(__dirname);
process.env["NODE_CONFIG_DIR"] = "../resources/config/";
const config = require('config')
var express = require('express');
var bodyParser = require('body-parser')
const jwt = require('./jwt');
const Logger = require('./logger');
const errorHandler = require('./error-handler');
const logger = Logger.createLogger("server");
var path = require('path');
var cors = require('cors')
var app = express();
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

function logRequest(req, res, next) 
{
    logger.debug(req.url);
    logger.debug(req.headers)
    logger.debug(req.body);
    next();
}
app.use(logRequest);
app.use(express.static('dist'));

app.use(jwt());
app.use(errorHandler);
app.use(cors());
app.use('/players', require("./controllers/playerController"));




app.get('/*', function(req, res) {
    res.sendFile(path.join(__dirname, '/dist/index.html'), function(err) {
      if (err) {
        logger.error(JSON. stringify(err));
        res.status(500).send(JSON. stringify(err));
      }
    })
  })
const PORT = process.env.PORT || config.server.listenPort;
app.listen(PORT, function () {
    logger.info('xela all app listening on port ' + PORT + '!');
});

