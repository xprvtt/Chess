#include "Bishop.h"

string Bishop::Set_ID_FIGURE()
{
	return "Bishop";
}

vector<vector<bool>> Bishop::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 1 ������ �����

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//���������� ������� ��� ����� ��������� ���
	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//// �� ���������

	//� ������ ��� �� ������
	for (int YPos = YPositionCurrent + 1, XPos = XPositionCurrent + 1; YPos < Row || XPos < Col; YPos++, XPos++)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}

	// � ������ ���� �� ������
	for (int YPos = YPositionCurrent - 1, XPos = XPositionCurrent + 1; YPos > 0 || XPos < Col; YPos--, XPos++)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}


	//����� ���� �� ������
	for (int YPos = YPositionCurrent - 1, XPos = XPositionCurrent - 1; YPos > 0 || XPos > 0; YPos--, XPos--)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}
	//����� ��� �� ������
	for (int YPos = YPositionCurrent + 1, XPos = XPositionCurrent - 1; YPos < Row || XPos > 0; YPos++, XPos--)
	{
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}

	return result;
}

bool Bishop::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Bishop::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Bishop::GetPromoutionFigure(string ID_Figure)
{
	return false;
}