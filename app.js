var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(3000,()=>{
    console.log("Server is running!")
});
// WARNING: app.listen(80) will NOT work here!

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {
  socket.emit('iot_push', { hello: 'world' });
  socket.on('iot_push', function (data) {
    console.log(data);
  });
});