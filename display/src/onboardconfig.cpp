/**
 * Created by Karol Dudzic @ 2021
 */

#include "onboardconfig.hpp"
#include "display.hpp"
#include "configtranslator.hpp"


namespace dsp
{
OnboardConfig::OnboardConfig(std::string command)
    : m_item{ConfigTranslator{}.toItem(std::move(command))}
{}

}  // namespace dsp
