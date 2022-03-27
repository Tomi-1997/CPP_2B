#include "Line.hpp"

ariel::Line::Line() : char_line() // Init array of '_'
{
    //printf("Line init\n");
    char_line.fill('_');
}