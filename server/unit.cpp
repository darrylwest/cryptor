//
// 2024-12-10 18:27:44 dpw
//

#include "version.hpp"
#include "cli.hpp"

using namespace colors;

/*
 * Results struct to hold values related to test runs; counts of passed, failed, skipped, etc.
 * The result name helps identify the test groupings.  Methods include equals(book, string) to
 * support test evaluation.  
*/
struct Results {
    std::string name;
    int tests = 0;
    int passed = 0;
    int failed = 0;
    int skipped = 0;


    // show the results
    friend std::ostream& operator<<(std::ostream& os, const Results v) {

        auto msg = (v.failed == 0) ? green + ", Ok" : red + ", Tests failed!" ;
        os << "\t" 
            << v.name
            << ": tests=" << v.tests
            << ", passed=" << v.passed
            << ", failed=" << v.failed
            << ", skipped=" << v.skipped
            << msg
            << reset
            ;
        return os;
    }

    // use this to test a bool result, e.g., result.equals(1 == 1) would increment the passed count,
    // result.equals(1 == 2) increments the failed count and result.equals("this" == "that", "should equal this")
    // increments the failed count and shows the fail comment in red.
    // all calls to equals increments the number of tests.
    void equals(bool ok, std::string comment = "") {
        tests++;
        if (ok) {
            passed++ ; 
        } else {
            failed++;
            if (comment != "") {
                std::cerr << red << "ERROR! " << comment << reset << std::endl;
            }
        }
    }

    // use skip to replace equals when you want to skip a test
    void skip(bool ok, std::string comment = "") {
        tests++;
        if (ok) {
            skipped++;
            if (comment != "") {
                std::cout << red << comment << " skipped..." << std::endl;
            }
        }
    }

    // use this to add to the summary
    void add(Results r) {
        tests += r.tests;
        passed += r.passed;
        failed += r.failed;
        skipped += r.skipped;
    }

};

// the actual tests

Results test_version() {
    Results r = { .name = "CLI Tests" };

    return r;
}

Results test_cli() {
    Results r = { .name = "CLI Tests" };

    std::vector<std::string> args;
    // args.push_back("unit");
    // args.push_back("0:50");

    return r;
}

int main(int argc, char *argv[]) {
    std::cout << cyan << "Cryptor Server Tests, Version: " << yellow << Version() << reset << "\n" << std::endl;
    std::vector<std::string> args(argv, argv + argc);

    Results summary = Results { .name = "Unit Test Summary" };

    // lambda to run a test and add its result to the summary
    auto run_test = [&summary](auto test_func) {
        auto result = test_func();
        std::cout << result << std::endl;
        summary.add(result);
    };

    run_test(test_version);
    run_test(test_cli);

    std::cout << "\n" << summary << std::endl;
    auto msg = (summary.failed == 0) ? green + "Ok" : "\n" + red + "Tests failed!" ;
    std::cout << cyan << "\nUnit Test Results: " << msg << reset << std::endl;

    return 0;
}


