/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

namespace dsp
{
enum class Piece
{
    EPawn   = 0,
    ERook   = 1,
    EBishop = 2,
    EKnight = 3,
    EQueen  = 4,
    EKing   = 5
};

enum class Player
{
    EWhite  = 0,
    EBlack  = 6
};
}  // namespace dsp
