#pragma once

#include "Core.h"

struct PropertiesFigure;
using GridPropertiesFigure = std::vector<std::vector<PropertiesFigure>>;



/// <summary>
/// Свойства фигуры
/// </summary>
struct PropertiesFigure
{

	/// <summary>
	/// сторона, к которой принадлежит фигура
	/// </summary>
	int side = 0;

	/// <summary>
	/// уникальный id первоначальной фигуры 
	/// </summary>
	std::wstring idFigure = L"";

	/// <summary>
	/// неуязвима ли фигура
	/// </summary>
	bool invulnerable = false;

	/// <summary>
	/// важная ли фигура
	/// </summary>
	bool important = false;

	/// <summary>
	/// может ли фигура преврашаться
	/// </summary>
	bool promoution = false;




	bool operator== (const PropertiesFigure& other) const
	{
		return side == other.side && idFigure == other.idFigure && invulnerable == other.invulnerable && important == other.important && promoution == other.promoution;
	};

};





struct PositionAndPropertiesFigure
{


	PositionAndPropertiesFigure(size_t xPosition, size_t yPosition, PropertiesFigure propertions, std::vector<PropertiesFigure> vectorPromoution)
	{
		this->xPosition = xPosition;
		this->yPosition = yPosition;
		this->propertions = propertions;
		this->vectorPromoution = vectorPromoution;
	}

	size_t xPosition;

	size_t yPosition;

	/// <summary>
	/// Свойства фигуры
	/// </summary>
	PropertiesFigure propertions;

	/// <summary>
	/// вектор с указанными свойствами фигур, в которые можно превратиться данной фигуре
	/// </summary>
	std::vector<PropertiesFigure> vectorPromoution;



	bool operator==(const PositionAndPropertiesFigure& other) const
	{
		return xPosition == other.xPosition && yPosition == other.yPosition && propertions == other.propertions && vectorPromoution == other.vectorPromoution;
	};


};
