//
// 2024-12-10 18:27:44 dpw
//

#include <ansi_colors.hpp>

#include "cli.hpp"
#include "testlib.hpp"
#include "version.hpp"

// the actual tests

Results test_version() {
    Results r = {.name = "Version Tests"};

    return r;
}

Results test_cli() {
    Results r = {.name = "CLI Tests"};

    std::vector<std::string> args = {"test", "-p", "2500"};
    char** argv = new char*[args.size()];

    for (std::size_t i = 0; i < args.size(); i++) {
        argv[i] = const_cast<char*>(args[i].c_str());
    }

    auto config = parse_cli(args.size(), argv);
    r.equals(config.port == 2500, "the port assignment");

    return r;
}

int main(int argc, char* argv[]) {
    std::cout << cyan << "Cryptor Server Tests, Version: " << yellow << Version() << reset << "\n"
              << std::endl;
    std::vector<std::string> args(argv, argv + argc);

    Results summary = Results{.name = "Unit Test Summary"};

    // lambda to run a test and add its result to the summary
    auto run_test = [&summary](auto test_func) {
        auto result = test_func();
        std::cout << result << std::endl;
        summary.add(result);
    };

    run_test(test_version);
    run_test(test_cli);

    std::cout << "\n" << summary << std::endl;
    auto msg = (summary.failed == 0) ? green + "Ok" : "\n" + red + "Tests failed!";
    std::cout << cyan << "\nUnit Test Results: " << msg << reset << std::endl;

    return 0;
}
