#pragma once

#include "errors.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @class Terminal
 * @brief Класс для работы с терминалом.
 */
class Terminal
{
public:
    /**
     * @brief Конструктор класса Terminal.
     */
    Terminal();

    /**
     * @brief Возвращает адрес сервера.
     * @return Адрес сервера.
     */
    string getAddress();

    /**
     * @brief Возвращает порт сервера.
     * @return Порт сервера.
     */
    int getPort();

    /**
     * @brief Возвращает путь к входному файлу.
     * @return Путь к входному файлу.
     */
    string getInputPath();

    /**
     * @brief Возвращает путь к выходному файлу.
     * @return Путь к выходному файлу.
     */
    string getOutputPath();

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * @return Путь к файлу конфигурации.
     */
    string getConfigPath();

    /**
     * @brief Разбирает аргументы командной строки.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throw ArgsDecodeError В случае ошибки разбора аргументов.
     */
    void parseArgs(int argc, char *argv[]);

    /**
     * @brief Показывает справку.
     */
    void showHelp();

private:
    string address;     ///< Адрес сервера.
    uint16_t port;      ///< Порт сервера.
    string input_path;  ///< Путь к входному файлу.
    string output_path; ///< Путь к выходному файлу.
    string config_path; ///< Путь к файлу конфигурации.
    bool help_flag;     ///< Флаг для отображения справки.
};
