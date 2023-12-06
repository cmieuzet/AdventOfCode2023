#include <iostream>
#include <fstream>
#include <vector>

class Race
{
private:
    size_t _time;
    size_t _distance;
    ssize_t _nbWin;

public:
    Race();
    ~Race();

    void parse(const std::vector<std::string> &lineSplit);
    void calcul();
    int getResult();
};

Race::Race()
{
    _time = 0;
    _distance = 0;
    _nbWin = 0;
}

Race::~Race() {}

void Race::parse(const std::vector<std::string> &lineSplit)
{
    std::string tim;
    std::string dis;

    for (size_t i = 1; i < lineSplit.size() / 2; i++)
    {
        tim += lineSplit[i];
        dis += lineSplit[i + lineSplit.size() / 2];
    }
    _time += (strtoul(tim.c_str(), NULL, 10));
    _distance += (strtoul(dis.c_str(), NULL, 10));
}

void Race::calcul()
{
    size_t tmp;

    for (size_t i = _time - 1; i > 0; i--)
    {
        tmp = i * (_time - i);
        if (tmp > _distance)
            _nbWin += 1;
    }
}

int Race::getResult() { return _nbWin; }

std::vector<std::string> split(const std::string &file, char sep)
{
    std::vector<std::string> s_split;
    size_t x = 0;
    size_t i = 0;

    while ((i = file.find(sep, x)) != std::string::npos)
    {
        s_split.push_back(file.substr(x, i - x));
        x = i;
        while (file[x] == sep && x < file.size())
            x++;
    }
    if (x != file.size())
        s_split.push_back(file.substr(x, file.size() - x));
    return s_split;
}

int main(int argc, char **argv)
{
    std::string line;
    std::string tmp;
    std::ifstream file;
    Race race;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        tmp += line + ' ';
    race.parse(split(tmp, ' '));
    file.close();
    race.calcul();
    std::cout << "Answer : " << race.getResult() << std::endl;
    return 0;
}
