const app = require('express')()
const http = require('http').Server(app)
const io = require('socket.io')(http)

// 宣告點數與變數
const value = ["A0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"]
var out = ''

// Render html
app.get('/', function (req, res) {
	res.sendFile(__dirname + '/index.html')
});

// 宣告 Serial port, COM3 為本機端
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort('\\\\.\\COM3', { baudRate: 115200 })

// 讀取 Serial port 整行輸出
const parser = new Readline()
port.pipe(parser)

// 當 Serial port 有 data 時，將變數 out 令為點數值
parser.on('data', line => {
	if (line[0] == "5") {
		var point = value[parseInt(line.split('=')[1])]
		console.log(`Point: ${point}`)
		out = point
	}
})

// 利用 Socket 達到電腦端與網頁端溝通
io.on('connection', socket => {
	console.log('Connected')
	socket.on('rfid message', () => {
		// 傳送本機資料 
		io.emit('rfid message', out)
	})
	socket.on('disconnect', () => {
		console.log('Disconnected')
	})
})

// 宣告本機 port 3000
http.listen(3000, () => {
	console.log('listening on 127.0.0.1:3000')
})