#include "ActionGetColor.h"





ActionGetColor::ActionGetColor(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionGetColor::Execute()
{

	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 pGUI->PrintMessage("You want to change background color, Please pick color.");
	 UI.BkGrndColor = pGUI->DrawPallate();
	 pGUI->CreateDrawToolBar();
	 pGUI->CreateDrawArea();
	 
	 pManager->AddAction();
}
