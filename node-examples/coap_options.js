const coap = require('/home/devanshu/node-v6.10.0/lib/node_modules/coap')

var opts = {
	host: 'localhost',
	port: 5683,
	method: 'GET',
	confirmable: true,
	observe: false,
	pathname: '/Temperature'
};


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
