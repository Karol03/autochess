/**
 * Created by Karol Dudzic @ 2021
 */
#include "stringlog.hpp"


namespace common::lsrc
{
Stringlog::Stringlog(std::shared_ptr<Buffer> buffer)
{
    std::swap(m_buffer, buffer);
}

void Stringlog::put(std::string&& msg)
{
    m_buffer->add(std::forward<std::string>(msg));
}



Stringlog::Buffer::Buffer(std::size_t size)
    : m_begin{0}
    , m_size{0}
    , m_logs(size)
{}

std::vector<Stringlog::Log> Stringlog::Buffer::all()
{
    const auto endOffset = (m_begin + m_size % m_logs.capacity());
    const auto to = (endOffset == 0 ? m_logs.cend() : m_logs.cbegin() + endOffset);
    return get(m_logs.cbegin() + m_begin, to);
}

void Stringlog::Buffer::capacity(std::size_t set)
{
    m_logs.resize(set);
    if (set < m_size)
    {
        m_size = set;
    }
}

std::vector<Stringlog::Log> Stringlog::Buffer::head(std::size_t elements)
{
    if (elements == 0)
    {
        return {};
    }
    else if (elements >= m_size)
    {
        return all();
    }
    const auto itBeg = m_logs.begin();
    const auto capacity = m_logs.capacity();
    const auto last = (m_begin + elements + 1) % capacity;
    const auto itEnd = (last == 0 ? m_logs.cend() : m_logs.cbegin() + last);
    return get(itBeg, itEnd);
}

std::vector<Stringlog::Log> Stringlog::Buffer::tail(std::size_t elements)
{
    if (elements == 0)
    {
        return {};
    }
    else if (elements >= m_size)
    {
        return all();
    }

    const auto capacity = m_logs.capacity();
    const auto last = (m_begin + m_size) % capacity;
    const auto itEnd = (last == 0 ? m_logs.cend() : m_logs.cbegin() + last);
    const auto begin = ((last + capacity) - elements) % capacity;
    const auto itBeg = m_logs.cbegin() + begin;
    return get(itBeg, itEnd);
}

std::vector<Stringlog::Log> Stringlog::Buffer::get(
        std::vector<Log>::const_iterator from,
        std::vector<Log>::const_iterator to)
{
    if (from < to)
    {
        return std::vector<Stringlog::Log>(from, to);
    }
    else
    {
        auto result = std::vector<Stringlog::Log>(from, m_logs.cend());
        result.insert(result.end(), m_logs.cbegin(), to);
        return result;
    }
}

void Stringlog::Buffer::add(std::string&& msg)
{
    const auto begin = m_begin.load();
    const auto capacity = m_logs.capacity();
    const auto last = (begin + m_size) % capacity;

    std::swap(m_logs[last], msg);
    if (m_size + 1 < capacity)
    {
        ++m_size;
    }
    else
    {
        ++m_begin;
    }
    m_isChanged = true;
}

}  // namespace common::lsrc
