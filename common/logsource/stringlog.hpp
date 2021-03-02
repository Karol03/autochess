/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <atomic>
#include <memory>
#include <vector>
#include "stream.hpp"


namespace common::lsrc
{
class Stringlog : public Stream
{
    using Log = std::string;

public:
    struct Buffer
    {
    public:
        explicit Buffer(std::size_t size = 128);
        std::vector<Log> all();
        std::vector<Log> head(std::size_t elements);
        std::vector<Log> tail(std::size_t elements);
        bool isChanged() { return m_isChanged.exchange(false); }
        void capacity(std::size_t set);

    private:
        friend class Stringlog;

        void add(std::string&& msg);
        std::vector<Log> get(std::vector<Log>::const_iterator from,
                             std::vector<Log>::const_iterator to);

    private:
        std::atomic_bool m_isChanged;
        std::atomic_size_t m_begin;
        std::atomic_size_t m_end;
        std::vector<Log> m_logs;
    };


public:
    explicit Stringlog(std::shared_ptr<Buffer> buffer);

    virtual void put(std::string&& msg) final;

private:
    std::shared_ptr<Buffer> m_buffer;
};
}  // namespace common::lsrc

