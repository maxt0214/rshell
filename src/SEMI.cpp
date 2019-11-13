#include "../header/SEMI.h"

SEMI::SEMI(Base* lf,Base* rf) : Connector(lf,rf){}

pid_t SEMI::Execute(){
	childLeft -> Execute();
	return childRight -> Execute();
}