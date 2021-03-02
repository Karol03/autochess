/**
 * Created by Karol Dudzic @ 2021
 */

#include "displayhandler.hpp"

#include "display.hpp"
#include "movestream.hpp"


namespace dsp
{

DisplayHandler::DisplayHandler(MoveStreamPtr stream,
                               int width, int height)
    : m_isCalledClose{false}
    , m_display{std::make_shared<dsp::Display>(width, height)}
    , m_stream{std::make_shared<MoveStream>()}
{
    if (stream)
    {
        std::swap(m_stream, stream);
    }
    m_display->tie(m_stream);
}

void DisplayHandler::close()
{
    m_isCalledClose = true;
}

void DisplayHandler::work()
{
    StreamItem item;
    while (m_display->isActive() && !m_isCalledClose)
    {
        if (m_stream->isAvailable() && m_stream->dequeue(item))
        {
            item.modifyOn(m_display);
            m_display->run();
        }
        m_display->refresh();
    }
}

MoveStreamPtr DisplayHandler::stream()
{
    return m_stream;
}

}  // namespace dsp
