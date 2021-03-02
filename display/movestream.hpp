/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <chrono>
#include <thread>
#include <memory>
#include "src/streamitem.hpp"
#include "external/concurrentqueue.h"


namespace dsp
{
class MoveStream : std::enable_shared_from_this<MoveStream>
{
public:
    explicit MoveStream() = default;
    virtual ~MoveStream() = default;

    template <typename Item>
    inline MoveStream& operator<<(Item item)
    {
        enqueue(std::forward<Item>(item));
        return *this;
    }

    inline bool enqueue(const StreamItem& item) { return m_data.enqueue(item); }
    inline bool enqueue(StreamItem&& item) { return m_data.enqueue(item); }

    inline bool dequeue(StreamItem& item) { return m_data.try_dequeue(item); }
    inline bool isAvailable() const { return m_data.size_approx() > 0; }

private:
    template <typename T>
    inline bool try_enqueue(T item)
    {
        using namespace std::chrono_literals;
        for (auto i = 0; i < 3; i++)
        {
            if (m_data.enqueue(std::forward<T>(item)))
            {
                return true;
            }
            std::this_thread::sleep_for(5ms);
        }
        return false;
    }

private:
    moodycamel::ConcurrentQueue<StreamItem> m_data;
};
}  // namespace dsp

using MoveStreamPtr = std::shared_ptr<dsp::MoveStream>;
