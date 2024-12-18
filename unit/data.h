#pragma once

#include <string>
#include <vector>
#include <array>
#include "errors.h"

using namespace std;

class Data
{
public:
    Data(
        const string &path_to_conf,
        const string &path_to_in,
        const string &path_to_out);

    array<string, 2> conf();
    vector<vector<uint64_t>> read();
    void write(const vector<uint64_t> &data);

    string getPathToConf() const;  // Геттер для path_to_conf
    string getPathToIn() const;    // Геттер для path_to_in
    string getPathToOut() const;   // Геттер для path_to_out

private:
    string path_to_conf; ///< Путь к файлу конфигурации.
    string path_to_in;   ///< Путь к входному файлу.
    string path_to_out;  ///< Путь к выходному файлу.
};
