#include <cstring>
#include <unistd.h>
#include <iostream>

#include "client.h"
#include "errors.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

// Конструктор
Client::Client(const string &address, uint16_t port)
    : address(address), port(port), socket(-1) {}

// Метод для установки соединения
void Client::conn()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket < 0)
    {
        throw NetworkError("Failed to create socket", "Client.conn()");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);

    if (inet_pton(AF_INET, this->address.c_str(), &server_addr.sin_addr) <= 0)
        throw NetworkError("Invalid address/ Address not supported", "Client.conn()");

    if (connect(this->socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        throw NetworkError("Connection failed", "Client.conn()");
}

// Метод для аутентификации
void Client::auth(const string &login, const string &password)
{
    // Отправка логина серверу
    if (send(this->socket, login.c_str(), login.size(), 0) < 0)
    {
        throw AuthError("Failed to send login", "Client.auth()");
    }

    // Получение соли от сервера
    char salt[17]; // Соль должна быть 16 символов
    int salt_length = recv(this->socket, salt, sizeof(salt) - 1, 0);
    if (salt_length < 0)
    {
        throw AuthError("Failed to receive salt", "Client.auth()");
    }
    salt[salt_length] = '\0';

    // Вычисление хеша с использованием CryptoPP
    CryptoPP::SHA1 hash_func; // создаем объект хеш-функции
    string hash_hex;

    // формирование хэша и преобразование в шестнадцатеричную строку
    CryptoPP::StringSource(
        string(salt) + password,
        true,
        new CryptoPP::HashFilter(
            hash_func,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash_hex),
                true // Заглавные буквы
                )));

    // Отправка хеша серверу
    if (send(this->socket, hash_hex.c_str(), hash_hex.size(), 0) < 0)
    {
        throw AuthError("Failed to send hash", "Client.auth()");
    }

    // Получение ответа от сервера
    char response[1024];
    int response_length = recv(this->socket, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw AuthError("Failed to receive auth response", "Client.auth()");
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw AuthError("Authentication failed", "Client.auth()");
    }
}

vector<uint64_t> Client::calc(const vector<vector<uint64_t>> &data)
{
    // Передача количества векторов
    uint32_t num_vectors = data.size();
    if (send(this->socket, &num_vectors, sizeof(num_vectors), 0) < 0)
    {
        throw NetworkError("Failed to send number of vectors", "Client.calc()");
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vec_size = vec.size();
        if (send(this->socket, &vec_size, sizeof(vec_size), 0) < 0)
        {
            throw NetworkError("Failed to send vector size", "Client.calc()");
        }
        if (send(this->socket, vec.data(), vec_size * sizeof(uint64_t), 0) < 0)
        {
            throw NetworkError("Failed to send vector data", "Client.calc()");
        }
    }

    // Получение результатов
    vector<uint64_t> results(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        if (recv(this->socket, &results[i], sizeof(uint64_t), 0) < 0)
        {
            throw NetworkError("Failed to receive result", "Client.calc()");
        }
    }

    // Логирование результата
    cout << "Log: \"Client.calc()\"\n";
    cout << "Results: {";
    for (const auto &val : results)
    {
        cout << val << ", ";
    }
    if (!results.empty())
    {
        cout << "\b\b"; // Удалить последнюю запятую и пробел
    }
    cout << "}\n";

    return results;
}


// Метод для закрытия соединения
void Client::close()
{
    if (this->socket >= 0)
    {
        ::close(this->socket);
        this->socket = -1;
    }
}
