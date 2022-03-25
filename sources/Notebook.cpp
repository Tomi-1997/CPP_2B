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

void Notebook::write(int page, int row, int col, Direction dir, const std::string &word)
{
	if (invalidIntegers(page, row, col) || invalidWriteable(word))
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}
}

std::string Notebook::read(int page, int row, int col, Direction dir, int len)
{
	if (invalidIntegers(page, row, col) || len < 0)
	{
		throw std::invalid_argument("Invalid argument\\s.");
	}
	return " ";
}

void Notebook::erase(int page, int row, int col, Direction dir, int len)
{
	if (invalidIntegers(page, row, col) || len < 0)
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



