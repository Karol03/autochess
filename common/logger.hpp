/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <mutex>
#include <memory>
#include "logsource/stream.hpp"


namespace common
{
class Logger
{
public:
    explicit Logger() = default;

    inline Logger& set(std::unique_ptr<lsrc::Stream> stream)
    {
        std::scoped_lock lock(m_mutex);
        std::swap(m_stream, stream);
        return *this;
    }

    inline Logger& operator<<(std::string msg)
    {
        std::scoped_lock lock(m_mutex);
        if (m_stream)
        {
            m_stream->put(std::move(msg));
        }
        return *this;
    }

private:
    static std::unique_ptr<lsrc::Stream> m_stream;
    static std::mutex m_mutex;
};
}  // namespace common
