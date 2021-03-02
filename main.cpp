/**
 * Created by Karol Dudzic @ 2021
 */
#include <iostream>
#include "board/board.hpp"
#include "displayapi.hpp"

#include <thread>
#include <functional>

using namespace std;

std::vector<std::string> actions{
    "e2e4",
    "e7e6",
    "d2d4",
    "d7d5",
    "Nb1c3",
    "Ng8f6",
    "Bc1g5",
    "Bf8b4",
    "e4e5",
    "h7h6",
    "e5xf6",
    "h6xg5",
    "f6xg7",
    "Rh8g8",
    "h2h4",
    "g5xh4",
    "Qd1g4",
    "Bb4e7",
    "g2g3",
    "c7c5",
    "g3xh4",
    "c5xd4",
    "h4h5",
    "d4xc3",
    "h5h6",
    "c3xb2",
    "Ra1b1",
    "Qd8a5+",
    "Ke1e2",
    "Qa5xa2",
    "h6h7",
    "Qa2xb1",
    "h7xg8=Q+",
    "Ke8d7",
    "Qg8xf7",
    "Qb1xc2+",
    "Ke2f3",
    "Nb8c6",
    "Qg4xe6+",
    "Kd7c7",
    "Qf7f4+",
    "Kc7b6",
    "Qe6e3+",
    "Be7c5",
    "g7g8=Q",
    "b2b1=Q",
    "Rh1h6",
    "Qb1xf1",
    "Qf4b4+",
    "Qf1b5",
    "Qg8d8+",
    "Kb6a6",
    "Qe3a3+",
    "Qc2a4",
    "Qa3xa4+",
    "Qb5xa4",
    "Qb4xa4#"
};

void control_main(dsp::MoveStream& stream)
{
    std::this_thread::sleep_for(3s);
    stream << dsp::OnboardConfig("changecolor black 108, 64, 19")
           << dsp::OnboardConfig("changecolor white 207, 192, 175");
    for (unsigned i = 0; i < actions.size(); ++i)
    {
        actions[i] = std::to_string(i + 1) + ". " + actions[i];
        stream << dsp::OnboardMove(actions[i]);
        std::this_thread::sleep_for(1s);
    }
    stream << dsp::OnboardConfig("reset");
    std::this_thread::sleep_for(3s);
}

int main()
{
    auto handler = dsp::DisplayHandler();
    std::thread thread([stream = handler.stream()]() { control_main(*stream); } );
    handler.work();
    return 0;
}
