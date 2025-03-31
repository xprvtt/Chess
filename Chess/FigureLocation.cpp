
#include "FigureLocation.h"




FigureLocation::FigureLocation(size_t CountCellOnXPosition, size_t CountCellOnYPosition, int WindowHeight, path PathToEmptyTextureGameField , path PathToEmptyTextureEdge , float PrecentSizeFigure)
{
	if (CountCellOnXPosition < 3 || CountCellOnYPosition < 3)
	{
		return;
	}

	this->CountCellOnXPosition  = CountCellOnXPosition;
	this->CountCellOnYPosition  = CountCellOnYPosition;
	this->SizeCell              = float(WindowHeight / CountCellOnXPosition);
	this->PrecentSizeFigure     = PrecentSizeFigure;
	this->SizeRectangInCell     = SizeCell * PrecentSizeFigure;

	PrecentSizeFigure <= 0 ? this->PositionRectangInCell = 0 : this->PositionRectangInCell = (SizeCell - SizeRectangInCell) / 2;


	VectorLocationFigure.resize(CountCellOnXPosition, vector<pair<int,string>>(CountCellOnXPosition));

	/// ������� 

	//--//--//--//--//--//--//--//--//--//    ��� ����� �� �����   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																													
	LocationClassFigure.resize(   CountCellOnYPosition, vector<shared_ptr<Figure>> (CountCellOnXPosition));
	LocationTexture.resize(       CountCellOnYPosition, vector<shared_ptr<Texture>>(CountCellOnXPosition));
	LocationRectangleShape.resize(CountCellOnYPosition, vector<RectangleShape>     (CountCellOnXPosition));
																												    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


	//--//--//--//--//--//--//--//--//--//  ��� ���������� �����   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																															
	UniqueFigureLocationRectangleShape.resize(CountCellOnYPosition,vector<pair<int, RectangleShape>>(CountCellOnXPosition));																																																									// 	// ���������� ���������� �����

	// ������� ������� == ����
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(-1, true));
	//
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureEdge));

	// ������ ������� == ������ ������
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(NULL, false));
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureGameField));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (int YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			int U; // �������� ������������ ����������� ������ � ���������� �������� � ��������

			// ���� ���� �� ���������� ������-���� == Side -1
			if (XPosition == 0 || YPosition == 0 || XPosition == CountCellOnXPosition - 1 || YPosition == CountCellOnYPosition - 1)
			{
				U = 0; // �������� �� ����

				LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[U];
				LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[U];

				LocationRectangleShape[YPosition][XPosition].setTexture(UniqueFigureLocationTexture[U].get(), true);

				UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setTexture(UniqueFigureLocationTexture[U].get(), true);
				UniqueFigureLocationRectangleShape[YPosition][XPosition].first = U;
			}
			// � ��������� ������ ������� ��� ������ ������
			else

			{
				U = 1; // �������� �� ������ ������ (������)

				LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[U];
				LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[U];

				LocationRectangleShape[YPosition][XPosition].setTexture(UniqueFigureLocationTexture[U].get(), true);

				UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setTexture(UniqueFigureLocationTexture[U].get(), true);
			}

			//--//--//--//--//--//--//--//--//--//   ��� ����� �� �����  //--//--//--//--//--//--//--//--//--//--//--//--//--//-//
																																
			LocationRectangleShape[YPosition][XPosition].setSize(Vector2f(SizeCell, SizeCell));										
			LocationRectangleShape[YPosition][XPosition].setPosition(Vector2f(XPosition * SizeCell, YPosition * SizeCell));		

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			//--//--//--//--//--//--//--//--//--//     ��� ���������� �����   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));			
			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setPosition(Vector2f(XPosition * SizeCell * PrecentSizeFigure + WindowHeight, YPosition * SizeCell * PrecentSizeFigure + WindowHeight / 2 ));
			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setOutlineColor(Color::Black);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			VectorLocationFigure[YPosition][XPosition].first = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			VectorLocationFigure[YPosition][XPosition].second = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
		}
	}
}

//--//--//--//--//--//--//--//--//--//    ��� ����� �� �����   //--//--//--//--//--//--//--//--//--//--//--//--//


bool FigureLocation::SetFigure(int XPosition, int YPosition, string ID_Figure, int Side, bool invulnerable)
{

	if (LocationClassFigure[YPosition][XPosition]->GetSIDE() == -1)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> ������� ���������� �� �������");
		return false;
	}

	for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
	{
		//������� �������� ��������� ������
		if (   UniqueFigureLocationClassFigure[it]->GetSIDE() == Side 
			&& UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE() == ID_Figure
			&& UniqueFigureLocationClassFigure[it]->GetINVULNERABLE() == invulnerable
		   )
		{

			// ������������ �������� ������ �� ����
			LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[it];

			// ������������� ������� � ������ ������ -> ������ ��� ������ ������ ��� ����
			LocationRectangleShape[YPosition][XPosition].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
			LocationRectangleShape[YPosition][XPosition].setPosition(Vector2f(XPosition * SizeCell + PositionRectangInCell, YPosition * SizeCell + PositionRectangInCell));
			// �������� ������������� ��������
			LocationRectangleShape[YPosition][XPosition].setTexture(LocationTexture[YPosition][XPosition].get(), true);

			//������ ����� ������ �� ����
			LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[it];

			return true;
		}
	}
	OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> ������ �� �������, ������� �� ���������� �������� -> AddUniqueFigure()");
	return false;
}

bool FigureLocation::PromoutionSelectFigure(string ID_Figure)
{
	// ������ ����� ������������ � ��������� ������???.........
	if (LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first]->GetPromoutionFigure(ID_Figure))
	{
		for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
		{
			if (UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE() == ID_Figure && UniqueFigureLocationClassFigure[it]->GetSIDE() == LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first]->GetSIDE())
			{
				// �������� ��������
				LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationTexture[it];

				// �������� ������������� ��������
				LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

				//������ ����� ������ �� ����
				LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationClassFigure[it];

				return true;
			}
		}
		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> �� ������ ��������");
	}
	{
		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> ���������� ������������ � ��� ������");
	}
	return false;
}

bool FigureLocation::AddUniqueFigure(shared_ptr<Figure> NewFigure, path CurrentTextureFigure)
{
	// ���������� ������� ��� ������ ���������� 
	// ��������� ���� �� ����� ������ � ��� ���?
	// �������� � 2 �.�. 0 � 1 ����� ������ ������� "�����" � ������ ������� "�������" ��������������
	int Size = UniqueFigureLocationClassFigure.size();

	for (int it = 2; it < Size; it++)
	{
		// ���� ���� ��������� ������ �� ��������� � �� ���������
		if ( UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()         == NewFigure->Get_ID_FIGURE() 
			 && UniqueFigureLocationClassFigure[it]->GetSIDE()            == NewFigure->GetSIDE()
			 && UniqueFigureLocationClassFigure[it]->GetINVULNERABLE()    == NewFigure->GetINVULNERABLE()
		   )
		{
			//�� ���������
			return false;
		}	
	}

	// �����, ���� ���� ���������� ���������
	UniqueFigureLocationClassFigure.push_back(NewFigure);
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(CurrentTextureFigure));

	for (int Row = 1; Row < CountCellOnYPosition - 1; Row++)
	{
		for (int Col = 1; Col < CountCellOnXPosition - 1; Col++)
		{
			// ���� ������ ������ �� ����� �� ��������� ���������� ������ �� ���� ���������� �����
			if (UniqueFigureLocationRectangleShape[Row][Col].first == 0)
			{
				size_t LatestElement = UniqueFigureLocationTexture.size() - 1;

				// ������ ��������
				UniqueFigureLocationRectangleShape[Row][Col].second.setTexture(UniqueFigureLocationTexture[LatestElement].get(), true);
				UniqueFigureLocationRectangleShape[Row][Col].second.setOutlineThickness(-2);
				UniqueFigureLocationRectangleShape[Row][Col].second.setOutlineColor(Color::Black);

				// ������ �������� ������ ���������
				UniqueFigureLocationRectangleShape[Row][Col].first = LatestElement;
				return true;
			}
		}
	}	
	return false;
}


bool FigureLocation::MoveSelectFigure(int XPositionMove, int YPositionMove)
{
	vector<vector<bool>> AvailableMove = GetAvailableMovesForSelectFigure();

	if (!AvailableMove[YPositionMove][XPositionMove])
	{
		OutputLog("��� ����������");
		return false;
	}

	if (LocationClassFigure[YPositionMove][XPositionMove]->GetSIDE() == 0)
	{
		swap(LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first], LocationClassFigure[YPositionMove][XPositionMove]);
		swap(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first], LocationTexture[YPositionMove][XPositionMove]);


		//�������� ������ � ���������
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setSize(Vector2f(SizeCell, SizeCell));
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setPosition(Vector2f(SizeCell * PositionSelectFigure.first, SizeCell * PositionSelectFigure.second));

		// ���������� ������� �.�. ��� ��������
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

		//�������� ������ � ���������
		LocationRectangleShape[YPositionMove][XPositionMove].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
		LocationRectangleShape[YPositionMove][XPositionMove].setPosition(Vector2f(SizeCell * XPositionMove + PositionRectangInCell, SizeCell * YPositionMove + PositionRectangInCell));

		// ���������� ������� �.�. ��� ��������
		LocationRectangleShape[YPositionMove][XPositionMove].setTexture(LocationTexture[YPositionMove][XPositionMove].get(), true);

		return true;
	}
	// ���� ������ �� ������ �������������� ��� ��� ������ ������� ������
	else
	{	
		// ������ ������ ���� �������� ��� ������ �.�. Invulnerability = false		
		if (LocationClassFigure[YPositionMove][XPositionMove]->GetINVULNERABLE())
		{
			OutputLog("ERROR -> class -> FigureLocation -> MoveSelectFigure() -> ������ ���������");
			return false;
		}

		swap(LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first], LocationClassFigure[YPositionMove][XPositionMove]);
		swap(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first], LocationTexture[YPositionMove][XPositionMove]);

		//
		LocationRectangleShape[YPositionMove][XPositionMove].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
		LocationRectangleShape[YPositionMove][XPositionMove].setPosition(Vector2f(SizeCell * XPositionMove + PositionRectangInCell, SizeCell * YPositionMove + PositionRectangInCell));

		//
		LocationRectangleShape[YPositionMove][XPositionMove].setTexture(LocationTexture[YPositionMove][XPositionMove].get(), true);

		//
		LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationTexture[1]; // 1 - ������ ��������

		//
		LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationClassFigure[1]; // 1 - ������ ������ (������)

		//
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setSize(Vector2f(SizeCell, SizeCell));
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setPosition(Vector2f(SizeCell * PositionSelectFigure.first, SizeCell * PositionSelectFigure.second));
		//
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

		return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////

pair<int, int> FigureLocation::GetPositionFigureWhenMousePressed(Vector2f PositonMouse)
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			// ���� ������ ������ �� ������� ����
			if (LocationRectangleShape[YPosition][XPosition].getGlobalBounds().contains(PositonMouse))
			{
				return make_pair(XPosition, YPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////


bool FigureLocation::SeletcFigure(int XPositionFigure, int YpositionFigure)
{
	int SideFigure = LocationClassFigure[YpositionFigure][XPositionFigure]->GetSIDE();

	if (SideFigure == 0 || SideFigure == -1)
	{
		return false;
	}
	if (SelectFigure)
	{
		UnSeletcFigure();
	}

	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineThickness(-3);
	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineColor(Color::Red);

	PositionSelectFigure = make_pair(XPositionFigure, YpositionFigure);
	SelectFigure = true;

	return SelectFigure;
}

bool FigureLocation::UnSeletcFigure()
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			LocationRectangleShape[YPosition][XPosition].setOutlineThickness(0);
		}
	}
	PositionSelectFigure = make_pair(0, 0);
	SelectFigure = false;

	return true;
}

bool FigureLocation::FiguresSelectedOrNot()
{
	return SelectFigure;
}
pair<int, int> FigureLocation::GetPositionSelectFigure()
{
	return PositionSelectFigure;
}
//////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////

vector<vector<bool>> FigureLocation::GetAvailableMovesForSelectFigure()
{
	pair<int, int> Position = GetPositionSelectFigure();
	return LocationClassFigure[Position.second][Position.first]->GetMoveForFigure(Position.first, Position.second, GetVectorLocationFigure());
}

bool FigureLocation::PromoutionFigureOnPosition(int XPositionFigure, int YpositionFigure)
{
	return LocationClassFigure[YpositionFigure][XPositionFigure]->GetPossibilityPromotion(XPositionFigure, YpositionFigure, GetVectorLocationFigure());
}

vector<vector<pair<int,string>>>  FigureLocation::GetVectorLocationFigure()
{
	UpdateVectorIntLocationFigure();
	return VectorLocationFigure;
}

void FigureLocation::UpdateVectorIntLocationFigure()
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			VectorLocationFigure[YPosition][XPosition].first = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			VectorLocationFigure[YPosition][XPosition].second = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
		}
	}
}

//////////////////////////////////////////////////////////////////////

string FigureLocation::GetIDFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->Get_ID_FIGURE();
}

int FigureLocation::GetSideFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetSIDE();
}

const RectangleShape& FigureLocation::GetRectangleShapeFigure(int XPosition, int Yposition)
{
	return LocationRectangleShape[Yposition][XPosition];
}

bool FigureLocation::GetInvulnerableFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetINVULNERABLE();
}
//////////////////////////////////////////////////////////////////////








//--//--//--//--//--//--//--//--//--//      ��� ���� ���������� �����     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::GetInvulnerableUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetINVULNERABLE();
}

string FigureLocation::GetIDUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE();
}

int FigureLocation::GetSideUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetSIDE();
}

const RectangleShape& FigureLocation::GetRectangleShapeUniqueFigure(int XPosition, int Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].second;
}

int FigureLocation::GetIteratorUniqueFigure(int XPosition, int Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].first;
}

bool FigureLocation::SeletcUniqueFigureForPromoution(int XPositionFigure, int YPositionFigure)
{
	// �������� ������ � ������� ����� ������������ ������
	int SideFigure = LocationClassFigure[YPositionFigure][XPositionFigure]->GetSIDE();

	for ( auto& VectorRectangleShape : UniqueFigureLocationRectangleShape)
	{
		for ( auto& RectangleShape : VectorRectangleShape)
		{
			int it = RectangleShape.first;

			// ���� ������ ��� �� �������.......
			if (UniqueFigureLocationClassFigure[it]->GetSIDE() == SideFigure)
			{
				// � ����� ������������ � ��������� ������???... ......
				if (LocationClassFigure[YPositionFigure][XPositionFigure]->GetPromoutionFigure(UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()))
				{
					//������������ ������
					RectangleShape.second.setOutlineColor(Color::Red);
				}
			}
		}
	}
	return true;
}

bool FigureLocation::UnSeletcUniqueFigure()
{
	for (auto& VectorRectangleShape : UniqueFigureLocationRectangleShape)
	{
		for (auto& RectangleShape : VectorRectangleShape)
		{
			RectangleShape.second.setOutlineColor(Color::Black);
		}
	}
	return true;
}

pair<int, int> FigureLocation::GetPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse)
{
	for (int YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			// ���� ������ ������ �� ���� ���������� ����� ���������� ������� � ������
			if (UniqueFigureLocationRectangleShape[YPosition][XPosition].second.getGlobalBounds().contains(PositonMouse))
			{
				return make_pair(XPosition, YPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}


