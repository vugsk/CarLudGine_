
#include <CarLudGine/Errors/CError.hpp>


clg_errors::CError::CError( const char *message_error )
    : m_message(message_error) {}



const char * clg_errors::CError::getMessageError() const
{
    return m_message;
}

