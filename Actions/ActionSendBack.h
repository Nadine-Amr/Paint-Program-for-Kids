#ifndef ACTION_SEND_BACK_H
#define ACTION_SEND_BACK_H

#include "Action.h"

class ActionSendBack : public Action
{
public:
	ActionSendBack(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif