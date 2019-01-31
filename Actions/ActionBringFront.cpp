#include "ActionBringFront.h"


#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionBringFront::ActionBringFront(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionBringFront::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	CFigure* frontfig = pManager->GetSelectedFig();
	if (frontfig)
	{
		pManager->SetSaved(0);		
		pManager->FrontBack(frontfig->getid(), 1);
		pGUI->CreateDrawArea();
		pManager->UpdateInterface();
		pGUI->PrintMessage("Figure successfully brought to front");
		pManager->AddAction();
	}
	
	else
	{
		pGUI->PrintMessage("Error: No figure selected");
	}
}
