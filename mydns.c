#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

int main (void) {
	char* hostname;
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1\n",13,10);
	char* get = getenv("QUERY_STRING");
	if (get == NULL ) {
	  	printf("no query string\n");
   		return 0;
	}
	else {
		hostname = (char*)malloc(strlen(get)*sizeof(char));
		int i;
		if (i = sscanf(get, "hostname=%s", hostname) < 1 ) {
        		puts("No addresses given.");
        		return 0;
		}
  	}

	
	char* cmd = (char*)malloc(sizeof(char)*strlen(hostname)+9);
	cmd[0] = '\0';
	strcat(cmd, "host -a ");
	strcat(cmd, hostname);	
	FILE* host_out = popen(cmd, "r");
	char* out;
	free(cmd);
	free(hostname);
	if ( host_out == NULL ) { 
		perror("popen: ");
		exit(-1);
	}
	else {
		while(fscanf(host_out, "%s\n", out) == 1)
			printf("%s\n",out);
	}
	pclose(host_out);
}

