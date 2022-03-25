#include "Direction.hpp"
#include "Page.hpp" // has line and unordered map

namespace ariel
{
    class Notebook
    {
        public:

        std::unordered_map<int, Page> pages;

        void write(int page, int row, int col, Direction dir, const std::string &word);

	    std::string read(int page, int row, int col, Direction dir, int len);

        void erase(int page, int row, int col, Direction dir, int len);

        void show(int range);
    };
}
