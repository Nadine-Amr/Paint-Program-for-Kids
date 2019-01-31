#include "ActionRotate.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionRotate::ActionRotate(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionRotate::Execute()
{
	

	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();


	pGUI->PrintMessage("You want to rotate figure");	
	


}
