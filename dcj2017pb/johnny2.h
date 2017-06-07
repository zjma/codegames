// Sample input 2, in CPP.

#include <cassert>

long long NumberOfCards() {
  return 3LL;
}

bool IsBetter(long long i, long long j) {
  if (i == 0 && j == 0) return false;
  if (i == 0 && j == 1) return false;
  if (i == 0 && j == 2) return true;
  if (i == 1 && j == 0) return true;
  if (i == 1 && j == 1) return false;
  if (i == 1 && j == 2) return false;
  if (i == 2 && j == 0) return false;
  if (i == 2 && j == 1) return true;
  if (i == 2 && j == 2) return false;
  assert(0);
}
