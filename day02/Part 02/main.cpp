#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class Power
{
private:
    std::map<std::string, int> _map;

public:
    void getCubesbyPower(const std::string &line);
    size_t getPower() const;
    Power();
    ~Power();
};

Power::Power()
{
    _map = {{"red", 0}, {"green", 0}, {"blue", 0}};
}

Power::~Power() {}

void Power::getCubesbyPower(const std::string &line)
{
    std::string tmp;
    std::stringstream ss(line);

    while (std::getline(ss, tmp, ','))
    {
        std::string cubes;
        std::string color;
        std::stringstream ss2(tmp);
        ss2 >> cubes;
        ss2 >> color;
        std::map<std::string, int>::iterator it = _map.find(color);
        if (atoi(cubes.c_str()) > it->second)
            it->second = atoi(cubes.c_str());
    }
}

size_t Power::getPower() const
{
    size_t resultPower = 1;
    std::map<std::string, int>::const_iterator it = _map.begin();

    for (; it != _map.end(); it++)
        resultPower *= it->second;
    return resultPower;
}

size_t getPowerPerGame(const std::string &line)
{
    Power power;
    std::string set;
    std::string CubesColor;
    std::stringstream ss(line);

    std::getline(ss, set, ':');
    while (std::getline(ss, set, ';'))
        power.getCubesbyPower(set);
    return power.getPower();
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
        value += getPowerPerGame(line);
    file.close();
    std::cout << "Answer : " << value << std::endl;
    return 0;
}
