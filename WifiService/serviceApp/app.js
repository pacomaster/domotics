var express = require('express');
var app = express();

global.client = [1,2,3];
global.led = [[1,1,1],[1,1,1],[1,1,1]];

app.get('/', function (req, res) {
  res.send('{"response":"Hello"}');
});

app.get('/client/:clientId/led/:led', function (req, res) {
  var clientId = req.params.clientId - 1;
  var led = req.params.led - 1;
	
  res.send('{"response":{"status" : ' + global.led[clientId][led] + '}}');
});

app.post('/client/:clientId/led/:led/turn/:onoff', function (req, res) {
  var clientId = req.params.clientId - 1;
  var led = req.params.led - 1;
  var onoff = req.params.onoff;	
  
  global.led[clientId][led] = onoff;
	
  res.send('{"response":{"status" : ' + global.led[clientId][led] + '}}');
});

app.listen(8080, function () {
  console.log('App listening on port 8080!');
});