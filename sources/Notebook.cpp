#include "Notebook.hpp"
#include <stdexcept>
using namespace ariel;

bool invalidIntegers(int p, int r, int c)
{
	return p < 0 || r < 0 || c < 0;
}

bool invalidWriteable(const std::string &word)
{
	for (char const &c : word)
		{
			if (c == '~' || c == '\n' || c == '\t' || c == '\r')
			{
				return true;
			}
		}
		return word.length() == 0;
}

void Notebook::write(int page, int line, int col, Direction dir, const std::string &word, bool writeCheck)
{
	if (invalidIntegers(page, line, col) || invalidWriteable(word))
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	int word_len = word.length();

	if ( !pages.contains(page) )
	{
		pages[page] = new ariel::Page();
	}
	//printf("pages now: %lu\n", pages.size());

	ariel::Page* current_page = pages[page];
	int last_index = 99;
	int current_line = line;
	int current_place = col % last_index;

	//printf("pages now: %lu\n", pages.size());
	if (dir == ariel::Direction::Horizontal)
	{
		// Check how many lines needed, for horizontal, num of lines needed is the same as the length of the word.
		for (int i = 0; i < word_len; i++)
		{
			if ( !current_page->lines.contains(line + i))
			{
				current_page->lines[line + i] = new ariel::Line();
			}
		}

		// Check if already written / deleted
		if (current_page->lines[current_line]->line[col] != '_' && writeCheck)
		{
			throw std::runtime_error("Trying to overwrite.");
		}

		// Write
		for (char const &c : word)
		{
			printf("Writing\n");
			current_page->lines[current_line]->line[col] = c;
			current_line++;
		}
	}

	if (dir == ariel::Direction::Vertical)
	{
		// Check how many lines needed for this write
		// If requested line \ overflowing lines from writing does not exist yet, initalize it.
		int lines_needed = ( (col + word_len) / 100 ) + 1;
		std::printf("lines needed: %d\n",lines_needed);
		for (int l = 0; l < lines_needed ; l++)
		{
			if ( !current_page->lines.contains(line + l) )
			{
				current_page->lines[line + l] = new ariel::Line();
			}
		}

		for (char const &c : word)
		{
			if (current_place == last_index + 1)
			{
				current_line++;
				current_place = 0;
			}

			// Check if already written / deleted
			if (current_page->lines[current_line]->line[current_place] != '_' && writeCheck)
			{
				throw std::runtime_error("Trying to overwrite.");
			}
			// In current page, in current line, in current place, change character.
			printf("Writing\n");
			current_page->lines[current_line]->line[current_place] = c;
			current_place++;
		}

	}

	printf("current notebook has this many pages: %lu\n", pages.size());
	printf("current page: %d has this many lines: %lu\n", page, current_page->lines.size());

}

std::string Notebook::read(int page, int line, int col, Direction dir, int len)
{
	if (invalidIntegers(page, line, col) || len < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}

	int lines_to_read;
	if (dir == ariel::Direction::Horizontal)
	{
		lines_to_read = len;
	}
	else
	{
		lines_to_read = (len / 100) + 1;
	}

	// check for existing page and lines, and init if needed.

	if ( !pages.contains(page) )
	{
		printf("read() new page \n");
		pages[page] = new ariel::Page();
	}
	ariel::Page* current_page = pages[page];

	printf("current notebook has this many pages: %lu\n", pages.size());
	printf("current page: %d has this many lines: %lu\n", page, current_page->lines.size());

	for (int i = 0; i < lines_to_read; i++)
	{
		if ( current_page->lines.contains(line + i) == false )
		{
			current_page->lines[line + i] = new ariel::Line();
			printf("%d, read() new line \n", i);
		}
	}

	std::string myAns;
	ariel::Line* current_line = current_page->lines[line];
	int current_place = col;
	int current_line_ind = line;

	for (int i = 0; i < len; i++)
	{
		myAns += current_line->line[current_place];

		if (dir == ariel::Direction::Vertical)
		{
			current_place++;
			if (current_place == 100)
			{
				myAns += "\n";
				current_line_ind++;
				current_line = current_page->lines[current_line_ind];
				current_place = 0;
			}
		}
		else
		{
			myAns += "\n";
			current_line_ind++;
			current_line = current_page->lines[current_line_ind];
		}
	}
	return myAns;
}

void Notebook::erase(int page, int line, int col, Direction dir, int len)
{
	if (invalidIntegers(page, line, col) || len < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}
}

void Notebook::show(int range)
{
	if (range < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}
}



