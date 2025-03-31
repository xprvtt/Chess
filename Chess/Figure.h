#pragma once

#include "Core.h"


class Figure
{
private:

	/// <summary>
	/// ������ id ��� ����� ����� ����
	/// </summary>
	string ID_FIGURE;

	/// <summary>
	/// ������� ������ 1 - ����� \ 2 - ������
	/// </summary>
	int SIDE;

	/// <summary>
	/// ������ ����� �����?
	/// </summary>
	bool INVULNERABLE;

public:


	
	/// <summary>
	/// ���������� ������� ������ ������ � ���������� ��� �������������
	/// </summary>
	/// <param name="SIDE">������� ������</param>
	/// <param name="Inulnerability">true = ������������ \ false = ����� ����� ����� (�����) </param>
	Figure(int SIDE, bool INVULNERABLE);

	/// <summary>
	/// ����������� �����������
	/// </summary>
	/// <param name="OthreFigure"></param>
	Figure(const Figure &OthreFigure);

	/// <summary>
	/// ��������� �������� �� ��� �� ��������� ����������
	/// </summary>
	/// <param name="MoveCoordinate"> �������� �������� ����������</param>
	/// <returns>���������� ��������</returns>
	bool CheckMoveForFigure(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// �������� ��� ������
	/// </summary>
	/// <returns>��� ������</returns>
	string Get_ID_FIGURE();

	/// <summary>
	/// �������� ������� ������ � ������
	/// </summary>
	/// <returns>������� ������</returns>
	int GetSIDE();


	/// <summary>
	/// ��������� �� ������?
	/// </summary>
	/// <returns>true = ��������� \ false - ����� �����</returns>
	bool GetINVULNERABLE();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//																			  
	// vector<vector<pair<int, string>>> VectorLocationFigure ��� int ������ ������ ��������� =>
	// -1 == �������															  
	// 0 == ������ ������ 														  
	// 1+ == ������� ������														  
	//																	  
	///////////////////////////////////////////////////////////////////////////////////////////////


	/// ��� ����������� ������� ������� �������������� � ����������� 

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


protected:

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

