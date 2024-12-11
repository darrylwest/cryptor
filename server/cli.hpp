//
// 2024-12-09 10:28:16 dpw
//

#ifndef CLI_INCLUDE
#define CLI_INCLUDE

#include <iostream>
#include <cxxopts.hpp>

#include "version.hpp"

struct Config {
    std::string host = "0.0.0.0";
    int port = 2022;
    std::string base_dir = "./";
    int verbose = 1;
    std::string cert_file = "./cert.pem";
    std::string key_file = "./key.pem";

    friend std::ostream& operator<<(std::ostream& os, const Config v) {
        // better to use <format> but it breaks on linux and fmt broken on darwin
        os << "host: " << v.host << ", "
            << "port: " << v.port << ", "
            << "base : " << v.base_dir << ", "
            << "verbose: " << v.verbose << "."
        ;
        return os;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << *this;

        return oss.str();
    }
};

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
                ("H,host", "listening host", cxxopts::value<std::string>())
                ("b,base", "base directory to serve", cxxopts::value<std::string>())
                ("C,cert", "the cert pem file", cxxopts::value<std::string>())
                ("K,key", "the key pem file", cxxopts::value<std::string>())
                ("l,level", "verbose level 0--4", cxxopts::value<int>())
                ("V,version", "Show the current version and exit")
                ("h,help", "Show this help")
            ;

        const auto version = Version();
        const auto result = options.parse(argc, argv);
        if (result.count("version")) {
            std::cout << "Server Version: " << version << std::endl;
            exit(0);
        }

        if (result.count("help")) {
            std::cout << "Server Version: " << version << std::endl;
            std::cout << options.help() << std::endl;
            exit(0);
        }

        if (result.count("port")) {
            config.port = result["port"].as<int>();
        }

        if (result.count("base")) {
            config.base_dir = result["base"].as<std::string>();
        }

        if (result.count("cert")) {
            config.cert_file = result["cert"].as<std::string>();
        }

        if (result.count("key")) {
            config.cert_file = result["key"].as<std::string>();
        }

    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing cli options: " << e.what() << std::endl;
    }

    return config;
}


#endif
