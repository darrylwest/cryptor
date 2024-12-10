//
//  cryptor server
//
// from the cpp-httplib examples folder
//

#include <cstdio>
#include <httplib.h>
#include <iostream>
#include <spdlog/spdlog.h>

#include "version.hpp"
#include "cli.hpp"

#define SERVER_CERT_FILE "./cert.pem"
#define SERVER_PRIVATE_KEY_FILE "./key.pem"

void show_headers(const httplib::Headers &headers) {
    for (const auto &x : headers) {
        spdlog::info("{}:{}", x.first.c_str(), x.second.c_str());
    }
}

void log_request(const httplib::Request &req, const httplib::Response &res) {
    spdlog::info("{} {} {}", req.method.c_str(), req.version.c_str(), req.path.c_str());

    for (auto it = req.params.begin(); it != req.params.end(); ++it) {
        const auto &x = *it;
        spdlog::info("{}={}", x.first.c_str(), x.second.c_str());
    }

    show_headers(req.headers);

    if (res.status > 299) {
        spdlog::error("Response status: {}", res.status);
    } else {
        spdlog::info("Response status: {}", res.status);
    }

    show_headers(res.headers);
}

int main(int argc, const char **argv) {
    using namespace httplib;

    const auto config = parse_cli(argc, argv);

    std::string version = "Server Version: ";
    auto vers = Version();
    
    version.append(vers.to_string());

    if (config.verbose > 0) {
        spdlog::info("Server Version: {}", version);
        spdlog::info("Server Config : {}", config.to_string());
    }

    SSLServer svr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);

    if (svr.is_valid() == 0) {
        spdlog::error("ERROR! Server is not valid. Check the cert/key files? exiting...");
        return 1;
    }

    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html"); 
    });

    svr.set_logger (
        [](const Request &req, const Response &res) { 
            log_request(req, res); 
        });

    if (!svr.set_mount_point("/", config.base_dir)) {
        spdlog::error("ERROR! The specified base directory {} doesn't exist...", config.base_dir);
        return 1;
    }

    spdlog::info("Server starting at https://{}:{}", config.host, config.port);

    auto code = svr.listen(config.host, config.port);

    spdlog::info("Server shutdown, code: {}...", code);

    return code;
}
