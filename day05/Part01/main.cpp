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
    std::vector<size_t> _seeds;
    std::map<std::string, std::vector<Ranges>> _data;

    void setSeeds(const std::vector<std::string> &seeds);
    Ranges setRangesStruct(const std::vector<std::string>::iterator &it);

public:
    Garden();
    ~Garden();

    void parseData(std::vector<std::vector<std::string>> &data);
    void processCalcul(std::vector<size_t>::iterator seed, std::vector<Ranges> ranges);
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
    // std::cout << "Dest ->" << range.dest << "|"
    //           << "Src ->" << range.src << "|"
    //           << "Range ->" << range.range << "|" << std::endl;
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

void Garden::processCalcul(std::vector<size_t>::iterator seed, std::vector<Ranges> ranges)
{
    for (auto it = ranges.begin(); it != ranges.end(); it++)
    {
        if ((*seed >= it->src) && (*seed < (it->src + it->range)))
        {
            *seed += it->dest - it->src;
            break;
        }
    }
}

void Garden::calculSeeds()
{
    static const std::vector<std::string> nameOfMap = {"seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location"};
    std::map<std::string, std::vector<Ranges>>::iterator itD;

    for (auto it = _seeds.begin(); it != _seeds.end(); it++)
    {
        for (auto itNofm = nameOfMap.begin(); itNofm != nameOfMap.end(); itNofm++)
        {
            itD = _data.find(*itNofm);
            this->processCalcul(it, itD->second);
        }
    }
}

size_t Garden::getSmallestResultSeed()
{
    std::sort(_seeds.begin(), _seeds.end());
    return _seeds[0];
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
