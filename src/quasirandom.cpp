#include "include/quasirandom.h"

#include <cmath>
#include <vector>

double haltonQuasi(int index, int base){
    double result {0};
    double temp {1};
    int indextemp {index};

    while (indextemp>0){
        temp = temp/static_cast<double>(base);
        result = result + temp *(indextemp%base);
        indextemp = indextemp/base;
    }
    return result;
}

sobolDimension::sobolDimension(int degree,unsigned int coeff,  unsigned int initial[18], bool firstDim){
    m_degree = degree;
    m_coeff = coeff;
    m_firstDim = firstDim;
    m_currentIndex = 0;
    m_currentPoint = 0;

    for (int i {0}; i<degree; ++i){
        m_initial[i] = initial[i];
    }
}

unsigned int sobolDimension::m_directionNumber(int CIndex){
    if (m_firstDim){
        return 1<<(32-CIndex);
    }
    if (CIndex<m_degree){
        return m_initial[CIndex];
    }
    else{
        unsigned int mNext {1};
        unsigned int mTemp {1};
        std::vector<unsigned int> mVals(m_degree, 0);

        for (int i{0}; i<m_degree; ++i) mVals[m_degree-1-i] = m_initial[i];

        for (int i {m_degree}; i<=CIndex;++i){
            mNext = mVals[m_degree-1];
            for (int j {1}; j<=m_degree; ++j){
                if (j==m_degree) mTemp = pow(2, j) * mVals[j-1];
                else mTemp = pow(2, j) * ((m_coeff >> (m_degree-1-j)) & 1) * mVals[j-1];
                mNext^=mTemp;
            }
            for (int k {m_degree-1}; k>0; --k) mVals[k] = mVals[k-1];

            mVals[0] = mNext;
        }
        return mNext<<(32-CIndex);
    }
}

unsigned int sobolDimension::m_getCIndex(int index){
    if (index == 0)
        return 1;
    int n = ~index;
    return log2(n&-n)+1;;
}

double sobolDimension::getPoint(){
    if (m_currentIndex==0){
        return 0;
    }
    return (double) m_currentPoint/pow(2, 32);
}

void sobolDimension::nextPoint(){
    ++m_currentIndex;
    m_currentPoint = m_currentPoint ^ m_directionNumber(m_getCIndex(m_currentIndex));
}


// sobolQuasi::sobolQuasi(int dimensions, std::string directory){

// }
