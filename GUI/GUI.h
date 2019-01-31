#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"



//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
	Point CurrentClick;  //Current mouse click postion
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	bool GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType(int x, int y);//Read the user click and map to an action

	/////////// Output Functoinality  ////////////////
	void CreateDrawArea() const;
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	color DrawPallate();  //Draw Colo Pallate to allow user to pick one color
	color GetColors(const int x, const int y) const;  //Return color  of given x and y for mouse in the window
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void DrawColor() const;  //Draw Drawing, Filling and background Colors in the toolmenue 
	void ShowScore(int score[2]) const;  //Show how many wrong and how many right in playmode
	void ClearScore(bool Case) const;  //Reset the score to 0 rights and 0 wrongs
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a Square
	void DrawEllip(Point P1, int major, int minor, GfxInfo EllipGfxInfo, bool selected = false) const;  //Draw an Ellipse
	void DrawHex(int* Px, int* Py, GfxInfo HexGfxInfo, bool selected = false) const; //Draw a Hexagon
	///TODO: Make similar functions for drawing all other figures.
	void GetMouseCord(int &x, int &y);
	void PrintMessage(string msg) const;	//Print a message on Status bar
	bool IsMouseClicked();
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color 
  	color getCrntBkGrndColor() const;  //get current background color
	int getCrntPenWidth() const;		//get current pen width


};


#endif