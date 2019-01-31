#include "ActionExit.h"
#include "..\\ApplicationManager.h"
#include "..\\GUI\GUI.h"



ActionExit::ActionExit(ApplicationManager * pApp) :Action(pApp)
{}

void ActionExit::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Do you really want to exit? Y/N");
	string userchoice1 = pGUI->GetSrting();
	if (userchoice1 == "Y")
	{
		pManager->ExitFlag = 1;
		if (!(pManager->isSaved()))
		{
			pGUI->PrintMessage("Do you want to save the current drawing window first? Y/N");
			string userchoice2 = pGUI->GetSrting();
			if (userchoice2 == "Y")
			{
				Action* pAct = (pManager->CreateAction(SAVE));
				pManager->ExecuteAction(pAct);
			}
		}
		pManager->ClearFigList();
		pGUI->ClearDrawArea();
	}
	else
	{
		pGUI->ClearStatusBar();
	}
}