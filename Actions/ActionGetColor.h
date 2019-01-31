#ifndef ACTION_GET_COLOR_H
#define ACTION_GET_COLOR_H

#include "Action.h"
#include "..\ApplicationManager.h"

class ActionGetColor : public Action
{
public:
	ActionGetColor(ApplicationManager *pApp);

	virtual void Execute() ;
	
};

#endif