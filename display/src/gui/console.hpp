/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <string>
#include <cstring>

#include "logsource/stringlog.hpp"


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
    char* history(std::size_t elements = 32);
    void reset() { handle(); }

private:
    void process(std::string command);

private:
    char m_command[64];
    std::string m_history;
    std::shared_ptr<common::lsrc::Stringlog::Buffer> m_buffer;
};
}  // namespace dsp::gui
