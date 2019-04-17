const XCB = require('bindings')('xcb');

const connection = new XCB.Connection();
connection.connect();
console.log("Connected to X server!");
connection.disconnect();
console.log("Disconnected from X server!");