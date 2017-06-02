// Sample input 1, in CPP.

#include <cassert>

long long GetNumSegments() {
  return 5LL;
}

long long GetSafeDistance() {
  return 10LL;
}

long long GetPosition(long long airplane, long long i) {
  if (airplane == 0 && i == 0) return 10485770LL;
  if (airplane == 0 && i == 1) return 10LL;
  if (airplane == 0 && i == 2) return 10485770LL;
  if (airplane == 0 && i == 3) return 1048586LL;
  if (airplane == 0 && i == 4) return 0LL;
  if (airplane == 0 && i == 5) return 10485770LL;
  if (airplane == 1 && i == 0) return 10485770LL;
  if (airplane == 1 && i == 1) return 10485760LL;
  if (airplane == 1 && i == 2) return 10LL;
  if (airplane == 1 && i == 3) return 10485771LL;
  if (airplane == 1 && i == 4) return 10485761LL;
  if (airplane == 1 && i == 5) return 0LL;
  assert(0);
}

long long GetTime(long long airplane, long long i) {
  if (airplane == 0 && i == 0) return 1LL;
  if (airplane == 0 && i == 1) return 1LL;
  if (airplane == 0 && i == 2) return 1LL;
  if (airplane == 0 && i == 3) return 1LL;
  if (airplane == 0 && i == 4) return 1LL;
  if (airplane == 1 && i == 0) return 1LL;
  if (airplane == 1 && i == 1) return 1LL;
  if (airplane == 1 && i == 2) return 1LL;
  if (airplane == 1 && i == 3) return 1LL;
  if (airplane == 1 && i == 4) return 1LL;
  assert(0);
}
