
#include "Config.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <utility>


const std::pair clg_cursescpp::NULL_XY = std::make_pair(0, 0);

const std::pair<short, short> clg_cursescpp::NULL_XY_int16 = 
    std::make_pair<short, short>(0, 0);

const clg_cursescpp::TextXY clg_cursescpp::NULL_TEXT_XY = {
    "", 0
};

std::pair clg_cursescpp::MAX_SCREEN_XY = std::make_pair(0, 0);

const wchar_t* clg_cursescpp::converterCharInWchar(const char* ch)
{
    size_t cSize = strlen(ch)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, ch, cSize);
    return wc;
}
