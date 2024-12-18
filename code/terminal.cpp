#include "terminal.h"
#include <iostream>
#include <cstring>

// Конструктор
Terminal::Terminal()
    : address("127.0.0.1"), port(33333),
      config_path("./config/vclient.conf"), help_flag(false) {}

string Terminal::getConfigPath()
{
    return this->config_path;
}

string Terminal::getAddress()
{
    return this->address;
};
int Terminal::getPort()
{
    return this->port;
};
string Terminal::getInputPath()
{
    return this->input_path;
};
string Terminal::getOutputPath()
{
    return this->output_path;
};

// Метод для разбора аргументов
void Terminal::parseArgs(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            this->showHelp();
        else if (
            strcmp(argv[i], "-a") == 0 ||
            strcmp(argv[i], "--address") == 0)
        {
            if (i + 1 < argc)
                this->address = argv[++i];
            else
                throw ArgsDecodeError(
                    "Missing value for address parameter",
                    "Terminal::parseArgs");
        }
        else if (
            strcmp(argv[i], "-p") == 0 ||
            strcmp(argv[i], "--port") == 0)
        {
            if (i + 1 < argc)
                this->port = stoi(argv[++i]);
            else
                throw ArgsDecodeError(
                    "Missing value for port parameter",
                    "Terminal::parseArgs");
        }
        else if (
            strcmp(argv[i], "-i") == 0 ||
            strcmp(argv[i], "--input") == 0)
        {
            if (i + 1 < argc)
                this->input_path = argv[++i];
            else
                throw ArgsDecodeError(
                    "Missing value for input parameter",
                    "Terminal::parseArgs()");
        }
        else if (
            strcmp(argv[i], "-o") == 0 ||
            strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc)
                this->output_path = argv[++i];
            else
                throw ArgsDecodeError(
                    "Missing value for output parameter",
                    "Terminal::parseArgs()");
        }
        else if (
            strcmp(argv[i], "-c") == 0 ||
            strcmp(argv[i], "--config") == 0)
        {
            if (i + 1 < argc)
                this->config_path = argv[++i];
            else
                throw ArgsDecodeError(
                    "Missing value for config parameter",
                    "Terminal::parseArgs()");
        }
        else
            throw ArgsDecodeError(
                "Unknown parameter: " + string(argv[i]),
                "Terminal::parseArgs()");

        if (this->help_flag)
        {
            this->showHelp();
            exit(0);
        }
    }
}

// Метод для показа справки
void Terminal::showHelp()
{
    std::cout << "Usage: vclient [options]\n"
              << "Options:\n"
              << "  -h, --help            Show this help message and exit\n"
              << "  -a, --address ADDRESS Server address (default: 127.0.0.1)\n"
              << "  -p, --port PORT       Server port (default: 33333)\n"
              << "  -i, --input PATH      Path to input data file\n"
              << "  -o, --output PATH     Path to output data file\n"
              << "  -c, --config PATH     Path to config file (default: ./config/vclient.conf)\n";
}
