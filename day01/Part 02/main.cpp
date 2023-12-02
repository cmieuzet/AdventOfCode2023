#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdbool.h>
#include <stdlib.h>
#include <cstring>

const std::map<std::string, std::pair<int, int>> &getMapNumberWord(void)
{

	static std::map<std::string, std::pair<int, int>> numberUtils;

	if (numberUtils.empty())
	{

		numberUtils["one"] = {3, 1};
		numberUtils["two"] = {3, 2};
		numberUtils["three"] = {5, 3};
		numberUtils["four"] = {4, 4};
		numberUtils["five"] = {4, 5};
		numberUtils["six"] = {3, 6};
		numberUtils["seven"] = {5, 7};
		numberUtils["eight"] = {5, 8};
		numberUtils["nine"] = {4, 9};
	}
	return numberUtils;
}

int findNumberWord(const std::string &word)
{

	static const std::map<std::string, std::pair<int, int>> numberUtils = getMapNumberWord();
	std::map<std::string, std::pair<int, int>>::const_iterator it = numberUtils.begin();

	for (; it != numberUtils.end(); it++)
	{

		if (!strncmp(word.c_str(), it->first.c_str(), it->second.first))
			return it->second.second;
	}
	return 0;
}

size_t getNumberLine(const std::string &line)
{

	int tmp;
	std::vector<int> vec;
	std::string::const_iterator it = line.begin();
	std::string::const_iterator itEnd = line.end();

	for (; it != itEnd; it++)
	{
		if (std::isdigit(*it))
		{
			vec.push_back(*it - '0');
		}
		else
		{
			tmp = findNumberWord(&*it);
			if (tmp != 0)
				vec.push_back(tmp);
		}
	}
	return (*(vec.begin()) * 10) + (*(vec.end() - 1));
}

int main(int argc, char **argv)
{

	std::string line;
	std::ifstream file;
	size_t value = 0;

	if (argc != 2)
		return 1;
	file.open(argv[1]);

	while (getline(file, line))
		value += getNumberLine(line);
	file.close();
	std::cout << "Answer : " << value << std::endl;
	return 0;
}
