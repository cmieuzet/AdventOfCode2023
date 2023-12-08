#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstring>

class Poker
{
private:
    std::vector<std::vector<std::pair<std::string, int>>> _card;

public:
    Poker();
    ~Poker();

    void parse(const std::vector<std::string> &file);
    void printDebug();
};

Poker::Poker()
{
    auto it = _card.begin();

    for (int i = 0; i < 8; i++)
    {
        std::vector<std::pair<std::string, int>> vec;
        _card.push_back(vec);
    }
}

Poker::~Poker() {}

int calculate(const std::map<char, int> &card)
{
    // static int i[] = {};

    return 1;
}

int handWeight(std::string hand)
{
    std::map<char, int> card;

    for (size_t i = 0; i < card.size(); i++)
    {
        auto it = card.find(hand[i]);
        if (it != card.end())
            (it->second += 1);
        else
            card.insert(std::pair<char, int>(hand[i], 1));
    }
    return calculate(card);

    // std::sort(hand.begin(), hand.end());

    // for (size_t i = hand.size() - 1; i > 0; i--)
    // {
    //     if (i > 2 && hand[0] == hand[i])
    //         return i + 1;
    //     else if (i > 1 && hand[0] == hand[i])
    //     {
    //         if (hand[i + 1] == hand[i + 2])
    //             return 4;
    //         return 3;
    //     }
    //     else if (i > 0 && hand[0] == hand[i])
    //     {
    //         if (hand[i + 1] == hand[i + 2] || hand[i + 2] == hand[i + 3])
    //             return 2;
    //         return 1;
    //     }
    // }
    // return 0;
}

void Poker::parse(const std::vector<std::string> &file)
{
    int i;
    std::string hand;
    std::string bid;

    for (auto it = file.begin(); it != file.end(); it++)
    {
        std::stringstream ss(*it);
        ss >> hand;
        ss >> bid;
        i = handWeight(hand);
        _card[i].push_back(std::pair<std::string, int>(hand, atoi(bid.c_str())));
    }
}

void Poker::printDebug()
{
    for (auto it = _card.begin(); it != _card.end(); it++)
    {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
        {
            std::cout << it2->first << std::endl;
        }
        std::cout << std::endl;
    }
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
    Poker poker;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        tmp += line + '\n';

    poker.parse(split(tmp, '\n'));
    file.close();
    poker.printDebug();
    // poker.sort();
    // poker.calcul();
    // std::cout << "Answer : " << poker.getResult() << std::endl;
    std::cout << "Answer : " << 1 << std::endl;
    return 0;
}
