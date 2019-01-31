#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include <fstream>
#include <string>

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxFigCount = 200 };	//Max no of figures
	enum { MaxActions = 200 };	//Max no of actions for do/redo (not consecutive)


private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* DrawFigList[MaxFigCount];	//List of all figures (Array of pointers)
	string ActionsList[MaxActions];
	bool isNew = 1;
	int ActionCounter = 0; //Actual number of actions
	//Pointers to Input and Output classes
	GUI* pGUI;
	bool Saved;  //Current graph is saved

public:	
	
	ApplicationManager(); 
	~ApplicationManager();

	bool ExitFlag = 0;
	int GetMaxFigCount();
	void Run();		//to run the application
	// -- Action-Related Functions
	int UndoCount = 0;
	int RedoCount = 0;
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	int ShapeFigList(string SHAPE);
	// -- Figures Management Functions
	void AddAction();  //
	int ColorShapeFigList(color* Col, string FigType); //return number of specific type and color figures
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void SelectFigure(int x, int y);  //Helper function for action select
	void SelectMany(int x, int y);  //Helper function for multiple delete
	void RemoveFigure(int id); //set pointer of figure (id) to NULL (PLAYING MODE)
	CFigure* GetSelectedFig() const; //Get pointer to the selected figure
	void StartPlay(); //Store the figures of drawmode in temp. array of 
	void StartDraw(); //get the original array of pointers to figures of drawmode
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window
	int ColorFigList(color* Col); //return number of colored figures with certain color
	int getActionCounter() const;
	void setActionCounter(int x);
	string GetAction(int i) const;
	void SaveAll(fstream &Outfile); //Saves the drawing window information
	int GetFigCount();
	void ClearFigList();  //It clears figlist
	void SetSaved(bool);
	bool isSaved();
	void FrontBack(int, bool);  //Helper function for send to back and bring to front actions
	void DeleteFig(int);  //Helper function for action delete
};

#endif