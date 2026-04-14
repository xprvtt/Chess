#include "Main.h"
#include "json.hpp"

std::vector<PositionAndPropertiesFigure> fromJsonPositionAndPropertiesFigure(const nlohmann::json& jV);

bool importSave(std::filesystem::path pathToSave, int numberSave)
{
	std::ifstream jFile(pathToSave);

    if (!jFile.is_open())
    {
        OUTPUT_LOG("Не удалось открыть файл сохранения:\t" + pathToSave.string());
        return false;
    }

    nlohmann::json jsonSave;
    jFile >> jsonSave;
    jFile.close();

    for (const auto& currentSave : jsonSave)
    {
        if (currentSave.contains("numberSave") && currentSave["numberSave"].get<int>() == numberSave)
        {
            if (   currentSave.contains("v2CountCell")
                && currentSave.contains("countPlayer")
                && currentSave.contains("currnetPlayer")
                && currentSave.contains("vectorLocationFigure")
                && currentSave.contains("party")
                )
            {
                propertiesGame::countPlayer = currentSave["countPlayer"].get<int>();
                propertiesGame::currentPlayer = currentSave["currnetPlayer"].get<int>();
                propertiesGame::currentParty = currentSave["party"].get<std::wstring>();

                auto cc = currentSave["v2CountCell"].get<std::pair<size_t, size_t>>();
                propertiesGame::countCellOnLengthWindow = cc.first;
                propertiesGame::countCellOnHeightWindow = cc.second;

                propertiesGame::currentVectorLocationFigure = fromJsonPositionAndPropertiesFigure(currentSave["vectorLocationFigure"]);
            }
            else
            {
                return false;
            }
        }
    }
    return true;

}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool exportSave()
{
    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<PositionAndPropertiesFigure> fromJsonPositionAndPropertiesFigure(const nlohmann::json& jV)
{
    std::vector<PositionAndPropertiesFigure> result;

    for (const auto& properties : jV)
    {
        // координаты фигуры x \ y
        Position::Coordinates pos;
        if (properties.contains("v2Coordinate"))
        {
            auto tmpPos = properties["v2Coordinate"].get<std::pair<size_t, size_t>>();
            pos = { tmpPos.first, tmpPos.second };
        }
        else
        {
            return {};
        }
        
        // свойства фигуры
        PropertiesFigure currentPropertiesFigure;
        if (   properties.contains("side")
            && properties.contains("idFigure")
            && properties.contains("invulnerable")
            && properties.contains("important")
            && properties.contains("promoution")
           )
        {
            currentPropertiesFigure.m_side         = properties["v2Coordinate"].get<int>();
            currentPropertiesFigure.m_idFigure     = properties["v2Coordinate"].get<std::wstring>();
            currentPropertiesFigure.m_invulnerable = properties["v2Coordinate"].get<bool>();
            currentPropertiesFigure.m_important    = properties["v2Coordinate"].get<bool>();
            currentPropertiesFigure.m_promoution   = properties["v2Coordinate"].get<bool>();
        }
        else
        {
            return {};
        }

        // промоушен для текущей фигуры
        std::vector<PropertiesFigure> currentPromoutionFigure;

        if (properties.contains("vecPromoutionFigure"))
        {
            for (const auto& currentPropertiesForFigure : properties)
            {
                PropertiesFigure currentPropertiesFigure;

                if (   properties.contains("s")
                    && properties.contains("id")
                    && properties.contains("in")
                    && properties.contains("im")
                    && properties.contains("pr")
                   )
                {
                    currentPropertiesFigure.m_side         = properties["v2Coordinate"].get<int>();
                    currentPropertiesFigure.m_idFigure     = properties["v2Coordinate"].get<std::wstring>();
                    currentPropertiesFigure.m_invulnerable = properties["v2Coordinate"].get<bool>();
                    currentPropertiesFigure.m_important    = properties["v2Coordinate"].get<bool>();
                    currentPropertiesFigure.m_promoution   = properties["v2Coordinate"].get<bool>();
                }
                else
                {
                    return {};
                }
                currentPromoutionFigure.push_back(currentPropertiesFigure);
            }
        }
        else
        {
            return {};
        }
        result.emplace_back(pos, currentPropertiesFigure, currentPromoutionFigure);
    }

    return result;
}