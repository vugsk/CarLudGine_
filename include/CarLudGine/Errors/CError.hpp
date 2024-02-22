
#pragma once



namespace clg_errors {

    class CError
    {
    public:
        explicit CError(const char* message_error);
        virtual  ~CError()                           = default;
        CError( const CError &other )                = delete;
        CError( CError &&other ) noexcept            = delete;
        CError &operator=( const CError &other )     = delete;
        CError &operator=( CError &&other ) noexcept = delete;

        [[nodiscard]] virtual const char* getMessageError() const;

    private:
        const char* _message{};

    };



}


