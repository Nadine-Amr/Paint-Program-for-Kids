#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <string>

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	virtual bool IsInside(int, int) = 0;
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	bool isFilled();
	int getid() const;
	bool Iscolor(color COLOR) const;
	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	virtual void Move(int x, int y) = 0;
	virtual string action() const = 0; //return string data of figure for do/redo
	void setid(int id);
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual string FigType() = 0;

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	virtual bool Resize(double) = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(fstream &OutFile, int id) = 0;	//Save the figure parameters to the file
	virtual void Load(fstream &Infile) = 0;	//Load the figure parameters to the file
	virtual void Load(istringstream &str) = 0; //Load from Action String do/redo

	virtual void PrintInfo(GUI*) = 0;	//print important figure info on the status bar
};

#endif