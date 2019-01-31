#ifndef ACTION_DRAW_MODE_H
#define ACTION_DRAW_MODE_H

#include "Action.h"

class ActionDrawMode : public Action
{
public:
	ActionDrawMode(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif