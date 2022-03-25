/** *
 * AUTHORS: <Tom Inbar>
 * 
 */

#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"

using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

//template CHECK_THROWS(); 

TEST_CASE("Good input")
{
ariel::Notebook myNote;
const int LIM = 50;
for (int i = 0; i < LIM; i = i  + 2)
	{
	CHECK_NOTHROW(myNote.write(i, 0, 0, Direction::Horizontal, "no seg fault please"));
	CHECK_NOTHROW(myNote.write(i + 1, 0, 0, Direction::Horizontal, "no core dump please"));

	CHECK_NOTHROW(myNote.read(i, 0, 0, Direction::Horizontal, 10));
	CHECK_NOTHROW(myNote.read(i + 1, 0, 0, Direction::Horizontal, 20));

	CHECK_NOTHROW(myNote.erase(i, 0, 0, Direction::Horizontal, 5));
	CHECK_NOTHROW(myNote.erase(i + 1, 0, 0, Direction::Horizontal, 5));

	CHECK_NOTHROW(myNote.read(i, 0, 0, Direction::Horizontal, 10));
	CHECK_NOTHROW(myNote.read(i + 1, 0, 0, Direction::Horizontal, 20));
	}
}

TEST_CASE("Bad input")
{
	ariel::Notebook myNote;
	for (int i = - 5; i < 0; i ++)
	{
		/* Test invalid page, col, or row */
		CHECK_THROWS(myNote.write(i, 100, 50, Direction::Horizontal, "write me"));
		CHECK_THROWS(myNote.read(0, 10, 10, Direction::Vertical, i));
		CHECK_THROWS(myNote.erase(0, i, 10, Direction::Horizontal, 5));
		CHECK_THROWS(myNote.show(i));

		/* Test invalid string to write */
		CHECK_THROWS(myNote.write(10, 100, 50, Direction::Horizontal, "w~rit~e m~e~"));
	}
}

TEST_CASE("Invalid overwrite cases")
{
	ariel::Notebook myNote;
    CHECK_NOTHROW(myNote.write(1, 10, 10, Direction::Horizontal, "don't overwrite me"));
	CHECK_THROWS(myNote.write(1, 10, 10, Direction::Horizontal, "i am overwriting"));
	// line above will throw after implementation
}
