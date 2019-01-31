#include "ActionChangeDC.h"


ActionChangeDC::ActionChangeDC(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeDC::Execute()
{
	pManager->SetSaved(0);
	
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 pGUI->PrintMessage("You want to change drawing color, Please pick color.");
	 CFigure* SelectedFig = pManager->GetSelectedFig();

	 color GetColor = pGUI->DrawPallate();


	 if ((SelectedFig == NULL))
	 {
		 UI.IsFilled = 0;
		 UI.DrawColor = GetColor;
	 }
	 else
	 {
		 SelectedFig->ChngDrawClr(GetColor);
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
