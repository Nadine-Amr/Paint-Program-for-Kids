#include "ActionAddHexagon.h"
#include "../Figures/CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <math.h>

ActionAddHexagon::ActionAddHexagon(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	pManager->SetSaved(0);
	
	Point P1,P2;

	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();


	GfxInfo HexGfxInfo;
	HexGfxInfo.isFilled = UI.IsFilled;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	
	//Step 1 - Read Hexagon data from the user

	pGUI->PrintMessage("New Hexagon: Choose top left corner");	
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Hexagon: Choose bottom right corner");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->ClearStatusBar();
	if (P1.x == P2.x && P1.y == P2.y)
	{
		pGUI->PrintMessage("NO Hexagon is Drawn: The two clicked points are the same");
		return;
	}
	//Step 2 - prepare hexagon data
	//User has entered two points P1&P2
	int* Px = new int[6];
	int* Py = new int[6];
	Point Center;
	Py[0] = P1.y<P2.y ? P1.y : P2.y;
	Px[0] = P1.x<P2.x ? P1.x : P2.x;
	Px[3] = P1.x>P2.x ? P1.x : P2.x;
	Py[3] = Py[0] + 2 * abs(P1.x - P2.x)* sqrt(3) / 2;
	Center.x = (Px[0] + Px[3]) / 2;
	Center.y = (Py[0] + Py[3]) / 2;
	double Radius = sqrt(pow(Px[0] - Center.x, 2) + pow(Py[0] - Center.y, 2));
	Px[1] = Px[3];
	Py[1] = Py[0];
	Px[5] = Center.x - Radius;
	Py[5] = Center.y;
	Px[2] = Center.x + Radius;
	Py[2] = Center.y;
	Px[4] = Px[0];
	Py[4] = Py[3];

	if (Py[0] > UI.ToolBarHeight && Py[0] < (UI.height - UI.StatusBarHeight) && Py[4] < (UI.height - UI.StatusBarHeight))
	{
		//Step 3 - Create a Hexagon with the parameters read from the user
		CHexagon *R = new CHexagon(Px, Py, HexGfxInfo);

		//Step 4 - Add the Hexagon to the list of figures
		pManager->AddFigure(R);
	}
	else
	{
		pGUI->PrintMessage("The hexagon exceeds the dimensions of the window");
	}
	pManager->AddAction();
}
