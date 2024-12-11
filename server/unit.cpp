//
// 2024-12-10 18:27:44 dpw
//

#include <ansi_colors.hpp>

#include "cli.hpp"
#include "logging.hpp"
#include "version.hpp"
#include "service.hpp"
#include "testlib.hpp"

// the actual tests

Results test_version() {
    Results r = {.name = "Version Tests"};

    return r;
}

//
// cli tests and helper funcs
//
std::pair<int, char**> build_args(const std::vector<std::string>& vargs) {
    int argc = vargs.size();

    // Allocate memory for argv
    char** argv = new char*[argc];

    // Fill the argv array with C-style strings
    for (int i = 0; i < argc; ++i) {
        argv[i] = const_cast<char*>(vargs[i].c_str());  // Unsafe cast for illustration purposes
    }

    return {argc, argv};
}

void test_default_config(Results& r) {
    const std::vector<std::string> args = {"test"};
    auto [argc, argv] = build_args(args);
    auto cfg = parse_cli(argc, argv);

    r.equals(cfg.port == 2022, "the default port assignment");
    r.equals(cfg.host == "0.0.0.0", "the default host assignment");
    r.equals(cfg.base_dir == "./", "the default base dir assignment");
    r.equals(cfg.verbose == 1, "the default verbose assignment");
    r.equals(cfg.cert_file == "./cert.pem", "the default cert file assignment");
    r.equals(cfg.key_file == "./key.pem", "the default key file assignment");
}

void test_port(Results& r) {
    const std::vector<std::string> args = {"test", "-p", "2500"};
    auto [argc, argv] = build_args(args);
    auto cfg = parse_cli(argc, argv);

    r.equals(cfg.port == 2500, "the port assignment");

    r.equals(cfg.host == "0.0.0.0", "the default host assignment");
    r.equals(cfg.base_dir == "./", "the default base dir assignment");
    r.equals(cfg.verbose == 1, "the default verbose assignment");
    r.equals(cfg.cert_file == "./cert.pem", "the default cert file assignment");
    r.equals(cfg.key_file == "./key.pem", "the default key file assignment");
}

void test_host(Results& r) {
    const std::vector<std::string> args = {"test", "--host", "1.1.1.1"};
    auto [argc, argv] = build_args(args);
    auto cfg = parse_cli(argc, argv);

    r.equals(cfg.host == "1.1.1.1", "the host assignment");
    r.equals(cfg.port == 2022, "the default port assignment");
    r.equals(cfg.base_dir == "./", "the default base dir assignment");
    r.equals(cfg.verbose == 1, "the default verbose assignment");
    r.equals(cfg.cert_file == "./cert.pem", "the default cert file assignment");
    r.equals(cfg.key_file == "./key.pem", "the default key file assignment");
}

void test_base(Results& r) {
    auto base = "/www/home";
    const std::vector<std::string> args = {"test", "--base", base};
    auto [argc, argv] = build_args(args);
    auto cfg = parse_cli(argc, argv);

    r.equals(cfg.base_dir == base, "the base assignment");
    r.equals(cfg.port == 2022, "the default port assignment");
    r.equals(cfg.host == "0.0.0.0", "the default host assignment");
    r.equals(cfg.verbose == 1, "the default verbose assignment");
    r.equals(cfg.cert_file == "./cert.pem", "the default cert file assignment");
    r.equals(cfg.key_file == "./key.pem", "the default key file assignment");
}

void test_cert_key(Results& r) {
    auto cert = "my-cert.pem";
    auto key = "my-key.pem";

    const std::vector<std::string> args = {"test", "--cert", cert, "--key", key};
    auto [argc, argv] = build_args(args);
    auto cfg = parse_cli(argc, argv);

    r.equals(cfg.cert_file == cert, "the cert file assignment");
    r.equals(cfg.key_file == key, "the key file assignment");
    r.equals(cfg.port == 2022, "the default port assignment");
    r.equals(cfg.host == "0.0.0.0", "the default host assignment");
    r.equals(cfg.base_dir == "./", "the default base dir assignment");
    r.equals(cfg.verbose == 1, "the default verbose assignment");
}

Results test_cli() {
    Results r = {.name = "CLI Tests"};

    test_default_config(r);
    test_port(r);
    test_host(r);
    test_base(r);
    test_cert_key(r);

    return r;
}

void test_default_service(Results& r) {
    auto config = Config();
    httplib::SSLServer svr(config.cert_file.c_str(), config.key_file.c_str());
    auto ok = setup_service(svr, config);

    r.equals(ok == true, "should create the default server");
}

void test_bad_cert(Results& r) {
    auto config = Config();
    config.cert_file = "./no-file-here.pem";
    httplib::SSLServer svr(config.cert_file.c_str(), config.key_file.c_str());
    auto ok = setup_service(svr, config);

    r.equals(ok == false, "should fail with bad cert file server");
}

void test_bad_key(Results& r) {
    auto config = Config();
    config.key_file = "./no-file-here.pem";
    httplib::SSLServer svr(config.cert_file.c_str(), config.key_file.c_str());
    auto ok = setup_service(svr, config);

    r.equals(ok == false, "should fail with bad cert file server");
}

Results test_service() {
    Results r = {.name = "HTTPS Service Tests"};

    test_default_service(r);
    test_bad_cert(r);
    test_bad_key(r);

    return r;
}

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::off);

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
    run_test(test_service);

    std::cout << "\n" << summary << std::endl;
    auto msg = (summary.failed == 0) ? green + "Ok" : "\n" + red + "Tests failed!";
    std::cout << cyan << "\nUnit Test Results: " << msg << reset << std::endl;

    return 0;
}
