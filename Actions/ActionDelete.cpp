#include "ActionDelete.h"


#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDelete::ActionDelete(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionDelete::Execute()
{
	pManager->SetSaved(0);

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	CFigure* delfig = pManager->GetSelectedFig();
	if (delfig)
	{
		pManager->DeleteFig(delfig->getid());
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();
		pGUI->PrintMessage("Figure successfully deleted");
	}
	else
	{
		pGUI->PrintMessage("Select the figures you want to delete and repress the delete icon");
		pGUI->GetPointClicked(pGUI->CurrentClick.x, pGUI->CurrentClick.y);
		while (!((pGUI->CurrentClick.y >= 0 && pGUI->CurrentClick.y < UI.ToolBarHeight) && (pGUI->CurrentClick.x / UI.MenuItemWidth == ITM_DEL)))
		{
			pManager->SelectMany(pGUI->CurrentClick.x, pGUI->CurrentClick.y);
			pGUI->GetPointClicked(pGUI->CurrentClick.x, pGUI->CurrentClick.y);
		}
		for (int i = 0; i < pManager->GetMaxFigCount(); i++)
		{
			CFigure* delfig2 = pManager->GetSelectedFig();
			if (delfig2)
			{
				pManager->DeleteFig(delfig2->getid());
				pGUI->ClearDrawArea();
				pManager->UpdateInterface();
			}
		}
		pGUI->PrintMessage("Figures sucssefully deleted");
	}
	pManager->AddAction();
}