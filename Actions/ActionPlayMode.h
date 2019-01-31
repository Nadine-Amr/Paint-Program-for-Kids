#ifndef ACTION_PLAY_MODE_H
#define ACTION_PLAY_MODE_H

#include "Action.h"

class ActionPlayMode : public Action
{
public:
	ActionPlayMode(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif