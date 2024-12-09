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

// TODO : replace with log
std::string dump_headers(const httplib::Headers &headers) {
    std::string s;
    char buf[BUFSIZ];

    for (const auto &x : headers) {
        snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
        s += buf;
    }

    return s;
}

// TODO : replace with log
std::string log(const httplib::Request &req, const httplib::Response &res) {
    std::string s;
    char buf[BUFSIZ];

    s += "================================\n";

    snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
             req.version.c_str(), req.path.c_str());
    s += buf;

    std::string query;
    for (auto it = req.params.begin(); it != req.params.end(); ++it) {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%c%s=%s",
                 (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
                 x.second.c_str());
        query += buf;
    }
    snprintf(buf, sizeof(buf), "%s\n", query.c_str());
    s += buf;

    s += dump_headers(req.headers);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d\n", res.status);
    s += buf;
    s += dump_headers(res.headers);

    return s;
}

int main(int argc, const char **argv) {
    using namespace httplib;

    const auto config = parse_cli(argc, argv);

    std::string version = "Server Version: ";
    auto vers = Version();
    
    version.append(vers.to_string());

    if (config.verbose > 0) {
        spdlog::info("Server Version: {}", version);
        // spdlog::info("Server Config : {}", config);
    }

    SSLServer svr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);

    if (svr.is_valid() == 0) {
        std::cout << "Server is not valid. Check the cert/key files? " << std::endl;
        return 1;
    }

    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html"); 
    });

    svr.set_logger (
        [](const Request &req, const Response &res)
        { std::cout << log(req, res); });


    if (!svr.set_mount_point("/", config.base_dir)) {
        std::cout << "The specified base directory doesn't exist...";
        return 1;
    }

    std::cout << "Server starting at https://" << config.host << ":" << config.port << std::endl;

    auto code = svr.listen(config.host, config.port);

    std::cout << "Server exited with code:" << code << std::endl;

    return code;
}
