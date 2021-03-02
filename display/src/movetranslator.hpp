/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include "streamitem.hpp"


namespace dsp
{
class MoveTranslator
{
public:
    StreamItem toItem(std::string description);

private:
    int player(const std::string& description);
    void toUpper(std::string& description);
    void skipToMove(std::string& description);
    void removeSpaces(std::string& description);
    void removePiecesType(std::string& description);
    void removeUnknownSymbols(std::string& description);

    StreamItem makeMoveItem(const std::string& description, bool player);
    bool isLongCastle(const std::string& description);
    bool isShortCastle(const std::string& description);
    bool isPromotion(const std::string& description);
    bool isInPassing(const std::string& description);
    bool isTakesMove(std::string description);
    bool isNormalMove(std::string description);

    void addLongCastle(bool player, StreamItem::MovesQueue& moves);
    void addShortCastle(bool player, StreamItem::MovesQueue& moves);
    void addPromotion(const std::string& description, StreamItem::MovesQueue& moves);
    void addInPassingMove(const std::string& description, StreamItem::MovesQueue& moves);
    void addTakesMove(const std::string& description, StreamItem::MovesQueue& moves);
    void addNormalMove(const std::string& description, StreamItem::MovesQueue& moves);
};

}  // namespace dsp
