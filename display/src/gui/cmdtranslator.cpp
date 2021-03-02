/**
 * Created by Karol Dudzic @ 2021
 */

#include "cmdtranslator.hpp"

#include <sstream>

#include "logger.hpp"
#include "movestream.hpp"
#include "onboardconfig.hpp"
#include "onboardmove.hpp"
#include "demo.hpp"


namespace dsp::gui
{

void Translator::translateExecute(MoveStreamPtr stream, std::string command)
{
    try
    {
        command.erase(std::remove(command.begin(), command.end(), '\n'));
        execute(std::move(stream), std::move(command));
    }
    catch (std::exception& e)
    {
        std::stringstream result;
        result << "An exception occurs during handle the command '" << command << "'\n"
               << e.what();
        common::Logger{} << result.str();
    }
}

void Translator::execute(std::shared_ptr<dsp::MoveStream> stream, std::string command)
{
    if (command == "help")
    {
        help();
        return;
    }
    else if (command == "playdemo")
    {
        dsp::demo::demo(*stream);
        return;
    }

    auto pos = command.find(' ');
    if (pos == std::string::npos)
    {
        std::stringstream result;
        result << "Invalid command '" << command << "'\n";
        common::Logger{} << result.str();
        return;
    }

    auto service = command.substr(0, pos);
    command = command.substr(pos + 1);
    handle(service, std::move(command), std::move(stream));
}

void Translator::help()
{
    std::stringstream result;
    result << "To build your command use pattern: \n\t\t<destination> <command> <args>\n"
              ",where <destination> is service related to handle your command,\n"
              "<command> and <args> describe what you want to call\n\n"
              "Availbale services:\n"
              "  cfg  - program configuration related,\n"
              "  brd  - game related\n"
              "To see all available commands for service type: <destination> help\n"
              "To run some demo type: 'playdemo'";
    common::Logger{} << result.str();
}

void Translator::handle(const std::string& srvc,
                        std::string command,
                        std::shared_ptr<dsp::MoveStream> stream)
{
    auto result = StreamItem{};
    if (srvc == "cfg")
    {
        if (command == "help")
        {
            common::Logger{} << dsp::OnboardConfig::commands();
        }
        else
        {
            result = dsp::OnboardConfig(command);
        }
    }
    else if (srvc == "brd")
    {
        if (command == "help")
        {
            common::Logger{} << dsp::OnboardMove::commands();
        }
        else
        {
            result = dsp::OnboardMove(command);
        }
    }
    else
    {
        std::stringstream result;
        result << "Unknown service '" << srvc << "'\n";
        common::Logger{} << result.str();
        return;
    }

    if (!result)
    {
        std::stringstream result;
        result << "Unknown command '" << command << "' for service '" << srvc << "'\n";
        common::Logger{} << result.str();
    }
    else
    {
        (*stream) << result;
    }
}

}  // namespace dsp::gui


