//
//  cryptor server
//
// from the cpp-httplib examples folder
//

#include <httplib.h>
#include <spdlog/spdlog.h>

#include <cstdio>
#include <iostream>

#include "cli.hpp"
#include "logging.hpp"
#include "version.hpp"

int main(const int argc, char **argv) {
    using namespace httplib;

    const auto config = parse_cli(argc, argv);

    std::string version = "Server Version: ";
    auto vers = Version();

    version.append(vers.to_string());

    if (config.verbose > 0) {
        spdlog::info("Server Version: {}", version);
        spdlog::info("Server Config : {}", config.to_string());
    }

    SSLServer svr(config.cert_file.c_str(), config.key_file.c_str());

    if (svr.is_valid() == 0) {
        spdlog::error("ERROR! Server is not valid. Check the cert/key files? exiting...");
        return 1;
    }

    // TODO : create a better error page
    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    svr.set_logger([](const Request &req, const Response &res) {
        log_request(req, res);
    });

    if (!svr.set_mount_point("/", config.base_dir)) {
        spdlog::error("ERROR! The specified base directory {} doesn't exist...", config.base_dir);
        return 1;
    }

    // shutdown hook
    svr.Delete("/shutdown", [&](const Request &, Response &res) {
        res.set_content("ok, shutting down...", "text/plain");
        spdlog::info("shutting down...");
        svr.stop();
    });

    spdlog::info("Server starting at https://{}:{}", config.host, config.port);

    auto code = svr.listen(config.host, config.port);

    spdlog::info("Server shutdown, code: {}...", code);

    return code;
}
