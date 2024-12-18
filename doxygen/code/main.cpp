#include "errors.h"
#include "data.h"
#include "client.h"
#include "terminal.h"
#include <array>

int main(int argc, char *argv[])
{

    Terminal terminal;
    terminal.parseArgs(argc, argv);
    Client client(terminal.getAddress(), terminal.getPort());
    client.conn();
    Data data(terminal.getConfigPath(), terminal.getInputPath(), terminal.getOutputPath());
    array<string, 2> userpass = data.conf();
    client.auth(userpass[0], userpass[1]);
    vector<vector<uint64_t>> vectors = data.read();
    vector<uint64_t> result = client.calc(vectors);
    data.write(result);
    return 0;
}
