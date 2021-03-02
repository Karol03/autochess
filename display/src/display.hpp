/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <atomic>
#include <memory>
#include <inttypes.h>
#include "movestream.hpp"
#include "src/piecetype.hpp"


namespace dsp
{
class Window;
}  // namespace dsp

namespace dsp
{
struct RGB
{
    uint8_t r, g, b;
};

class Display
{
public:
    explicit Display(int width = 800, int height = 800);
    virtual ~Display() = default;

    bool isActive() const;
    void clear(int horiz, int vert);
    void move(int fromHoriz, int fromVert, int toHoriz, int toVert);
    void promote(int horiz, int vert, dsp::Piece to);
    void refresh();
    void run();
    void tie(MoveStreamPtr stream);

    void colorLastMove(bool isColor);
    void setColor(dsp::Player player, RGB rgb);
    void resetBoard();

private:
    std::atomic_bool m_isFreerun;
    std::shared_ptr<dsp::Window> m_window;
    MoveStreamPtr m_stream;
};
}  // namespace dsp
