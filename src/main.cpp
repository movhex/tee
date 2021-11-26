#include <cstdio>
#include <string>
#include <stdexcept>
extern "C" {
#include <unistd.h> // getopt
}

#include "myio.h"


static MyIO::Mode file_mode = MyIO::Mode::REWRITE;
static std::string output_file;


void parse_argv(int argc, char *const argv[])
{
    char c;
    while ((c = getopt(argc, argv, ":a")) != -1) {
        switch (c) {
        case 'a':
            file_mode = MyIO::Mode::APPEND;
            break;
        }
    }
    if (argc >= 2) {
        output_file = argv[argc -1];
    }
}


int main(int argc, char *const argv[])
{
    parse_argv(argc, argv);

    MyIO in(STDIN_FILENO);
    MyIO out(STDOUT_FILENO);

    std::string str = in.read();
    out.write(str);

    if (!output_file.empty()) {
        MyIO file(output_file, file_mode);
        file.write(str);
    }

    return 0;
}
