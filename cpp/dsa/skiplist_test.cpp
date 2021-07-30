#include "skiplist.h"

/**
 * Main function:
 * Creates and inserts random 2^[number of levels]
 * elements into the skip lists and than displays it
 */
int main() {
    std::srand(std::time(nullptr));

    kid::SkipList sl;

    for (int j = 0; j < (1 << (kid::MAX_LEVEL + 1)); j++) {
        int k = (std::rand() % (1 << (kid::MAX_LEVEL + 2)) + 1);
        sl.insertElement(k, &j);
    }

    sl.displayList();

    return 0;
}