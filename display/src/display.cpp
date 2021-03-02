/**
 * Created by Karol Dudzic @ 2021
 */

#include "display.hpp"

#include "src/window.hpp"


namespace dsp
{
Display::Display(int width, int height)
    : m_isFreerun{true}
    , m_window{std::make_shared<dsp::Window>(width, height)}
{}

bool Display::isActive() const
{
    return m_window && m_window->is_open();
}

void Display::run()
{
    m_window->draw();
}

void Display::refresh()
{
    m_window->handle_events();
}

void Display::move(int fromHoriz, int fromVert, int toHoriz, int toVert)
{
    auto from_to = uint32_t(fromHoriz);
    from_to <<= 8;
    from_to |= fromVert;
    from_to <<= 8;
    from_to |= toHoriz;
    from_to <<= 8;
    from_to |= toVert;
    m_window->move(from_to);
}

void Display::clear(int horiz, int vert)
{
    auto from = uint16_t(horiz);
    from <<= 8;
    from |= vert;
    m_window->remove(from);
}

void Display::promote(int horiz, int vert, Piece to)
{
    auto from = uint16_t(horiz);
    from <<= 8;
    from |= vert;
    m_window->promote(from, to);
}

void Display::tie(MoveStreamPtr stream)
{
    if (!m_isFreerun)
    {
        throw std::runtime_error{"Change stream after detach is impossible"};
    }
    std::swap(m_stream, stream);
    m_window->tie(m_stream);
}

void Display::resetBoard()
{
    m_window->reset();
}

void Display::colorLastMove(bool isColor)
{
    m_window->color_last_word(isColor);
}

void Display::setColor(dsp::Player player, RGB rgb)
{
    m_window->color_fields(player) = sf::Color(rgb.r, rgb.g, rgb.b);
    m_window->color_board();
}

}  // dsp
