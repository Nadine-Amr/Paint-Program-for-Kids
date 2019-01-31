#ifndef ACTION_CHANGE_FC_H
#define ACTION_CHANGE_FC_H

#include "Action.h"
#include "..\ApplicationManager.h"

class ActionChangeFC: public Action
{
public:
	ActionChangeFC(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif