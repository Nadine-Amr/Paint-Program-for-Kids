#include "GUI.h"
#include <iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 70;
	UI.PlayMenuItemWidth = 100;
	
	UI.DrawColor = BLUE1;	//Drawing color
	UI.FillColor = GOLD;	//Filling color
	UI.MsgColor = LIGHTBLUE1;		//Messages color
	UI.BkGrndColor = BINKBODY;	//Background color
	UI.HighlightColor = GREENYELLOW;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = WHITE;
	UI.PenWidth = 3;	//width of the figures frames
	UI.ColorChagne = 1;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//
bool GUI::IsMouseClicked()
{
	Point P;
	pWind->GetMouseClick(P.x, P.y);
	if (P.x == -1)
		return false;
	else return true;
}
void GUI::GetMouseCord(int &x, int &y)
{
	pWind->GetMouseCoord(x, y);
}
bool GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
	if (y >= 0 && y < UI.ToolBarHeight && x>ITM_RESTART*UI.PlayMenuItemWidth && x<(ITM_DM+1)*UI.PlayMenuItemWidth)
		return true;
	else
		return false;
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType(int x, int y)
{
	if (y==0 && x==0)
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	else
	{
		UI.PointX = 0;
		UI.PointY = 0;
	}
	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX:  return DRAW_HEX;
			case ITM_DEL:  return DEL;
			case ITM_DC:   return CHNG_DRAW_CLR;
			case ITM_FC:   return CHNG_FILL_CLR;
			case ITM_RSZ:  return RESIZE;
			case ITM_STB:  return SEND_BACK;
			case ITM_BTF:  return BRNG_FRNT;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_PAL:  return GET_COLOR;
			case ITM_PM:   return TO_PLAY;
			case ITM_MOVE: return MOVE;
			case ITM_REDO:  return REDO;
			case ITM_UNDO:   return UNDO;

			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			CurrentClick.x = x;
			CurrentClick.y = y;
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.PlayMenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_FIG: return FIG;
			case ITM_FIG_COLOR: return FIG_COLOR;
			case ITM_COLOR:  return COLOR;
			case ITM_RESTART:  return RESTART;

			case ITM_DM:   return TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			CurrentClick.x = x;
			CurrentClick.y = y;
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}

void GUI::CreateDrawArea() const
{
	pWind->SetBrush(UI.BkGrndColor);
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::GetColors(const int x, const int y) const
{
	return pWind->GetColor(x, y);

}

void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, 15*UI.width/20, UI.height);
}

void GUI::DrawColor() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle((ITM_PAL)*UI.MenuItemWidth, 0, (ITM_PAL+0.9)*UI.MenuItemWidth,  0.95*UI.ToolBarHeight);
	
	pWind->SetPen(UI.DrawColor, 5);
	if (UI.IsFilled)
	pWind->SetBrush(UI.FillColor);
	else
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle((ITM_PAL+0.15)*UI.MenuItemWidth, 0.15*UI.ToolBarHeight , (ITM_PAL+0.75)*UI.MenuItemWidth , 0.75* UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetBrush(UI.StatusBarColor);
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//changing ToolMenue Color
	/* pWind->SetPen(UI.MenuBarColor, 1);
	pWind->SetBrush(UI.MenuBarColor);
	pWind->DrawRectangle(0,0, UI.width, UI.ToolBarHeight);
	*/


	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Elps.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Hex.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Del.jpg";
	MenuItemImages[ITM_DC] = "images\\MenuItems\\DC.jpg";
	MenuItemImages[ITM_FC] = "images\\MenuItems\\FC.jpg";
	MenuItemImages[ITM_RSZ] = "images\\MenuItems\\RSZ.jpg";
	MenuItemImages[ITM_STB] = "images\\MenuItems\\STB.jpg";
	MenuItemImages[ITM_BTF] = "images\\MenuItems\\BTF.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ITM_PAL] = "images\\MenuItems\\Pal.jpg";
	MenuItemImages[ITM_PM] = "images\\MenuItems\\PM.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\MOVE.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\REDO.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\UNDO.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\EX.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<DRAW_ITM_COUNT; i++)
	{
		if (!(i == ITM_PAL))
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		pWind->SetPen(LIGHTBLUE1, 2);
		pWind->DrawLine(i*(UI.MenuItemWidth) + (UI.MenuItemWidth - 3), 0, i*(UI.MenuItemWidth) + (UI.MenuItemWidth - 3), UI.ToolBarHeight);
	}
	
	DrawColor();

	//Draw a line under the toolbar
	pWind->SetPen(LIGHTBLUE1, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	ClearScore(false); //Clear score Section in PlayMode

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	pWind->SetBrush(UI.StatusBarColor);
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_COLOR] = "images\\MenuItems\\FIG.jpg";
	MenuItemImages[ITM_FIG] = "images\\MenuItems\\COLOR.jpg";
	MenuItemImages[ITM_FIG_COLOR] = "images\\MenuItems\\FIG_COLOR.jpg";
	MenuItemImages[ITM_RESTART] = "images\\MenuItems\\RESTART.jpg";
	MenuItemImages[ITM_DM] = "images\\MenuItems\\DRAW_MODE.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<PLAY_ITM_COUNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i*UI.PlayMenuItemWidth, 0, UI.PlayMenuItemWidth, UI.ToolBarHeight);
		pWind->SetPen(LIGHTBLUE1, 2);
		pWind->DrawLine(i*(UI.PlayMenuItemWidth) + (UI.PlayMenuItemWidth - 3), 0, i*(UI.PlayMenuItemWidth) + (UI.PlayMenuItemWidth - 3), UI.ToolBarHeight);
	}



	//Draw a line under the toolbar
	pWind->SetPen(LIGHTBLUE1, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	//Draw score images
	string right = "images\\ScoreItems\\Right.jpg";
	string wrong = "images\\ScoreItems\\Wrong.jpg";
	pWind->DrawImage(right, (16 * UI.width / 20) + 30, UI.height - UI.StatusBarHeight + 5, 50, UI.StatusBarHeight-25);
	pWind->DrawImage(wrong, 18 * UI.width / 20, UI.height - UI.StatusBarHeight + 5, 50, UI.StatusBarHeight-25);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::DrawPallate() 	//get current drwawing color
{
	Point P1;
	
	pWind->SetBrush(UI.StatusBarColor);
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	string pallate = "images\\MenuItems\\Pallate.jpg";
	pWind->DrawImage(pallate, 2 * UI.MenuItemWidth, 0, 13 * UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(LIGHTBLUE1, 2);
	GetPointClicked(P1.x, P1.y);
	color getcolor = GetColors(P1.x, P1.y);
	return getcolor;
	
}
void GUI::ShowScore(int score[2]) const
{
	ClearScore(true);
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString((17 * UI.width / 20)+30, UI.height - (int)(UI.StatusBarHeight / 1.5), to_string(score[0]));
	pWind->DrawString(19 * UI.width / 20, UI.height - (int)(UI.StatusBarHeight / 1.5), to_string(score[1]));
}
void GUI::ClearScore(bool Case) const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	if (Case) //Clearthe current score to update it
	{
		pWind->DrawRectangle((17 * UI.width / 20) + 30, UI.height - UI.StatusBarHeight, 18 * UI.width / 20, UI.height);
		pWind->DrawRectangle(19 * UI.width / 20, UI.height - UI.StatusBarHeight, UI.width, UI.height);
	}
	else //Clear Score Section
	{
	pWind->DrawRectangle(11 * UI.width / 15, UI.height - UI.StatusBarHeight, UI.width , UI.height);
	}
}
color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntBkGrndColor() const
{ return UI.BkGrndColor;	}


int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
	{
		style = FRAME;
	}

	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);	
}

void GUI::DrawEllip(Point P1, int major, int minor, GfxInfo EllipGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = EllipGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, EllipGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (EllipGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(EllipGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y - minor / 2, P1.x + major, P1.y + minor / 2, style);

}

void GUI::DrawHex(int* Px, int* Py, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawPolygon(Px, Py, 6, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

