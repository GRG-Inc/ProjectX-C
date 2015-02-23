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
#include <chrono>
#include "AI.cpp"
#include <locale>
#include <thread>

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
	 ssize_t bytes_received, bytes_sent, n;
        int sockfd, tempo;
        char buffer[256];
        bool home;
public:
    
    Client(const char* serverAddress, const char* port, int time){
        struct sockaddr_in serv_addr;
        struct hostent *server;
        
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname(serverAddress);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(atoi(port));
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        
        
        
        ai = new AI();
        (*ai).distanza();

		tempo = time;
    }
    
    ~Client(){
        freeaddrinfo(host_info_list);
        close(sockfd);
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
        
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        
        if(startsWith(buffer, (char*)"WELCOME"))
            printf(buffer);

        
        string colour;
        if(buffer[9]=='l'){
        	home=true;
            colour="black";
        }
        else{
            colour="white";
            home=false;
        }
        
        char* msg = new char[256];
        
        while(true){
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            
            
            if(startsWith(buffer, (char*)"VALID_MOVE"))
                cout << "Valid move, please wait" << endl;
            else if(startsWith(buffer, (char*)"OPPONENT_MOVE")){
                
                substr(buffer, 14, msg);
                
                ai->convertiStringaMossa(msg);
                cout << "Opponent move: " << msg << endl;
                if (buffer[23] == 'Y' && buffer[24] == 'O' && buffer[25] == 'U' && buffer[26] == 'R')
                {
                	goto your_turn;
                }
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
               your_turn:
                
                string move = ai->generaProssimaMossa(*ai->getScacchiera(), colour, tempo, home);
                
                
                int i;
                for(i=0;i<8; i++){
                    msg[i] = move.at(i);
                }
                msg[i] = 0;
                
                sprintf(buffer, "MOVE %s\n", msg);
                
                

                n = write(sockfd,buffer,strlen(buffer));
                cout << "La tua mossa è: " << move << endl;
                ai->convertiStringaMossa(move);
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

int main(int argc, char** argv)
	{
	char *serverAddr = argv[1];
				char *port = argv[2];
				int time = atoi(argv[3]);
				Client * client = new Client(serverAddr, port, time);
				client->play();
				delete client;
				return 0;
	}
