# CS 100 Programming Project
Ryan Lam, 862110744	                                                                                            		

Xiaotian Ma, 862094705                                                            						

CS100 Brian Crites - Fall 2019

Introduction:
	We are currently using a composite design pattern to design our shell. 
Our project design consists of 6 classes which inherit from an interface in 
order to execute certain commands and functions. From our Base interface, 
we have two classes Connector and Command which allow for command execution 
based on the arguments and executables. From our connector class we have an 
AND, OR, and SEMICOLON class which are used to differentiate between single 
and several command executions. Furthermore, our EXIT class inherits from our 
Command class in order to follow specific procedures before exiting our shell


OMT Diagram:
	Our OMT diagram shows how we build composite pattern using multiple classes
inherited from base class

	Path: Images/

Classes: 
	
Base:
	Our Base class consists of a virtual execute function that will be inherited 
	by all of our other classes. It will be used in order to support both connector and command execute functions. 

Connector:

	Our Connector class will contain another virtual execute function that will 
	allow for proper differentiation between a single and double command. 
	For example, it will allow us to differentiate between calling two echo commands 
	using a logical operator and a single command line. We will do this using a 
	parser (code shown below) in order to compare characters and execute certain commands. 

	Our AND class will only execute the right hand side command if the left hand 
	side operator executes on through the parser. Furthermore, if the left hand 
	side operator fails, either a flag will be set and an error will be output.

	Our OR class will execute the right hand side command if the left hand side operator fails to do so. 

	The Semicolon will allow for execution regardless of the use of an AND or OR, 
	allowing for execution of multiple commands at a time. 

Command:
	
	Our Command Class will use a value returned from the parser in order to execute specific commands.
	It will allow us to use functions such as waitpid(), fork(), and execvp() as well. 

 	Furthermore, our EXIT class will contain procedures among execution that will ensure that 
	the command queue is empty and that there are no other commands being prompted after it. 
	Shortly afterward, the command will execute and exit the shell. 

Prototype

	Our prototype folder contains two parts, prototype functions to test execvp(), fork(), and 
	waitpid(), and parser class to output a vector of  commands and connectors, ex: {command1, connector, command2, etc}. 
	Commands and connectors are implemented as arrays of c-string. One single command could be {“ls”, ”-a”, “-l”}. 
	Connector are implemented such as {“;”}, which only contain one string of connector. 

	For the part how we could distinguish between multiple commands in one line or single command in one line, 
	the returned vector of c-string arrays would only contain one array if the user only input single command, and vice versa. 

	Code: prototype/


Development and Testing Roadmap

	Base Class                                 				-Xiaotian Ma
	CMD Class(concurrently with connector)					-Xiaotian Ma
	Unit_test for CMD Class							-Xiaotian Ma
	Connector Class								-Ryan Lam
	Unit_test for Connector Class						-Ryan Lam
	Exit Class								-Xiaotian Ma
	Unit_test for Exit Class						-Xiaotian Ma
	And Class								-Ryan Lam
	Unit_test for And Class							-Ryan Lam
	Or Class								-Ryan Lam
	Unit_test for Or Class							-Ryan Lam
	Semicolon Class								-Ryan Lam
	Unit_test for Semicolon Class						-Ryan Lam
	Integrated Tests							-Xiaotian Ma
	

