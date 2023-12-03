
#include "Config.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>


const clg_cursescpp::PairNum<int> clg_cursescpp::NULL_XY = {
    0, 0
};

const clg_cursescpp::PairNum<clg_cursescpp::__int16> clg_cursescpp::NULL_XY_int16 = {
    0, 0
};

const clg_cursescpp::TextXY clg_cursescpp::NULL_TEXT_XY = {
    "", 0
};

clg_cursescpp::PairNum<clg_cursescpp::__int16> clg_cursescpp::MAX_SCREEN_XY = {
    0, 0
};

const wchar_t* clg_cursescpp::converterCharInWchar(const char* ch)
{
    size_t cSize = strlen(ch)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, ch, cSize);
    return wc;
}
