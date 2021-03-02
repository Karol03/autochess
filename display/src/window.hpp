/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "gui/gui.hpp"
#include "pieces.hpp"
#include "piecesmap.hpp"


namespace dsp
{
constexpr auto VERTEXES_IN_QUAD = 4;
constexpr auto CHESS_BOARD_SIZE = 64;

class Window
{
    using Board = sf::Vertex[CHESS_BOARD_SIZE * VERTEXES_IN_QUAD];

public:
    explicit Window(float width,
                    float height,
                    sf::Color white = sf::Color(255, 243, 204),
                    sf::Color black = sf::Color(189, 153, 117));
    virtual ~Window() = default;

    void draw();
    void handle_events();
    void move(uint32_t from_to);
    void promote(uint16_t from, Piece to);
    void remove(uint16_t from);
    void reset();
    void color_board();
    void color_field(sf::Vector2i position, sf::Color color);

    inline bool is_open() const
    {
        return (m_window && m_window->isOpen());
    }

    inline auto& color_fields(Player player)
    {
        return player == Player::EWhite ? m_white : m_black;
    }

    inline void color_last_word(bool set = true)
    {
        m_isColorLastMove = set;
    }

    inline void tie(MoveStreamPtr stream)
    {
        m_gui.tie(std::move(stream));
    }

private:
    void draw_pieces();
    void prepare_board();
    void prepare_pieces();

private:
    gui::Gui m_gui;
    bool m_isGuiOpened;
    bool m_isColorLastMove;
    uint32_t m_drawablePieces;
    sf::Vector2f m_size;
    sf::Color m_black;
    sf::Color m_white;
    std::shared_ptr<sf::RenderWindow> m_window;
    PieceMap m_map;
    Board m_board;
    PiecesImages m_pieces;
};
}  // namespace dsp
