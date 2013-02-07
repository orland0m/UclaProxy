#include "cache.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define TIME_OUT 4

using namespace std;

string GetFromRemoteServer(HttpRequest * request, int socketFd){ // GetErrorPage
	string response = GetErrorPage(404); // problem processing the request
	char * buffer = new char[request->GetTotalLength()];
	buffer[0] = '\0';
	request->FormatRequest(buffer);
	int error = 0; // set to 1 if there was a problem
	
	//### Send buffer, put response back in buffer, and create response string
	/*
	response = string(buffer);
	*/
	
	if(!error){
		response = SaveToCache(response, request->GetHost()+request->GetPath()); 
	}
	return response;
}