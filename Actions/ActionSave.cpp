#include "ActionSave.h"
#include <fstream>
#include <string>

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSave::ActionSave(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionSave::Execute()
{
	pManager->SetSaved(1);
	
	// check if file exists & clr it  
	
	//Get a Pointer to the Interface
	 GUI* pGUI = pManager->GetGUI();
	 pGUI->ClearStatusBar();
	 pGUI->PrintMessage("You want to save file; please enter the file name");
	 string savefilename = pGUI->GetSrting() + ".txt";
	 fstream savefile;
	 savefile.open(savefilename, ios::out);

	 if (savefile) 
	 {
		 savefile.clear();
		 pManager->SaveAll(savefile);
		 pGUI->ClearStatusBar();
		 savefile.close();
		 pGUI->PrintMessage("Done saving");
	 }
	 else 
	 {
		 pGUI->PrintMessage("Error in loading file");
	 }
}
