#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int status, i, sock, start, end;
    char host[100];
    struct sockaddr_in servaddr;

    std::cout << "Enter host IP: ";
    std::cin >> host;

    std::cout << "\nEnter start port number: ";
    std::cin >> start;

    std::cout << "\nEnter end port number: ";
    std::cin >> end;

    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host);

    for (i = start; i <= end; i++) {
        std::cout <<"Scanning port "<<i<<" ... Address = "<<host<<":"<<i<<"\n";

        servaddr.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0) {
            perror("socket");
            exit(1);
        }

        status = connect(sock, reinterpret_cast<struct sockaddr*>(&servaddr), sizeof servaddr);

        if (status < 0) {
            std::cout << "Port " << i << " is closed\n";
        } else {
            std::cout << "Port " << i << " is open\n";
        }
        close(sock);
    }

    return 0;
}