//
// 2024-12-13 15:25:10 dpw
//

#include <httplib.h>
#include <spdlog/spdlog.h>

#include <ansi_colors.hpp>
#include <atomic>
#include <cassert>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "testlib.hpp"
#include "version.hpp"

using namespace colors;

// Define the function to start the service
void run_server(std::atomic<bool>& running) {
    running = true;

    // Start the service in a separate process
    std::system("build/cryptor --level 1 --base html --port 22022 &");

    std::cout << cyan << "service running..." << reset << std::endl;

    // Wait for a brief period to allow the service to initialize
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// use cxxopts to parse host and port
// if the service is not local (localhost or 127.0.0.1), then skip the startup?
int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::critical);

    std::string msg = "Cryptor Server Unit Tests, Version: ";
    std::cout << cyan << msg << yellow << cryptor::Version() << reset << "\n" << std::endl;

    std::atomic<bool> server_running(false);
    std::thread server_thread(run_server, std::ref(server_running));

    // Wait for the server to start
    while (!server_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Create a client for testing
    httplib::Client cli("https://localhost:22022");
    cli.enable_server_certificate_verification(false);

    // Test 1: Verify version endpoint
    if (auto res = cli.Get("/version")) {
        assert(res->status == 200);
        assert(res->body == "1.0.0");
        std::cout << "Test 1 passed: Version endpoint returned correct response.\n";
    } else {
        std::cerr << "Test 1 failed: Unable to reach version endpoint.\n";
        return 1;
    }

    // Test 2: Verify index page title
    if (auto res = cli.Get("/")) {
        assert(res->status == 200);
        assert(res->body.find("<title>Cryptor</title>") != std::string::npos);
        std::cout << "Test 2 passed: Index page contains correct title.\n";
    } else {
        std::cerr << "Test 2 failed: Unable to reach index page.\n";
        return 1;
    }

    // Test 3: Shut down the server
    if (auto res = cli.Delete("/shutdown")) {
        assert(res->status == 200);
        assert(res->body == "Shutting down");
        std::cout << "Test 3 passed: Shutdown endpoint returned correct response.\n";
    } else {
        std::cerr << "Test 3 failed: Unable to reach shutdown endpoint.\n";
        return 1;
    }

    // Wait for the server thread to stop
    server_thread.join();

    // Verify server has stopped
    assert(!server_running);
    std::cout << "Test 4 passed: Server thread has stopped.\n";

    return 0;
}