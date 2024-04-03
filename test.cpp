#include <cassert>
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
  skipList.Print();
  assert(skipList.size() == 10);
  int value;
  assert(skipList.find(19, value));
  assert(value == 19);

  skipList.remove(17);
  skipList.remove(19);
  skipList.remove(21);
  skipList.Print();
  assert(skipList.size() == 7);
  assert(!skipList.find(17, value));
  assert(!skipList.find(19, value));
  assert(!skipList.find(21, value));
  return 0;
}
