//
// 2024-12-09 10:28:16 dpw
//
// all standard includes are done here...
// create a version struct with major, minor, patch and build attributes
//

#ifndef VERSION_INCLUDE
#define VERSION_INCLUDE

#include <iostream>
#include <sstream>
#include <ansi_colors.hpp>
#include <vector>
#include <stdexcept>
#include <algorithm>

/*
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <thread>
*/

// version numbers are year.month.day.build where the year/month/day is the release date
struct Version {
    int major = 2024;
    int minor = 12;
    int patch = 10;
    int build = 108;

    friend std::ostream& operator<<(std::ostream& os, const Version v) {
        // better to use <format> but it breaks on linux and fmt broken on darwin
        os << v.major << "."
            << v.minor << "."
            << v.patch << "."
            << v.build
        ;
        return os;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << *this;

        return oss.str();
    }

};

#endif