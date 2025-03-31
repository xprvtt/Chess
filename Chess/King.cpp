#include "King.h"

string King::Set_ID_FIGURE()
{
	return "King";
}

vector<vector<bool>> King::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ����� 1 ������ �����

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//���������� ������� ��� ����� ��������� ���
	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	int YPos = YPositionCurrent;
	int XPos = XPositionCurrent;


	for (int count = 0; count < 8; count++)
	{
		switch (count)
		{
		case 0:
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent;
			break;
		case 1:
			//����� �� ������
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent;
			break;
		case 2:
			//����� �� ������
			XPos = XPositionCurrent;
			YPos = YPositionCurrent - 1;
			break;
		case 3:
			//���� �� ������
			XPos = XPositionCurrent;
			YPos = YPositionCurrent + 1;
			break;
		case 4:
			///// ���������

			//� ����� ����� �� ������
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent - 1;
			break;
		case 5:
			//  � ����� ���� �� ������
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent + 1;
			break;
		case 6:

			// ����� ���� �� ������
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent + 1;
			break;
		case 7:
			// ����� ����� �� ������
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent - 1;
			break;

		default:
			break;
		}
		// ���������� ���� �� �������� ���� ��� ����� ������
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// ���� �������� ������ ���������� ��������� ����������� ������ � �������
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
		}
		// ����� ������������ ��� ��������� ������ ����� ������� � �� �� �������
		else
		{
			result[YPos][XPos] = false;
		}
	}
	return result;
}

bool King::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool King::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool King::GetPromoutionFigure(string ID_Figure)
{
	return false;
}