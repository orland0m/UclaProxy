#include <iostream>
#include <fstream>
#include <string>

//project wireframe
#include "http-request.h"
#include "http-headers.h"
#include "http-response.h"

//custom defined files
#include "web-request.h" /* GetFromRemoteServer */
#include "cache.h" /* GetFromCache */
#include "connection-handler.h" //handles http connections

using namespace std;

void ProcessRequest(string rq){
	cout << rq << endl;
	HttpRequest * request = new HttpRequest;
	request -> ParseRequest(rq.c_str(), rq.length()); // parse request
	string response = GetFromCache(request, 0); // get non expired file from cache
	if(response.length()>0){
		cout << "Bingo! request in cache/" << request->GetHost() << request->GetPath() << endl;
		return;
	}
	cout << "Making remote request..." << endl;
	
	string destPort = "80"; // port
	string destHost = string(request->GetHost()); // host URL
	
	int socket = serverNegotiateClientConnection(destHost.c_str(), destPort.c_str());//created socket
	
	response = GetFromRemoteServer(request, socket); //requesting to remote server
	
	cout << "Response received! length: "<< endl << response.length() <<endl;
	// "response" should contain a file ready to be sent to the client, even if there was an error
}

int ProcessFile (string name){
	string line;
	std::ifstream myfile (name.c_str());
	if (myfile.is_open()){
    	while ( myfile.good() ){
    		getline(myfile,line);
    		ProcessRequest(line);
    	}
    	myfile.close();
	}else cout << "Unable to open file " << name;
	return 0;
}