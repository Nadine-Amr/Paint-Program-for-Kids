#include "ActionAddEllipse.h"
#include "../Figures/CEllipse.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	pManager->SetSaved(0);
	
	Point P1, P2, P3;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo EllipGfxInfo;
	EllipGfxInfo.isFilled = UI.IsFilled;	//default is not filled
											//get drawing, filling colors and pen width from the interface
	EllipGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	EllipGfxInfo.FillClr = pGUI->getCrntFillColor();
	EllipGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Ellipse data from the user

	pGUI->PrintMessage("New Ellipse: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Ellipse: Set major axis horizontally");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->PrintMessage("New Ellipse: Set semi-minor axis");
	//Read 3nd point and store in point P3
	pGUI->GetPointClicked(P3.x, P3.y);

	pGUI->ClearStatusBar();

	if (P1.x == P2.x && P1.y == P2.y || P1.x == P3.x && P1.y == P3.y || P3.x == P2.x && P3.y == P2.y)
	{
		pGUI->PrintMessage("NO Elipse is Drawn: The two clicked points are the same");
		return;
	}

	//Step 2 - prepare ellipse data
	//2.1- Set the left major point
	Point LeftMajor;
	LeftMajor.x = P1.x<P2.x ? P1.x : P2.x;
	LeftMajor.y = (P1.y + P2.y) / 2;

	//2.2- Calcuate ellipse major and minor
	int Major = abs(P1.x - P2.x);
	int Minor = 2 * abs(P3.y - LeftMajor.y);

	if (LeftMajor.y + Minor < (UI.height - UI.StatusBarHeight) && LeftMajor.y - Minor > UI.ToolBarHeight)
	{
		//Step 3 - Create an ellipse with the parameters read from the user
		CEllipse *R = new CEllipse(LeftMajor, Major, Minor, EllipGfxInfo);

		//Step 4 - Add the ellipse to the list of figures
		pManager->AddFigure(R);
	}
	else
	{
		pGUI->PrintMessage("The ellipse exceeds the dimensions of the window");
	}
	pManager->AddAction();
}