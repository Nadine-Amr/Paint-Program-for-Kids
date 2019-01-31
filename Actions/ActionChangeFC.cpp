#include "ActionChangeFC.h"


ActionChangeFC::ActionChangeFC(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeFC::Execute()
{
	pManager->SetSaved(0);
	
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 pGUI->PrintMessage("You want to change filling color, Please pick color.");
	 color GetColor =pGUI->DrawPallate();

	 CFigure* SelectedFig = pManager->GetSelectedFig();


		 if ((SelectedFig==NULL))
		 {
			 UI.IsFilled = 1;
			 UI.FillColor = GetColor;
		 }
		 else
		 {
			 SelectedFig->ChngFillClr(GetColor);
		 }
	 

	 pGUI->ClearStatusBar();
	 std::string str = "The color is (r,g,b) : ";
	 std::string Blue = std::to_string(GetColor.ucBlue);
	 std::string Red = std::to_string(GetColor.ucRed);
	 std::string Green = std::to_string(GetColor.ucGreen);
	 str.append("(");
	 str.append(Red);
	 str.append(",");
	 str.append(Green);
	 str.append(",");
	 str.append(Blue);
	 str.append(")");
	 pGUI->PrintMessage(str);
	 pGUI->CreateDrawToolBar();

	 pManager->AddAction();


}
