#include <string>
#define LINE_VER_LEN 100

namespace ariel
{
    class Line
    {
        public:
        char line[LINE_VER_LEN];

        Line()
        {
            for (int i = 0; i < LINE_VER_LEN; i++)
            {
                line[i] = '_';
            }
        }
    };
}