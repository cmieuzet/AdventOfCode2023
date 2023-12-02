#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <cstring>

int findNumberWord(const std::string &word)
{
	static const std::map<std::string, int> numberUtils = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
	std::map<std::string, int>::const_iterator it = numberUtils.begin();

	for (; it != numberUtils.end(); it++)
	{

		if (!strncmp(word.c_str(), it->first.c_str(), it->first.length()))
			return it->second;
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
			vec.push_back(*it - '0');
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
