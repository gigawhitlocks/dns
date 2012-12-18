#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

int main (void) {
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1\n",13,10);
  char* get = getenv("QUERY_STRING");
  if (get == NULL ) {
  	printf("no query string\n");
   	return 0;
  }

	else {
		char* hostname = (char*)malloc(strlen(get)*sizeof(char));
		int i;
		if (i = sscanf(get, "hostname=%s", hostname) < 1 ) {
        		puts("No addresses given.");
        		return 0;
  	}
		pid_t pid = fork();
		if ( pid == 0 ) { //child
	//		printf("in the child. hostname = %s",hostname);
			char* args[] = {"host","-a",hostname, NULL};
			printf("%s\n%s\n%s\n",args[0],args[1],args[2]);
			execvp(args[0], args);
		} else if ( pid > 0 ) {
			int status;
			wait(NULL);
		//	waitpid(pid, &status, 0);
	//		printf("The input is: %s",hostname);

		} else {
			perror( "fork" );
			exit(0);
		}
	}
}

