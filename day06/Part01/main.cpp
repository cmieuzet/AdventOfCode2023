#include <iostream>
#include <fstream>
#include <vector>

class Race
{
private:
    std::vector<std::pair<int, int>> _infRace;
    std::vector<int> _nbWin;

public:
    Race();
    ~Race();

    void parse(const std::vector<std::string> &lineSplit);
    void calcul();
    int getResult();
};

Race::Race() {}

Race::~Race() {}

void Race::parse(const std::vector<std::string> &lineSplit)
{
    for (size_t i = 1; i < lineSplit.size() / 2; i++)
        _infRace.push_back(std::pair<int, int>(atoi(lineSplit[i].c_str()), atoi(lineSplit[i + lineSplit.size() / 2].c_str())));
}

void Race::calcul()
{
    int tmp;
    int result;
    auto it = _infRace.begin();
    for (; it != _infRace.end(); it++)
    {
        result = 0;
        for (size_t i = it->first - 1; i > 0; i--)
        {
            tmp = i * (it->first - i);
            if (tmp > it->second)
                result += 1;
        }
        _nbWin.push_back(result);
    }
}

int Race::getResult()
{
    int tmp = 1;
    for (auto it = _nbWin.begin(); it != _nbWin.end(); it++)
        tmp *= *it;
    return tmp;
}

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
