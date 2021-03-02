/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <functional>
#include <memory>
#include <vector>


namespace dsp
{
class Display;

class StreamItem
{
public:
    using DisplayPtr = std::shared_ptr<dsp::Display>;
    using StreamFunction = std::function<void(const DisplayPtr&)>;
    using MovesQueue = std::vector<std::function<void(const DisplayPtr&)>>;

public:
    explicit StreamItem(StreamFunction move = nullptr)
    {
        if (move != nullptr)
        {
            m_moves.push_back(move);
        }
    }

    explicit StreamItem(MovesQueue moves)
        : m_moves{std::move(moves)}
    {}

    inline void modifyOn(DisplayPtr display)
    {
        for (const auto& move : m_moves)
        {
            move(display);
        }
    }

    inline bool isAvailable()
    {
        return !m_moves.empty();
    }

private:
    MovesQueue m_moves;
};
}  // namespace dsp
