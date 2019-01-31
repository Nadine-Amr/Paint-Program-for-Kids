#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddSquare::ActionAddSquare(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionAddSquare::Execute() 
{
	pManager->SetSaved(0);
	
	Point P1,P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = UI.IsFilled;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	pGUI->PrintMessage("New Square: Click at first point");	
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Square: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->ClearStatusBar();

	if (P1.x == P2.x && P1.y == P2.y)
	{
		pGUI->PrintMessage("NO Square is Drawn: The two clicked points are the same");
		return;
	}
	//Step 2 - prepare square data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the square
	Point topLeft ;
	topLeft.y = P1.y<P2.y ? P1.y : P2.y;
	topLeft.x = P1.x<P2.x? P1.x: P2.x;

	//2.2- Calcuate square side legnth
	//The square side length would be the longer distance between the two points coordinates
	int SideLength = max(abs(P1.x-P2.x), abs(P1.y-P2.y));

	if (topLeft.y > UI.ToolBarHeight && topLeft.y < (UI.height - UI.StatusBarHeight) && (topLeft.y + SideLength) < (UI.height - UI.StatusBarHeight))
	{
		//Step 3 - Create a Square with the parameters read from the user
		CSquare *R = new CSquare(topLeft, SideLength, SqrGfxInfo);

		//Step 4 - Add the Square to the list of figures
		pManager->AddFigure(R);
	}
	else
	{
		pGUI->PrintMessage("The square exceeds the dimensions of the window");
	}
	pManager->AddAction();
}
