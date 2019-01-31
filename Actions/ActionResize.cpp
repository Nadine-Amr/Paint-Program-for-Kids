#include "ActionResize.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionResize::ActionResize(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionResize::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	CFigure* resizefig = pManager->GetSelectedFig();
	if (resizefig)
	{
		pManager->SetSaved(0);
		pGUI->PrintMessage("You want to resize, please enter 0.25 or 0.5 or 2 or 4");
		string userchoice = pGUI->GetSrting();
		while (!(userchoice == "0.25" || userchoice == "0.5" || userchoice == "2" || userchoice == "4"))
		{
			pGUI->PrintMessage("Please enter 0.25 or 0.5 or 2 or 4");
			userchoice = pGUI->GetSrting();
		}
		if (resizefig->Resize(std::stod(userchoice)))
		{
			pGUI->ClearDrawArea();
			pManager->UpdateInterface();
			pGUI->PrintMessage("Object sucssefully resized");
		}
		else
		{
			pGUI->PrintMessage("Object exceeds window dimensions");
		}
		pManager->AddAction();
	}
	else
	{
		pGUI->PrintMessage("Error: No figure selected");
	}
}
