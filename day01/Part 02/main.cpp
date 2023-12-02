#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

	std::map<std::string, int>	number;

bool	findNumberWord(const std::string & word) {

	std::cout << word << std::endl;
	return true;
}

size_t	getNumberLine(const std::string & line) {

	std::vector<int>	vec;
	std::string::const_iterator	it = line.begin();
	std::string::const_iterator	itEnd = line.end();

	for (; it != itEnd; it++) {
		if (std::isdigit(*it)) {
			vec.push_back(*it - '0');
		} else if (findNumberWord(&*it)) {
			//vec.push_back(getInt())
		}
	}

	(void)line;
	return 1;
}

int main(int argc, char **argv) {

	std::string	line;
	std::ifstream	file;
	size_t		value = 0;

	if (argc != 2)
		return 1;
	file.open(argv[1]);

	while (getline(file, line))
		value += getNumberLine(line);
	file.close();
	std::cout << "Answer : " << value << std::endl;
	return 0;
}
/*
zpcvkjjqeight94one82mrvfzdvlgjgkhj

if *it isdigit push_back

if *it match = singleton return 9
*/
