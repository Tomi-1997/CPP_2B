#define LINE_VER_LEN 100
#include <stdio.h>
#include <array>

namespace ariel
{
    class Line
    {
        public:
        std::array<char, LINE_VER_LEN> char_line;
        Line();
    };
}