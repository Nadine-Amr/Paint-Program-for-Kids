#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	CSquare(fstream &Infile, GfxInfo FigGfxInfo);
	CSquare(istringstream &str, GfxInfo FigGfxInfo);
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