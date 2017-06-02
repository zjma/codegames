// Sample input 2, in CPP.

#include <cassert>

long long GetNumSegments() {
  return 4LL;
}

long long GetSafeDistance() {
  return 5LL;
}

long long GetPosition(long long airplane, long long i) {
  if (airplane == 0 && i == 0) return 0LL;
  if (airplane == 0 && i == 1) return 1048581LL;
  if (airplane == 0 && i == 2) return 1048582LL;
  if (airplane == 0 && i == 3) return 2097158LL;
  if (airplane == 0 && i == 4) return 6291465LL;
  if (airplane == 1 && i == 0) return 0LL;
  if (airplane == 1 && i == 1) return 3145728LL;
  if (airplane == 1 && i == 2) return 6291459LL;
  if (airplane == 1 && i == 3) return 1048579LL;
  if (airplane == 1 && i == 4) return 6291464LL;
  assert(0);
}

long long GetTime(long long airplane, long long i) {
  if (airplane == 0 && i == 0) return 8LL;
  if (airplane == 0 && i == 1) return 1LL;
  if (airplane == 0 && i == 2) return 1LL;
  if (airplane == 0 && i == 3) return 2LL;
  if (airplane == 1 && i == 0) return 7LL;
  if (airplane == 1 && i == 1) return 3LL;
  if (airplane == 1 && i == 2) return 1LL;
  if (airplane == 1 && i == 3) return 1LL;
  assert(0);
}
