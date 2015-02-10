////
////  main.cpp
////  ProjectX
////
////  Created by Gaetano Belcastro on 03/02/15.
////  Copyright (c) 2015 GRG. All rights reserved.
////

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include "AI.cpp"
#include <locale>

using namespace::std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

class Client{

private:
	AI* ai;
	 struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	 struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
	 ssize_t bytes_received, bytes_sent;
public:
    int socketfd;
    
    Client(const char* serverAddress, const char* port){
        int status;
        
        ai = new AI();
        (*ai).distanza();
    }
    
    ~Client(){
        freeaddrinfo(host_info_list);
        close(socketfd);
        delete ai;
    }
    
    bool startsWith(char c1[], char c2[]){
        int i=0;
        while(c2[i] != 0){
            if(c1[i]==0)
                return false;
            if(c1[i] != c2[i])
                return false;
            i++;
        }
        
        return true;
    }
    
    void substr(char c[], int pos, char* s){
        int i;
        for(i=pos; c[i]!=0; i++){
            s[i-pos] = c[i];
        }
        s[i-pos] = 0;
    }

    void play(){
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        
        char buffer[256];
        
        portno = 8901;
        
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname("127.0.0.1");
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        
        if(startsWith(buffer, (char*)"WELCOME"))
            printf(buffer);
        else
            printf("Altro messaggio\n");
        
        char* col = new char[6];
        substr(buffer, 8, col);
        
        string colour(col);
        
        char* msg = new char[256];
        
        while(true){
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            //printf(buffer);
            
            if(startsWith(buffer, (char*)"VALID_MOVE"))
                cout << "Valid move, please wait" << endl;
            else if(startsWith(buffer, (char*)"OPPONENT_MOVE")){
                
                substr(buffer, 14, msg);
                
                ai->convertiStringaMossa(msg);
                cout << "Opponent move: " << msg << endl;
            }
            else if(startsWith(buffer, (char*)"VICTORY")){
                cout << "You win" << endl;
                break;
            }
            else if(startsWith(buffer, (char*)"DEFEAT")){
                cout << "You lose" <<endl;
                break;
            }
            else if(startsWith(buffer, (char*)"TIE")){
                cout << "You tied" << endl;
                break;
            }
            else if(startsWith(buffer, (char*)"YOUR_TURN")){
                cout << "Entro in YOUR_TURN" << endl;
                string move = ai->generaProssimaMossa(*ai->getScacchiera(), col, 3);
                cout << "La tua mossa è: " << move << endl;
                
                int i;
                for(i=0;i<8; i++){
                    msg[i] = move.at(i);
                }
                msg[i] = 0;
                
                sprintf(buffer, "MOVE %s\n", msg);
                printf("Sto per inviare la mossa: %s\n", buffer);
                
                n = write(sockfd,buffer,strlen(buffer));
                
                ai->convertiStringaMossa(msg);
            }
            else if(startsWith(buffer, (char*)"TIMEOUT")){
                cout << "Time out" << endl;
                break;
            }
            else if(startsWith(buffer, (char*)"MESSAGE")){
                substr(buffer, 8, msg);
                cout << msg << endl;
            }
            
        }
        close(sockfd);
    }
};

int main()
	{
        const char serverAddr[]="127.0.0.1";
        const char port[]="8901";
	Client * client = new Client(serverAddr, port);
	client->play();
	/*string move = ai.generaProssimaMossa(*ai.getScacchiera(), "Black", 3);
	cout << move << endl;*/
        delete client;
	return 0;
	}
