/*
	Implementation of the function get from cache
*/

#include "http-response.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <clocale>
using namespace std;

/**
	Used to get the time in seconds of an HTML-date
*/
time_t GMTToSeconds(const char *date){
	struct tm time_rt={0,0,0,0,0,0,0,0,0};
    if((char *)strptime(date,"%a, %d %b %Y %T GMT",&time_rt)){
    	return mktime(&time_rt);
    }
    return time(NULL)+1; // if there is a badly formed date, 
    					//  we asume the document is not expired
}

/**
	Tests whether a date has expired
*/
int isExpired(char * date){
	setlocale(LC_ALL,"GMT");
	time_t now = time(NULL);
	time_t docs = GMTToSeconds(date);
	return now>docs;
}

string GetFromCache(string file){
	string data = getData(file); 
	int dataLength = data.length();
	if(dataLength>1){
		try{
			HttpResponse response();
			response::ParseResponse(data,dataLength);
			if(isExpired(response::FindHeader("Expires"))){
				//remove(file);
				cout << "File removed!" << endl;
			}else{
    			return data;
    		}
  		}catch (int e){
  		}
	}
	return NULL;
}


string getData(const char *filename){
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in){
    string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  return "";
}