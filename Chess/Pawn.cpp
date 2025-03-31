#include "Pawn.h"

bool CustomCheckMove1(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);
bool CustomCheckMove2(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

vector<vector<bool>> AvailableMoveForFigure1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);
vector<vector<bool>> AvailableMoveForFigure2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

bool PossibilityPromotion1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>&VectorLocationFigure);
bool PossibilityPromotion2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>&VectorLocationFigure);


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// vector<vector<pair<int, string>>> VectorIntLocationFigure ��� int ������ ������ ��������� => 	  
// -1 == �������															  
// 0 == ������ ������ 														  
// 1+ == ������� ������														  
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{

	switch (GetSIDE())
	{
	case 1:
		return CustomCheckMove1(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);
	case 2:
		return CustomCheckMove2(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);

	default:
		OutputLog("����� �� ��������� ��������� ����� -> Figure -> Pawn -> CheckMove() -> case");
		return false;
	}
}
bool CustomCheckMove1(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = AvailableMoveForFigure1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	if (temp[XPositionMove][YPositionMove] == true)
	{
		return true;
	}

	return false;
}

bool CustomCheckMove2(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = AvailableMoveForFigure2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	if (temp[XPositionMove][YPositionMove] == true)
	{
		return true;
	}

	return false;
}

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//



//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

vector<vector<bool>> Pawn::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{

	// �������� ����� � ����������� �� ������� ������
	switch (GetSIDE())
	{
	case 1:
		return AvailableMoveForFigure1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);
	case 2:
		return AvailableMoveForFigure2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);


	default:
		OutputLog("����� �� ��������� ��������� ����� -> Figure -> Pawn -> GetMoveForFigure() -> case");
		return vector<vector<bool>>(VectorLocationFigure.size(), vector<bool>(VectorLocationFigure[0].size(), false));
	}
}



vector<vector<bool>> AvailableMoveForFigure1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{

	/// ����� 1 ������ �����

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//���������� ������� ��� ����� ��������� ���
	vector<vector<bool>> result(Row, vector<bool>(Col, false));
	



	// ������������ ��� �� ������ ������
	// 
	//���� ������� ����� ������ ��� �� ��� ��������
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent].first == 0)
	{
		result[YPositionCurrent-1][XPositionCurrent] = true;

		//����������� ��������� ��������� ������� ����� (2 ��� ��� ������) ����� ����� ������� ��� �� 1 ������ ������, �.�. ����� �� 2
		if (YPositionCurrent == Row - 3 && VectorLocationFigure[YPositionCurrent - 2][XPositionCurrent].first == 0)
		{
			// ��������� ��������� ��� �� 2 ������ ������
			result[YPositionCurrent-2][XPositionCurrent] = true;
		}
	}

	// ����������� ����������� ������ ������ ���������� ������ � ����� ������ 2
	// ������ �� ������ �� ������ ���� ������ ( SIDE 0 ) �� ������ ���� ����� ( SIDE -1 ) � ������ ����� ���� �� ������ 
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1].first > 0 && VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent - 1][XPositionCurrent - 1] = true;
	}
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1].first > 0 && VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent - 1][XPositionCurrent + 1] = true;
	}


	return result;
}

vector<vector<bool>> AvailableMoveForFigure2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 2 ������� ������

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//���� ������� ����� ������ ���
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent].first == 0)
	{
		result[YPositionCurrent + 1][XPositionCurrent] = true;

		//����������� ��������� ��������� ������� ����� (2 ��� ��� ������) ����� ����� ������� ��� �� 1 ������ ������ ���� ��� �� ������
		if (YPositionCurrent == 2 && VectorLocationFigure[YPositionCurrent + 2][XPositionCurrent].first == 0)
		{
			// ��������� ��������� ��� �� 2 ������ ������
			result[YPositionCurrent + 2][XPositionCurrent] = true;
		}
	}

	// ����������� ����������� ������ ������ ���������� ������ � ����� ������ 2
    // ������ �� ������ �� ������ ���� ������ ( SIDE 0 ) �� ������ ���� ����� ( SIDE -1 ) � ������ ����� ���� �� ������ 
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1].first > 0 && VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent + 1][XPositionCurrent - 1] = true;
	}
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1].first > 0 && VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent + 1][XPositionCurrent + 1] = true;
	}


	return result;
}


//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//






//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	switch (GetSIDE())
	{
	case 1:
		return PossibilityPromotion1(XPositionCurrent,  YPositionCurrent,  VectorLocationFigure);
	case 2:
		return PossibilityPromotion2(XPositionCurrent,  YPositionCurrent, VectorLocationFigure);

	default:
		OutputLog("����� �� ��������� ��������� ����� -> Figure -> Pawn -> GetPossibilityPromotion() -> case");
		return false;
	}
}

bool PossibilityPromotion1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 1 ����� ������

	return YPositionCurrent == 1 ? true : false;

	
}


bool PossibilityPromotion2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 2 ������ �������
	return YPositionCurrent == VectorLocationFigure.size() - 2 ? true : false;

}


//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//







//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

string Pawn::Set_ID_FIGURE()
{
	return "Pawn";
}
//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//



//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

bool Pawn::GetPromoutionFigure(string ID_Figure)
{
	//�� ��������� ����� ����� ������������ � 4 ������ ����������� ������, �� ����� �������� � ������
	if (ID_Figure == "Rook" || ID_Figure == "Queen" || ID_Figure == "Knight" || ID_Figure == "Bishop" )
	{
		return true;
	}

	return false;
}
