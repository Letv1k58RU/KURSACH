#include "data.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Конструктор
Data::Data(
    const string &path_to_conf,
    const string &path_to_in,
    const string &path_to_out)
    : path_to_conf(path_to_conf),
      path_to_in(path_to_in),
      path_to_out(path_to_out) {}

// Метод для чтения конфигурационных данных
array<string, 2> Data::conf()
{
    ifstream conf_file(this->path_to_conf);
    if (!conf_file.is_open())
    {
        throw InputOutputError(
            "Failed to open configuration file \"" +
                this->path_to_conf + "\"",
            "Data.conf()");
    }

    array<string, 2> credentials;
    string line;
    getline(conf_file, line);
    conf_file.close();

    istringstream iss(line);
    getline(iss, credentials[0], ':');
    getline(iss, credentials[1]);

    // Проверка на наличие обоих значений
    if (credentials[0].empty() || credentials[1].empty())
    {
        throw DataDecodeError(
            "Missing login or password",
            "Data.conf()");
    }

    // Логирование считанных логина и пароля
    cout << "Log: \"Data.conf()\"\n";
    cout << "UserData: " << credentials[0]
              << " " << credentials[1] << "\n";

    return credentials;
}

vector<vector<uint64_t>> Data::read()
{
    ifstream input_file(this->path_to_in);
    if (!input_file.is_open())
        throw InputOutputError(
            "Failed to open input file for reading.",
            "Data.read()");

    // Чтение количества векторов
    uint32_t num_vectors;
    input_file >> num_vectors;

    vector<vector<uint64_t>> data(num_vectors);

    // Чтение каждого вектора
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        // Чтение размера вектора
        uint32_t vector_size;
        input_file >> vector_size;

        // Чтение значений вектора
        vector<uint64_t> vec(vector_size);
        for (uint32_t j = 0; j < vector_size; ++j)
        {
            input_file >> vec[j]; // Чтение в десятичном формате
        }

        data[i] = vec;
    }

    input_file.close();

    // Логирование всех прочитанных векторов
    cout << "Log: Data.read()\n";
    cout << "Vectors: {";
    for (const auto &vec : data)
    {
        cout << "{";
        for (const auto &val : vec)
            cout << val << ", ";
        if (!vec.empty())
            cout << "\b\b";
        cout << "}, ";
    }
    if (!data.empty())
        cout << "\b\b";
    cout << "}\n";

    return data;
}

// Метод для записи числовых данных
void Data::write(const vector<uint64_t> &data)
{
    ofstream output_file(this->path_to_out, ios::binary);
    if (!output_file.is_open())
    {
        throw InputOutputError(
            "Failed to open output file \"" +
                this->path_to_out + "\"",
            "Data.write()");
    }

    // Запись количества результатов
    uint32_t count = data.size();
    output_file.write(reinterpret_cast<const char *>(&count), sizeof(count));

    // Запись самих результатов
    for (const auto &num : data)
    {
        output_file.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    output_file.close();
}
