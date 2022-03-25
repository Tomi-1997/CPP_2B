#define LINE_VER_LEN 100
#include <stdio.h>

namespace ariel
{
    class Line
    {
        public:
        char line[LINE_VER_LEN];

        Line()
        {
            printf("Line init\n");
            for (int i = 0; i < LINE_VER_LEN; i++)
            {
                line[i] = '_';
            }
        }
    };
}