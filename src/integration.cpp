//
// 2024-12-13 15:25:10 dpw
//

#include <ansi_colors.hpp>

#include "cli.hpp"
#include "logging.hpp"
#include "service.hpp"
#include "version.hpp"
#include "testlib.hpp"

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::critical);
    using namespace colors;

    std::string msg = "Cryptor Server Unit Tests, Version: ";
    std::cout << cyan << msg << yellow << cryptor::Version() << reset << "\n" << std::endl;
    // std::vector<std::string> args(argv, argv + argc);

    // here is what the tests should do
    // 1. start the cryptor server (may have to stop first, with shutdown)
    // 2. request the server version and verify
    // 3. request the index page and inspect key elements
    // 4. request help page and verify
    // 5. shutdown the service

    return 0;

}
