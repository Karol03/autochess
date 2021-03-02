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
    , m_end{0}
    , m_logs(size)
{}

std::vector<Stringlog::Log> Stringlog::Buffer::all()
{
    return get(m_logs.cbegin() + m_begin, m_logs.cend() + m_end);
}

void Stringlog::Buffer::capacity(std::size_t set)
{
    m_logs.resize(set);
}

std::vector<Stringlog::Log> Stringlog::Buffer::head(std::size_t elements)
{
    if (elements == 0)
    {
        return {};
    }

    const auto begin = m_begin.load();
    const auto end = m_end.load();
    const auto capacity = m_logs.capacity();
    const auto size = (end > begin ? end - begin : capacity);
    if (elements >= size)
    {
        return all();
    }

    const auto itBeg = m_logs.begin();
    const auto itEnd = m_logs.begin() + ((begin + elements) % capacity);
    return get(itBeg, itEnd);
}

std::vector<Stringlog::Log> Stringlog::Buffer::tail(std::size_t elements)
{
    if (elements == 0)
    {
        return {};
    }

    const auto begin = m_begin.load();
    const auto end = m_end.load();
    const auto capacity = m_logs.capacity();
    const auto size = (end > begin ? end - begin : capacity);
    if (elements >= size)
    {
        return all();
    }

    const auto itEnd = m_logs.begin() + end;
    const auto itBeg = m_logs.begin() + ((end + capacity - elements) % capacity);
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
    const auto end = m_end.load() % m_logs.capacity();
    const auto capacity = m_logs.capacity();
    const auto isFull = (end + capacity - begin == capacity);

    if (isFull)
    {
        m_begin = (begin + 1) % capacity;
    }
    std::swap(m_logs[end], msg);
    m_end = (end + 1) % capacity;
    m_isChanged = true;
}

}  // namespace common::lsrc
