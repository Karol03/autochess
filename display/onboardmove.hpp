/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include "src/streamitem.hpp"


namespace dsp
{
class OnboardMove
{
public:

    /**
     * Important!
     * Description should starts from move number and
     * requires long algebraic notation!
     * example input:
     *  4. Bb5xc6
     *  7. O-O
     *  11. a7a6
     */
    explicit OnboardMove(std::string description);
    inline operator StreamItem() { return m_item; }

protected:
    StreamItem m_item;
};

}  // namespace dsp
