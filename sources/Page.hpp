#include "Line.hpp"
#include <unordered_map>

namespace ariel 
{
    class Page
    {
        public:

        std::unordered_map<int, Line> lines;
    };
}