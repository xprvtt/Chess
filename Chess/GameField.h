#pragma once

#include "Core.h"

class GameField
{
private:

	/// <summary>
	/// ������ � ������������ ������ (�����)
	/// </summary>
	vector<vector<RectangleShape>> RectangleShapeOnField;

	/// <summary>
	/// ������ � ������������ ��������� 
	/// </summary>
	vector<vector<Text>> FieldCoordinate;

	/// <summary>
	/// ������ ����� ������ �� ����
	/// </summary>
	float SizeCell = 0.f;

	Font GameFieldFont;

public:
	
	/// <summary>
	/// ����������� ������
	/// </summary>
	/// <param name="CountCell">����������� ������, �� ��������� 10�10 �.�. 2 ������ � 2 ������� ������ �� ����������� ��������</param>
	/// <param name="SizeWindow">���������� ����</param>
	GameField(int CountCell, int WindowHeight, const Font& font, Color OuterSide, Color ColorCellOne, Color ColorCellTwo);

	/// <summary>
	/// �������� ������� ������� ��� ���������
	/// </summary>
	/// <returns>������� �������</returns>
	RectangleShape GetRectangleShapeOnField(int XPosition, int YPosition);


	/// <summary>
	/// �������� ��������� ��� ����������
	/// </summary>
	/// <param name="XPosition">������� �</param>
	/// <param name="YPosition">������� Y</param>
	/// <param name="font">�����</param>
	/// <returns></returns>
	Text GetFieldCoordinateOnField(int XPosition, int YPosition);

	/// <summary>
	/// �������� ����������� ����� � ����
	/// </summary>
	/// <returns>����������� �����</returns>
	int GetCounRowRectangleShape();

	/// <summary>
	/// �������� ����������� �������� � ����
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	int GetCounCollRectangleShape(int No = 0);

	/// <summary>
	/// �������� ����������� ��������� � ����
	/// </summary>
	/// <returns></returns>
	int GetCounRowFieldCoordinate();

	/// <summary>
	/// �������� ����������� �������� � ����
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	int GetCounCollFieldCoordinate(int No = 0);

	/// <summary>
	/// ������ ������ ��� float
	/// </summary>
	/// <returns></returns>
	float GetSizeCell();

	/// <summary>
	/// �������� ������ ��������� � �������
	/// </summary>
	/// <param name="Coordinate">������ ���������</param>
	bool SelectCell(const vector<vector<bool>>& Coordinate);

	/// <summary>
	/// ����� ��������� � ������
	/// </summary>
	/// <returns></returns>
	bool UnSelectCell();
};

