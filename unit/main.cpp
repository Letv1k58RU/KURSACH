#include <UnitTest++/UnitTest++.h>
#include "terminal.h"
#include "errors.h"
#include "data.h"
#include <fstream> 
#include <sstream> 
#include <iostream>

SUITE(TerminalTests)
{
    TEST(Constructor)
    {
        Terminal terminal;

        CHECK_EQUAL("127.0.0.1", terminal.getAddress());
        CHECK_EQUAL(33333, terminal.getPort());
        CHECK_EQUAL("./config/vclient.conf", terminal.getConfigPath());
        CHECK_EQUAL("", terminal.getInputPath());
        CHECK_EQUAL("", terminal.getOutputPath());
    }

    TEST(ParseArgsAddress)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-a", "192.168.1.1"};
        terminal.parseArgs(3, const_cast<char**>(args));

        CHECK_EQUAL("192.168.1.1", terminal.getAddress());
    }

    TEST(ParseArgsPort)
    {   
        Terminal terminal;
        const char* args[] = {"vclient", "-p", "12345"};
        terminal.parseArgs(3, const_cast<char**>(args));

        CHECK_EQUAL(12345, terminal.getPort());
    }

    TEST(ParseArgsInputPath)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-i", "/path/to/input"};
        terminal.parseArgs(3, const_cast<char**>(args));

        CHECK_EQUAL("/path/to/input", terminal.getInputPath());
    }

    TEST(ParseArgsOutputPath)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-o", "/path/to/output"};
        terminal.parseArgs(3, const_cast<char**>(args));

        CHECK_EQUAL("/path/to/output", terminal.getOutputPath());
    }

    TEST(ParseArgsConfigPath)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-c", "/path/to/config"};
        terminal.parseArgs(3, const_cast<char**>(args));

        CHECK_EQUAL("/path/to/config", terminal.getConfigPath());
    }

    TEST(ParseArgsMissingValue)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-a"};

        CHECK_THROW(terminal.parseArgs(2, const_cast<char**>(args)), ArgsDecodeError);
    }

    TEST(ParseArgsUnknownParameter)
    {
        Terminal terminal;
        const char* args[] = {"vclient", "-x"};

        CHECK_THROW(terminal.parseArgs(2, const_cast<char**>(args)), ArgsDecodeError);
    }
}

SUITE(DataTests)
{
    // Тест конструктора
    TEST(Constructor)
    {
        Data data("config.conf", "input.txt", "output.txt");

        CHECK_EQUAL("config.conf", data.getPathToConf());
        CHECK_EQUAL("input.txt", data.getPathToIn());
        CHECK_EQUAL("output.txt", data.getPathToOut());
    }

    // Тест метода conf()
    TEST(Conf)
    {
        // Создаем тестовый конфигурационный файл
        ofstream conf_file("test_config.conf");
        conf_file << "username:password\n";
        conf_file.close();

        Data data("test_config.conf", "input.txt", "output.txt");
        array<string, 2> credentials = data.conf();

        CHECK_EQUAL("username", credentials[0]);
        CHECK_EQUAL("password", credentials[1]);

        // Удаляем тестовый конфигурационный файл
        remove("test_config.conf");
    }

    // Тест метода conf() с отсутствующим значением
    TEST(ConfMissingValue)
    {
        // Создаем тестовый конфигурационный файл
        ofstream conf_file("test_config.conf");
        conf_file << "username:\n";
        conf_file.close();

        Data data("test_config.conf", "input.txt", "output.txt");

        CHECK_THROW(data.conf(), DataDecodeError);

        // Удаляем тестовый конфигурационный файл
        remove("test_config.conf");
    }

    // Тест метода read()
    TEST(Read)
    {
        // Создаем тестовый входной файл
        ofstream input_file("test_input.txt");
        input_file << "2\n";
        input_file << "3\n1 2 3\n";
        input_file << "2\n4 5\n";
        input_file.close();

        Data data("config.conf", "test_input.txt", "output.txt");
        vector<vector<uint64_t>> vectors = data.read();

        CHECK_EQUAL(2, vectors.size());
        CHECK_EQUAL(3, vectors[0].size());
        CHECK_EQUAL(2, vectors[1].size());
        CHECK_EQUAL(1, vectors[0][0]);
        CHECK_EQUAL(5, vectors[1][1]);

        // Удаляем тестовый входной файл
        remove("test_input.txt");
    }

    // Тест метода write()
    TEST(Write)
    {
        Data data("config.conf", "input.txt", "test_output.txt");

        vector<uint64_t> data_to_write = {1, 2, 3, 4};
        data.write(data_to_write);

        ifstream input_file("test_output.txt", ios::binary);
        uint32_t count;
        input_file.read(reinterpret_cast<char*>(&count), sizeof(count));
        CHECK_EQUAL(data_to_write.size(), count);

        vector<uint64_t> read_data(count);
        for (uint32_t i = 0; i < count; ++i)
        {
            uint64_t num;
            input_file.read(reinterpret_cast<char*>(&num), sizeof(num));
            CHECK_EQUAL(data_to_write[i], num);
        }

        input_file.close();

        // Удаляем тестовый выходной файл
        remove("test_output.txt");
    }
}

int main()
{
    return UnitTest::RunAllTests();
}
