#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

bool isGamePossible(const std::string &set)
{
    std::string tmp;
    std::stringstream ss(set);
    static const std::map<std::string, int> colorRef = {{"red", 12}, {"green", 13}, {"blue", 14}};
    std::map<std::string, int>::const_iterator it;

    while (std::getline(ss, tmp, ','))
    {
        std::string cubes;
        std::string color;
        std::stringstream ss2(tmp);
        ss2 >> cubes;
        ss2 >> color;
        it = colorRef.find(color);
        if (it->second < atoi(cubes.c_str()))
            return false;
    }
    return true;
}

size_t getIndexGameWon(const std::string &line)
{
    std::string game;
    std::string set;
    std::stringstream ss(line);

    std::getline(ss, game, ':');
    while (std::getline(ss, set, ';'))
    {
        if (!isGamePossible(set))
            return 0;
    }
    game.erase(0, 5);
    return (atoi(game.c_str()));
}

int main(int argc, char **argv)
{
    size_t value = 0;
    std::string line;
    std::ifstream file;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        value += getIndexGameWon(line);
    file.close();
    std::cout << "Answer : " << value << std::endl;
    return 0;
}
