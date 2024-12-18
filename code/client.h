#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class Client
{
public:
    Client(const string &address, uint16_t port);

    void conn();
    void auth(const string &username, const string &password);
    vector<uint64_t> calc(const vector<vector<uint64_t>> &data);
    void close();

private:
    int socket;     ///< Сокет подключения.
    string address; ///< Адрес сервера.
    uint16_t port;  ///< Порт сервера.
};
