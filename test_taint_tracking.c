#include <stdio.h>
#include <unistd.h>

#include "ptaxi.h"

#define TAINT_TAGBIT 1

void __attribute__ ((constructor)) ptaxi_app_policy() {
  ptaxi_policy_privilege_init(TAINT_TAGBIT);
  ptaxi_base_policy_propatgate_by_type(TAINT_TAGBIT, PTAXI_INSN_TYPE_OP, 1, 1);
  ptaxi_base_policy_propatgate_by_type(TAINT_TAGBIT, PTAXI_INSN_TYPE_OPIMM, 1, 0);
  ptaxi_enforce_policy();
}

uint64_t get_unfiltered_input() {
  uint64_t input = 42;
  ptaxi_base_policy_settag(TAINT_TAGBIT, (void *) (&input), 1);
  printf("DEBUGE: %d\n", (int) ptaxi_base_policy_gettag(TAINT_TAGBIT, (void *) (&input)));
  return input;
}

int main(int argc, char** argv) {
  uint64_t a = get_unfiltered_input();
  uint64_t b = 4;
  uint64_t c = b * 20;
  uint64_t d = a + 5;

  int s1 = ptaxi_base_policy_gettag(TAINT_TAGBIT, (void *) (&c));
  int s2 = ptaxi_base_policy_gettag(TAINT_TAGBIT, (void *) (&d));
  printf("TAG(C) = %d (should be 0), TAG(D) = %d (should be 1)\n", s1, s2);

  return 0;
}
