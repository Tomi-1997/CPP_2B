#include "Line.hpp"
#include <map>

namespace ariel 
{
    class Page
    {
        public:
        Page();
        std::map<int, Line*> lines;

    };
}