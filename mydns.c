#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

int main (void) {
	char* hostname;

	//set up the environment
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1\n",13,10);
	char* get = getenv("QUERY_STRING");

	//QUERY_STRING improperly set
	//(should only get this when running on cmd line
	//and if you've done something wrong)
	if (get == NULL ) {
	  	printf("no query string\n");
   		return 0;
	}
	
	//otherwise get the hostname
	else {
		hostname = (char*)malloc(strlen(get)*sizeof(char));
		int i;

		//this is probably insecure.
		if (i = sscanf(get, "hostname=%s", hostname) < 1 ) {
        		puts("No addresses given.");
        		return 0;
		}
  	}

	
	//set up the command to run
	char* cmd = (char*)malloc(sizeof(char)*strlen(hostname)+9);
	cmd[0] = '\0';
	strcat(cmd, "host -a ");
	strcat(cmd, hostname);	

	//run it with popen() (yay don't have to fork() manually)
	FILE* host_out = popen(cmd, "r");
	char* out;

	//this runs if something goes wrong
	if ( host_out == NULL ) { 
		perror("popen: ");
		exit(-1);
	}

	//otherwise, poop out the output
	else {
		while(fscanf(host_out, "%s\n", out) == 1)
			printf("%s\n",out);
	}

	//clean up
	free(cmd);
	free(hostname);
	pclose(host_out);
}

