#include <include/quasirandom.h>

#include <cmath>

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

int grayCode(int n){
    return n^(n/2);
}

sobolDimension::sobolDimension(int degree, unsigned int initial[18], bool firstDim){
    m_degree = degree;
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
        unsigned int mMinus1 {m_initial[m_degree-1]};
        unsigned int mMinus2 {1};
        unsigned int mMinus3 {1};

        if (m_degree>1){
            mMinus2 = m_initial[m_degree-2];
        }
        if (m_degree>2){
            mMinus3 = m_initial[m_degree-3];
        }

        unsigned int mNext {0};

        for (int i {m_degree}; i<=CIndex;++i){
            mNext = (4*mMinus2)^(8*mMinus3)^mMinus3;
            mMinus3 = mMinus2;
            mMinus2 = mMinus1;
            mMinus1 = mNext;
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
    return (double) m_currentPoint/pow(2,32);
}

void sobolDimension::nextPoint(){
    ++m_currentIndex;
    m_currentPoint = m_currentPoint ^ m_directionNumber(m_getCIndex(m_currentIndex));
}


// sobolQuasi::sobolQuasi(int dimensions, std::string directory){

// }
