#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv){

    int status, i, sock, start, end;
    char host[100];
    struct sockaddr_in servaddr;

    printf("Enter host IP:");
    gets(host);

    printf("\n");

    printf("Enter start port number: ");
    scanf("%d", &start);

    printf("\n");

    printf("Enter end port number: ");
    scanf("%d", &end);

    strncpy((char*)&servaddr, "", sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host);

    for(i = start;  i <= end; i++){
        printf("Scanning port %i\n",i);

        servaddr.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(socket < 0){
            exit(1);    
        }

        status = connect(sock, (struct sockaddr*)&servaddr, sizeof servaddr);

        if (status < 0){
            fflush(stdout);
            printf("Port %i is closed\n", i);
        }
        else {
            printf("Port %i is open\n", i);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}