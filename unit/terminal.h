#pragma once

#include "errors.h"
#include <string>
#include <vector>

using namespace std;

class Terminal
{
public:
    Terminal();
    string getAddress();
    int getPort();
    string getInputPath();
    string getOutputPath();
    string getConfigPath();
    void parseArgs(int argc, char *argv[]);
    void showHelp();

private:
    string address;     ///< Адрес сервера.
    uint16_t port;      ///< Порт сервера.
    string input_path;  ///< Путь к входному файлу.
    string output_path; ///< Путь к выходному файлу.
    string config_path; ///< Путь к файлу конфигурации.
    bool help_flag;     ///< Флаг для отображения справки.
};
