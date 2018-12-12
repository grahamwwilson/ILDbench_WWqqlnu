#include "jetVariables.h"


jetVariables::jetVariables(eventVariables*& evtvar){
	_evtvar=evtvar;
	_localTree = evtvar->_localTree;

	//init rest of local stuff

}
