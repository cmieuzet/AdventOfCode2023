#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstring>

class Network
{
private:
    int _nbRoute;
    std::string _start;
    std::string _end;
    std::vector<char> _instruct;
    std::map<std::string, std::pair<std::string, std::string>> _route;

public:
    Network();
    ~Network();

    void parseInstruct(std::string instruct);
    void parse(const std::vector<std::string> &file);
    void resolve();
    int getResult() const;
};

Network::Network()
{
    _nbRoute = 0;
    _start = "AAA";
    _end = "ZZZ";
}

Network::~Network() {}

void Network::parseInstruct(std::string instruct)
{
    for (auto it = instruct.begin(); it != instruct.end(); it++)
        _instruct.push_back(*it);
}

void Network::parse(const std::vector<std::string> &file)
{
    std::string tmp;
    auto it = file.begin();

    this->parseInstruct(*it);
    it++;
    for (; it != file.end(); it++)
    {
        std::stringstream ss(*it);
        std::string key;
        std::string valueOne;
        std::string valueTwo;
        getline(ss, key, ' ');
        getline(ss, tmp, '(');
        getline(ss, valueOne, ',');
        getline(ss, tmp, ' ');
        getline(ss, valueTwo, ')');
        std::pair<std::string, std::string> pr(valueOne, valueTwo);
        _route.insert(std::pair<std::string, std::pair<std::string, std::string>>(key, pr));
    }
}

void Network::resolve()
{
    auto it = _route.find(_start);
    while (1)
    {
        for (auto itI = _instruct.begin(); itI != _instruct.end(); itI++)
        {
            if (it->first == _end)
                return;
            _nbRoute++;
            if (*itI == 'L')
                it = _route.find(it->second.first);
            else
                it = _route.find(it->second.second);
        }
    }
}

int Network::getResult() const
{
    return _nbRoute;
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
    Network network;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        tmp += line + '\n';
    network.parse(split(tmp, '\n'));
    file.close();
    network.resolve();
    std::cout << "Answer : " << network.getResult() << std::endl;
    return 0;
}
