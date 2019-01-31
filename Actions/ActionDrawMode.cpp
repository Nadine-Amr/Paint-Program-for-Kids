#include "ActionDrawMode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDrawMode::ActionDrawMode(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionDrawMode::Execute()
{
	

	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 
	 pGUI->CreateDrawToolBar();
	 pManager->StartDraw();
	pGUI->PrintMessage("You are now in Draw Mode");	
	
	pManager->AddAction();

}
