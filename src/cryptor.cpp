//
//  cryptor main
//

#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

#include <vendor/ansi_colors.hpp>
#include <cryptor/cli.hpp>
#include <cryptor/logging.hpp>
#include <cryptor/service.hpp>
#include <cryptor/unit.hpp>
#include <cryptor/version.hpp>

int main(const int argc, char **argv) {
    using namespace httplib;

    fmt::print("{}{}{}\n", colors::yellow, argv[0], colors::reset);
    const std::string ss = std::string(argv[0]);

    // run the unit tests
    if (ss.substr(ss.size() - 4) == "unit") {
        int code = run_unit_tests(argc, argv);
        return code;
    }

    const auto config = cryptor::parse_cli(argc, argv);

    if (config.verbose > 0) {
        auto vers = cryptor::Version().to_string();
        spdlog::info("Server Version: {}{}{}", colors::cyan, vers, colors::reset);
        spdlog::info("Server Config : {}", config.to_string());
    }

    auto ok = cryptor::run_service(config);

    spdlog::info("Server shutdown, code: {}...", ok);

    return 0;
}
