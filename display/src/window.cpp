/**
 * Created by Karol Dudzic @ 2021
 */

#include "window.hpp"
#include <iostream>

#define PIECES_IMAGE_PATH RESOURCES_PATH "/pawns.png"


namespace dsp
{
Window::Window(float width, float height, sf::Color white, sf::Color black)
    : m_isGuiOpened{false}
    , m_isColorLastMove{false}
    , m_drawablePieces(0xFFFFFFFF)
    , m_size{width, height}
    , m_black{black}
    , m_white{white}
{
    prepare_board();
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "board");
    m_gui.init(*m_window);
    draw();
}

void Window::color_board()
{
    constexpr auto CHESS_BOARD_HORIZONTAL_FIELDS = 8.f;
    constexpr auto CHESS_BOARD_VERTICAL_FIELDS = 8.f;

    const auto w = m_size.x / CHESS_BOARD_HORIZONTAL_FIELDS;
    const auto h = m_size.y / CHESS_BOARD_VERTICAL_FIELDS;

    for(auto i{0u}; i < CHESS_BOARD_VERTICAL_FIELDS; ++i)
    {
        for(auto j{0u}; j < CHESS_BOARD_HORIZONTAL_FIELDS; ++j)
        {
            const auto x = static_cast<float>(j) * w;
            const auto y = static_cast<float>(i) * h;
            const auto position = static_cast<int>(i * CHESS_BOARD_VERTICAL_FIELDS + j);
            const auto& color = (i % 2 xor j % 2 ? m_black : m_white);
            const auto fieldNo = position * VERTEXES_IN_QUAD;
            auto* field = &m_board[fieldNo];

            field[0].position = sf::Vector2f(x, y);
            field[1].position = sf::Vector2f(x + w, y);
            field[2].position = sf::Vector2f(x + w, y + h);
            field[3].position = sf::Vector2f(x, y + h);

            field[0].color = color;
            field[1].color = color;
            field[2].color = color;
            field[3].color = color;
        }
    }
}

void Window::color_field(sf::Vector2i position, sf::Color color)
{
    constexpr auto CHESS_BOARD_VERTICAL_FIELDS = 8;
    const auto pos = position.y * CHESS_BOARD_VERTICAL_FIELDS + position.x;
    const auto fieldNo = pos * VERTEXES_IN_QUAD;
    auto* field = &m_board[fieldNo];
    field[0].color = color;
    field[1].color = color;
    field[2].color = color;
    field[3].color = color;
}

void Window::prepare_board()
{
    color_board();
    prepare_pieces();
}

void Window::handle_events()
{
    if (m_window && m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            m_gui.processEvent(event);
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
                m_window.reset();
                return;
            }
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Tilde)
            {
                m_isGuiOpened = !m_isGuiOpened;
                m_gui.setVisible(m_isGuiOpened);
                return;
            }
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Enter)
            {
                m_gui.handleEnter();
            }
        }

        m_gui.draw(*m_window);
        draw();
    }
}

void Window::draw()
{
    m_window->clear();
    m_window->draw(m_board, CHESS_BOARD_SIZE * VERTEXES_IN_QUAD, sf::Quads);
    draw_pieces();
    m_gui.display(*m_window);
    m_window->display();
}

void Window::draw_pieces()
{
    for (int i = 0; i < PIECES_IN_CHESS; ++i)
    {
        if (m_drawablePieces & (1 << i))
        {
            m_window->draw(m_pieces.get(i));
        }
    }
}

void Window::prepare_pieces()
{
#ifndef RESOURCES_PATH
    static_assert (false, "No path to resources defined");
#else
    if (not m_pieces.load(PIECES_IMAGE_PATH, m_size.x, m_size.y))
    {
        throw std::runtime_error{"Texture with pawns not found"};
    }
#endif
}

void Window::promote(uint16_t position, Piece to)
{
    const auto piece = m_map.findByPosition(position);
    if (piece != -1)
    {
        const auto player = (piece >= PIECES_PER_PLAYER) ? Player::EBlack : Player::EWhite;
        m_pieces.get(piece).setTexture(m_pieces.getTextureOf(player, to));
    }
}

void Window::remove(uint16_t from)
{
    const auto piece = m_map.findByPosition(from);
    if (piece != -1)
    {
        m_drawablePieces &= ~(1 << piece);
        m_map.update(piece, -1);
    }
}

void Window::reset()
{
    color_board();
    m_pieces.sort_pieces();
    m_drawablePieces = 0xFFFFFFFF;
}

void Window::move(uint32_t from_to)
{
    constexpr auto MAX_Y_POS = 7;
    const auto piece = m_map.findByPosition((from_to >> 16));
    if (piece != -1)
    {
        color_board();
        const auto oldPosition = sf::Vector2i{int(from_to >> 24),
                                              MAX_Y_POS - int((from_to >> 16) & 0xFF)};
        auto position = sf::Vector2i{int(from_to & 0xFF00) >> 8, int(from_to & 0xFF)};
        position.y = MAX_Y_POS - position.y;
        m_pieces.move(piece, position);
        m_map.update(piece, (from_to & 0xFFFF));
        if (m_isColorLastMove)
        {
            color_field(oldPosition, sf::Color::Red);
            color_field(position, sf::Color::Blue);
        }
    }
}
}  // namespace dsp
