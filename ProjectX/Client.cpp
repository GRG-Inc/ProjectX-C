//
//  main.cpp
//  ProjectX
//
//  Created by Gaetano Belcastro on 03/02/15.
//  Copyright (c) 2015 GRG. All rights reserved.
//

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include "AI.h"
#include <unistd.h>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

using namespace::std;

class Client{

private:
	AI ai;
	 struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	 struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

public:
	int socketfd;

	Client(string serverAddress, string port){
		int status;


			    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
			    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
			    // is created in c++, it will be given a block of memory. This memory is not nessesary
			    // empty. Therefor we use the memset function to make sure all fields are NULL.
			    memset(&host_info, 0, sizeof host_info);

			    std::cout << "Setting up the structs..."  << std::endl;

			    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
			    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

			    // Now fill up the linked list of host_info structs with google's address information.
			    status = getaddrinfo("127.0.0.1", "8901", &host_info, &host_info_list);
			    // getaddrinfo returns 0 on succes, or some other value when an error occured.
			    // (translated into human readable text by the gai_gai_strerror function).
			    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;


			    std::cout << "Creating a socket..."  << std::endl;

			    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
			                      host_info_list->ai_protocol);
			    if (socketfd == -1)  std::cout << "socket error " ;


			    std::cout << "Connect()ing..."  << std::endl;
			    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
			    if (status == -1)  std::cout << "connect error" ;


			    /*std::cout << "send()ing message..."  << std::endl;
			    char *msg; //= "GET / HTTP/1.1\nhost: www.google.com\n\n";
			    int len;
			    ssize_t bytes_sent;
			    len = strlen(msg);
			    bytes_sent = send(socketfd, msg, len, 0);*/


	}

	~Client(){
	    freeaddrinfo(host_info_list);
	    close(socketfd);
	}

	void play(){
		string colour;

		std::cout << "Waiting to receieve data..." << std::endl;
		ssize_t bytes_recieved;
		char incomming_data_buffer[1000];
		bytes_recieved = recv(socketfd, incomming_data_buffer, 1000, 0);
		// If no data arrives, the program will just wait here until some data arrives.
		if (bytes_recieved == 0)
			std::cout << "host shut down." << std::endl;
		if (bytes_recieved == -1)
			std::cout << "recieve error!" << std::endl;
		std::cout << bytes_recieved << " bytes receieved :" << std::endl;
		//incomming_data_buffer[bytes_recieved] = '\0';

		string response(incomming_data_buffer);

		if (boost::starts_with(response, "WELCOME"))
		        colour = response.substr(8, 5);
		std::cout << colour << std::endl;

		while(true){
			bytes_recieved = recv(socketfd, incomming_data_buffer, 1000, 0);
			string response(incomming_data_buffer);
		}



	}

};

int main()
	{

	Client * client = new Client("127.0.0.1", "8901");
	client->play();

	return 0;
	}
