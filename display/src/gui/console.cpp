/**
 * Created by Karol Dudzic @ 2021
 */
#include "console.hpp"

#include <cstring>
#include "logger.hpp"


namespace dsp::gui
{
Console::Console()
    : m_command{}
{
    m_buffer = std::make_shared<common::lsrc::Stringlog::Buffer>();
    common::Logger{}.set(std::make_unique<common::lsrc::Stringlog>(m_buffer));
}

void Console::handle()
{
    auto fullcmd = std::string(m_command);
    fullcmd += '\n';
    memset(&m_command[0], '\0', 64);
    process(fullcmd);    
}

void Console::process(std::string command)
{
    common::Logger{} << command;
}

char* Console::history(std::size_t elements)
{
    if (m_buffer->isChanged())
    {
        m_history.clear();
        for (auto&& log : m_buffer->tail(elements))
        {
            m_history += log;
        }
    }
    return &m_history[0];
}


}  // namespace dsp::gui
