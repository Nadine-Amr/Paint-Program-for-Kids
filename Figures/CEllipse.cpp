#include "CEllipse.h"
#include <sstream>
#include <fstream>

CEllipse::CEllipse(Point P1, int major, int minor, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	LeftMajor = P1;
	Major = major;
	Minor = minor;
}

CEllipse::CEllipse(fstream &InFile, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Load(InFile);
}

CEllipse::CEllipse(istringstream &str, GfxInfo  FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Load(str);
}

void CEllipse::Move(int x, int y)
{
	LeftMajor.x += x;
	LeftMajor.y += y;
	if (LeftMajor.y - Minor / 2 < UI.ToolBarHeight)
		LeftMajor.y = UI.ToolBarHeight + Minor / 2 + 2;

	if (LeftMajor.y + Minor / 2 > UI.height - UI.StatusBarHeight)
		LeftMajor.y = UI.height - UI.StatusBarHeight - Minor / 2 - 2;
	if (LeftMajor.x  < 2)
		LeftMajor.x = 2;
	if (LeftMajor.x + Major > UI.width - 2)
		LeftMajor.x = UI.width - Major - 2;
}
string CEllipse::FigType()
{
	string Fig_Type = "ELLIPSE";
	return Fig_Type;
}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw an ellipse on the screen	
	pGUI->DrawEllip(LeftMajor, Major, Minor, FigGfxInfo, Selected);
}

bool CEllipse::IsInside(int x, int y)
{
	if (4 * pow((x - (LeftMajor.x + Major/2)), 2) / pow(Major, 2) + 4 * pow((y - LeftMajor.y),2) / pow(Minor, 2) <= 1)
	{
		return true;
	}
	return false;
}


void CEllipse::Save(fstream &OutFile, int id) 
{
	OutFile << "ELPS " << id << " " << LeftMajor.x << " " << LeftMajor.y << " " << Major << " " << Minor << " " << FigGfxInfo.isFilled << " " << std::to_string(FigGfxInfo.DrawClr.ucRed) << " " << std::to_string(FigGfxInfo.DrawClr.ucGreen) << " " << std::to_string(FigGfxInfo.DrawClr.ucBlue) << " " << std::to_string(FigGfxInfo.FillClr.ucRed) << " " << std::to_string(FigGfxInfo.FillClr.ucGreen) << " " << std::to_string(FigGfxInfo.FillClr.ucBlue) << "\n";
}

string CEllipse::action() const
{
	return("ELPS " + std::to_string(ID) + " " + std::to_string(LeftMajor.x) + " " + std::to_string(LeftMajor.y) + " " + std::to_string(Major) + " " + std::to_string(Minor) + " " + std::to_string(FigGfxInfo.isFilled) + " " + std::to_string(FigGfxInfo.DrawClr.ucRed) + " " + std::to_string(FigGfxInfo.DrawClr.ucGreen) + " " + std::to_string(FigGfxInfo.DrawClr.ucBlue) + " " + std::to_string(FigGfxInfo.FillClr.ucRed) + " " + std::to_string(FigGfxInfo.FillClr.ucGreen) + " " + std::to_string(FigGfxInfo.FillClr.ucBlue) + "\n");
}

void CEllipse::Load(fstream &InFile)
{
	string word;
	InFile >> word; //retrieving ID which is the same as the index of the figure in FigList
	InFile >> word; LeftMajor.x = stoi(word, 0, 10);
	InFile >> word; LeftMajor.y = stoi(word, 0, 10);
	InFile >> word; Major = stoi(word, 0, 10);
	InFile >> word; Minor = stoi(word, 0, 10);
	InFile >> word; FigGfxInfo.isFilled = stoi(word, 0, 10);
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

void CEllipse::Load(istringstream &str)
{
	string word;
	str >> word; ID = stoi(word, 0, 10); //retrieving ID which is the same as the index of the figure in FigList
	str >> word; LeftMajor.x = stoi(word, 0, 10);
	str >> word; LeftMajor.y = stoi(word, 0, 10);
	str >> word; Major = stoi(word, 0, 10);
	str >> word; Minor = stoi(word, 0, 10);
	str >> word; FigGfxInfo.isFilled = stoi(word, 0, 10);
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

void CEllipse::PrintInfo(GUI* pGUI)
{
	string info = "The selected figure is an ";
	info += "ellipse. ID: " + std::to_string(ID) + " LeftMost Point: " + std::to_string(LeftMajor.x) + " " + std::to_string(LeftMajor.y) + " Major Axis: " + std::to_string(Major) + " Minor Axis: " + std::to_string(Minor);

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

bool CEllipse::Resize(double A)
{
	if ((LeftMajor.y + Minor * A < (UI.height - UI.StatusBarHeight) && LeftMajor.y - Minor * A > UI.ToolBarHeight) && (LeftMajor.x + Major * A <= UI.width))
	{
		Major *= A;
		Minor *= A;
		return true;
	}
	return 0;
}