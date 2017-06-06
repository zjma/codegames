// Sample input 1, in CPP.

#include <cassert>

long long GetLength() {
  return 1LL;
}

char GetScrollOne(long long i) {
  switch ((int)i) {
    case 0: return 'B';
    default: assert(0);
  }
}

char GetScrollTwo(long long i) {
  switch ((int)i) {
    case 0: return 'A';
    default: assert(0);
  }
}
