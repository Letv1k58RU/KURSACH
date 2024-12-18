#pragma once

#include <string>
#include <vector>
#include <array>
#include "errors.h"

using namespace std;

/**
 * @class Data
 * @brief Класс для работы с данными, включая конфигурацию и ввод/вывод файлов.
 */
class Data
{
public:
    /**
     * @brief Конструктор класса Data.
     * @param path_to_conf Путь к файлу конфигурации.
     * @param path_to_in Путь к входному файлу.
     * @param path_to_out Путь к выходному файлу.
     */
    Data(
        const string &path_to_conf,
        const string &path_to_in,
        const string &path_to_out);

    /**
     * @brief Читает конфигурационные данные из файла.
     * @return Массив строк, содержащий логин и пароль.
     * @throw InputOutputError В случае ошибки открытия файла.
     * @throw DataDecodeError В случае отсутствия логина или пароля.
     */
    array<string, 2> conf();

    /**
     * @brief Читает данные из входного файла.
     * @return Вектор векторов целых чисел.
     * @throw InputOutputError В случае ошибки открытия файла.
     */
    vector<vector<uint64_t>> read();

    /**
     * @brief Записывает числовые данные в выходной файл.
     * @param data Вектор целых чисел для записи.
     * @throw InputOutputError В случае ошибки открытия файла.
     */
    void write(const vector<uint64_t> &data);

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * @return Путь к файлу конфигурации.
     */
    string getPathToConf() const;

    /**
     * @brief Возвращает путь к входному файлу.
     * @return Путь к входному файлу.
     */
    string getPathToIn() const;

    /**
     * @brief Возвращает путь к выходному файлу.
     * @return Путь к выходному файлу.
     */
    string getPathToOut() const;

private:
    string path_to_conf; ///< Путь к файлу конфигурации.
    string path_to_in;   ///< Путь к входному файлу.
    string path_to_out;  ///< Путь к выходному файлу.
};
