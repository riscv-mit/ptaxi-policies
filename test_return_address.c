#include <stdio.h>
#include "ptaxi.h"

#define TAG_RETURNADDRESS 1

void __attribute__ ((constructor)) ptaxi_app_policy() {
  ptaxi_policy_return_address(TAG_RETURNADDRESS);
  ptaxi_enforce_policy();
}

int i;
int limit = 20;
int g(int x) {
  return x * 27 % 13; // To prevent compiler optimizations
}

int f() {
  uint64_t a[2];
  a[i] = 0xDEADBEEF;
  for (i = 1; i < limit; i++) {
    a[i] = a[i - 1] + g(i);
  }
  return 7;
}
int main(int argc, char** argv) {
  if (argc > 1) {
    printf("Should pass instead of fail.\n");
    limit = 2;
  }
  f();
  return 0;
}
