/**
 * Created by Karol Dudzic @ 2021
 */

#include "streamitem.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include "display.hpp"
#include "configtranslator.hpp"
#include "pieces.hpp"


namespace dsp
{

StreamItem ConfigTranslator::toItem(std::string command)
{
    std::cerr << "Translate input: " << command << '\n';

    if (command.empty())
    {
        std::cerr << "Empty command\n";
        return StreamItem{};
    }
    toUpper(command);

    {
        const auto item = resetItem(command);
        if (item.second)
        {
            std::cerr << "[Command] Reset board\n";
            return item.first;
        }
    }

    {
        const auto item = changeColorItem(command);
        if (item.second)
        {
            std::cerr << "[Command] Change color\n";
            return item.first;
        }
    }

    {
        const auto item = colorLastMoveItem(command);
        if (item.second)
        {
            std::cerr << "[Command] Color last move\n";
            return item.first;
        }
    }

    {
        const auto item = notColorLastMoveItem(command);
        if (item.second)
        {
            std::cerr << "[Command] Not color last move\n";
            return item.first;
        }
    }

    return StreamItem{};
}

void ConfigTranslator::toUpper(std::string& command)
{
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
}

void ConfigTranslator::skipWord(std::string& command)
{
    auto it = command.find(' ');
    if (it == std::string::npos)
    {
        command.clear();
        return;
    }

    it = command.find_first_not_of(' ', it);
    if (it == std::string::npos)
    {
        command.clear();
        return;
    }

    command = command.substr(it);
}

std::pair<StreamItem, bool> ConfigTranslator::changeColorItem(std::string& command)
{
    const auto isCk = (command.substr(0, command.find(' ')) == "CHANGECOLOR");
    if (!isCk)
    {
        return {StreamItem{}, false};
    }

    skipWord(command);
    const auto color = command.substr(0, command.find(' '));
    skipWord(command);
    const auto r = static_cast<uint8_t>(std::stoi(command.substr(0, command.find(' '))));
    skipWord(command);
    const auto g = static_cast<uint8_t>(std::stoi(command.substr(0, command.find(' '))));
    skipWord(command);
    const auto b = static_cast<uint8_t>(std::stoi(command.substr(0, command.find(' '))));
    if (color == "WHITE")
    {
        return {
            StreamItem{[r, g, b](const std::shared_ptr<dsp::Display>& display)
                {
                    display->setColor(Player::EWhite, {r, g, b});
                }}, true};
    }
    else if (color == "BLACK")
    {
        return {
            StreamItem{[r, g, b](const std::shared_ptr<dsp::Display>& display)
                {
                    display->setColor(Player::EBlack, {r, g, b});
                }}, true};
    }

    return {StreamItem{}, false};
}

std::pair<StreamItem, bool> ConfigTranslator::resetItem(std::string& command)
{
    if (command == "RESET")
    {
        return {
            StreamItem{
            [](const std::shared_ptr<dsp::Display>& display)
            {
                display->resetBoard();
            }}, true};
    }
    return {StreamItem{}, false};
}

std::pair<StreamItem, bool> ConfigTranslator::colorLastMoveItem(std::string& command)
{
    if (command == "COLORLASTMOVE")
    {
        return {
            StreamItem{
            [](const std::shared_ptr<dsp::Display>& display)
            {
                display->colorLastMove(true);
            }}, true};
    }
    return {StreamItem{}, false};
}

std::pair<StreamItem, bool> ConfigTranslator::notColorLastMoveItem(std::string& command)
{
    if (command == "NOTCOLORLASTMOVE")
    {
        return {
            StreamItem{
            [](const std::shared_ptr<dsp::Display>& display)
            {
                display->colorLastMove(false);
            }}, true};
    }
    return {StreamItem{}, false};
}

}  // namespace dsp
