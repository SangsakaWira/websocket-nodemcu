const app = require('express')();
const server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(6500,()=>{
    console.log("Server is running!")
});

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {
  socket.on('iot_push', function (data) {
    console.log(data);
  });
});