#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

/**
 * @class Client
 * @brief Класс для взаимодействия с сервером.
 */
class Client
{
public:
    /**
     * @brief Конструктор класса Client.
     * @param address Адрес сервера.
     * @param port Порт сервера.
     */
    Client(const string &address, uint16_t port);

    /**
     * @brief Устанавливает соединение с сервером.
     * @throw NetworkError В случае ошибки создания сокета или подключения.
     */
    void conn();

    /**
     * @brief Аутентифицирует пользователя на сервере.
     * @param username Логин пользователя.
     * @param password Пароль пользователя.
     * @throw AuthError В случае ошибки отправки данных или неверной аутентификации.
     */
    void auth(const string &username, const string &password);

    /**
     * @brief Выполняет вычисления на сервере.
     * @param data Вектор векторов данных для отправки на сервер.
     * @return Вектор результатов вычислений от сервера.
     * @throw NetworkError В случае ошибки отправки или получения данных.
     */
    vector<uint64_t> calc(const vector<vector<uint64_t>> &data);

    /**
     * @brief Закрывает соединение с сервером.
     */
    void close();

private:
    int socket;     ///< Сокет подключения.
    string address; ///< Адрес сервера.
    uint16_t port;  ///< Порт сервера.
};
