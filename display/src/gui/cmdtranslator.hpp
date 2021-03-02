/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <memory>


namespace dsp { class MoveStream; }  // namespace dsp

namespace dsp::gui
{
class Translator
{
public:
    void translateExecute(std::shared_ptr<dsp::MoveStream> stream, std::string command);

private:
    void execute(std::shared_ptr<dsp::MoveStream> stream, std::string command);
    void handle(const std::string& srvc,
                std::string command,
                std::shared_ptr<dsp::MoveStream> stream);
    void help();
};
}  // namespace dsp::gui
