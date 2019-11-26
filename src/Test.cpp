#include "../header/Test.h"

#include <iostream>

using namespace std;

TestCmd::TestCmd(char** pathDirectory){

	string flagStart = pathDirectory[0];


	if(flagStart == "-f"){
		flag = 'f';
		filePath = pathDirectory[1];
	}

	else if(flagStart == "-d"){
		flag = 'd';
		filePath = pathDirectory[1];
	}

	else if (flagStart == "-e"){
		flag = 'e';
		filePath = pathDirectory[1];
	}

	else{
		filePath = pathDirectory[0];
		flag = 'e';
	}
}



pid_t TestCmd::Execute(){

	struct stat buf;

	if(flag == 'e'){
    	if(stat(filePath, &buf) == 0) {
    		cout << "(True)" << endl;
    		return 0;
    	}

    	else {
    		cout << "(False)" << endl;
    		return -1;
    	}
	}

   else if(flag == 'f'){

   	   if(stat(filePath, &buf) == 0){
   	   		if(S_ISREG(buf.st_mode) != 0) {
   	   			cout << "(True)" << endl;
   	   			return 0;
   	   		}
   	   		else {
   	   			cout << "(False)" << endl;
   	   			return -1;
   	   		}
   	   }

   	   else {
   	   		cout << "(False)" << endl;
   	   		return -1;
   	   }

   }

   else{

	   	if(stat(filePath, &buf) == 0){

	   		if(S_ISDIR(buf.st_mode) != 0) {
	   			cout << "(True)" << endl;
	   			return 0;
	   		}
	   		else {
	   			cout << "(False)" << endl;
	   	 		return -1;
	   		}
	   	}

	   	else {
	   		cout << "(False)" << endl;
	   		return -1;
	   	}
	}
}




