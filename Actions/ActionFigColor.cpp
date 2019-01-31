#include "ActionFigColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"


ActionFigColor::ActionFigColor(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFigColor::Execute()
{
	pManager->SetSaved(0);
	
	GUI* pGUI = pManager->GetGUI();
	if (pManager->GetFigCount())
	{

		//Get a Pointer to the Interface

		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You shall pick figures based only on both the Selected Color & Shape");

		srand(time(NULL));
		int Color;  //random number from 0 to 10 for Figure colors
		int Shape; //random number from 0 to 2 for Figure Shapes

		int FiguresRemain;
		string COLOR, SHAPE, TYPE;
		color Col[2];
		CFigure* Selected;
		bool answer;
		int Score[2] = { 0, 0 };

		do
		{
			Color = rand() % 13;
			Shape = rand() % 3;

			switch (Color)
			{
			case 0:
				COLOR = "YELLOW";
				Col[0] = YELLOW;
				Col[1] = GOLD;
				break;
			case 1:
				COLOR = "BLUE";
				Col[0] = DEEPSKYBLUE;
				Col[1] = BLUE1;
				break;
			case 2:
				COLOR = "Green";
				Col[0] = MEDIUMSPRINGGREEN;
				Col[1] = GREEN1;
				break;
			case 3:
				COLOR = "Orange";
				Col[0] = ORANGE;
				Col[1] = DARKORANGE;
				break;
			case 4:
				COLOR = "PURBLE";
				Col[0] = PURPLE;
				Col[1] = PURPLE1;
				break;
			case 5:
				COLOR = "VIOLET ";
				Col[0] = VIOLET;
				Col[1] = VIOLET1;
				break;
			case 6:
				COLOR = "MAGENTA";
				Col[0] = MAGENTA;
				Col[1] = DARKMAGENTA;
				break;
			case 7:
				COLOR = "GRAY";
				Col[0] = GREY;
				Col[1] = BROWN; //unused color
				break;
			case 8:
				COLOR = "BROWN";
				Col[0] = ROSYBROWN;
				Col[1] = BROWN;
				break;
			case 9:
				COLOR = "BINKBODY";
				Col[0] = BINKBODY;
				Col[1] = BROWN;
				break;
			case 10:
				COLOR = "BLACK";
				Col[0] = BLACK;
				Col[1] = BROWN;
				break;
			case 11:
				COLOR = "RED";
				Col[0] = RED;
				Col[1] = RED1;
				break;
			case 12:
				COLOR = "UNFILLED";
				Col[0] = WHITE; //White for unfilled Color
				Col[1] = BROWN;
				break;
			}

			switch (Shape)
			{
			case 0:
				SHAPE = "SQUARE";
				break;
			case 1:
				SHAPE = "ELLIPSE";
				break;
			case 2:
				SHAPE = "HEXAGON";
				break;
			}
			FiguresRemain = pManager->ColorShapeFigList(Col,SHAPE);


		} while (!FiguresRemain);


		pGUI->PrintMessage("Pick all " + COLOR + " " + SHAPE + " Figures");

		while (FiguresRemain)
		{
			pGUI->PrintMessage("Pick all " + COLOR + " " + SHAPE + " Figures");
			Point P1;

			if (pGUI->GetPointClicked(P1.x, P1.y)) //Break if restart or DM is pressed
			{
				UI.PointX = P1.x;
				UI.PointY = P1.y;
				break;
			}

			pManager->SelectFigure(P1.x, P1.y);
			Selected = pManager->GetSelectedFig();



			if (Selected)

			{
				if ((Selected->Iscolor(Col[0]) || Selected->Iscolor(Col[1])) && (Selected->FigType() == SHAPE))
				{
					answer = true;
					FiguresRemain--;
				}
				else
				{
					answer = false;
				}
				pManager->RemoveFigure(Selected->getid());
				pGUI->CreateDrawArea();
				pManager->UpdateInterface();

				if (answer)
					Score[0] += 1;
				else
					Score[1] += 1;
				pGUI->ShowScore(Score);

			}
		}

		pGUI->PrintMessage("Your Score is " + to_string(Score[0]) + " RIGHT and " + to_string(Score[1]) + " WRONG");
		Score[0] = 0;
		Score[1] = 0;
		pGUI->ShowScore(Score);
		pManager->StartDraw();
		pManager->UpdateInterface();
	}
	else
		pGUI->PrintMessage("Please Draw figures in draw mode of load a file to start play");

	pManager->AddAction();
	
}
