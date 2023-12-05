#include <iostream>
#include <fstream>

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
