#include <iostream>
#include <fstream>
#include <vector>

class Puzzle
{
private:
    std::vector<std::vector<char>> _matrix;
    std::vector<int> _numbers;

public:
    Puzzle();
    ~Puzzle();

    void setMatrix(const std::string &line);
    void printMatrix() const;
    int pushNumber(int y, int x);
    void getSomeNumbersAdjacent(int y, int x);
    void setNumbers();
    size_t getSomeNumbers();
};

Puzzle::Puzzle() {}

Puzzle::~Puzzle() {}

void Puzzle::setMatrix(const std::string &line)
{
    std::vector<char> lineChar;
    std::string::const_iterator it = line.begin();

    for (; it != line.end(); it++)
    {
        if (!std::isdigit(*it) && *it != '.')
            lineChar.push_back('#');
        else
            lineChar.push_back(*it);
    }
    _matrix.push_back(lineChar);
}

void Puzzle::printMatrix() const
{
    for (auto it = _matrix.begin(); it != _matrix.end(); it++)
    {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
            std::cout << "[" << *it2 << "]";
        std::cout << std::endl;
    }
}

int Puzzle::pushNumber(int y, int x)
{
    int xTmp = x;
    int numbers = 0;

    while (xTmp >= 0 && std::isdigit(_matrix[y][xTmp]))
        xTmp--;
    xTmp++;
    while (xTmp < _matrix[y].size() && std::isdigit(_matrix[y][xTmp]))
    {
        numbers *= 10;
        numbers += _matrix[y][xTmp] - '0';
        xTmp++;
    }
    _numbers.push_back(numbers);
    if (xTmp >= x)
        return (xTmp - x);
    return 0;
}

void Puzzle::getSomeNumbersAdjacent(int y, int x)
{
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (i < 0 || i >= _matrix.size() || j < 0 || j >= _matrix[i].size())
                continue;
            if (std::isdigit(_matrix[i][j]))
                j += this->pushNumber(i, j);
        }
    }
}

void Puzzle::setNumbers()
{
    for (int y = 0; y < _matrix.size(); y++)
    {
        for (int x = 0; x < _matrix[y].size(); x++)
        {
            if (_matrix[y][x] == '#')
                this->getSomeNumbersAdjacent(y, x);
        }
    }
}

size_t Puzzle::getSomeNumbers()
{
    size_t result = 0;
    std::vector<int>::const_iterator it = _numbers.begin();

    for (; it != _numbers.end(); it++)
        result += *it;
    return result;
}

int main(int argc, char **argv)
{
    size_t value = 0;
    std::string line;
    std::ifstream file;
    Puzzle puzzle;

    if (argc != 2)
        return 1;
    file.open(argv[1]);
    while (getline(file, line))
        puzzle.setMatrix(line);
    file.close();
    puzzle.printMatrix();
    puzzle.setNumbers();
    value = puzzle.getSomeNumbers();
    std::cout << "Answer : " << value << std::endl;
    return 0;
}
