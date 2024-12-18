#pragma once

#include <exception>
#include <string>

/**
 * @file exception.h
 * @brief Определения классов исключений для клиентской части.
 * @details Этот файл содержит определения классов для обработки различных исключений, возникающих в клиентской части программы.
 * @date 19.11.2024
 * @version 1.0
 * @authors Белов А. Р.
 * @copyright ИБСТ ПГУ
 */

/**
 * @brief Базовый класс для клиентских ошибок.
 */
class BasicClientError : public std::exception
{
public:
    BasicClientError(const std::string &name, const std::string &message, const std::string &func);

    const char *what() const noexcept override;

protected:
    std::string name;            ///< Имя исключения.
    std::string func;            ///< Имя функции, в которой возникла ошибка.
    mutable std::string message; ///< Сообщение об ошибке.
};

class InputOutputError : public BasicClientError
{
public:
    InputOutputError(const std::string &message, const std::string &func);
};

class ArgsDecodeError : public BasicClientError
{
public:
    ArgsDecodeError(const std::string &message, const std::string &func);
};

class DataDecodeError : public BasicClientError
{
public:
    DataDecodeError(const std::string &message, const std::string &func);
};

class AuthError : public BasicClientError
{
public:
    AuthError(const std::string &message, const std::string &func);
};

class NetworkError : public BasicClientError
{
public:
    NetworkError(const std::string &message, const std::string &func);
};
