/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <ctype.h>
#include <inttypes.h>
#include <utility>
#include <string>


struct Position
{
    explicit Position() = default;
    explicit Position(char horiz, char vert) { set(toupper(horiz) - 'A', toupper(vert) - '1'); }
    explicit Position(int32_t horiz, int32_t vert) { set(horiz - 1, vert - 1); }

    inline bool operator==(const Position& rhs) const
    {
        return m_pos == rhs.m_pos;
    }
    inline bool operator!=(const Position& rhs) const
    {
        return m_pos != rhs.m_pos;
    }

    inline bool set(int32_t horiz, int32_t vert)
    {
        if ((vert & 0xFFF8) or (horiz & 0xFFF8))
        {
            return false;
        }
        m_pos = (horiz << 4) | vert;
        return true;
    }

    inline uint64_t to_bitboard() const
    {
        const auto position = get();
        auto result = uint64_t{};
        result = (1 << position.first);
        result <<= (8 * position.second);
        return result;
    }

    inline std::pair<uint8_t, uint8_t> get() const
    {
        auto result = std::pair<uint8_t, uint8_t>{};
        result.first = m_pos >> 4;
        result.second = m_pos & 0x7;
        return result;
    }

    inline std::string print() const
    {
        constexpr auto POSITIONS = "abcdefgh12345678";
        const auto position = get();
        auto result = std::string{};
        result = POSITIONS[position.first];
        result += POSITIONS[(8 + position.second)];
        return result;
    }

private:
    uint8_t m_pos{};
};
