/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include "src/streamitem.hpp"


namespace dsp
{
class OnboardConfig
{
public:
    /**
     * @brief OnboardConfig
     * @param command
     *     changecolor <player> <r g b> - change color <black|white> <0-255 0-255 0-255>
     *     colorlastmove
     *     notcolorlastmove
     *     reset - reset board to begin state
     *
     */
    explicit OnboardConfig(std::string command);
    inline operator StreamItem() { return m_item; }
    static std::string commands();

protected:
    StreamItem m_item;
};

}  // namespace dsp
