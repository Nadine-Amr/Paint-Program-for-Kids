#include "ActionLoad.h"

#include "..\Figures\CSquare.h"

#include "..\Figures\CEllipse.h"

#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

#include <fstream>

#include <iostream>

ActionLoad::ActionLoad(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionLoad::Execute()
{
	pManager->SetSaved(1);
	
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 if (pManager->GetFigCount())  // Save if figure list in not empty
	 {
		 pGUI->PrintMessage("Do you want to save the current drawing window first? Y/N");
		 string userchoice = pGUI->GetSrting();
		 if (userchoice == "Y")
		 {
			 Action* pAct = (pManager->CreateAction(SAVE));
			 pManager->ExecuteAction(pAct);
		 }
	 }
	 pManager->ClearFigList();
	 pGUI->ClearDrawArea();

	 pGUI->PrintMessage("You want to load file; please enter the file name");
	 string loadfilename = pGUI->GetSrting() + ".txt";
	 fstream loadfile;
	 loadfile.open(loadfilename, ios::in);

	 if (loadfile)
	 {
		 string word;
		 int RGB[3];
		 for (int i = 0; i < 3; i++)
		 {
			 loadfile >> word;
			 RGB[i] = stoi(word, 0, 10);
		 }
		 UI.DrawColor.ucRed = RGB[0];
		 UI.DrawColor.ucGreen = RGB[1];
		 UI.DrawColor.ucBlue = RGB[2];

		 for (int i = 0; i < 3; i++)
		 {
			 loadfile >> word;
			 RGB[i] = stoi(word, 0, 10);
		 }
		 UI.FillColor.ucRed = RGB[0];
		 UI.FillColor.ucGreen = RGB[1];
		 UI.FillColor.ucBlue = RGB[2];

		 for (int i = 0; i < 3; i++)
		 {
			 loadfile >> word;
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
		 loadfile >> word;
		 int numfig = stoi(word, 0, 10);
		 for (int i = 0; i < numfig; i++) 
		 {
			 loadfile >> word;
			 if (word == "SQR") 
			 {
				 CSquare *R = new CSquare(loadfile,FigGfxInfo);
				 pManager->AddFigure(R);
				 pGUI->PrintMessage("Loaded successfully");
			 }
			 else if (word == "ELPS")
			 {
				 CEllipse *R = new CEllipse(loadfile, FigGfxInfo);
				 pManager->AddFigure(R);
				 pGUI->PrintMessage("Loaded successfully");
			 }
			 else if (word == "HEX")
			 {
				 CHexagon *R = new CHexagon(loadfile, FigGfxInfo);
				 pManager->AddFigure(R);
				 pGUI->PrintMessage("Loaded successfully");
			 } 
			 else 
			 {
				 pGUI->PrintMessage("Some errors occured while loading");
			 }
		 }
	 }
	 else
	 {
		 pGUI->PrintMessage("Error loading file");
	 }
}
