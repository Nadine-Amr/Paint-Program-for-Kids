#ifndef ACTION_REDO_H
#define ACTION_REDO_H

#include "Action.h"

class ActionRedo : public Action
{
	enum { ConsActions = 100 };	//Max no of actions for undo/redo (consecutive)
public:
	ActionRedo(ApplicationManager *pApp);

	virtual void Execute();
};

#endif