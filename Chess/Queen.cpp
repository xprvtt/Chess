#include "Queen.h"

string Queen::Set_ID_FIGURE()
{
	return "Queen";
}

vector<vector<bool>> Queen::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 1 ������ �����

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//���������� ������� ��� ����� ��������� ���
	vector<vector<bool>> result(Row, vector<bool>(Col, false));


	// ������ �� ������
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

bool Queen::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Queen::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Queen::GetPromoutionFigure(string ID_Figure)
{
	return false;
}
