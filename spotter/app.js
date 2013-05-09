
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , Classifier = require('./routes/classifier')
  , http = require('http')
  , path = require('path');

if (!process.env.IMAGE_PATH)
	throw new Error('env variable IMAGE_PATH must be defined');

var app = express()
  , classifier = new Classifier(process.env.IMAGE_PATH);

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.bodyParser({ keepExtensions: true, uploadDir: '/tmp' }));
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
}

app.get('/', routes.index);
app.post('/image/classify', classifier.classify.bind(classifier));
app.post('/image/confirm', classifier.confirm.bind(classifier));

http.createServer(app).listen(app.get('port'), function () {
  console.log('Express server listening on port ' + app.get('port'));
});
