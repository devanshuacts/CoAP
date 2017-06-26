const coap = require('/home/devanshu/node-v6.10.0/lib/node_modules/coap')

var req = coap.request('coap://localhost:5683/Temperature')
req.on('response', function(res) {
    res.pipe(process.stdout)
    res.on('end', function() {
      process.exit(0)
    })
});
req.end()
