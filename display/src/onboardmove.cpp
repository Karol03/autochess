/**
 * Created by Karol Dudzic @ 2021
 */

#include "onboardmove.hpp"

#include <sstream>
#include "display.hpp"
#include "movetranslator.hpp"


namespace dsp
{
OnboardMove::OnboardMove(std::string description)
    : m_item{MoveTranslator{}.toItem(std::move(description))}
{}

std::string OnboardMove::commands()
{
    std::stringstream result;
    result << "Game available commands are used to move pieces on the board.\n"
              "To move piece just write your move in long algebraic chess notation.\n"
              "Remember that each move must contains player number at the begining \n"
              "(1 - white player, 2 - black player)"
              "examples: '1. e4e5', '2. Bb5xc6', '1. O-O', '1. Qa3xa4+', '2. b2b1=Q'\n";
    return result.str();
}

}  // namespace dsp
