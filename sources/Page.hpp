#include "Line.hpp"
#include <unordered_map>

namespace ariel 
{
    class Page
    {
        public:
        Page();
        std::unordered_map<int, Line*> lines;

    };
}