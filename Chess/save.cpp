#include "Main.h"
#include "json.hpp"

std::vector<PositionAndPropertiesFigure> fromJson_PositionAndPropertiesFigure(const nlohmann::json& jV);

bool importSave(std::filesystem::path pathToSave, int numberSave)
{
	std::ifstream jFile(pathToSave);

    if (!jFile.is_open())
    {
        OutputLog("Не удалось открыть файл сохранения:\t" + pathToSave.string());
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


                propertiesGame::currentVectorLocationFigure = fromJson_PositionAndPropertiesFigure(currentSave["vectorLocationFigure"]);
            }
            else
            {
                return false;
            }
            
            


        }
    }
    return true;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




bool exportSave()
{
    return false;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::vector<PositionAndPropertiesFigure> fromJson_PositionAndPropertiesFigure(const nlohmann::json& jV)
{
    std::vector<PositionAndPropertiesFigure> result;

    for (const auto& properties : jV)
    {
        ///
        /// координаты фигуры x \ y
        /// 
        std::pair<size_t, size_t> pos;
        if (properties.contains("v2Coordinate"))
        {
            pos = properties["v2Coordinate"].get< std::pair<size_t, size_t>>();
        }
        else
        {
            return {};
        }







        ///
        /// свойства фигуры
        /// 
        PropertiesFigure currentPropertiesFigure;
        if (   properties.contains("side")
            && properties.contains("idFigure")
            && properties.contains("invulnerable")
            && properties.contains("important")
            && properties.contains("promoution")
           )
        {
            currentPropertiesFigure.side         = properties["v2Coordinate"].get<int>();
            currentPropertiesFigure.idFigure     = properties["v2Coordinate"].get<std::wstring>();
            currentPropertiesFigure.invulnerable = properties["v2Coordinate"].get<bool>();
            currentPropertiesFigure.important    = properties["v2Coordinate"].get<bool>();
            currentPropertiesFigure.promoution   = properties["v2Coordinate"].get<bool>();
        }
        else
        {
            return {};
        }









        ///
        /// промоушен для текущей фигуры
        /// 
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
                    currentPropertiesFigure.side         = properties["v2Coordinate"].get<int>();
                    currentPropertiesFigure.idFigure     = properties["v2Coordinate"].get<std::wstring>();
                    currentPropertiesFigure.invulnerable = properties["v2Coordinate"].get<bool>();
                    currentPropertiesFigure.important    = properties["v2Coordinate"].get<bool>();
                    currentPropertiesFigure.promoution   = properties["v2Coordinate"].get<bool>();
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







        result.emplace_back(pos.first, pos.second, currentPropertiesFigure, currentPromoutionFigure);
    }

    return result;
}