#pragma once

#include "Core.h"

struct PropertiesFigure;

/// <summary>
/// Сетка содержащая информацию о фигурах находящихся на позициях
/// </summary>
template<typename T>
using Grid = std::vector<std::vector<T>>;

/// <summary>
/// свойства фигуры
/// </summary>
struct PropertiesFigure
{
	/// <summary>
	/// уникальный id первоначальной фигуры 
	/// </summary>
	std::wstring m_idFigure = L"";

	/// <summary>
	/// сторона, к которой принадлежит фигура
	/// </summary>
	int m_side = 0;

	/// <summary>
	/// неуязвима ли фигура
	/// </summary>
	bool m_invulnerable = false;

	/// <summary>
	/// важная ли фигура
	/// </summary>
	bool m_important = false;

	/// <summary>
	/// может ли фигура преврашаться
	/// </summary>
	bool m_promoution = false;

	PropertiesFigure() = default;

	PropertiesFigure(std::wstring idFigure, int side, bool invulnerable, bool important, bool promoution)
		: m_side(side), m_idFigure(idFigure), m_invulnerable(invulnerable), m_important(important), m_promoution(promoution) {};

	bool operator== (const PropertiesFigure& other) const
	{
		return (m_side         == other.m_side 
			&& 	m_idFigure     == other.m_idFigure 
			&& 	m_invulnerable == other.m_invulnerable 
			&& 	m_important    == other.m_important 
			&& 	m_promoution   == other.m_promoution);
	};
};

struct PositionAndPropertiesFigure
{
	/// <summary>
	/// Свойства фигуры
	/// </summary>
	PropertiesFigure m_propertions{};

	/// <summary>
	/// вектор с указанными свойствами фигур, в которые можно превратиться данной фигуре
	/// </summary>
	std::vector<PropertiesFigure> m_gridPromoution{};
	
	Position::Coordinates m_position{};

	PositionAndPropertiesFigure() = default;

	PositionAndPropertiesFigure(Position::Coordinates coordinates, PropertiesFigure propertions, std::vector<PropertiesFigure> gridPromoution) : m_position(coordinates), m_propertions(propertions), m_gridPromoution(gridPromoution) {};

	bool operator==(const PositionAndPropertiesFigure& other) const
	{
		return m_position == other.m_position && m_propertions == other.m_propertions && m_gridPromoution == other.m_gridPromoution;
	};

};
