/**
 * Created by Karol Dudzic @ 2021
 */

#include "pieces.hpp"


namespace dsp
{
bool PiecesImages::load(std::string path, int width, int height)
{
    if (not m_piecesImage.loadFromFile(path))
    {
        return false;
    }
    return prepare_pieces(width, height);
}

bool PiecesImages::prepare_pieces(int width, int height)
{
    constexpr auto FIELDS_IN_ROW = 8.0f;
    constexpr auto FIELDS_IN_COLUMN = 8.0f;
    const auto IMAGE_WIDTH = m_piecesImage.getSize().x / 6.0f;
    const auto IMAGE_HEIGHT = m_piecesImage.getSize().y / 2.0f;

    m_fieldWidth = (width / FIELDS_IN_ROW);
    m_fieldHeight = (height / FIELDS_IN_COLUMN);

    const auto WIDTH_SCALE_FACTOR = m_fieldWidth / IMAGE_WIDTH;
    const auto HEIGHT_SCALE_FACTOR = m_fieldHeight / IMAGE_HEIGHT;
    const auto MAX_SCALE_FACTOR = std::min(WIDTH_SCALE_FACTOR, HEIGHT_SCALE_FACTOR);

    m_widthOffset = (m_fieldWidth - (IMAGE_WIDTH * MAX_SCALE_FACTOR)) / 2;
    m_heightOffset = (m_fieldHeight - (IMAGE_HEIGHT * MAX_SCALE_FACTOR)) / 2 - 10.f;

    auto pieceNo = 0;

    for (int i = 0; i < PIECES_TYPES_IN_CHESS * PLAYERS_IN_CHESS; ++i)
    {
        const auto piece = i % PIECES_TYPES_IN_CHESS;
        const auto player = (i / PIECES_TYPES_IN_CHESS) * PIECES_TYPES_IN_CHESS;
        const auto LEFT_CORN = piece * IMAGE_WIDTH;
        const auto TOP_CORN = i < PIECES_TYPES_IN_CHESS ? 0 : IMAGE_HEIGHT;
        m_textures[i].loadFromImage(m_piecesImage, sf::IntRect(LEFT_CORN, TOP_CORN, IMAGE_WIDTH, IMAGE_HEIGHT));

        auto pieceCopies = get_piece_copies_no(piece);
        while (pieceCopies--)
        {
            m_sprites[pieceNo].setTexture(m_textures[i]);
            m_sprites[pieceNo].scale(MAX_SCALE_FACTOR, MAX_SCALE_FACTOR);
            m_sprites[pieceNo].setPosition(
                        get_piece_position(piece, player, pieceCopies));
            ++pieceNo;
        }
    }

    return true;
}

void PiecesImages::sort_pieces()
{
    auto pieceNo = 0;
    for (int i = 0; i < PIECES_TYPES_IN_CHESS * PLAYERS_IN_CHESS; ++i)
    {
        const auto piece = i % PIECES_TYPES_IN_CHESS;
        const auto player = (i / PIECES_TYPES_IN_CHESS) * PIECES_TYPES_IN_CHESS;

        auto pieceCopies = get_piece_copies_no(piece);
        while (pieceCopies--)
        {
            m_sprites[pieceNo].setTexture(m_textures[i]);
            m_sprites[pieceNo].setPosition(
                        get_piece_position(piece, player, pieceCopies));
            ++pieceNo;
        }
    }
}

sf::Vector2<float> PiecesImages::get_piece_position(int piece, int player, int no)
{
    auto result = sf::Vector2<float>{};
    const auto color = static_cast<Player>(player);
    switch (static_cast<Piece>(piece))
    {
    case Piece::EPawn:
        result.x = m_fieldWidth * no;
        result.y = (color == Player::EBlack) ? m_fieldHeight : m_fieldHeight * 6;
        break;
    case Piece::ERook:
        result.x = (m_fieldWidth * 7) * no;
        result.y = (color == Player::EBlack) ? 0 : m_fieldHeight * 7;
        break;
    case Piece::EKnight:
        result.x = m_fieldWidth + (m_fieldWidth * 5) * no;
        result.y = (color == Player::EBlack) ? 0 : m_fieldHeight * 7;
        break;
    case Piece::EBishop:
        result.x = 2 * m_fieldWidth + (m_fieldWidth * 3) * no;
        result.y = (color == Player::EBlack) ? 0 : m_fieldHeight * 7;
        break;
    case Piece::EQueen:
        result.x = 3 * m_fieldWidth;
        result.y = (color == Player::EBlack) ? 0 : m_fieldHeight * 7;
        break;
    case Piece::EKing:
        result.x = 4 * m_fieldWidth;
        result.y = (color == Player::EBlack) ? 0 : m_fieldHeight * 7;
        break;
    default: break;
    }
    result.x += m_widthOffset;
    result.y += m_heightOffset;
    return result;
}

int PiecesImages::get_piece_copies_no(int piece)
{
    auto pieceCopies = 1;
    switch (static_cast<Piece>(piece))
    {
    case Piece::EPawn: pieceCopies = 8; break;
    case Piece::ERook:
    case Piece::EBishop:
    case Piece::EKnight: pieceCopies = 2; break;
    default: break;
    }
    return pieceCopies;
}

sf::Sprite& PiecesImages::get(unsigned i)
{
    return m_sprites[i % PIECES_IN_CHESS];
}

void PiecesImages::move(int piece, sf::Vector2<int> position)
{
    m_sprites[piece].setPosition(position.x * m_fieldWidth + m_widthOffset,
                                 position.y * m_fieldHeight + m_heightOffset);
}

sf::Texture& PiecesImages::getTextureOf(Player player, Piece piece)
{
    const auto textureId = static_cast<int>(player) + static_cast<int>(piece);
    return m_textures[textureId];
}
}  // namespace dsp
