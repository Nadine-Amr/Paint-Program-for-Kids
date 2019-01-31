#ifndef ACTION_COLOR_H
#define ACTION_COLOR_H

#include "Action.h"
#include <ctime>
#include <cstdlib>

class ActionColor : public Action
{
public:
	ActionColor(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif