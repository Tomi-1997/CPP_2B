#include "Direction.hpp"
#include "Page.hpp" // has line and unordered map
#include <string>

namespace ariel
{
    class Notebook
    {
        public:

        std::unordered_map<int, ariel::Page*> pages;

        Notebook()
        {
            printf("Notebook init \n");
            std::unordered_map<int, ariel::Page*> pages = {};
        }

        void write(int page, int line, int col, Direction dir, const std::string &word, /* 0 for wite, 1 for erase */ bool writeCheck);

	    std::string read(int page, int line, int col, Direction dir, int len);

        void erase(int page, int line, int col, Direction dir, int len);

        void show(int range);

    };
}
