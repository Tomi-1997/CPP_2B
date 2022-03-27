#include "Notebook.hpp"
#include <stdexcept> // To raise exception
#include <ctype.h> // Check if character is printable 
#include <iostream>
using namespace ariel;

constexpr int LAST_VALID_INDEX = 99;
constexpr int INVALID_INDEX = 100;

// #define LAST_VALID_INDEX 99
// #define INVALID_INDEX 100

ariel::Notebook::Notebook()
{
	// printf("Notebook init \n");
	// reference https://en.cppreference.com/w/cpp/container/unordered_map
	std::unordered_map<int, ariel::Page*> pages = {};
}

ariel::Notebook::~Notebook()
{
	//printf("Notebook delete \n");
	for (auto& page : pages)
	{
		ariel::Page* current_page = page.second;
		for (auto& line : current_page->lines)
		{
			delete line.second;
		}
		delete current_page;
	}
}

bool invalidIntegers(int p, int r, int c)
{
	return p < 0 || r < 0 || c < 0;
}

bool invalidWriteable(const std::string &word)
{
	for (char const &c : word)
		{
			if ( isprint(c) == 0 || c == '~' || c == '\n' || c == '\t' || c == '\r')
			{
				return true;
			}
		}
		return word.length() == 0;
}

/**
 * @brief Default write(), will raise exception if overwriting occurs.
 * 
 * @param page 
 * @param line 
 * @param col 
 * @param dir 
 * @param word 
 */
void Notebook::write(int page, int line, int col, Direction dir, const std::string &word)
{
	write(page, line, col, dir, word, false);
}

/**
 * @brief Writes given string, will raise exception if is called from default write() while trying to overwrite existing characters.
 * 
 * @param page 
 * @param line 
 * @param col 
 * @param dir 
 * @param word 
 * @param isDelete 
 */
void Notebook::write(int page, int line, int col, Direction dir, const std::string &word, bool isDelete)
{
	if (invalidIntegers(page, line, col) || ( !isDelete && invalidWriteable(word)))
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	int word_len = word.length();

	if (dir == ariel::Direction::Horizontal && col + word_len > LAST_VALID_INDEX)
	{
		throw std::invalid_argument("Invalid write length.");
	}

	if ( !pages.contains(page) )
	{
		pages[page] = new ariel::Page();
	}
	//printf("pages now: %lu\n", pages.size());

	ariel::Page* current_page = pages[page];
	int current_line = line;
	size_t current_place = (size_t) col;

	//printf("pages now: %lu\n", pages.size());
	if (dir == ariel::Direction::Vertical)
	{
		// Check how many lines needed, for vertical, num of lines needed is the same as the length of the word.
		for (int i = 0; i < word_len; i++)
		{
			if ( !current_page->lines.contains(line + i))
			{
				current_page->lines[line + i] = new ariel::Line();
			}
		}


		// Write
		for (char const &c : word)
		{
			
			// Check if already written / deleted
			if (current_page->lines[current_line]->char_line.at(current_place) != '_' && !isDelete)
			{
				throw std::runtime_error("Trying to overwrite.");
			}

			//printf("Writing\n");
			current_page->lines[current_line]->char_line.at(current_place) = c;
			current_line++;
		}
	}

	if (dir == ariel::Direction::Horizontal)
	{
		// Check how many lines needed for this write
		// // If requested line \ overflowing lines from writing does not exist yet, initalize it.
		// int lines_needed = ( (col + word_len) / (last_index+1) ) + 1;
		// //printf("lines needed: %d\n",lines_needed);
		// for (int l = 0; l < lines_needed ; l++)
		// {
		if ( !current_page->lines.contains(line) )
		{
			current_page->lines[line] = new ariel::Line();
		}
		// }

		for (char const &c : word)
		{
			if (current_place == INVALID_INDEX)
			{
				current_line++;
				current_place = 0;
			}

			// Check if already written / deleted
			if (current_page->lines[current_line]->char_line.at(current_place) != '_' && !isDelete)
			{
				throw std::runtime_error("Trying to overwrite.");
			}
			// In current page, in current line, in current place, change character.
			//printf("Writing\n");
			current_page->lines[current_line]->char_line.at(current_place) = c;
			current_place++;
		}

	}

	//printf("current notebook has this many pages: %lu\n", pages.size());
	//printf("current page: %d has this many lines: %lu\n", page, current_page->lines.size());

}

/**
 * @brief Will read existing lines, and if needed initialize new lines and read them.
 * 
 * @param page 
 * @param line 
 * @param col 
 * @param dir 
 * @param len 
 * @return std::string 
 */
std::string Notebook::read(int page, int line, int col, Direction dir, int len)
{
	if (invalidIntegers(page, line, col) || len < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	if (dir == ariel::Direction::Horizontal && col + len > LAST_VALID_INDEX + 1)
	{
		throw std::invalid_argument("invaid read() length");
	}

	int lines_to_read = 1;
	const int last_index = INVALID_INDEX;
	if (dir == ariel::Direction::Vertical)
	{
		lines_to_read = len; 
	}
	// check for existing page and lines, and init if needed.

	if ( !pages.contains(page) )
	{
		//printf("read() new page \n");
		pages[page] = new ariel::Page();


		// Fixed to match testing
		//throw std::invalid_argument("Nonexistent page read at read()");
	}
	ariel::Page* current_page = pages[page];

	// printf("current notebook has this many pages: %lu\n", pages.size());
	// printf("current page: %d has this many lines: %lu\n", page, current_page->lines.size());

	for (int i = 0; i < lines_to_read; i++)
	{
		if ( !current_page->lines.contains(line + i) )
		{
			current_page->lines[line + i] = new ariel::Line();
			//printf("%d, read() new line \n", i);

			// Fixed to match testing
			//throw std::invalid_argument("Nonexistent line read at read()");
		}
	}

	std::string myAns;
	size_t current_place = (size_t) col;
	int current_line_ind = line;

	for (int i = 0; i < len; i++)
	{
		std::array<char,INVALID_INDEX> current_line = current_page->lines[current_line_ind]->char_line;
		char current = current_line.at(current_place);

		myAns += current;

		if (dir == ariel::Direction::Horizontal)
		{
			current_place++;
			// if (current_place == last_index)
			// {
			// 	//myAns += "\n";
			// 	current_line_ind++;
			// 	current_line = current_page->lines[current_line_ind]->line;
			// 	current_place = 0;
			// }
		}
		else
		{
			current_line_ind++;
		}
	}
	return myAns;
}

/**
 * @brief Calls write() with delete flag to mark '~' regardless of current written characters on given position.
 * 
 * @param page 
 * @param line 
 * @param col 
 * @param dir 
 * @param len 
 */
void Notebook::erase(int page, int line, int col, Direction dir, int len)
{
	if (invalidIntegers(page, line, col) || len < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	if (dir == ariel::Direction::Horizontal && col + len > LAST_VALID_INDEX)
	{
		throw std::invalid_argument("invaid read() length");
	}

	std::string word;
	for (int i = 0; i < len; i++)
	{
		word += '~';
	}

	write(page, line, col, dir, word, true);

}

void Notebook::show(int range)
{
	if (range < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	display();
}

void Notebook::display()
{
	std::string dis;
	for (auto& page : pages)
	{
		std::string page_headline = "----- PAGE ";
		page_headline += std::to_string(page.first);
		page_headline += " -----\n";

		ariel::Page* current_page = page.second;
		for (auto& line : current_page->lines)
		{
			std::string line_headline = "[LINE " + std::to_string(line.first) + "]";
			std::array<char,INVALID_INDEX> current_line = line.second->char_line;
			for (const char c: current_line)
			{
				line_headline += c;
			}
			line_headline += "\n";
			dis.insert(0, line_headline);
		}

		dis.insert(0, page_headline);
	}

	std::cout << dis << std::endl;
}


