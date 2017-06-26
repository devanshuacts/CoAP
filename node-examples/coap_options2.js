const coap = require('/home/devanshu/node-v6.10.0/lib/node_modules/coap')
const url = require('url')

var opts = url.parse('coap://localhost:5683/Temperature')
opts.confirmable = true
opts.method = 'GET'
opts.observe = false

var req = coap.request(opts)
console.log(req)

req.on('response', function(res) {
	console.log(res)
    res.pipe(process.stdout)
    res.on('end', function() {
      process.exit(0)
    })
});
req.end()
