#include "Line.hpp"
ariel::Line::Line()
{
    printf("Line init\n");
    for (int i = 0; i < LINE_VER_LEN; i++)
    {
        line[i] = '_';
    }
}