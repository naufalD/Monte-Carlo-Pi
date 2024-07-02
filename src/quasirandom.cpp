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
