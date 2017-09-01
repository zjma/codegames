// Sample input 1, in CPP.

#include <cassert>

long long GetNecklaceLength() {
  return 5LL;
}

long long GetMessageLength() {
  return 3LL;
}

int GetNecklaceElement(long long index) {
  switch ((int)index) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    default: assert(0);
  }
}

int GetMessageElement(long long index) {
  switch ((int)index) {
    case 0: return 0;
    case 1: return 2;
    case 2: return 4;
    default: assert(0);
  }
}
