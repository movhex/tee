#ifndef MYIO_H
#define MYIO_H

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>
#include <stdexcept>
extern "C" {
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
}

class MyIO {
public:
    enum class Mode : uint8_t;
public:
    MyIO(int fd);
    MyIO(const std::string &fname, Mode mode);
    MyIO(const MyIO &other) = delete;
    MyIO(MyIO &&other) = delete;
    std::string read(void) const;
    ssize_t write(const std::string &data) const;
    void operator=(const MyIO &other) = delete;
    void operator=(MyIO &&other) = delete;
    ~MyIO(void);
private:
    int m_fd;
    bool m_need_to_close;
}; // End of class

enum class MyIO::Mode : uint8_t {
    APPEND,
    REWRITE
}; // End of enum


#endif // MYIO_H
