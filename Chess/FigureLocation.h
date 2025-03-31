#pragma once

#include "Core.h"
#include "Figure.h"

/// <summary>
/// ����� � ������������� �����
/// </summary>
class FigureLocation
{

private:

	///////////////////////////////////////////////////////////////////////////////////////////////////


	//--//--//--//--//--//--//--//   ��� ����� �� �����  //--//--//--//--//--//--//--//--//--//--//--//
	
	vector< vector< shared_ptr<Figure>>>   LocationClassFigure;
	vector< vector< shared_ptr<Texture>>>  LocationTexture;
	vector< vector< RectangleShape >>      LocationRectangleShape;
	
	//--//--//--//--//--//--//--//     ��� ���������� �����   //--//--//--//--//--//--//--//--//--//--//

	vector<shared_ptr<Figure>>				   UniqueFigureLocationClassFigure;
	vector<shared_ptr<Texture>>				   UniqueFigureLocationTexture;
	vector<vector<pair<int, RectangleShape>>>  UniqueFigureLocationRectangleShape;


	///////////////////////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////
																				  //
	// vector<vector<int>> VectorIntLocationFigure ������ ������ ��������� => 	  //
	// -1 == �������															  //
	// 0 == ������ ������ 														  //
	// 1+ == ������� ������														  //
																				  //
	////////////////////////////////////////////////////////////////////////////////
	
	vector<vector<pair<int, string>>> VectorLocationFigure;
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// ����������� ������ � 1 ����
	/// </summary>
	size_t CountCellOnXPosition;


	/// <summary>
	/// ����������� �����
	/// </summary>
	size_t CountCellOnYPosition;

	/// <summary>
	/// ������ ����� ������
	/// </summary>
	float SizeCell;

	/// <summary>
	///  ������� ������� ����� ������ �� ������������� ������� SizeCell
	/// </summary>
	float PrecentSizeFigure;

	/// <summary>
	/// ������ ������ ������, ������������� �� �������� Precent
	/// </summary>
	float SizeRectangInCell;

	/// <summary>
	/// ������� ������ ������
	/// </summary>
	float PositionRectangInCell;
	
	/// <summary>
	/// �������� ����� ������ ���� ������, ������� ���� �������� = true;
	/// </summary>
	bool SelectFigure = false;

	/// <summary>
	/// ���������� ���������� ������ � \ � 
	/// </summary>
	pair<int, int> PositionSelectFigure = make_pair(0, 0);


	/// <summary>
	/// �������� �������� � �������� ���������� ������� ����� � �������
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetIteratorUniqueFigure(int XPosition, int Yposition);

	///////////////////////////////////////////////////////////////////////////////////////////

public:


	//--//--//--//--//--//--//--//   ��� ����� �� �����  //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// ������������� �������� ���� \ ������� X �� X
	/// </summary>
	/// <param name="CountCellOnSideWindow">����������� ������ �� ������� </param>
	/// <param name="WindowHeight">������ ����</param>
	/// <param name="PathToEmptyImage">���� �� ������ ��������</param>
	FigureLocation(size_t CountCellOnLengthWindow, size_t CountCellOnHeightWindow,  int WindowHeight, path PathToEmptyImage, path PathToEmptyTextureEdge , float PrecentSizeFigure);

	/// <summary>
	/// ����� ������������ ������ �� ����
	/// </summary>
	/// <param name="XPosition">������� � �� ������� ����� ����������� ������</param>
	/// <param name="Yposition">������� � �� ������� ����� ����������� ������</param>
	/// <param name="NameFigure">�������� ������</param>
	/// <param name="Side">������� ������ ��� ������</param>
	/// <param name="CurrentTextureFigure">����� �� �������� ������</param>
	/// <returns>true - ������ �����������</returns>
	bool SetFigure(int XPosition, int YPosition, string NameFigure_ID_Figure, int Side, bool invulnerable);


	/// <summary>
	/// �������� ���������� ������
	/// </summary>
	/// <param name="NewFigure">�����-��������� Figure</param>
	/// <param name="CurrentTextureFigure">�������� ������</param>
	/// <returns></returns>
	bool AddUniqueFigure(shared_ptr<Figure> NewFigure, path CurrentTextureFigure);
	








	//////////////////////////////  �������� ������  ///////////////////////////////////////////////////

	/// <summary>
	/// �������� ��������� �� "�������" (������) ������, ������������� �� ������� �\�
	/// </summary>
	/// <param name="XPosition">������� � ������</param>
	/// <param name="Yposition">������� � ������</param>
	/// <returns>��������� �� RectangleShape  ������</returns>
	const RectangleShape& GetRectangleShapeFigure(int XPosition, int Yposition);








	//////////////////////////////  ���������� � ������  ///////////////////////////////////////////////////

	/// <summary>
	/// �������� �������� ������ �� �������
	/// </summary>
	/// <param name="XPosition">������� � ������</param>
	/// <param name="Yposition">������� � ������</param>
	/// <returns>�������� ������</returns>
	string GetIDFigure(int XPosition, int Yposition);

	/// <summary>
	/// �������� ������� ������ ������
	/// </summary>
	/// <param name="XPosition">������� � ������</param>
	/// <param name="Yposition">������� � ������</param>
	/// <returns>������� ������ � ������</returns>
	int GetSideFigure(int XPosition, int Yposition);

	/// <summary>
	/// �������� ���������� ������ �� ������������ �� ������� ����
	/// </summary>
	/// <param name="Positon">������� � ����</param>
	/// <returns>���� ����������� X , Y </returns>
	pair<int, int> GetPositionFigureWhenMousePressed(Vector2f Positon);


	/// <summary>
	/// ���� ���� ��������� ������, �������� �� ������� x \ y 
	/// </summary>
	/// <returns></returns>
	pair<int, int> GetPositionSelectFigure();

	/// <summary>
	/// ������� �� ������ �� �������
	/// </summary>
	bool GetInvulnerableFigure(int XPosition, int Yposition);





		
	//////////////////////////////  �������������� � �������  ///////////////////////////////////////////////////

	/// <summary>
	/// ������������ ���������� ������ �� ��������� �������
	/// </summary>
	/// <param name="XPositionFigure">������� ������� � ������</param>
	/// <param name="YpositionFigure">������� ������� � ������</param>
	/// <param name="XPositionMove">������� � �� ������� ����� �����������</param>
	/// <param name="YPositionMove">������� � �� ������� ����� �����������</param>
	/// <returns>true - ������ �����������</returns>
	bool MoveSelectFigure (int XPositionMove, int YPositionMove);

	/// <summary>
	/// �������� ������ �� �������
	/// </summary>
	/// <param name="XPositionFigure">������� � ������</param>
	/// <param name="YpositionFigure">������� � ������</param>
	/// <returns>true - ���� ������ �� ������� ���� � ���� ��������</returns>
	bool SeletcFigure(int XPositionFigure, int YpositionFigure);

	/// <summary>
	/// �������� ���������
	/// </summary>
	/// <param name="XPositionFigure">������� � ������</param>
	/// <param name="YpositionFigure">������� � ������</param>
	/// <returns>true - ���� ��������� �����</returns>
	bool UnSeletcFigure();

	/// <summary>
	/// ���� �� ���� ���� ��������� ������?
	/// </summary>
	/// <returns>true - ���� ������ ��������</returns>
	bool FiguresSelectedOrNot();

	/// <summary>
	/// �������� ������ ��������� ����� ��� ���������� ������
	/// </summary>
	/// <returns></returns>
	vector<vector<bool>> GetAvailableMovesForSelectFigure();


	/// <summary>
	/// �������� �� �����-���� ����������� ��� ������ �� ��������� ������� // ������ ������������ ����� ����� ������������ ������
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YpositionFigure"></param>
	/// <returns>true - ���� �������� </returns>
	bool PromoutionFigureOnPosition(int XPositionFigure, int YpositionFigure);


	/// <summary>
	/// ������������ � ��������� ������ ���� ��������
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <returns></returns>
	bool PromoutionSelectFigure(string ID_Figure);





	//////////////////////////////  �������������� � ������� ����� �����  ///////////////////////////////////////////////////

	/// <summary>
	/// �������� ������ � ������������ �������� �� ������� ����
	/// </summary>
	void UpdateVectorIntLocationFigure();


	/// <summary>
	/// �������� ������ � ������������� ����� �� ������� ����
	/// </summary>
	/// <returns></returns>
	vector<vector<pair<int,string>>> GetVectorLocationFigure();







	//--//--//--//--//--//--//--//     ��� ���������� �����   //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// �������� ID ���������� ������ � ���� ���������� �����
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	string GetIDUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// �������� ������� � ���������� ������
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetSideUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// �������� "��������" ���� ���������� �����
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	const RectangleShape& GetRectangleShapeUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// �������� ������ �� ���� ���������� �����
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool SeletcUniqueFigureForPromoution(int XPositionFigure, int YPositionFigure);

	/// <summary>
	/// �������� ��������� ���� ����� �� ���� ���������� �����
	/// </summary>
	/// <returns></returns>
	bool UnSeletcUniqueFigure();


	/// <summary>
	/// �������� ������� ������, �� ���� ���������� �����
	/// </summary>
	/// <param name="PositonMouse"></param>
	/// <returns></returns>
	pair<int, int> GetPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse);

	/// <summary>
	/// ������� �� ������ �� ���� ���������� �����
	/// </summary>
	bool GetInvulnerableUniqueFigure(int XPosition, int Yposition);


};
