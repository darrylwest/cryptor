//
// 2024-12-10 18:27:44 dpw
//

#include <httplib.h>
#include <spdlog/spdlog.h>

#include <cstdio>
#include <iostream>

using namespace httplib;

// Function to set up the server and apply configurations
bool setup_service(SSLServer& svr, const Config& config) {
    if (svr.is_valid() == 0) {
        spdlog::error("ERROR! Server is not valid. Check the cert/key files? Exiting...");
        return false;
    }

    // Error handler
    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    // Logger
    svr.set_logger([](const Request &req, const Response &res) {
        log_request(req, res);
    });

    // Mount point
    if (!svr.set_mount_point("/", config.base_dir)) {
        spdlog::error("ERROR! The specified base directory {} doesn't exist...", config.base_dir);
        return false;
    }

    // Shutdown hook
    svr.Delete("/shutdown", [&](const Request &, Response &res) {
        res.set_content("ok, shutting down...", "text/plain");
        spdlog::info("Shutting down...");
        svr.stop();
    });

    return true;
}

// Function to run the server
bool run_service(const Config& config) {
    SSLServer svr(config.cert_file.c_str(), config.key_file.c_str());

    // Set up the server
    if (!setup_service(svr, config)) {
        return false;
    }

    spdlog::info("Server starting at https://{}:{}", config.host, config.port);

    // Start the server
    return svr.listen(config.host, config.port);
}
