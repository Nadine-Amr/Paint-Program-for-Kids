#include "ActionSendBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSendBack::ActionSendBack(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionSendBack::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	CFigure* backfig = pManager->GetSelectedFig();
	if (backfig)
	{
		pManager->SetSaved(0);
		pManager->FrontBack(backfig->getid(), 0);
		pGUI->CreateDrawArea();
		pManager->UpdateInterface();
		pGUI->PrintMessage("Figure successfully brought to back");
		pManager->AddAction();
	}
	else
	{
		pGUI->PrintMessage("Error: No figure selected");
	}
}
