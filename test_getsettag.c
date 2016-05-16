#include <stdio.h>
#include <unistd.h>

#include "ptaxi.h"

#define TAGBIT 1

void __attribute__ ((constructor)) ptaxi_app_policy() {
  ptaxi_policy_privilege_init(TAGBIT);
  ptaxi_enforce_policy();
}

int main(int argc, char** argv) {
  uint64_t a = 5;
  printf("A is at %p\n", &a);
  printf ("A = %lu, TAG(A) = %d (should be 0)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 1);
  printf ("A = %lu, TAG(A) = %d (should be 1)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 1);
  printf ("A = %lu, TAG(A) = %d (should be 1)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 0);
  printf ("A = %lu, TAG(A) = %d (should be 0)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  return 0;
}
