#include "Line.hpp"
#include <unordered_map>

namespace ariel 
{
    class Page
    {
        public:
        Page()
        {
            printf("Page init\n");
            std::unordered_map<int, Line*> lines = {};
        }
        std::unordered_map<int, Line*> lines;

    };
}