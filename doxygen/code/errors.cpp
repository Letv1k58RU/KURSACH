#include "errors.h"

// Реализация конструктора BasicClientError
BasicClientError::BasicClientError(
    const std::string &name,
    const std::string &message,
    const std::string &func)
    : name(name), message(message), func(func) {}

const char *BasicClientError::what() const noexcept
{
    message = name + " in " + func + "\nMessage: " + message + ".";
    return message.c_str();
}

InputOutputError::InputOutputError(const std::string &message, const std::string &func)
    : BasicClientError("InputOutputError", message, func) {}

ArgsDecodeError::ArgsDecodeError(const std::string &message, const std::string &func)
    : BasicClientError("ArgsDecodeError", message, func) {}

DataDecodeError::DataDecodeError(const std::string &message, const std::string &func)
    : BasicClientError("DataDecodeError", message, func) {}

AuthError::AuthError(const std::string &message, const std::string &func)
    : BasicClientError("AuthError", message, func) {}

NetworkError::NetworkError(const std::string &message, const std::string &func)
    : BasicClientError("NetworkError", message, func) {}
