#include "Rook.h"

string Rook::Set_ID_FIGURE()
{
	return "Rook";
}

vector<vector<bool>> Rook::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 1 ������ �����

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//���������� ������� ��� ����� ��������� ���
	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//���������� �� �����������

	// ������ �� ������ (�����)
	for (int XPos = XPositionCurrent + 1; XPos < Col; XPos++)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPositionCurrent][XPos].first == 0)
		{
			result[YPositionCurrent][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPositionCurrent][XPos].first != GetSIDE() && VectorLocationFigure[YPositionCurrent][XPos].first > 0)
		{
			result[YPositionCurrent][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPositionCurrent][XPos] = false;
			break;
		}
	}
	// ����� �� ������
	for (int XPos = XPositionCurrent - 1; XPos > 0; XPos--)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPositionCurrent][XPos].first == 0)
		{
			result[YPositionCurrent][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPositionCurrent][XPos].first != GetSIDE() && VectorLocationFigure[YPositionCurrent][XPos].first > 0)
		{
			result[YPositionCurrent][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPositionCurrent][XPos] = false;
			break;
		}
	}

	//����� �� ������
	for (int YPos = YPositionCurrent - 1; YPos > 0; YPos--)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPositionCurrent].first == 0)
		{
			result[YPos][XPositionCurrent] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPositionCurrent].first != GetSIDE() && VectorLocationFigure[YPos][XPositionCurrent].first > 0)
		{
			result[YPos][XPositionCurrent] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPositionCurrent] = false;
			break;
		}
	}
	//���� �� ������
	for (int YPos = YPositionCurrent + 1; YPos < Row; YPos++)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPositionCurrent].first == 0)
		{
			result[YPos][XPositionCurrent] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPositionCurrent].first != GetSIDE() && VectorLocationFigure[YPos][XPositionCurrent].first > 0)
		{
			result[YPos][XPositionCurrent] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPositionCurrent] = false;
			break;
		}
	}
	return result;
}

bool Rook::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Rook::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Rook::GetPromoutionFigure(string ID_Figure)
{
	return false;
}
