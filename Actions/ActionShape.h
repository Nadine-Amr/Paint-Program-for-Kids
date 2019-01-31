#ifndef ACTION_SHAPE_H
#define ACTION_SHAPE_H

#include "Action.h"
#include <ctime>
#include <cstdlib>

//Add Square Action class
class ActionShape : public Action
{
public:
	ActionShape(ApplicationManager *pApp);
	
	//Add Square to the ApplicationManager
	virtual void Execute() ;
	
};

#endif