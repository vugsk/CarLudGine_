
#include <CarLudGine/Errors/CError.hpp>


clg_errors::CError::CError( const char *message_error )
    : _message(message_error) {}



const char * clg_errors::CError::getMessageError() const
{
    return _message;
}

