#pragma once


#include "Core.h"


#include "Figure.h"

#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Space.h"

#include "PropertiesFigure.h"




namespace propertiesGame
{


	///////////////////////////////////// СВОЙСТВА ОКНА ////////////////////////////////////////////////////////////////

	/// <summary>
	/// высота окна
	/// </summary>
	extern  unsigned sizeWindowHeight;

	/// <summary>
	/// длина окна
	/// </summary>
	extern  unsigned sizeWindowLength;


	/// <summary>
	/// количество ИГРОВЫХ клеток на стороне + всегда 2 клетки для координат
	/// </summary>
	extern  size_t countCellOnLengthWindow;

	/// <summary>
	/// количество ИГРОВЫХ клеток на стороне + всегда 2 клетки для координат
	/// </summary>
	extern  size_t countCellOnHeightWindow;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////















	/////////////////////////////////////// СТАНДАРТНЫЕ ТЕКСТУРЫ И ШРИФТЫ ///////////////////////////////////////////

	/// <summary>
	/// используемый шрифт
	/// </summary>
	extern sf::Font currentFont;

	/// <summary>
	/// стандартная текстура для "края"
	/// </summary>
	extern std::filesystem::path pathToEmptyImage;

	/// <summary>
	/// стандартная текстура для "пустой клетки" на игровом поле
	/// </summary>
	extern std::filesystem::path pathToEmptyPawn;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


















	//////////////////////////////////////////// СВОЙСТВА ФИГУР //////////////////////////////////////////////////////



	/// превращения
	
	//inline extern std::array<PropertiesFigure, 4> promoutionForPawnPlayerOne;

	//inline extern std::array<PropertiesFigure, 4> promoutionForPawnPlayerTwo;









	/// УНИКАЛЬНЫЕ ФИГУРЫ

	/// <summary>
	/// вектор уникальный фигур и путей до текстур к ним
	/// </summary>
	extern std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> addedVectorUniqueFigures;









	/// РАСПОЛОЖЕНИЕ ФИГУР

	/// <summary>
	/// Предварительно готовый вектор с расположением фигур
	/// </summary>
	extern std::vector<PositionAndPropertiesFigure> currentVectorLocationFigure;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////





















	///////////////////////////////////// СВОЙСТВА ИГРОКОВ //////////////////////////////////////////////////////////


	/// <summary>
	/// количество игроков (сторон)
	/// </summary>
	extern int countPlayer;

	/// <summary>
	/// начальный игрок
	/// </summary>
	extern int currentPlayer;



	extern std::wstring currentParty;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




}