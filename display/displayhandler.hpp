/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <atomic>
#include <thread>


namespace dsp
{
class Display;
class MoveStream;
class StreamItem;

class DisplayHandler
{
public:
    explicit DisplayHandler(std::shared_ptr<MoveStream> stream = nullptr,
                            int width = 800, int height = 800);

    std::shared_ptr<MoveStream> stream();
    void close();
    void work();

private:
    std::atomic_bool m_isCalledClose;
    std::shared_ptr<Display> m_display;
    std::shared_ptr<MoveStream> m_stream;
    std::thread m_thread;
};
}  // namespace dsp
