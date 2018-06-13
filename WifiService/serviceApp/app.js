var express = require('express');
var app = express();

global.led = [0,0,0,0];

global.temp = 0;

app.get('/', function (req, res) 
{
  res.send('{"response":"Hello"}');
});

app.get('/client/:clientId/led/:led', function (req, res) 
{
  var clientId = req.params.clientId;
  var led = req.params.led;
  res.send('{"status" : "' + global.led[led] + '"}');
});

app.get('/client/:clientId/leds', function (req, res) 
{
  var clientId = req.params.clientId;
  res.send('{"status" : "' + global.led + '"}');
});

app.get('/client/:clientId/temp', function (req, res) 
{	
  res.send('{"status" : "' + global.temp + '"}');
});

app.post('/client/:clientId/led/:led/turn/:onoff', function (req, res) 
{
  var clientId = req.params.clientId;
  var led = req.params.led;
  var onoff = req.params.onoff;	
  
  global.led[led] = onoff;
  console.log(global.led);	
  res.send('{"status" : "' + global.led + '"}');
});

app.post('/client/:clientId/temp/:temp', function (req, res) 
{
  var clientId = req.params.clientId;
  var temp = req.params.temp;
  
  global.temp = temp;
  console.log(global.temp);
  res.send('{"status" : "' + global.temp + '"}');
});

app.listen(8080, function () 
{
  console.log('App listening on port 8080!');
});
