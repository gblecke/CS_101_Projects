#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>

using namespace std;

class InvalidOperationException {
private:
    std::string message;
public:
    InvalidOperationException(const char *msg) {
        message = msg;
    }
    InvalidOperationException(const std::string &msg) {
        message = msg;
    }
    std::string getMessage() const {
        return message;
    }
};

class IndexOutOfRangeException {
private:
    std::string message;
    int index;
public:
    IndexOutOfRangeException(const char *msg, const int &idx) {
        message = msg;
        index = idx;
    }
    IndexOutOfRangeException(const std::string &msg, const int &idx) {
        message = msg;
        index = idx;
    }
    std::string getMessage() const {
        return message;
    }
    int getIndex() const {
        return index;
    }
};

#endif
