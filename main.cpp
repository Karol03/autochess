/**
 * Created by Karol Dudzic @ 2021
 */
#include <iostream>
#include "board/board.hpp"
#include "display/displayapi.hpp"

using namespace std;

int main()
{
    auto handler = dsp::DisplayHandler();
    handler.work();
    return 0;
}
