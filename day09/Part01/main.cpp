#include <iostream>
#include <fstream>
#include <vector>

class Mirage
{
private:
    std::vector<std::vector<long>> _point;
    std::vector<long> _result;

public:
    Mirage();
    ~Mirage();

    void parse(const std::vector<std::string> &file);
    long resolveLine(const std::vector<long> &line);
    void resolve();
    long long int getResult() const;
};

Mirage::Mirage() {}

Mirage::~Mirage() {}

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

void Mirage::parse(const std::vector<std::string> &file)
{
    for (auto it = file.begin(); it != file.end(); it++)
    {
        std::vector<std::string> vec = split(*it, ' ');
        std::vector<long> vecNumber;
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++)
            vecNumber.push_back(atoi((*it2).c_str()));
        _point.push_back(vecNumber);
    }
}

bool equalAllEqual(const std::vector<long> &number)
{
    for (size_t i = 1; i < number.size(); i++)
    {
        if (number[i - 1] != number[i])
            return false;
    }
    return true;
}

long Mirage::resolveLine(const std::vector<long> &line)
{
    long tmp = 0;
    std::vector<long> newOne;
    if (equalAllEqual(line))
        return tmp;
    for (size_t i = 1; i < line.size(); i++)
        newOne.push_back(line[i] - line[i - 1]);
    tmp += this->resolveLine(newOne);
    return tmp + newOne[newOne.size() - 1];
}

void Mirage::resolve()
{
    long tmp = 0;
    for (auto it = _point.begin(); it != _point.end(); it++)
    {
        tmp = (*it)[(*it).size() - 1];
        tmp += this->resolveLine(*it);
        _result.push_back(tmp);
    }
}

long long int Mirage::getResult() const
{
    long long int tmp = 0;

    for (size_t i = 0; i < _result.size(); i++)
        tmp += _result[i];
    return tmp;
}

int main(int argc, char **argv)
{
    std::string line;
    std::string tmp;
    std::ifstream file;
    Mirage mirage;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        tmp += line + '\n';
    mirage.parse(split(tmp, '\n'));
    file.close();
    mirage.resolve();
    std::cout << "Answer : " << mirage.getResult() << std::endl;
    return 0;
}
