#include "ActionPlayMode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionPlayMode::ActionPlayMode(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionPlayMode::Execute()
{
	

	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 
	 pGUI->CreatePlayToolBar();
	 pManager->StartPlay();
	 pGUI->PrintMessage("You are now in Play Mode");	
	
	 pManager->AddAction();

}
