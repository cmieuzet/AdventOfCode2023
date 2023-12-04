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
    int getNbMatchCardFound();
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

int Card::getNbMatchCardFound()
{
    int match = 0;
    std::vector<int>::iterator it = _myNumbers.begin();

    for (; it != _myNumbers.end(); it++)
    {
        if ((std::find(_winningNumbers.begin(), _winningNumbers.end(), *it)) != _winningNumbers.end())
            match++;
    }
    return match;
}

int getNbCardsWonPerLine(const std::string &line)
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
    return (Card.getNbMatchCardFound());
}

void setNbCardsWon(std::vector<std::pair<int, int>> &cardsGame)
{
    std::vector<std::pair<int, int>>::iterator it = cardsGame.begin();
    int t = 0;
    std::vector<std::pair<int, int>>::iterator itTmp = cardsGame.begin();
    for (; it != cardsGame.end(); it++)
    {
        itTmp = it;
        itTmp++;
        int i = 0;
        while (itTmp != cardsGame.end() && i < it->second)
        {
            itTmp->first += it->first;
            itTmp++;
            i++;
        }
    }
}

size_t getNbCardsWon(const std::vector<std::pair<int, int>> &cardsGame)
{
    size_t cards = 0;
    std::vector<std::pair<int, int>>::const_iterator it = cardsGame.begin();

    for (; it != cardsGame.end(); it++)
        cards += it->first;
    return cards;
}

int main(int argc, char **argv)
{
    std::string line;
    std::ifstream file;
    size_t value = 0;
    std::vector<std::pair<int, int>> cardsGame;

    if (argc != 2)
        return 1;
    file.open(argv[1]);

    while (getline(file, line))
        cardsGame.push_back(std::pair<int, int>(1, getNbCardsWonPerLine(line)));
    setNbCardsWon(cardsGame);
    value = getNbCardsWon(cardsGame);
    file.close();
    std::cout << "Answer : " << value << std::endl;
    return 0;
}
