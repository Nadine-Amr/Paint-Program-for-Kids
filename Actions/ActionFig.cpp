#include "ActionFig.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionFig::ActionFig(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFig::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	if (pManager->GetFigCount())
	{

	pGUI->ClearStatusBar();
	pGUI->PrintMessage("You shall pick figures based only on their Shapes");
	srand(time(NULL));
	int Shape; //random number from 0 to 2 for Figure Shapes

	int FiguresRemain;
	string SHAPE, TYPE;

	CFigure* Selected;
	bool answer;
	int Score[2] = { 0, 0 };

	do
	{
		Shape = rand() % 3; 
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

		FiguresRemain = pManager->ShapeFigList(SHAPE);

	} while (!FiguresRemain);


	pGUI->PrintMessage("Pick all " + SHAPE);

	while (FiguresRemain)
	{
		pGUI->PrintMessage("Pick all " + SHAPE);

		Point P1;
		if (pGUI->GetPointClicked(P1.x, P1.y))
		{
			UI.PointX = P1.x;
			UI.PointY = P1.y;
			break;
		}
		pManager->SelectFigure(P1.x, P1.y);
		Selected = pManager->GetSelectedFig();

		answer = false;

		if (Selected != NULL)

		{
			if (Selected->FigType() == SHAPE)
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
		pGUI->PrintMessage("Please Draw figures in drawe mode or load a file to start playing");

	pManager->AddAction();
}
