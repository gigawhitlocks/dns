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
	printf("<html>\n<head>\n<title>DNS Tool</title>\n</head>\n<body>\n");

	//a form for using the script
	printf("<form action=\"/dns.cgi\" method=\"get\">\n");
	printf("<label for=\"hostname\">Enter a hostname:</label>\n");
	printf("<input type=\"text\" name=\"hostname\">\n");
	printf("<input type=\"submit\" value=\"Get DNS Zone\"></form>\n");
	printf("<pre style=\"width:900px\">");

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

		//Grab the input from GET and check to see if we got something
		if (i = sscanf(get, "hostname=%s", hostname) < 1 ) {
        		puts("No address given.");
        		return 0;

		//if we did get something:
		} else {

			// for each char in hostname:
			int x;
			for ( x = 0; x < strlen(hostname); x++ ) {
				if ( ! 						         // if current char is not a
					( hostname[x] == '-' || hostname[x] == '.'    || // hyphen or period,
					( hostname[x] >= '0' && hostname[x] <= '9' )  || // a numeral,
					( hostname[x] >= 'A' && hostname[x] <= 'Z' )  || // an uppercase letter,
					( hostname[x] >= 'a' && hostname[x] <= 'z' ) )   // or a lowercase letter
				  	) { // then the hostname is invalid

				//	printf("%s is invalid. %c (%d) is an invalid character.", hostname, hostname[x], x);
					printf("The given input is not a valid hostname.\n");
					free(hostname);
					return 0;
				}
			}

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
		while(fscanf(host_out, "%[^\n]\n", out) == 1)
			printf("%s\n",out);
			
	}


	printf("</pre>\n</body>\n</html>\n");
	//clean up
	free(cmd);
	free(hostname);
	pclose(host_out);
}

