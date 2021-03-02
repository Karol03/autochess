/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <inttypes.h>
#include "pieces.hpp"


namespace dsp
{
enum Field_value
{
    A_1 = 0x4131,
    B_1 = 0x4231,
    C_1 = 0x4331,
    D_1 = 0x4431,
    E_1 = 0x4531,
    F_1 = 0x4631,
    G_1 = 0x4731,
    H_1 = 0x4831,
    A_2 = 0x4132,
    B_2 = 0x4232,
    C_2 = 0x4332,
    D_2 = 0x4432,
    E_2 = 0x4532,
    F_2 = 0x4632,
    G_2 = 0x4732,
    H_2 = 0x4832,
    A_7 = 0x4137,
    B_7 = 0x4237,
    C_7 = 0x4337,
    D_7 = 0x4437,
    E_7 = 0x4537,
    F_7 = 0x4637,
    G_7 = 0x4737,
    H_7 = 0x4837,
    A_8 = 0x4138,
    B_8 = 0x4238,
    C_8 = 0x4338,
    D_8 = 0x4438,
    E_8 = 0x4538,
    F_8 = 0x4638,
    G_8 = 0x4738,
    H_8 = 0x4838
};

struct PieceAtPosition
{
    PieceAtPosition(int id, int multichar)
    {
        m_data = (id & 0xFF);
        m_data <<= 8;
        m_data |= ((toupper(((multichar & 0xFF00) >> 8)) - 'A') & 0xFF);
        m_data <<= 8;
        m_data |= (((multichar & 0xFF) - '1') & 0xFF);
    }

    inline bool isAt(uint32_t position) const
    {
        return (m_data & 0xFFFF) == (position & 0xFFFF);
    }

    inline int get() const
    {
        return (m_data >> 16) & 0xFF;
    }

    inline Player getPlayer() const
    {
        if ((m_data >> 16) >= PIECES_PER_PLAYER)
        {
            return Player::EBlack;
        }
        return Player::EWhite;
    }

    inline void update(uint32_t position)
    {
        m_data &= (0xFFFF0000);
        m_data |= (position & 0xFFFF);
    }

private:
    uint32_t m_data;
};

struct PieceMap
{
    explicit PieceMap()
        : m_data{{0, H_2}, {1, G_2}, {2, F_2}, {3, E_2},
                 {4, D_2}, {5, C_2}, {6, B_2}, {7, A_2},
                 {8, H_1}, {9, A_1}, {10, F_1}, {11, C_1},
                 {12, G_1}, {13, B_1}, {14, D_1}, {15, E_1},
                 {16, H_7}, {17, G_7}, {18, F_7}, {19, E_7},
                 {20, D_7}, {21, C_7}, {22, B_7}, {23, A_7},
                 {24, H_8}, {25, A_8}, {26, F_8}, {27, C_8},
                 {28, G_8}, {29, B_8}, {30, D_8}, {31, E_8}}
    {}

    inline int findByPosition(uint16_t position) const
    {
        auto it = std::find_if(std::begin(m_data), std::end(m_data),
                            [&position](const auto& pieceAt) { return pieceAt.isAt(position); });
        if (it != std::end(m_data))
        {
            return it->get();
        }
        return -1;
    }

    inline void update(int piece, uint16_t position)
    {
        m_data[piece].update(position);
    }

private:
    PieceAtPosition m_data[PIECES_IN_CHESS];
};
}  // namespace dsp
