#include "Page.hpp"
using namespace ariel;

ariel::Page::Page()
{
    printf("Page init\n");
    std::unordered_map<int, Line*> lines = {};
}