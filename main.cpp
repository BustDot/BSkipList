#include "SkipList.h"

int main() {
    BSkipList::SkipList<int, int> skipList(4, 0.25);
    skipList.insert(3, 3);
    skipList.insert(6, 6);
    skipList.insert(7, 7);
    skipList.insert(9, 9);
    skipList.insert(12, 12);
    skipList.insert(19, 19);
    skipList.insert(17, 17);
    skipList.insert(26, 26);
    skipList.insert(21, 21);
    skipList.insert(25, 25);
    skipList.print();
    skipList.remove(17);
    skipList.remove(19);
    skipList.remove(21);
    skipList.print();
    return 0;
}
