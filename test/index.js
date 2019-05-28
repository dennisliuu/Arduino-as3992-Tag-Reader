const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort('\\\\.\\COM3', {baudRate: 115200}	)

const parser = new Readline()
port.pipe(parser)

parser.on('data', line => {
    if (line[0] != "1") {
        // console.log(line[0])
        console.log(`> ${line}`)        
    }
})