/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "piecetype.hpp"


namespace dsp
{
constexpr auto PIECES_TYPES_IN_CHESS = 6;
constexpr auto PIECES_PER_PLAYER = 16;
constexpr auto PLAYERS_IN_CHESS = 2;
constexpr auto PIECES_IN_CHESS = 32;


struct PiecesImages
{
    explicit PiecesImages() = default;

    bool load(std::string path, int width, int height);
    bool prepare_pieces(int width, int height);
    sf::Sprite& get(Player player, Piece piece);
    sf::Sprite& get(unsigned i);
    sf::Texture& getTextureOf(Player player, Piece piece);
    void move(int piece, sf::Vector2<int> position);
    void sort_pieces();

private:
    int get_piece_copies_no(int piece);
    sf::Vector2<float> get_piece_position(int piece, int player, int no);

private:
    int m_fieldWidth;
    int m_fieldHeight;
    int m_widthOffset;
    int m_heightOffset;
    sf::Image m_piecesImage;
    sf::Texture m_textures[PIECES_TYPES_IN_CHESS * PLAYERS_IN_CHESS];
    sf::Sprite m_sprites[PIECES_IN_CHESS];
};
}  // namespace dsp
