//
// 2024-12-09 10:28:16 dpw
//

#ifndef CLI_INCLUDE
#define CLI_INCLUDE

#include <iostream>
#include <cxxopts.hpp>

struct Config {
    std::string host = "0.0.0.0";
    int port = 2022;
    std::string base_dir = "../html";
    int verbose = 1;

    friend std::ostream& operator<<(std::ostream& os, const Config v) {
        // better to use <format> but it breaks on linux and fmt broken on darwin
        os << "host: " << v.host << ", "
            << "port: " << v.port << ", "
            << "base : " << v.base_dir << ", "
            << "verbose: " << v.verbose << "."
        ;
        return os;
    }
};

// TODO: finish the help strings
void show_help(std::string pname) {
    std::cout
        << "Usage: " << pname << "[options]\n"
        << "Options:\n"
        << "  -p port : port to listen on\n"
        << "  -r host : host address\n"
        << "  -b base : the base folder to mount as '/'\n"
        << "  -v level: logging verbose level\n"
        << "  -h      : show this help message.\n"
        << std::endl
        ;
}

/*
 * parse the command line
 */
Config parse_cli(const int argc, const char** argv) {
    auto config = Config();

    try {
        cxxopts::Options options("cryptor", "tls server for cryptor web app");
        options
            .add_options()
                ("p,port", "listening port", cxxopts::value<int>())
                ("v,version", "Show the current version and exit")
                ("h,help", "Show this help")
            ;

        auto result = options.parse(argc, argv);
        if (result.count("version")) {
            std::cout << "Server Version: " << Version() << std::endl;
            exit(0);
        }

        if (result.count("help")) {
            std::cout << "Server Version: " << Version() << std::endl;
            std::cout << options.help() << std::endl;
            exit(0);
        }

        if (result.count("port")) {
            config.port = result["port"].as<int>();
        }

    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing cli options: " << e.what() << std::endl;
    }

    return config;
}


#endif
