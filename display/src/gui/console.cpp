/**
 * Created by Karol Dudzic @ 2021
 */
#include "console.hpp"

#include <cstring>


namespace dsp::gui
{
void Console::handle()
{
    const auto fullcmd = std::string(m_command);
    m_history += m_command;
    m_history += '\0';
    memset(&m_command[0], 0, 64);
    process(fullcmd);
}

void Console::process(std::string )
{

}

}  // namespace dsp::gui
