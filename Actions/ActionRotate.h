#ifndef ACTION_ROTATE_H
#define ACTION_ROTATE_H

#include "Action.h"

class ActionRotate : public Action
{
public:
	ActionRotate(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif