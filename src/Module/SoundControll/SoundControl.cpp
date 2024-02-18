
#include "CarLudGine/SoundControl.hpp"
#include "CarLudGine/Config.hpp"


clg_SoundControl::SoundControl::SoundControl( const char *name,
    const unsigned char volume, const unsigned char number_next_or_back )
        : _isRun(false)
        , _isStop(true)
        , _volume(volume)
        , _numberNextOrBack(number_next_or_back)
        , _name(name)
{
    #if DEBUG_SOUNG_CONTROL
        PRINT_CONSTRUCTED_DEBUG(SOUNG_CONTROL_CL)
    #endif
}

clg_SoundControl::SoundControl::~SoundControl()
{
    #if DEBUG_SOUNG_CONTROL
        PRINT_DESTRUCTED_DEBUG(SOUNG_CONTROL_CL)
    #endif
}


//! In development

void clg_SoundControl::SoundControl::run()
{
    _isRun = true;
    _isStop = false;
}

void clg_SoundControl::SoundControl::stop()
{
    _isRun = false;
    _isStop = true;
}


void clg_SoundControl::SoundControl::loop()
{
    run();
    while ( true )
    {
        reset();
    }
}

void clg_SoundControl::SoundControl::chageVolume( const int volume )
{
    _volume = volume;
}

void clg_SoundControl::SoundControl::reset() {}

void clg_SoundControl::SoundControl::speed( const int number ) {}

void clg_SoundControl::SoundControl::slowDown( const int number ) {}

void clg_SoundControl::SoundControl::back() {}

void clg_SoundControl::SoundControl::next() {}

//!


unsigned char clg_SoundControl::SoundControl::getVolume() const
{
    return _volume;
}

unsigned char clg_SoundControl::SoundControl::getNumberNextOrBack() const
{
    return _numberNextOrBack;
}

void clg_SoundControl::SoundControl::setNumberNextOrBack( const unsigned char number )
{
    _numberNextOrBack = number;
}

bool clg_SoundControl::SoundControl::getIsRun() const
{
    return _isRun;
}

bool clg_SoundControl::SoundControl::getIsStop() const
{
    return _isStop;
}
