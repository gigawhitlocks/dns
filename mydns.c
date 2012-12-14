#include <event2/util.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

void callback(int result, char type, int count, int ttl, void *addresses, void *arg) {  

}

int main (int argc, char ** argv) {
//	evdns_resolv_conf_parse(DNS_OPTIONS_ALL, "/etc/resolv.conf"); 
	printf("Content-Type: text/plain;charset=us-ascii\n\n");
	
	evdns_base_resolve_ipv4("www.theknown.net", 0, callback, NULL); 
}

