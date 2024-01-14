// basic server
var http = require('http'); // built in http library
var fs = require('fs'); // filesystem library to grab index page
var index = fs.readFileSync('index.html'); // grab index right now

// listen to serial port - console log anything received
var SerialPort = require("serialport");

const parsers = SerialPort.parsers;
const parser = new parsers.Readline({
    // how to receive data
    // receive data anytime new line is received
    delimeter: '\r\n'
});

var port1 = new SerialPort('/dev/cu.usbmodem14101', {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
}); // open up port to arduino

port1.pipe(parser); // attach port to parser

// create a server
var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end(index);
});

// initialize socket and connect it to app
var io = require('socket.io').listen(app);


io.on('connection', function(data){
    console.log('Node.js is listening');
});

parser.on('data', function(data){
    // receive data from serial port
    console.log(data);
    io.emit('data', data);
});

app.listen(3000);