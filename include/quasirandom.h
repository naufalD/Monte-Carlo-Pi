#ifndef QUASIRANDOM_H
#define QUASIRANDOM_H

double haltonQuasi(int index, int base);
int grayCode(int n);

class sobolDimension
{

public:
    sobolDimension(const int degree, unsigned int initial[18], bool firstDim);
    double getPoint();
    void nextPoint();
private:
    unsigned int m_initial[18];
    int m_degree;
    int m_currentIndex;
    unsigned int m_currentPoint;
    bool m_firstDim;

    unsigned int m_directionNumber(int CIndex);
    unsigned int m_getCIndex(int index);


};

// class sobolQuasi
// {

// public:
//     sobolQuasi(int dimensions, std::string directory);
// private:
//     std::vector<sobolDimension> sobolVector;
// };


#endif // QUASIRANDOM_H
