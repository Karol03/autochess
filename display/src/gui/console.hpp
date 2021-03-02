/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <future>
#include <string>
#include <cstring>

#include "logsource/stringlog.hpp"
#include "movestream.hpp"


namespace dsp::gui
{
class Console
{
public:
    explicit Console();

    void handle();
    inline char* buffer() { return &m_command[0]; }
    inline std::size_t size() const { return m_history.size(); }
    inline std::size_t bufferSize() const { return sizeof(m_command); }
    inline bool isBusy() const { return m_isBusy.load(); }
    inline void tie(MoveStreamPtr stream) { std::swap(m_stream, stream); }

    char* history(std::size_t elements = 128);
    void reset() { handle(); }

private:
    void process(std::string command);

private:
    std::atomic_bool m_isBusy{false};
    MoveStreamPtr m_stream;
    std::future<void> m_task;
    std::shared_ptr<common::lsrc::Stringlog::Buffer> m_buffer;
    std::string m_history;
    char m_command[64];
};
}  // namespace dsp::gui
