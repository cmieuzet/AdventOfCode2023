#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

struct Ranges
{
    size_t dest;
    size_t src;
    size_t range;
};

class Garden
{
private:
    size_t _result = SIZE_MAX;
    size_t _seed;
    std::vector<size_t> _seeds;
    std::map<std::string, std::vector<Ranges>> _data;

    void setSeeds(const std::vector<std::string> &seeds);
    Ranges setRangesStruct(const std::vector<std::string>::iterator &it);

public:
    Garden();
    ~Garden();

    void parseData(std::vector<std::vector<std::string>> &data);
    void processCalcul(size_t seed, std::vector<Ranges> ranges);
    void calculSeeds();
    size_t getSmallestResultSeed();
};

Garden::Garden() {}

Garden::~Garden() {}

void Garden::setSeeds(const std::vector<std::string> &seeds)
{
    auto it = seeds.begin() + 1;

    for (; it != seeds.end(); it++)
    {
        size_t tmp = strtoull((*it).c_str(), NULL, 10);
        _seeds.push_back(tmp);
    }
}

Ranges Garden::setRangesStruct(const std::vector<std::string>::iterator &it)
{
    Ranges range;

    range.dest = strtoull((*it).c_str(), NULL, 10);
    range.src = strtoull((*(it + 1)).c_str(), NULL, 10);
    range.range = strtoull((*(it + 2)).c_str(), NULL, 10);
    return range;
}

void Garden::parseData(std::vector<std::vector<std::string>> &data)
{
    std::vector<Ranges> ranges;
    std::string name;
    auto it = data.begin();

    this->setSeeds(*it);
    it++;
    for (; it != data.end(); it++)
    {
        auto it2 = it->begin();
        name = *it2;
        it2 += 2;
        for (; it2 != it->end();)
        {
            ranges.push_back(setRangesStruct(it2));
            it2 += 3;
        }
        _data.insert(std::pair<std::string, std::vector<Ranges>>(name, ranges));
        ranges.clear();
        name.clear();
    }
}

void Garden::processCalcul(size_t seed, std::vector<Ranges> ranges)
{
    _seed = seed;

    for (int i = 0; i < ranges.size(); i++)
    {
        if ((_seed >= ranges[i].src) && (_seed < (ranges[i].src + ranges[i].range)))
        {
            _seed += ranges[i].dest - ranges[i].src;
            break;
        }
    }
}

void Garden::calculSeeds()
{
    static const std::vector<std::string> nameOfMap = {"seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location"};
    std::map<std::string, std::vector<Ranges>>::iterator itD;

    std::vector<std::vector<Ranges>> rtmp;
    for (int i = 0; i < nameOfMap.size(); i++)
    {
        rtmp.push_back((_data.find(nameOfMap[i]))->second);
    }

    for (auto it = _seeds.begin(); it < _seeds.end() - 1; it += 2)
    {
        auto itEnd = it + 1;
        size_t seedIncr = *it;
        std::cout << "Range : " << seedIncr << " | " << *itEnd << std::endl;
        for (; seedIncr < *itEnd + *it; seedIncr++)
        {
            _seed = seedIncr;
            for (int i = 0; i < rtmp.size(); i++)
            {
                this->processCalcul(_seed, rtmp[i]);
            }
            if (_seed < _result)
                _result = _seed;
        }
    }
}

size_t Garden::getSmallestResultSeed()
{
    return _result;
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
    std::vector<std::string> vec;
    std::vector<std::vector<std::string>> data;
    Garden garden;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
    {
        if (line.empty())
            tmp += '\n';
        else
            tmp += line + " ";
    }
    vec = split(tmp, '\n');
    for (auto it = vec.begin(); it != vec.end(); it++)
        data.push_back(split(*it, ' '));
    vec.clear();
    garden.parseData(data);
    data.clear();
    file.close();
    garden.calculSeeds();
    std::cout << "Answer : " << garden.getSmallestResultSeed() << std::endl;
    return 0;
}
