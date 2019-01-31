#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

CFigure::CFigure()
{

}

void CFigure::SetSelected(bool s)
{	
	Selected = s;
}

int CFigure::getid() const
{
	return ID;
}

void CFigure::setid(int id)
{
	ID=id;
}
bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::isFilled()
{
	return FigGfxInfo.isFilled;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

bool CFigure::Iscolor(color COLOR) const
{
	if (FigGfxInfo.isFilled)
	{
		if (FigGfxInfo.FillClr.ucBlue == COLOR.ucBlue && FigGfxInfo.FillClr.ucGreen == COLOR.ucGreen && FigGfxInfo.FillClr.ucRed == COLOR.ucRed)
			return true;
		else return false;
	}

	else
	{
		if (WHITE.ucBlue == COLOR.ucBlue && WHITE.ucGreen == COLOR.ucGreen && WHITE.ucRed == COLOR.ucRed)
			return true;
		else return false;
	}
}