#include "ActionRedo.h"

#include "..\ApplicationManager.h"

#include "..\Figures\CEllipse.h"

#include "..\Figures\CHexagon.h"

#include "..\Figures\CSquare.h"

#include "..\GUI\GUI.h"

#include <sstream>

ActionRedo::ActionRedo(ApplicationManager * pApp) : Action(pApp)
{}

//Execute the action
void ActionRedo::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	if ((pManager->RedoCount < ConsActions) && ((pManager->getActionCounter()-1) < 200) && pManager->GetAction(pManager->getActionCounter()+1) != "")
	{
		pManager->UndoCount = 0;
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You want to redo action");

		//Clear Figlist
		pManager->ClearFigList();

		//Load Action String
		string str = pManager->GetAction(pManager->getActionCounter() + 1);
		pManager->setActionCounter(pManager->getActionCounter() + 1);

		//Create new FigList

		std::istringstream iss(str);
		if (iss)
		{
			string word;
			int RGB[3];
			for (int i = 0; i < 3; i++)
			{
				iss >> word;
				RGB[i] = stoi(word, 0, 10);
			}
			UI.DrawColor.ucRed = RGB[0];
			UI.DrawColor.ucGreen = RGB[1];
			UI.DrawColor.ucBlue = RGB[2];

			for (int i = 0; i < 3; i++)
			{
				iss >> word;
				RGB[i] = stoi(word, 0, 10);
			}
			UI.FillColor.ucRed = RGB[0];
			UI.FillColor.ucGreen = RGB[1];
			UI.FillColor.ucBlue = RGB[2];

			for (int i = 0; i < 3; i++)
			{
				iss >> word;
				RGB[i] = stoi(word, 0, 10);
			}
			UI.BkGrndColor.ucRed = RGB[0];
			UI.BkGrndColor.ucGreen = RGB[1];
			UI.BkGrndColor.ucBlue = RGB[2];
			pGUI->CreateDrawArea();
			pGUI->DrawColor();

			GfxInfo FigGfxInfo;
			FigGfxInfo.isFilled = false;	//default is not filled
											//get drawing, filling colors and pen width from the interface
			FigGfxInfo.DrawClr = pGUI->getCrntDrawColor();
			FigGfxInfo.FillClr = pGUI->getCrntFillColor();
			FigGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

			//Figures
			iss >> word;
			int numfig = stoi(word, 0, 10);
			for (int i = 0; i < numfig; i++)
			{
				iss >> word;
				if (word == "SQR")
				{
					CSquare *R = new CSquare(iss, FigGfxInfo);
					pManager->AddFigure(R);
				}
				else if (word == "ELPS")
				{
					CEllipse *R = new CEllipse(iss, FigGfxInfo);
					pManager->AddFigure(R);
				}
				else if (word == "HEX")
				{
					CHexagon *R = new CHexagon(iss, FigGfxInfo);
					pManager->AddFigure(R);
				}
				else
				{
					pGUI->ClearStatusBar();
					pGUI->PrintMessage("Some errors occured while re-doing");
				}
			}
			pManager->RedoCount++;
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("Action successfully redone");
		}
		else
		{
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("Some errors occured while re-doing");
		}
	}
	else if (pManager->RedoCount >= ConsActions)
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You cannot redo more actions");
	}
	else if (((pManager->getActionCounter()-1) >= 200) || pManager->GetAction(pManager->getActionCounter() + 1) == "")
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("No actions to redo");
	}

}