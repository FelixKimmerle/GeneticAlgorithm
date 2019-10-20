#include "Genome.hpp"
#include <random>
#include <bitset>
#include <iostream>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

Genome::Genome(unsigned int p_uiLength) : m_fFitness(0.f)
{
    for (unsigned int i = 0; i < p_uiLength; i++)
    {
        m_vData.push_back(rand() % (1L << (sizeof(unit) * 8)));
    }
}

Genome::Genome(const std::vector<unit> &p_vData)
{
    m_vData = p_vData;
}

Genome::~Genome()
{
}

float Genome::RandomFloat()
{
    return rand() / (float)RAND_MAX;
}

void Genome::MutateBit(float p_fProbability)
{
    for (unsigned int i = 0; i < m_vData.size(); i++)
    {
        for (unsigned short b = 0; b < sizeof(unit) * 8; b++)
        {
            if (RandomFloat() < p_fProbability)
            {
                BIT_FLIP(m_vData[i], b);
            }
        }
    }
}
void Genome::MutateByte(float p_fProbability)
{
    for (unsigned int i = 0; i < m_vData.size(); i++)
    {
        if (RandomFloat() < p_fProbability)
        {
            m_vData[i] = rand() % (1L << (sizeof(unit) * 8));
        }
    }
}

unsigned int Genome::size() const
{
    return m_vData.size();
}

float Genome::GetWeight(unsigned int p_uiIndex) const
{
    return (m_vData[p_uiIndex] / ((1L << (sizeof(unit) * 8)) / 2.f) - 1.f);
}

std::ostream &operator<<(std::ostream &stream, const Genome &p_Genome)
{
    stream << "Fitness: " << p_Genome.m_fFitness << std::endl;
    for (auto genome = p_Genome.m_vData.begin(); genome != p_Genome.m_vData.end(); genome++)
    {
        std::bitset<sizeof(unit) * 8> bitset(*genome);
        stream << bitset;
    }
    stream << " ";
    for (auto genome = p_Genome.m_vData.begin(); genome != p_Genome.m_vData.end(); genome++)
    {
        stream << (int)*genome << ", ";
    }
    return stream;
}

Genome Genome::CrossoverRandomBit(const Genome &p_Genome1, const Genome &p_Genome2)
{
    std::vector<unit> vData;
    if (p_Genome1.m_vData.size() == p_Genome2.m_vData.size())
    {
        for (unsigned int i = 0; i < p_Genome1.m_vData.size(); i++)
        {
            unit cCurrent = 0;
            for (unsigned short b = 0; b < sizeof(unit) * 8; b++)
            {
                if (rand() % 2)
                {
                    //Use bit from p_Genome1
                    if (BIT_CHECK(p_Genome1.m_vData[i], b))
                    {
                        BIT_FLIP(cCurrent, b);
                    }
                }
                else
                {
                    //Use bit from p_Genome2
                    if (BIT_CHECK(p_Genome2.m_vData[i], b))
                    {
                        BIT_FLIP(cCurrent, b);
                    }
                }
            }
            vData.push_back(cCurrent);
        }
        return Genome(vData);
    }
    else
    {
        std::cerr << "Genomes dont match!" << std::endl;
    }
    return Genome(0);
}

Genome Genome::CrossoverRandomByte(const Genome &p_Genome1, const Genome &p_Genome2)
{
    std::vector<unit> vData;
    if (p_Genome1.m_vData.size() == p_Genome2.m_vData.size())
    {
        for (unsigned int i = 0; i < p_Genome1.m_vData.size(); i++)
        {
            if (rand() % 2)
            {
                //Use byte from p_Genome1
                vData.push_back(p_Genome1.m_vData[i]);
            }
            else
            {
                //Use byte from p_Genome2
                vData.push_back(p_Genome2.m_vData[i]);
            }
        }
        return Genome(vData);
    }
    else
    {
        std::cerr << "Genomes dont match!" << std::endl;
    }
    return Genome(0);
}

float Genome::GetFitness()
{
    return m_fFitness;
}
void Genome::SetFitness(float p_fValue)
{
    m_fFitness = p_fValue;
}

bool Genome::operator<(const Genome &p_Other) const
{
    return m_fFitness > p_Other.m_fFitness;
}