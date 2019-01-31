#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "..\Figures\CFigure.h"

class CHexagon : public CFigure
{
private:
	int* PX;
	int* PY;
public:
	CHexagon(int*, int*, GfxInfo FigureGfxInfo);
	CHexagon(fstream &Infile, GfxInfo FigureGfxInfo);
	CHexagon(istringstream &str, GfxInfo FigureGfxInfo);
	~CHexagon();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Move(int x, int y);
	virtual bool IsInside(int, int);
	virtual string action() const;
	virtual string FigType();
	virtual void Save(fstream &OutFile, int id);
	virtual void Load(fstream &Infile);
	virtual void Load(istringstream &str);
	virtual void PrintInfo(GUI*);
	void PrintPoints();
	virtual bool Resize(double);
};

#endif