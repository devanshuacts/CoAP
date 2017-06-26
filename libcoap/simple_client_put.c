#include<stdio.h>
#include<stdlib.h>
#include "coap.h"

static void message_handler(struct coap_context_t *ctx, const coap_endpoint_t *local_interface, const coap_address_t *remote,
							coap_pdu_t *sent, coap_pdu_t *received, const coap_tid_t id)
{
	unsigned char *data;
	size_t data_len;
	if(COAP_RESPONSE_CLASS(received->hdr->code) == 2){
		if(coap_get_data(received, &data_len, &data)){
			data[data_len] = '\0';
			printf("response data: %s\n", data);
			coap_show_pdu(received);
		}
	}
}

int main(){
	coap_context_t* ctx;
	coap_address_t dst_addr, src_addr;
	
	coap_set_log_level(LOG_INFO);
	coap_address_init(&src_addr);
	src_addr.addr.sin.sin_family 	= AF_INET;
	src_addr.addr.sin.sin_port 		= htons(0);
	src_addr.addr.sin.sin_addr.s_addr 	= inet_addr("0.0.0.0"); //INADDR_ANY
	ctx = coap_new_context(&src_addr);
	
	coap_address_init(&dst_addr);
	dst_addr.addr.sin.sin_family		= AF_INET;
	dst_addr.addr.sin.sin_port			= htons(5683);
	dst_addr.addr.sin.sin_addr.s_addr	= inet_addr("127.0.0.1");
	
	static coap_uri_t uri;
	char server_uri[] = "coap://127.0.0.1:5683/updateme!";
	coap_split_uri(server_uri, strlen(server_uri), &uri);
	
	coap_pdu_t* request;
	unsigned char get_method = 1;
	unsigned char post_method = 2;
	unsigned char put_method = 3;
	request = coap_new_pdu();
	request->hdr->type = COAP_MESSAGE_CON;
	request->hdr->id = coap_new_message_id(ctx);
	request->hdr->code   = put_method; //3
	
	char buffer[] = "hello";
	coap_add_data(request, strlen(buffer), buffer);
	coap_add_option(request, COAP_OPTION_URI_PATH, uri.path.length, uri.path.s);
	coap_register_response_handler(ctx, message_handler);
	coap_send_confirmed(ctx, ctx->endpoint, &dst_addr, request);
	
	fd_set activefds, readfds;
	FD_ZERO(&activefds);
	FD_SET(ctx->sockfd, &activefds);
	readfds = activefds; //for multiple requests, loop start
	int ret;
	ret =select(FD_SETSIZE, &readfds, NULL, NULL,NULL);
	if(ret < 0){
		perror("select");
	}
	if(FD_ISSET(ctx->sockfd, &readfds)){
		coap_read(ctx);
	}	//loop ends
	
	return 0;
	
}
