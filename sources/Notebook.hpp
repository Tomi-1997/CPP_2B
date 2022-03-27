#include "Direction.hpp"
#include "Page.hpp" // has line and unordered map
#include <string>

namespace ariel
{
    class Notebook
    {
        public:

        // reference https://en.cppreference.com/w/cpp/container/unordered_map
        std::map<int, ariel::Page*> pages;

        Notebook();
        ~Notebook();

        // Calls write with flag to check for overwriting.
        void write(int page, int line, int col, Direction dir, const std::string &word);

        // Write / delete
        void write(int page, int line, int col, Direction dir, const std::string &word, /* 0 for wite, 1 for erase */ bool isDelete);

	    std::string read(int page, int line, int col, Direction dir, int len);

        // Calls write but with '~' with no overwriting flag.
        void erase(int page, int line, int col, Direction dir, int len);

        void show(int range);

        // Show all existing pages, and all existing lines.
        void display();

    };
}
