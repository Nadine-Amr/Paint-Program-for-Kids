#include "ActionMove.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionMove::ActionMove(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionMove::Execute()
{
	pManager->SetSaved(0);
	
	Point P1,P2;
	int count = 0;
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 pGUI->PrintMessage("Select figure to move");	
	 CFigure *selected;
	 do
	 {
		 pGUI->GetPointClicked(P1.x, P1.y);
		 pManager->SelectFigure(P1.x, P1.y);
		 selected = pManager->GetSelectedFig();
	 }
	 while (!selected);

	 while (!(pGUI->IsMouseClicked()))
	 {
		 count++;
		 if (count == 10000)
		 {
			 pGUI->GetMouseCord(P2.x, P2.y);
			 selected->Move(P2.x - P1.x, P2.y - P1.y);
			 P1 = P2;
			 pGUI->CreateDrawArea();
			 pManager->UpdateInterface();
			 count = 0;
		 }
	 }
	 selected->SetSelected(false);
	 pGUI->PrintMessage("Figure Moved Successfully");

	 pManager->AddAction();
	


}
