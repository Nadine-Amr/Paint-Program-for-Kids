#ifndef ACTION_UNDO_H
#define ACTION_UNDO_H

#include "Action.h"

class ActionUndo : public Action
{
	enum { ConsActions = 100 };	//Max no of actions for undo/redo (consecutive)
public:
	ActionUndo(ApplicationManager *pApp);

	virtual void Execute();

};

#endif