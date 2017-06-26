const coap = require('/home/devanshu/node-v6.10.0/lib/node_modules/coap')
const url = require('url')

var opts = url.parse('coap://127.0.0.1:5683/BlockTest')
var req = coap.request(opts)
var buf = new Buffer([2]);
req.setOption("Block2", buf);

req.on('response', function(res) {
    res.pipe(process.stdout)
    res.on('end', function() {
      process.exit(0)
    })
});
req.end()
