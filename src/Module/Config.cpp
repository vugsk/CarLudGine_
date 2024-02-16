
#include "Config.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>


const std::pair<unsigned, unsigned> clg_cursescpp::NULL_XY = std::make_pair(0, 0);

const std::pair<short, short> clg_cursescpp::NULL_XY_INT16 =
    std::make_pair<short, short>(0, 0);

std::pair<int, int> clg_cursescpp::MAX_SCREEN_XY = std::make_pair(0, 0);

const wchar_t* clg_cursescpp::converterCharInWchar(const char* ch)
{
    const size_t cSize = strlen(ch) + 1;
    auto* wc = new wchar_t[cSize];
    mbstowcs (wc, ch, cSize);
    return wc;
}