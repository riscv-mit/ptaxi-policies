#include <stdio.h>
#include "ptaxi.h"

uint64_t *gsecretnumberptr = NULL;

int i;

int g(int x) {
  return x * 2 + 9;
}

int f() {
  ptaxi_tag_command(123);
  uint64_t secretnumber = 0xDEADBEEF;
  gsecretnumberptr = &secretnumber;
  int i, s = 0;
  for (i = 0; i < 20; i++) {
    s += g(i) + secretnumber;
  }
  ptaxi_tag_command(456);
  return s;
}

int main(int argc, char** argv) {
  if (!(argc > 1)) {
    ptaxi_policy_gc();
    ptaxi_enforce_policy();
  } else {
    printf("Should show deadbeef\n");
  }
  ptaxi_tag_command(7);
  f();
  ptaxi_tag_command(8);
  printf("Secret = %x at %p\n", *gsecretnumberptr, (void *) gsecretnumberptr);

  return 0;
}
