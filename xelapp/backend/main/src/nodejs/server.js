console.log("Set working directory to:    ", __dirname); 
process.chdir(__dirname);
var express = require('express');
var bodyParser = require('body-parser')
const jwt = require('./jwt');
const Logger = require('./logger');
const errorHandler = require('./error-handler');
const logger = Logger.createLogger("server");
var path = require('path');
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

app.use(express.static('public'));
app.use(express.static('dist'));

app.use(jwt());
app.use(errorHandler);
app.use('/players', require("./controllers/playerController"));




app.get('/*', function(req, res) {
    res.sendFile(path.join(__dirname, '/public/index.html'), function(err) {
      if (err) {
        logger.error(JSON. stringify(err));
        res.status(500).send(JSON. stringify(err));
      }
    })
  })
const PORT = process.env.PORT || 3000;
app.listen(PORT, function () {
    logger.info('Example app listening on port ' + PORT + '!');
});

