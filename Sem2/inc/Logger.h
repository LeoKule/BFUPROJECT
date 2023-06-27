#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
public:
    template <typename T>
    static void error(const T& message) {
        std::cerr << "ERROR: " << message << std::endl;
    }
};

#endif  // LOGGER_H
