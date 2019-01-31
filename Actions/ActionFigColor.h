#ifndef ACTION_FIGCOLOR_H
#define ACTION_FIGCOLOR_H

#include "Action.h"
#include <ctime>
#include <cstdlib>

class ActionFigColor : public Action
{
public:
	ActionFigColor(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif