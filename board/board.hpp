/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <memory>
#include <iostream>

#include "src/position.hpp"
#include "src/rules.hpp"


struct Board
{
private:
    using Bitboards = uint64_t;

public:
    explicit Board()
    {
        resetBoard();
    }

    inline void resetBoard()
    {
        m_positions[EBlack] = 0xFFFF000000000000;
        m_positions[EWhite] = 0x000000000000FFFF;
    }

    inline bool move(Color color,
                     Piece piece,
                     Position from,
                     Position to,
                     const std::unique_ptr<Rules>& validator)
    {
        if (validator->isAvailable(m_positions, color, piece, from, to))
        {
            const auto piece_move = from.to_bitboard() | to.to_bitboard();
            m_positions[color] ^= piece_move;
            return true;
        }
        return false;
    }

private:
    Bitboards m_positions[2];
};
