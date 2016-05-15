#include <stdio.h>
#include <unistd.h>

#include "ptaxi.h"

#define TAGBIT 1

void __attribute__ ((constructor)) ptaxi_app_policy() {
  ptaxi_base_policy_create_settag(TAGBIT);
  ptaxi_base_policy_create_gettag(TAGBIT);
  ptaxi_base_policy_create_cleartag(TAGBIT);
  ptaxi_base_policy_propatgate_by_type(TAGBIT, PTAXI_INSN_TYPE_STORE64);
  ptaxi_base_policy_propatgate_by_type(TAGBIT, PTAXI_INSN_TYPE_LOAD64);
  ptaxi_base_policy_propatgate_by_type(TAGBIT, PTAXI_INSN_TYPE_COPY);
  ptaxi_enforce_policy();
}

int main(int argc, char** argv) {
  uint64_t a = 5;
  printf ("A = %lu, TAG(A) = %d (should be 0)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 1);
  printf ("A = %lu, TAG(A) = %d (should be 1)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 1);
  printf ("A = %lu, TAG(A) = %d (should be 1)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));
  ptaxi_base_policy_settag(TAGBIT, &a, 0);
  printf ("A = %lu, TAG(A) = %d (should be 0)\n", a, (int) ptaxi_base_policy_gettag(TAGBIT, &a));


  return 0;
}
