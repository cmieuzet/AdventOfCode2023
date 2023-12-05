#include <iostream>
#include <fstream>

size_t getNumberLine(const std::string &line)
{
	size_t value = 0;
	char first;
	char last;

	std::string::const_iterator it = line.begin();
	std::string::const_iterator itEnd = line.end();
	for (; it != itEnd; it++)
	{
		if (std::isdigit(*it))
		{
			last = *it;
			if (!first)
				first = *it;
		}
	}
	value = (first - '0') * 10 + (last - '0');
	return value;
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
