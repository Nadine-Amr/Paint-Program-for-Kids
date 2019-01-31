#include "ActionSelect.h"

#include "..\GUI\GUI.h"


ActionSelect::ActionSelect(ApplicationManager * pApp) :Action(pApp)
{}

void ActionSelect::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pManager->SelectFigure(pGUI->CurrentClick.x, pGUI->CurrentClick.y);
}