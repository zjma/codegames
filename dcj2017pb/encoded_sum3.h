// Sample input 3, in CPP.

#include <cassert>

long long GetLength() {
  return 10LL;
}

char GetScrollOne(long long i) {
  switch ((int)i) {
    case 0: return 'A';
    case 1: return 'C';
    case 2: return 'E';
    case 3: return 'G';
    case 4: return 'I';
    case 5: return 'A';
    case 6: return 'C';
    case 7: return 'E';
    case 8: return 'I';
    case 9: return 'G';
    default: assert(0);
  }
}

char GetScrollTwo(long long i) {
  switch ((int)i) {
    case 0: return 'B';
    case 1: return 'D';
    case 2: return 'F';
    case 3: return 'H';
    case 4: return 'J';
    case 5: return 'B';
    case 6: return 'D';
    case 7: return 'H';
    case 8: return 'F';
    case 9: return 'J';
    default: assert(0);
  }
}
