#include <iostream>
#include "list.h"

using namespace std;


int main() {
    List lista;
    char command [100];
    while(true)
    {
        scanf("%s", command);
        if(feof(stdin)!=0) break;
        if(strcmp(command, "I") == 0) {
            lista.init();
            int size;
            scanf("%d", &size);
        }
        else if(strcmp(command, "i") == 0) {
            int to;
            char from[3];
            scanf("%d %s", &to, from);
            lista.initOperator(to, getIteratorNr(from));
        }
        else if(command[0] == '+') {
            int number;
            scanf("%d", &number);
            lista.moveFurtherIterator(number);
        }
        else if(command[0] == '-') {
            int number;
            scanf("%d", &number);
            lista.moveBackwardIterator(number);
        }
        else if(command[0] == '.' && command[1] == 'A') {
            unsigned long long int value;
            char iterator[3];
            scanf("%s %llu", iterator, &value);
            lista.addBefore(getIteratorNr(iterator), value);
        }
        else if(command[0] == 'A' && command[1] == '.') {
            unsigned long long int value;
            char iterator[3];
            scanf("%s %llu", iterator, &value);
            lista.addAfter(getIteratorNr(iterator), value);
        }
        else if(command[0] == 'R') {
            char element[3];
            scanf("%s", element);
            lista.remove(getIteratorNr(element));
        }
        else if(command[0] == 'P') {
            char element[3];
            scanf("%s", element);
            lista.printElements(element);
        }
    }
    lista.deleteAll();
    return 0;
}