#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *input;
    char *data;
    char buffer[1024] = {0};


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    for(;;){

        input = malloc(256);
        data = malloc(256);
        scanf("%255s", input);

        if(strncmp(input, "POST", 4) == 0){
            // send to server
            scanf("%225s", data);
            send(sock, data, strlen(data), 0);

            // read from server
            valread = read(sock, buffer, 1024);
            printf("%s\n", buffer);

            memset(buffer, 0, 1024);
        }else if(strncmp(input, "GET", 3) == 0){

            // send to server
            send(sock, input, strlen(input), 0);

            // read from server
            valread = read(sock, buffer, 1024);
            printf("%s\n", buffer);
            break;
        }else{
            printf("bad Request");       
        }

        
    }


    return 0;
}