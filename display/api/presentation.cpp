/**
 * Created by Karol Dudzic @ 2021
 */

#include "presentation.hpp"
#include "display.hpp"
#include "movestream.hpp"


namespace
{
[[nodiscard]] DisplayPtr create_display() { return std::make_shared<dsp::Display>(); }
[[nodiscard]] DisplayPtr create_display(int w, int h) { return std::make_shared<dsp::Display>(w, h); }

[[nodiscard]] MoveStreamPtr create_stream() { return std::make_shared<dsp::MoveStream>(); }
}  // namespace

namespace disp
{
Handler::Handler(dsp::DisplayHandler&& handler)
    : m_handler(std::move(handler))
{}

Handler Handler::create_detached()
{
    auto display = create_display();
    auto stream = create_stream();
    display->tie(stream);
    return Handler(display->detach());
}

Handler Handler::create_detached(int w, int h)
{
    auto display = create_display(w, h);
    auto stream = create_stream();
    display->tie(stream);
    return Handler(display->detach());
}

void Handler::forward(const dsp::StreamItem& item)
{
    m_handler.forward(item);
}

void Handler::forward(dsp::StreamItem&& item)
{
    m_handler.forward(std::move(item));
}
}  // namespace disp
