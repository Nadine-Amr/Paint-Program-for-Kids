#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\ActionChangeDC.h"
#include "Actions\ActionChangeFC.h"
#include "Actions\ActionResize.h"
#include "Actions\ActionSendBack.h"
#include "Actions\ActionBringFront.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionGetColor.h"
#include "Actions\ActionDelete.h"
#include "Actions\ActionPlayMode.h"
#include "Actions\ActionDrawMode.h"
#include "Actions\ActionMove.h"
#include "Actions\ActionRedo.h"
#include "Actions\ActionUndo.h"
#include "Actions\ActionRotate.h"
#include "Actions\ActionColor.h"
#include "Actions\ActionFig.h"
#include "Actions\ActionFigColor.h"
#include "Actions\ActionRestart.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionExit.h"
#include <string>
#include <iostream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType(UI.PointX,UI.PointY);

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(!ExitFlag);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			for (int i = 0; i < FigCount; i++)
			{
				FigList[i]->SetSelected(false);
			}
			newAct = new ActionAddSquare(this);
			//AddAction();
			break;

		case DRAW_ELPS:
			for (int i = 0; i < FigCount; i++)
			{
				FigList[i]->SetSelected(false);
			}
			newAct = new ActionAddEllipse(this);
			//AddAction();
			break;

		case DRAW_HEX:
			for (int i = 0; i < FigCount; i++)
			{
				FigList[i]->SetSelected(false);
			}
			newAct = new ActionAddHexagon(this);
			//AddAction();
			break;

		case CHNG_DRAW_CLR:
			newAct = new ActionChangeDC(this);
			//AddAction();
			break;

		case CHNG_FILL_CLR:
			newAct = new ActionChangeFC(this);
			//AddAction();
			break;

		case RESIZE:
			newAct = new ActionResize(this);
			//AddAction();
			break;

		case SEND_BACK:
			newAct = new ActionSendBack(this);
			//AddAction();
			break;

		case BRNG_FRNT:
			newAct = new ActionBringFront(this);
			//ActionCounter++;
			break;

		case SAVE:
			newAct = new ActionSave(this);
			//AddAction();
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			//AddAction();
			break;

		case GET_COLOR:
			newAct = new ActionGetColor(this);
			//AddAction();
			break;

		case TO_PLAY:
			newAct = new ActionPlayMode(this);
			//AddAction();
			break;
		case TO_DRAW:
			newAct = new ActionDrawMode(this);
			//AddAction();
			break;

		case DEL:
			newAct = new ActionDelete(this);
			//AddAction();
			break;

		case MOVE:
			newAct = new ActionMove(this);
			//AddAction();
			break;

		case REDO:
			newAct = new ActionRedo(this);
			//AddAction();
			break;
		case UNDO:
			newAct = new ActionUndo(this);
			//AddAction();
			break;

		case FIG:
			newAct = new ActionFig(this);
			//AddAction();
			break;
		case FIG_COLOR:
			newAct = new ActionFigColor(this);
			//AddAction();
			break;
		case COLOR:
			newAct = new ActionColor(this);
			//AddAction();
			break;
		case RESTART:
			newAct = new ActionRestart(this);
			//AddAction();
			break;
		case EXIT:
			newAct = new ActionExit(this);
			
			break;

		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			//AddAction();
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//////////////////////////////////////////////////////////////////////
//Add action to action list
void ApplicationManager::AddAction()
{
	UndoCount = 0;
	RedoCount = 0;

	if (isNew)
	{
		string str = "";
		//Default Draw Color BLUE1 = color(2, 113, 156);
		//Defult  Fill Color GOLD = color(206, 188, 0);
		//Default Background Color BINKBODY = color(242, 211, 182);
		str += "2 113 156 206 188 0 242 211 182\n";
		str += "0\n";
		ActionsList[0] = str;
		isNew = 0;
		ActionCounter++;
	}

	if (ActionCounter >= MaxActions)
	{
		for (int i = 0; i < ActionCounter - 1; i++)
		{
			ActionsList[i] = ActionsList[i + 1];
		}
		ActionsList[ActionCounter - 1] = "";
		ActionCounter--;
	}
	else
	{
		for (int i = ActionCounter; i < MaxActions; i++)
		{
			ActionsList[i] = "";
		}
	}
	string str = "";

	str += std::to_string(pGUI->getCrntDrawColor().ucRed) + " " + std::to_string(pGUI->getCrntDrawColor().ucGreen) + " " + std::to_string(pGUI->getCrntDrawColor().ucBlue) + " ";
	str += std::to_string(pGUI->getCrntFillColor().ucRed) + " " + std::to_string(pGUI->getCrntFillColor().ucGreen) + " " + std::to_string(pGUI->getCrntFillColor().ucBlue) + " ";
	str += std::to_string(pGUI->getCrntBkGrndColor().ucRed) + " " + std::to_string(pGUI->getCrntBkGrndColor().ucGreen) + " " + std::to_string(pGUI->getCrntBkGrndColor().ucBlue) + " \n";
	str += std::to_string(FigCount) + "\n";

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i])
			str += FigList[i]->action();
	}
	ActionsList[ActionCounter] = str;
	//std::cout << str << endl << endl;
	ActionCounter++;
}

string ApplicationManager::GetAction(int i) const
{
	return ActionsList[i-1];
}

int ApplicationManager::getActionCounter() const
{
	return ActionCounter;
}

void ApplicationManager::setActionCounter(int x)
{
	ActionCounter = x;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		pFig->setid(FigCount);
		FigList[FigCount++] = pFig;
	}
}

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i])
		{
			if (FigList[i]->IsInside(x, y))
			{
				return FigList[i];
			}
		}
	}
	return NULL;
}

CFigure *ApplicationManager::GetSelectedFig() const
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i])
		{
			if (FigList[i]->IsSelected())
			{
				return FigList[i];
			}
		}
	}
	return NULL;
}

void ApplicationManager::SelectFigure(int x, int y)
{

	CFigure* SelectedFig;
	SelectedFig = GetFigure(x, y);
	if (SelectedFig)
	{
		if (SelectedFig->IsSelected())
		{
			for (int i = 0; i < FigCount; i++)
			{
				if (FigList[i])
					FigList[i]->SetSelected(false);
			}
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("You unselected this figure");
		}
		else
		{
			for (int i = 0; i < FigCount; i++)
			{
				if (FigList[i])
				{
					FigList[i]->SetSelected(false);
					if (i == SelectedFig->getid())
					{
						SelectedFig->SetSelected(true);
					}
				}
			}
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("You selected this figure");
		}
		SelectedFig->PrintInfo(pGUI);
	}
	else
	{
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i])
				FigList[i]->SetSelected(false);
		}
		pGUI->ClearStatusBar();
	}
}

void ApplicationManager::SelectMany(int x, int y)
{
	CFigure* SelectedFig;
	SelectedFig = GetFigure(x, y);
	if (SelectedFig)
	{
		if (SelectedFig->IsSelected())
		{
			SelectedFig->SetSelected(0);
			pGUI->ClearStatusBar();
			UpdateInterface();
			pGUI->PrintMessage("You unselected this figure");
		}
		else
		{
			SelectedFig->SetSelected(1);
			pGUI->ClearStatusBar();
			UpdateInterface();
			pGUI->PrintMessage("You selected this figure");
		}
	}
}

int ApplicationManager::ColorFigList(color* Col)
{
	int ColorCount = 0; //Number of colored figures of certail color

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i])
		{
			for (int j = 0; j < 2; j++)

				if (FigList[i]->Iscolor(Col[j]))
				{
				ColorCount += 1;
				}
		}	
	}

	return ColorCount;
}

int ApplicationManager::ColorShapeFigList(color* Col, string FigType)
{
	int ColorTypeCount = 0;

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i])
		{
			for (int j = 0; j < sizeof(Col); j++)

			if ((FigList[i]->Iscolor(Col[j])) && (FigList[i]->FigType() == FigType))
			{
				ColorTypeCount += 1;
			}
		}
	}

	return ColorTypeCount;
}

int ApplicationManager::ShapeFigList(string SHAPE)
{
	int Typecount = 0;

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] && FigList[i]->FigType() == SHAPE)
			Typecount++;
	}

	return Typecount;

}

void ApplicationManager::RemoveFigure(int id)
{
	FigList[id]=NULL;

}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
	if (FigList[i])
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }

void ApplicationManager::StartPlay() 
{
	for (int i = 0; i < FigCount; i++)
		DrawFigList[i] = FigList[i];
}

void ApplicationManager::StartDraw()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = DrawFigList[i];
		FigList[i]->SetSelected(false);
	}
}
void ApplicationManager::SaveAll(fstream &Outfile) 
{
	Outfile << std::to_string(pGUI->getCrntDrawColor().ucRed) << " " << std::to_string(pGUI->getCrntDrawColor().ucGreen) << " " << std::to_string(pGUI->getCrntDrawColor().ucBlue) << " ";
	Outfile << std::to_string(pGUI->getCrntFillColor().ucRed) << " " << std::to_string(pGUI->getCrntFillColor().ucGreen) << " " << std::to_string(pGUI->getCrntFillColor().ucBlue) << " ";
	Outfile << std::to_string(pGUI->getCrntBkGrndColor().ucRed) << " " << std::to_string(pGUI->getCrntBkGrndColor().ucGreen) << " " << std::to_string(pGUI->getCrntBkGrndColor().ucBlue) << " \n";
	Outfile << FigCount << "\n";

	for (int i=0; i<FigCount; i++) 
	{ 
		FigList[i]->Save(Outfile, i);
	}
}

int ApplicationManager::GetFigCount()
{

	return FigCount;
}

void ApplicationManager::SetSaved(bool x)
{
	Saved = x;
}

bool ApplicationManager::isSaved()
{
	return Saved;
}

void ApplicationManager::ClearFigList()
{
	for (int i = 0; i<FigCount; i++)
		delete FigList[i];
	FigCount = 0;
}

void ApplicationManager::DeleteFig(int id)
{
	for (int i = id; i < FigCount - 1; i++)
	{
		FigList[i] = FigList[i + 1];
		FigList[i]->setid(i);
	}
	FigList[FigCount - 1] = NULL;
	FigCount--;
}

void ApplicationManager::FrontBack(int id, bool fb)
{
	if (fb)
	{
		FigList[FigCount] = FigList[id];
		for (int i = id; i < FigCount - 1; i++)
		{
			FigList[i + 1]->setid(FigList[i + 1]->getid() - 1);
			FigList[i] = FigList[i + 1];
		}
		FigList[FigCount - 1] = FigList[FigCount];
		FigList[FigCount - 1]->setid(FigCount - 1);
		FigList[FigCount] = NULL;
	}
	else
	{
		FigList[FigCount] = FigList[id];
		for (int i = id; i > 0; i--)
		{
			FigList[i - 1]->setid(FigList[i - 1]->getid() + 1);
			FigList[i] = FigList[i - 1];
		}
		FigList[0] = FigList[FigCount];
		FigList[0]->setid(0);
		FigList[FigCount] = NULL;
	}
}

int ApplicationManager::GetMaxFigCount()
{
	return MaxFigCount;
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
