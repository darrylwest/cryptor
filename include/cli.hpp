//
// 2024-12-09 10:28:16 dpw
//

#ifndef CLI_INCLUDE
#define CLI_INCLUDE

#include <cxxopts.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

#include "version.hpp"

namespace cryptor {

    struct Config {
        std::string host = "0.0.0.0";
        int port = 2022;
        std::string base_dir = "./";
        int verbose = 1;
        std::string cert_file = "./.ssh/cert.pem";
        std::string key_file = "./.ssh/key.pem";

        friend std::ostream& operator<<(std::ostream& os, const Config v) {
            // better to use <format> but it breaks on linux and fmt broken on darwin
            os << "host: " << v.host << ", "
            << "port: " << v.port << ", "
            << "base: " << v.base_dir << ", "
            << "cert: " << v.cert_file << ", "
            << "key : " << v.key_file << ", "
            << "verbose: " << v.verbose << ".";
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
    Config parse_cli(const int argc, char** argv) {
        auto config = Config();

        try {
            cxxopts::Options options("cryptor", "tls server for cryptor web app");
            // clang-format off
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

            // clang-format on
            const auto version = cryptor::Version();
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

            if (result.count("host")) {
                config.host = result["host"].as<std::string>();
            }

            if (result.count("base")) {
                config.base_dir = result["base"].as<std::string>();
            }

            if (result.count("cert")) {
                config.cert_file = result["cert"].as<std::string>();
            }

            if (result.count("key")) {
                config.key_file = result["key"].as<std::string>();
            }

            if (result.count("level")) {
                auto level = result["level"].as<int>();
                switch (level) {
                case 0:
                    spdlog::set_level(spdlog::level::debug);
                    break;
                case 2:
                    spdlog::set_level(spdlog::level::warn);
                    break;
                case 3:
                    spdlog::set_level(spdlog::level::err);
                    break;
                case 4:
                    spdlog::set_level(spdlog::level::critical);
                    break;
                case 5:
                    spdlog::set_level(spdlog::level::off);
                    break;
                default:
                    spdlog::set_level(spdlog::level::info);
                    break;
                }
            }

        } catch (const std::exception& exp) {
            std::cout << "error parsing cli options: " << exp.what() << std::endl;
            exit(1);
        }

        return config;
    }
} // namespace

#endif
