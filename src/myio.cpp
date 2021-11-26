#include "myio.h"


MyIO::MyIO(int fd)
    : m_fd(fd)
    , m_need_to_close(false)
{}


MyIO::MyIO(const std::string &fname, Mode mode)
{
    int fmode = (mode == MyIO::Mode::APPEND) ?
        O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC;

    int fd = open(fname.c_str(), fmode, 0666);
    if (fd == -1) {
        char msg[100];
        std::snprintf(msg, sizeof(msg), "failed to open(%s)", fname.c_str());
        throw std::runtime_error(msg);
    }
    m_fd = fd;
    m_need_to_close = true;
}


std::string MyIO::read(void) const
{
    size_t buf_size = 16;
    size_t offset = 0;
    char *buf = new char [buf_size];
    char *temp = nullptr;

    while (true) {
        ssize_t n = ::read(m_fd, buf + offset, buf_size);
        if (n == 0) {
            break;
        }
        else if (n == -1) {
            char msg[100];
            std::snprintf(msg, sizeof(msg), "failed to read(%d)", m_fd);
            throw std::runtime_error(msg);
        }
        offset += n;
        temp = buf;
        buf_size *= 2;
        buf = new char [buf_size];
        std::memmove(buf, temp, offset);
        delete[] temp;
    }

    std::string res = std::string(buf, offset);

    delete[] buf;

    return res;
}


ssize_t MyIO::write(const std::string &data) const
{
    ssize_t n = ::write(m_fd, data.c_str(), data.size());
    if (n == -1) {
        char msg[100];
        std::snprintf(msg, sizeof(msg), "failed to write(%d)", m_fd);
        throw std::runtime_error(msg);
    }
    return n;
}


MyIO::~MyIO(void)
{
    if (m_need_to_close) {
        close(m_fd);
    }
}
