#include <iostream>
#include "Genome.hpp"

int main()
{
    srand(time(0));
    Genome gen(4);
    Genome gen2(4);
    std::cout << gen << std::endl;
    std::cout << gen2 << std::endl;
    std::cout << Genome::CrossoverRandomBit(gen, gen2) << std::endl;

    return 0;
}