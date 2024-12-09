//
// 2024-12-09 10:28:16 dpw
//

#ifndef CLI_INCLUDE
#define CLI_INCLUDE

#include <iostream>

struct Config {
    std::string host = "0.0.0.0";
    int port = 2022;
    int verbose = 1;
};

// TODO: finish the help strings
void show_help(std::string pname) {
    std::cout
        << "Usage: " << pname << "[options]\n"
        << "Options:\n"
        << "  -p port  : port to listen on\n"
        << "  -r host  : host address\n"
        << "  -v level : logging verbose level\n"
        << "  -h       : show this help message.\n"
        << std::endl
        ;
}

/*
 * parse the command line
 */
Config parse_cli(std::vector<std::string> args) {
    Config config = { };

    auto it = std::find(args.begin(), args.end(), "-r");
    if (it != args.end()) {
        config.host = *(it + 1);
    }

    // TODO: parse 

    return config;
}


#endif
