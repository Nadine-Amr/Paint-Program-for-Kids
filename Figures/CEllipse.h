#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "..\Figures\CFigure.h"

class CEllipse : public CFigure
{
private:
	Point LeftMajor;
	int Major;
	int Minor;
public:
	CEllipse(Point, int, int, GfxInfo FigureGfxInfo);
	CEllipse(fstream &Infile, GfxInfo FigureGfxInfo);
	CEllipse(istringstream &str, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool IsInside(int, int);
	virtual void Move(int x, int y);
	virtual string action() const;
	virtual string FigType();
	virtual void Save(fstream &OutFile, int id);
	virtual void Load(fstream &Infile);
	virtual void Load(istringstream &str);
	virtual void PrintInfo(GUI*);
	virtual bool Resize(double);
};

#endif