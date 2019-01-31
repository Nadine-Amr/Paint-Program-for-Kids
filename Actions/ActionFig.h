#ifndef ACTION_FIG_H
#define ACTION_FIG_H

#include "Action.h"
#include <ctime>
#include <cstdlib>
#include <string>


class ActionFig : public Action
{
public:
	ActionFig(ApplicationManager *pApp);
	
	virtual void Execute() ;
	
};

#endif