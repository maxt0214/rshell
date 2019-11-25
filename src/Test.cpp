#include "../header/Test.h"


Test::Test(char** pathDirectory){

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



bool Test::Execute(){

	struct stat buf;

	if(flag == 'e'){
    	if(stat(filePath, &buf) == 0)
    		return true;

    	else
    		return false;
	}

   else if(flag == 'f'){

   	   if(stat(filePath, &buf) == 0){
   	   		if(S_ISREG(buf.st_mode) != 0)
   	   			return true; 
   	   		else 
   	   			return false;
   	   }

   	   else 
   	   		return false;

   }

   else{

	   	if(stat(filePath, &buf) == 0){

	   		if(S_ISDIR(buf.st_mode) != 0)
	   			return true;
	   		else
	   	 		return false;
	   	}

	   	else
	   		return false;

	}
}




