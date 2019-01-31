#ifndef ACTION_RESTART_H
#define ACTION_RESTART_H

#include "Action.h"

class ActionRestart : public Action
{
public:
	ActionRestart(ApplicationManager *pApp);

	virtual void Execute() ;
	
};

#endif