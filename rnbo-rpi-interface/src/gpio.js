const Gpio = require('../onoff').Gpio;
const motorLeft = new Gpio(27, 'out');
const motorRight = new Gpio(27, 'out');

const { Server, Client } = require('node-osc');

// Add your server to the list of listeners
const client = new Client('127.0.0.1', 1234);
client.send('/rnbo/listeners/add', "127.0.0.1:4321", () => {
  client.close();
});

// Now listen for OSC messages
let oscServer = new Server(4321, '0.0.0.0', () => {
    console.log('OSC Server is listening');
});

oscServer.on('message', function (msg, contents) {
    if (msg === "/rnbo/inst/0/messages/out/body") {
        if (contents === 1) {
            motorLeft.writeSync(1);
            motorRight.writeSync(0);
        } else if (contents === 2) {
            motorLeft.writeSync(1);
            motorRight.writeSync(0);
        } else {
            motorLeft.writeSync(0);
            motorRight.writeSync(0);
        }
    }
});
