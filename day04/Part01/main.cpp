#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Card
{
private:
    std::vector<int> _winningNumbers;
    std::vector<int> _myNumbers;

public:
    Card();
    ~Card();

    void setWinningNumbersLine(std::string &card);
    void setMyNumbersLine(std::string &card);
    int getPointsCard();
};

Card::Card() {}

Card::~Card() {}

void Card::setWinningNumbersLine(std::string &card)
{
    std::string number;
    std::stringstream ss(card);

    while (std::getline(ss, number, ' '))
    {
        remove(number.begin(), number.end(), ' ');
        if (number.size())
            _winningNumbers.push_back(atoi(number.c_str()));
    }
}

void Card::setMyNumbersLine(std::string &card)
{
    std::string number;
    std::stringstream ss(card);

    while (std::getline(ss, number, ' '))
    {
        remove(number.begin(), number.end(), ' ');
        if (number.size())
            _myNumbers.push_back(atoi(number.c_str()));
    }
}

int Card::getPointsCard()
{
    int points = 0;
    std::vector<int>::iterator it = _myNumbers.begin();

    for (; it != _myNumbers.end(); it++)
    {
        if ((std::find(_winningNumbers.begin(), _winningNumbers.end(), *it)) != _winningNumbers.end())
        {
            if (points == 0)
                points++;
            else
                points *= 2;
        }
    }
    return points;
}

size_t getPointsPerLine(const std::string &line)
{
    std::string indexGame;
    std::string tmp;
    std::stringstream cards(line);
    Card Card;

    std::getline(cards, indexGame, ':');
    std::getline(cards, tmp, '|');
    Card.setWinningNumbersLine(tmp);
    std::getline(cards, tmp);
    Card.setMyNumbersLine(tmp);
    return (Card.getPointsCard());
}

int main(int argc, char **argv)
{
    std::string line;
    std::ifstream file;
    size_t value = 0;

    if (argc != 2)
        return 1;
    file.open(argv[1]);

    while (getline(file, line))
        value += getPointsPerLine(line);
    file.close();
    std::cout << "Answer : " << value << std::endl;
    return 0;
}
