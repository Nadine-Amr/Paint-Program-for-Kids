#ifndef ACTION_ADD_CHANGE_DC_H
#define ACTION_ADD_CHANGE_DC_H

#include "Action.h"
#include "..\ApplicationManager.h"

class ActionChangeDC: public Action
{
public:
	ActionChangeDC(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif