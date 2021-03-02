/**
 * Created by Karol Dudzic @ 2021
 */

#include "onboardmove.hpp"
#include "display.hpp"
#include "movetranslator.hpp"


namespace dsp
{
OnboardMove::OnboardMove(std::string description)
    : m_item{MoveTranslator{}.toItem(std::move(description))}
{}

}  // namespace dsp
