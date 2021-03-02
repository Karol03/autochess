/**
 * Created by Karol Dudzic @ 2021
 */

#include "onboardconfig.hpp"

#include <sstream>
#include "display.hpp"
#include "configtranslator.hpp"


namespace dsp
{
OnboardConfig::OnboardConfig(std::string command)
    : m_item{ConfigTranslator{}.toItem(std::move(command))}
{}

std::string OnboardConfig::commands()
{
    std::stringstream result;
    result << "Board configuration available commands\n"
              "  changecolor <player> <r g b> - change color <black|white> <0-255 0-255 0-255>\n"
              "  colorlastmove\n"
              "  notcolorlastmove\n"
              "  reset - reset board to begin state\n";
    return result.str();
}

}  // namespace dsp
