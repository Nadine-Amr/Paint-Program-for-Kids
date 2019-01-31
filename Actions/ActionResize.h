#ifndef ACTION_RESIZE_H
#define ACTION_RESIZE_H

#include "Action.h"

class ActionResize : public Action
{
public:
	ActionResize(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif