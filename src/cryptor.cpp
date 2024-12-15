//
//  cryptor main
//

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "logging.hpp"
#include "service.hpp"
#include "version.hpp"

int main(const int argc, char **argv) {
    using namespace httplib;

    const auto config = cryptor::parse_cli(argc, argv);

    std::string version = "Server Version: ";
    auto vers = cryptor::Version();

    version.append(vers.to_string());

    if (config.verbose > 0) {
        spdlog::info("{}", version);
        spdlog::info("Server Config : {}", config.to_string());
    }

    auto ok = cryptor::run_service(config);

    spdlog::info("Server shutdown, code: {}...", ok);

    return 0;
}
