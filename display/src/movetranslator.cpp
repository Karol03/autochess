/**
 * Created by Karol Dudzic @ 2021
 */

#include "streamitem.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include "display.hpp"
#include "movetranslator.hpp"
#include "pieces.hpp"


#define DSP_MOVE_MOVE(params) ([p = std::string(params)](const std::shared_ptr<dsp::Display>& display) \
    { \
        display->move(p[0] - 'A', p[1] - '1', p[2] - 'A', p[3] - '1'); \
    })

#define DSP_MOVE_CLEAR(params) ([p = std::string(params)](const std::shared_ptr<dsp::Display>& display) \
    { \
        display->clear(p[0] - 'A', p[1] - '1'); \
    })

#define DSP_MOVE_TAKE(params) ([p = std::string(params)](const std::shared_ptr<dsp::Display>& display) \
    { \
        display->clear(p[2] - 'A', p[3] - '1'); \
        display->move(p[0] - 'A', p[1] - '1', p[2] - 'A', p[3] - '1'); \
    })

#define DSP_MOVE_PROMOTE(params, figure) ([p = std::string(params), figure](const std::shared_ptr<dsp::Display>& display) \
    { \
        display->promote(p[0] - 'A', p[1] - '1', figure); \
    })



namespace dsp
{
StreamItem MoveTranslator::toItem(std::string description)
{
    std::cerr << "Translate input: " << description << '\n';

    if (description.empty())
    {
        std::cerr << "[ERROR] Empty move desctiption!\n";
        return StreamItem();
    }

    toUpper(description);
    auto pl = player(description);

    if (pl == -1)
    {
        std::cerr << "[ERROR] Move should start with a number\n";
        return StreamItem();
    }

    removeSpaces(description);
    skipToMove(description);
    if (description.size() <= 2)
    {
        std::cerr << "[ERROR] No move after move number: " << description << '\n';
        return StreamItem();
    }

    removePiecesType(description);
    removeUnknownSymbols(description);
    return makeMoveItem(description, pl);
}

int MoveTranslator::player(const std::string& description)
{
    const auto no = std::atoi(description.c_str());
    if (no <= 0)
    {
        return -1;
    }
    return (no - 1) % 2;
}

void MoveTranslator::removeSpaces(std::string& description)
{
    description.erase(remove_if(description.begin(), description.end(), isspace), description.end());
}

void MoveTranslator::removePiecesType(std::string& description)
{
    const auto isFigure = [](const char c) { return c == 'Q' || c == 'N' || c == 'R' || c == 'B' || c == 'K'; };
    const auto isField = [](const char c) { return ('A' <= c and c <= 'H'); };
    if (isFigure(description[0]) and isField(description[1]))
    {
        description = description.substr(1);
    }
}

void MoveTranslator::removeUnknownSymbols(std::string& description)
{
    const auto isFigure = [](const char c) { return c == 'Q' || c == 'N' || c == 'R' || c == 'B'; };
    const auto isKnown = [isFigure](const char c) { return ('A' <= c and c <= 'H') or ('1' <= c and c <= '8') or c == 'O' or c == 'X' or isFigure(c); };
    const auto isUnknown = [isKnown](const char c) { return not isKnown(c); };
    description.erase(remove_if(description.begin(), description.end(), isUnknown), description.end());
}

void MoveTranslator::skipToMove(std::string& description)
{
    auto it = description.find('.');
    if (it == std::string::npos)
    {
        description.clear();
        return;
    }

    description = description.substr(it + 1);
}

void MoveTranslator::toUpper(std::string& description)
{
    std::transform(description.begin(), description.end(), description.begin(), ::toupper);
}


StreamItem MoveTranslator::makeMoveItem(const std::string& description, bool player)
{
    StreamItem::MovesQueue moves;

    if (isLongCastle(description))
    {
        addLongCastle(player, moves);
    }
    else if (isShortCastle(description))
    {
        addShortCastle(player, moves);
    }
    else if (isInPassing(description))
    {
        addInPassingMove(description, moves);
    }
    else if (isTakesMove(description))
    {
        addTakesMove(description, moves);
        auto desc = description;
        desc.erase(remove(desc.begin(), desc.end(), 'X'), desc.end());
        if (isPromotion(desc))
        {
            addPromotion(desc, moves);
        }
    }
    else if (isNormalMove(description))
    {
        addNormalMove(description, moves);
        if (isPromotion(description))
        {
            addPromotion(description, moves);
        }
    }
    else
    {
        std::cerr << "[ERROR] Unknown move: " << description << '\n';
    }
    return StreamItem(std::move(moves));
}

bool MoveTranslator::isLongCastle(const std::string& description)
{
    return description == "OOO";
}

void MoveTranslator::addLongCastle(bool player, StreamItem::MovesQueue& moves)
{
    constexpr auto WHITE_PLAYER = false;
    if (player == WHITE_PLAYER)
    {
        moves.push_back(DSP_MOVE_MOVE("E1C1"));
        moves.push_back(DSP_MOVE_MOVE("A1D1"));
    }
    else
    {
        moves.push_back(DSP_MOVE_MOVE("E8C8"));
        moves.push_back(DSP_MOVE_MOVE("A8D8"));
    }
}

bool MoveTranslator::isShortCastle(const std::string& description)
{
    return description == "OO";
}

void MoveTranslator::addShortCastle(bool player, StreamItem::MovesQueue& moves)
{
    constexpr auto WHITE_PLAYER = false;
    if (player == WHITE_PLAYER)
    {
        moves.push_back(DSP_MOVE_MOVE("E1G1"));
        moves.push_back(DSP_MOVE_MOVE("H1F1"));
    }
    else
    {
        moves.push_back(DSP_MOVE_MOVE("E8G8"));
        moves.push_back(DSP_MOVE_MOVE("H8F8"));
    }
}

bool MoveTranslator::isPromotion(const std::string& description)
{
    auto isFigure = [](const char c) { return c == 'Q' || c == 'N' || c == 'R' || c == 'B'; };
    if (description.size() == 5 && isFigure(description[4]))
    {
        return description[1] == '2' or description[1] == '7';
    }
    return false;
}

void MoveTranslator::addPromotion(const std::string& description, StreamItem::MovesQueue& moves)
{
    auto figure = Piece::EQueen;
    switch (description[4])
    {
    case 'Q': break;
    case 'N': figure = Piece::EKnight; break;
    case 'R': figure = Piece::ERook; break;
    case 'B': figure = Piece::EBishop; break;
    default: break;
    }

    auto params = std::string{description[2]};
    params += description[3];
    moves.push_back(DSP_MOVE_PROMOTE(params, figure));
}

bool MoveTranslator::isInPassing(const std::string& description)
{
    return description.size() == 5 and description[4] == 'E';
}

void MoveTranslator::addInPassingMove(const std::string& description, StreamItem::MovesQueue& moves)
{
    auto oppontentField = std::string{description[2]};
    if (description[3] == '6')
    {
        oppontentField += '5';
    }
    else
    {
        oppontentField += '4';
    }

    moves.push_back(DSP_MOVE_CLEAR(oppontentField));
    moves.push_back(DSP_MOVE_MOVE(description));
}

bool MoveTranslator::isTakesMove(std::string description)
{
    return description[2] == 'X';
}

void MoveTranslator::addTakesMove(const std::string& description, StreamItem::MovesQueue& moves)
{
    auto result = description;
    remove(result.begin(), result.end(), 'X');
    moves.push_back(DSP_MOVE_TAKE(result));
}

bool MoveTranslator::isNormalMove(std::string description)
{
    return description.size() == 4 or description.size() == 5;
}

void MoveTranslator::addNormalMove(const std::string& description,
                                   StreamItem::MovesQueue& moves)
{
    moves.push_back(DSP_MOVE_MOVE(description));
}

}  // namespace dsp
