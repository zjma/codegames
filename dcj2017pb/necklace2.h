// Sample input 2, in CPP.

#include <cassert>

long long GetNecklaceLength() {
  return 3LL;
}

long long GetMessageLength() {
  return 3LL;
}

int GetNecklaceElement(long long index) {
  switch ((int)index) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    default: assert(0);
  }
}

int GetMessageElement(long long index) {
  switch ((int)index) {
    case 0: return 0;
    case 1: return 3;
    case 2: return 2;
    default: assert(0);
  }
}
