//
//  cryptor server
//
// from the cpp-httplib examples folder
//

#include <cstdio>
#include <httplib.h>
#include <iostream>

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
std::string dump_multipart_files(const httplib::MultipartFormDataMap &files) {
    std::string s;
    char buf[BUFSIZ];

    s += "--------------------------------\n";

    for (const auto &x : files) {
        const auto &name = x.first;
        const auto &file = x.second;

        snprintf(buf, sizeof(buf), "name: %s\n", name.c_str());
        s += buf;

        snprintf(buf, sizeof(buf), "filename: %s\n", file.filename.c_str());
        s += buf;

        snprintf(buf, sizeof(buf), "content type: %s\n", file.content_type.c_str());
        s += buf;

        snprintf(buf, sizeof(buf), "text length: %zu\n", file.content.size());
        s += buf;

        s += "----------------\n";
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
    s += dump_multipart_files(req.files);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d\n", res.status);
    s += buf;
    s += dump_headers(res.headers);

    return s;
}

int main(int argc, const char **argv) {
    using namespace httplib;

    std::vector<std::string> args(argv, argv + argc);
    auto config = parse_cli(args);

    std::cout << "Server Version: " << Version() << std::endl;

    auto it = std::find(args.begin(), args.end(), "-h");
    if (it != args.end()) {
        show_help(args[0]);
        return 0;
    }

    SSLServer svr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);

    svr.Post("/multipart", [](const Request &req, Response &res) {
        auto body = dump_headers(req.headers) + dump_multipart_files(req.files);

        res.set_content(body, "text/plain"); 
    });

    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html"); 
    });

    svr.set_logger (
        [](const Request &req, const Response &res)
        { std::cout << log(req, res); });

    auto port = config.port;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    auto base_dir = "../html";

    if (!svr.set_mount_point("/", base_dir)) {
        std::cout << "The specified base directory doesn't exist...";
        return 1;
    }

    auto host = config.host;
    std::cout << "Server started at https://" << host << ":" << port << std::endl;

    auto code = svr.listen(host, port);

    std::cout << "Server exited with code:" << code << std::endl;

    return code;
}
