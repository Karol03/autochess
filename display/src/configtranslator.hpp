/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include "streamitem.hpp"


namespace dsp
{
class ConfigTranslator
{
public:
    StreamItem toItem(std::string command);

private:
    void skipWord(std::string& command);
    void toUpper(std::string& command);

    std::pair<StreamItem, bool> colorLastMoveItem(std::string& command);
    std::pair<StreamItem, bool> changeColorItem(std::string& command);
    std::pair<StreamItem, bool> notColorLastMoveItem(std::string& command);
    std::pair<StreamItem, bool> resetItem(std::string& command);
};
}  // namespace dsp
