/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <string>


namespace dsp::gui
{
class Console
{
public:
    explicit Console() = default;

    void handle();
    inline char* buffer() { return &m_command[0]; }
    inline char* history() { return &m_history[0]; }
    inline std::size_t bufferSize() const { return sizeof(m_command); }
    inline std::size_t size() const { return m_history.size(); }

private:
    void process(std::string command);

private:
    std::string m_history;
    char m_command[64] = {};
};
}  // namespace dsp::gui
