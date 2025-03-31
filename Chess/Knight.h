#pragma once
#pragma once
#include "Figure.h"

class Knight : public Figure
{
	//��������� ��� �����������
	using Figure::Figure;

	/// <summary>
	/// �������� ��������� ���������� ��� ����
	/// </summary>
	/// <param name="Coordiante">���������� �� ������� �� ����� �������</param>
	/// <returns>���������� ��������</returns>
	virtual vector<vector<bool>> GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// ����������� ����������� ����� ���� ��������� �������
	/// </summary>
	/// <returns></returns>
	virtual bool GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// ����� �� �� ������������ � ������ ��������� ������?
	/// </summary>
	/// <returns></returns>
	virtual bool GetPromoutionFigure(string ID_Figure);

	/// <summary>
	/// ��������� �������� �� ��� �� ��������� ����������, ������������ ��� ������ ������
	/// </summary>
	/// <param name="Coordiante">���������� �� ������� �� ����� �������</param>
	/// <returns>���������� ��������</returns>
	virtual bool CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// ��������������� ID ��� ������ ������ ���� �� �������� ������ ��� ��������
	/// </summary>
	virtual string Set_ID_FIGURE();

};