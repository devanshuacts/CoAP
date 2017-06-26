const coap = require('/home/devanshu/node-v6.10.0/lib/node_modules/coap')
const url = require('url')

var opts = url.parse('coap://127.0.0.1:5683/RtcData')
opts.confirmable = true
opts.method = 'GET'
opts.observe = true

var req = coap.request(opts);

req.on('response', function(res) {
	console.log(res.code)
    //res.pipe(process.stdout)
    res.on('end', function() {
      process.exit(0)
    })
});
req.end()
