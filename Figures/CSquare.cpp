#include "CSquare.h"
#include <sstream>
#include <iostream>

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	
}
	
CSquare::CSquare(fstream &InFile, GfxInfo  FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Load(InFile);
}

CSquare::CSquare(istringstream &str, GfxInfo  FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Load(str);
}

void CSquare::Move(int x, int y)
{
	TopLeftCorner.x += x;
	TopLeftCorner.y += y;

	if (TopLeftCorner.y < UI.ToolBarHeight)
		TopLeftCorner.y = UI.ToolBarHeight + 2;

	if (TopLeftCorner.y + length > UI.height - UI.StatusBarHeight)
		TopLeftCorner.y = UI.height - UI.StatusBarHeight - length - 2;
	if (TopLeftCorner.x  < 2)
		TopLeftCorner.x = 2;

	if (TopLeftCorner.x + length > UI.width - 2)
		TopLeftCorner.x = UI.width - length - 2;
}
void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

string CSquare::FigType()
{
	string Fig_Type = "SQUARE";
	return Fig_Type;
}

bool CSquare::IsInside(int x, int y)
{
	if (x >= TopLeftCorner.x && x <= (TopLeftCorner.x + length) && y >= TopLeftCorner.y && y <= (TopLeftCorner.y + length))
	{
		return true;
	}
	return false;
}

void CSquare::Save(fstream &OutFile, int id) 
{
	OutFile << "SQR " << id << " " << TopLeftCorner.x << " " << TopLeftCorner.y << " " << length << " " << (FigGfxInfo.isFilled? "1" : "0") << " " <<  std::to_string(FigGfxInfo.DrawClr.ucRed) << " " << std::to_string(FigGfxInfo.DrawClr.ucGreen) << " " << std::to_string(FigGfxInfo.DrawClr.ucBlue) << " " << std::to_string(FigGfxInfo.FillClr.ucRed) << " " << std::to_string(FigGfxInfo.FillClr.ucGreen) << " " << std::to_string(FigGfxInfo.FillClr.ucBlue) << "\n";
}

string CSquare::action() const
{
	return("SQR " + std::to_string(ID) + " " + std::to_string(TopLeftCorner.x) + " " + std::to_string(TopLeftCorner.y) + " " + std::to_string(length) + " " + std::to_string(FigGfxInfo.isFilled) + " " + std::to_string(FigGfxInfo.DrawClr.ucRed) + " " + std::to_string(FigGfxInfo.DrawClr.ucGreen) + " " + std::to_string(FigGfxInfo.DrawClr.ucBlue) + " " + std::to_string(FigGfxInfo.FillClr.ucRed) + " " + std::to_string(FigGfxInfo.FillClr.ucGreen) + " " + std::to_string(FigGfxInfo.FillClr.ucBlue) + "\n");
}

void CSquare::Load(fstream &InFile)
{
	string word;
	InFile >> word; //retrieving ID which is the same as the index of the figure in FigList
	InFile >> word; TopLeftCorner.x = stoi(word, 0, 10);
	InFile >> word; TopLeftCorner.y = stoi(word, 0, 10);
	InFile >> word; length = stoi(word, 0, 10);
	InFile >> word; FigGfxInfo.isFilled = stoi(word, 0, 2);
	

	int RGB[3];
	for (int i = 0; i < 3; i++)
	{
		InFile >> word;
		RGB[i] = stoi(word, 0, 10);
	}
	FigGfxInfo.DrawClr.ucRed = RGB[0];
	FigGfxInfo.DrawClr.ucGreen = RGB[1];
	FigGfxInfo.DrawClr.ucBlue = RGB[2];
	
	for (int i = 0; i < 3; i++)
	{
		InFile >> word;
		RGB[i] = stoi(word, 0, 10);
	}
	FigGfxInfo.FillClr.ucRed = RGB[0];
	FigGfxInfo.FillClr.ucGreen = RGB[1];
	FigGfxInfo.FillClr.ucBlue = RGB[2];
	
}

void CSquare::Load(istringstream &str)
{
	string word;
	str >> word; ID = stoi(word, 0, 10); //retrieving ID which is the same as the index of the figure in FigList
	str >> word; TopLeftCorner.x = stoi(word, 0, 10);
	str >> word; TopLeftCorner.y = stoi(word, 0, 10);
	str >> word; length = stoi(word, 0, 10);
	str >> word; FigGfxInfo.isFilled = stoi(word, 0, 2);


	int RGB[3];
	for (int i = 0; i < 3; i++)
	{
		str >> word;
		RGB[i] = stoi(word, 0, 10);
	}
	FigGfxInfo.DrawClr.ucRed = RGB[0];
	FigGfxInfo.DrawClr.ucGreen = RGB[1];
	FigGfxInfo.DrawClr.ucBlue = RGB[2];

	for (int i = 0; i < 3; i++)
	{
		str >> word;
		RGB[i] = stoi(word, 0, 10);
	}
	FigGfxInfo.FillClr.ucRed = RGB[0];
	FigGfxInfo.FillClr.ucGreen = RGB[1];
	FigGfxInfo.FillClr.ucBlue = RGB[2];
}

void CSquare::PrintInfo(GUI* pGUI)
{
	string info = "The selected figure is a ";
	info += "square. ID: " + std::to_string(ID) + " Top-Left Corner: " + std::to_string(TopLeftCorner.x) + " " + std::to_string(TopLeftCorner.y) + " Length: " + std::to_string(length);
	if (FigGfxInfo.isFilled)
	{
		info += " DrawColor: " + std::to_string(FigGfxInfo.DrawClr.ucRed) + " " + std::to_string(FigGfxInfo.DrawClr.ucGreen) + " " + std::to_string(FigGfxInfo.DrawClr.ucBlue) + " FilColor: " + std::to_string(FigGfxInfo.FillClr.ucRed) + " " + std::to_string(FigGfxInfo.FillClr.ucGreen) + " " + std::to_string(FigGfxInfo.FillClr.ucBlue);
	}
	else
	{
		info += " DrawColor: " + std::to_string(FigGfxInfo.DrawClr.ucRed) + " " + std::to_string(FigGfxInfo.DrawClr.ucGreen) + " " + std::to_string(FigGfxInfo.DrawClr.ucBlue);
	}
	pGUI->PrintMessage(info);
}

bool CSquare::Resize(double A)
{
	if (TopLeftCorner.y > UI.ToolBarHeight && TopLeftCorner.y < (UI.height - UI.StatusBarHeight) && (TopLeftCorner.y + A * length) < (UI.height - UI.StatusBarHeight))
	{
		length *= A;
		return 1;
	}
	return 0;
}