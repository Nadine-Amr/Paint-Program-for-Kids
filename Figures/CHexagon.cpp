#include "CHexagon.h"
#include <iostream>
#include <sstream>

CHexagon::CHexagon(int* Px, int* Py, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	PX = Px;
	PY = Py;
}

CHexagon::CHexagon(fstream &InFile, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	PX = new int[6];
	PY = new int[6];
	Load(InFile);
}

CHexagon::CHexagon(istringstream &str, GfxInfo  FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	PX = new int[6];
	PY = new int[6];
	Load(str);
}

CHexagon::~CHexagon()
{
	delete [] PX;
	delete [] PY;
}

void CHexagon::Move(int x, int y)
{
	for (int i = 0; i < 6; i++)
	{
		PX[i] += x;
		PY[i] += y;
	}
	if (PY[0] < UI.ToolBarHeight)
	{
		for (int i = 1; i < 6; i++)
			PY[i] = PY[i] - PY[0] + UI.ToolBarHeight + 2;

		PY[0] = UI.ToolBarHeight + 2;
	}

	if (PY[3] > UI.height - UI.StatusBarHeight)
	{
		for (int i = 0; i < 6; i++)
			if (!(i == 3))
				PY[i] = PY[i] - PY[3] + (UI.height - UI.StatusBarHeight - 2);

		PY[3] = UI.height - UI.StatusBarHeight - 2;
	}
	if (PX[5] < 2)
	{
		for (int i = 0; i < 5; i++)
			PX[i] = PX[i] - PX[5] + 2;

		PX[5] = 2;
	}

	if (PX[2] > UI.width - 2)
	{
		for (int i = 0; i < 6; i++)
			if (!(i == 2))
				PX[i] = PX[i] - PX[2] + (UI.width - 2);

		PX[2] = (UI.width - 2);
	}
}

string CHexagon::FigType()
{
	string Fig_Type = "HEXAGON";
	return Fig_Type;
}
void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawPloygon to draw a Hexagon on the screen	
	pGUI->DrawHex(PX, PY, FigGfxInfo, Selected);
}

bool CHexagon::IsInside(int x, int y)
{
	if ((y >= PY[0]) && (y <= PY[4]) && (y >= (PY[1] + ((PY[2] - PY[1]) / (PX[2] - PX[1]))*(x - PX[1]))) && (y <= (PY[2] + ((PY[3] - PY[2]) / (PX[3] - PX[2]))*(x - PX[2]))) && (y >= (PY[0] + ((PY[5] - PY[0]) / (PX[5] - PX[0]))*(x - PX[0]))) && (y <= (PY[4] + ((PY[5] - PY[4]) / (PX[5] - PX[4]))*(x - PX[4]))))
	{
		return true;
	}
	return false;
}

void CHexagon::PrintPoints()
{
	std::cout << PX[0] << " " << PY[0] << " " << PX[3] << " " << PY[3] << " " << PX[1] << " " << PY[1] << " " << PX[2] << " " << PY[2] << " " << PX[4] << " " << PY[4] << " " << PX[5] << " " << PY[5];
}

void CHexagon::Save(fstream &OutFile, int id) 
{
	OutFile << "HEX " << id << " " << PX[0] << " " << PY[0] << " " << PX[3] << " " << PY[3] << " " << FigGfxInfo.isFilled << " " << std::to_string(FigGfxInfo.DrawClr.ucRed) << " " << std::to_string(FigGfxInfo.DrawClr.ucGreen) << " " << std::to_string(FigGfxInfo.DrawClr.ucBlue) << " " << std::to_string(FigGfxInfo.FillClr.ucRed) << " " << std::to_string(FigGfxInfo.FillClr.ucGreen) << " " << std::to_string(FigGfxInfo.FillClr.ucBlue)  << "\n";
}

string CHexagon::action() const
{
	return("HEX " + std::to_string(ID) + " " + std::to_string(PX[0]) + " " + std::to_string(PY[0]) + " " + std::to_string(PX[3]) + " " + std::to_string(PY[3]) + " " + std::to_string(FigGfxInfo.isFilled) + " " + std::to_string(FigGfxInfo.DrawClr.ucRed) + " " + std::to_string(FigGfxInfo.DrawClr.ucGreen) + " " + std::to_string(FigGfxInfo.DrawClr.ucBlue) + " " + std::to_string(FigGfxInfo.FillClr.ucRed) + " " + std::to_string(FigGfxInfo.FillClr.ucGreen) + " " + std::to_string(FigGfxInfo.FillClr.ucBlue) + "\n");
}

void CHexagon::Load(fstream &InFile)
{
	string word;
	InFile >> word; //retrieving ID which is the same as the index of the figure in FigList
	InFile >> word; PX[0] = stoi(word, 0, 10); 
	InFile >> word; PY[0] = stoi(word, 0, 10);
	InFile >> word; PX[3] = stoi(word, 0, 10);
	InFile >> word; PY[3] = stoi(word, 0, 10);
	InFile >> word; FigGfxInfo.isFilled = stoi(word, 0, 10);

	Point Center;
	Center.x = (PX[0] + PX[3]) / 2;
	Center.y = (PY[0] + PY[3]) / 2;
	double Radius = sqrt(pow(PX[0] - Center.x, 2) + pow(PY[0] - Center.y, 2));
	PX[1] = PX[3];
	PY[1] = PY[0];
	PX[5] = Center.x - Radius;
	PY[5] = Center.y;
	PX[2] = Center.x + Radius;
	PY[2] = Center.y;
	PX[4] = PX[0];
	PY[4] = PY[3];

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

void CHexagon::Load(istringstream &str)
{
	string word;
	str >> word; ID = stoi(word, 0, 10); //retrieving ID which is the same as the index of the figure in FigList
	str >> word; PX[0] = stoi(word, 0, 10);
	str >> word; PY[0] = stoi(word, 0, 10);
	str >> word; PX[3] = stoi(word, 0, 10);
	str >> word; PY[3] = stoi(word, 0, 10);
	str >> word; FigGfxInfo.isFilled = stoi(word, 0, 10);

	Point Center;
	Center.x = (PX[0] + PX[3]) / 2;
	Center.y = (PY[0] + PY[3]) / 2;
	double Radius = sqrt(pow(PX[0] - Center.x, 2) + pow(PY[0] - Center.y, 2));
	PX[1] = PX[3];
	PY[1] = PY[0];
	PX[5] = Center.x - Radius;
	PY[5] = Center.y;
	PX[2] = Center.x + Radius;
	PY[2] = Center.y;
	PX[4] = PX[0];
	PY[4] = PY[3];

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
void CHexagon::PrintInfo(GUI* pGUI)
{
	string info = "The selected figure is a ";
	info += "hexagon. ID: " + std::to_string(ID) + " Top-Left Corner: " + std::to_string(PX[0]) + " " + std::to_string(PY[0]) + " Bottom-Right Corner: " + std::to_string(PX[3]) + " " + std::to_string(PY[3]);

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

bool CHexagon::Resize(double A)
{

	if (((PY[0] + A * (PY[3] - PY[0])) < (UI.height - UI.StatusBarHeight)) && ((PX[0] - (A * (PX[3] - PX[0])*sqrt(3) / 2)) > 0) && (((PX[0] + A * (PX[3] - PX[0])) + (A * (PX[3] - PX[0])*sqrt(3) / 2)) < UI.width))
	{
		PX[3] = PX[0] + A * (PX[3] - PX[0]);
		PY[3] = PY[0] + A * (PY[3] - PY[0]);

		Point Center;
		Center.x = (PX[0] + PX[3]) / 2;
		Center.y = (PY[0] + PY[3]) / 2;
		double Radius = sqrt(pow(PX[0] - Center.x, 2) + pow(PY[0] - Center.y, 2));
		PX[1] = PX[3];
		PY[1] = PY[0];
		PX[5] = Center.x - Radius;
		PY[5] = Center.y;
		PX[2] = Center.x + Radius;
		PY[2] = Center.y;
		PX[4] = PX[0];
		PY[4] = PY[3];

		return true;
	}
	return 0;
}