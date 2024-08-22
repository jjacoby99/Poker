#include <vector>
#include <iostream>
#include <algorithm>
#include <random>


int main()
{
    std::vector<int> ordered = {1, 2, 3, 4, 5};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ordered.begin(),ordered.end(),g);

    for(int i = 0; i < ordered.size(); i++)
    {
        std::cout << ordered[i] << " ";
    }

    return 0;
}