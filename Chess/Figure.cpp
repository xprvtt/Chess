#include "Figure.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

// vector<vector<pair<int, string>>> VectorIntLocationFigure ��� int ������ ������ ��������� => 	  
// -1 == �������															  
// 0 == ������ ������ 														  
// 1+ == ������� ������														  

////////////////////////////////////////////////////////////////////////////////////////////////////

Figure::Figure(int SIDE, bool INVULNERABLE)
{
	this->SIDE = SIDE;
	this->INVULNERABLE = INVULNERABLE;
}


Figure::Figure(const Figure& OthreFigure)
{
	this->SIDE			  = OthreFigure.SIDE;
	this->ID_FIGURE		  = OthreFigure.ID_FIGURE;
	this->INVULNERABLE    = OthreFigure.INVULNERABLE;
}


bool Figure::CheckMoveForFigure(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return CheckMove(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);
}


string Figure::Get_ID_FIGURE()
{
	if (ID_FIGURE.empty()) 
	{ 
		ID_FIGURE = Set_ID_FIGURE();
	}
	return ID_FIGURE;
}

bool Figure::GetINVULNERABLE()
{
	return INVULNERABLE;
}


int Figure::GetSIDE()
{
	return SIDE;
}



/// ����������� ������� ������� �������������� � ����������� 


string Figure::Set_ID_FIGURE()
{
	//������ ���������� ��� �� ��� � �����-��������� ������ \\\\  ������� ���������������
	return "Figure";
}


vector<vector<bool>> Figure::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// ����������� �����, ������ vector<vector<bool=false>>  \\\\  ������� ���������������
	int Size = VectorLocationFigure.size();
	return vector<vector<bool>>(Size, vector<bool>(Size, false));
}


bool Figure::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// ����������� �����, ������ false   \\\\  ������� ���������������
	// ����������� ������ �� ����� ������� ��� ����������� � ������ ������
	return false;
}

bool Figure::GetPromoutionFigure(string ID_Figure)
{
	// ����������� �����, ������ false   \\\\  ������� ���������������
	// �� ����� ������������ � ����� ��������� ������
	return false;
}


bool Figure::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// ����������� �����, ������ false   \\\\  ������� ���������������
	// �������� �����
	return false;
}