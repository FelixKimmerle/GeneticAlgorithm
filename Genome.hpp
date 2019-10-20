#pragma once
#include <vector>
#include <ostream>

typedef int32_t unit;

class Genome
{
private:
    std::vector<unit> m_vData;
    float RandomFloat();
    float m_fFitness;

public:
    Genome(unsigned int p_uiLength);
    Genome(const std::vector<unit> &p_vData);
    ~Genome();
    void MutateBit(float p_fProbability);
    void MutateByte(float p_fProbability);
    unsigned int size() const;
    float GetWeight(unsigned int p_uiIndex) const;
    friend std::ostream &operator<<(std::ostream &stream, const Genome &p_Genome);
    static Genome CrossoverRandomBit(const Genome &p_Genome1, const Genome &p_Genome2);
    static Genome CrossoverRandomByte(const Genome &p_Genome1, const Genome &p_Genome2);
    float GetFitness();
    void SetFitness(float p_fValue);
    bool operator<(const Genome &p_Other) const;
};
