#ifndef CACHELIST_UTILS_H
#define CACHELIST_UTILS_H

#include <iostream>
#include <cstring>
#define ITERATORS_NUMBER 10

// returns number of Iterator from writing
int getIteratorNr(char* y) {
    if(strcmp( y, "BEG" ) == 0)
        return ITERATORS_NUMBER;
    else if(strcmp( y, "END" ) == 0)
        return ITERATORS_NUMBER+1;
    return atoi(y);
}

#endif //CACHELIST_UTILS_H
