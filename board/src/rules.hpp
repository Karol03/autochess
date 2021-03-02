/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include "position.hpp"


enum Color : bool
{
    EWhite = 0,
    EBlack = 1
};

enum Piece : uint8_t
{
    EKing = 0,
    EQueen = 1,
    EBishop = 2,
    EKnight = 3,
    ERook = 4,
    EPawn = 5
};

class Rules
{
public:
    virtual ~Rules() = default;
    virtual bool isAvailable(uint64_t bitboard[],
                             Color color,
                             Piece piece,
                             Position from,
                             Position to) = 0;
};
