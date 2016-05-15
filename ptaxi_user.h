#ifndef _PTAXI_USER_H
#define _PTAXI_USER_H

#include <stdint.h>
#include <string.h>

#include "ptaxi_common.h"

// Use macro so that we don't have to set previous return pointers.
void ptaxi_tag_command(code) {
  __asm__("tagcmd zero,zero,%0" ::"r"(code));

}

void ptaxi_enforce_policy() {
  ptaxi_tag_command(0);
}

void ptaxi_add_raw_policy(uint64_t a, uint64_t b, uint64_t c) {
	__asm__ volatile ("tagpolicy %2,%0,%1" ::"r"(a), "r"(b), "r"(c));
}

void ptaxi_add_policy(struct ptaxi_policy_t policy) {
	union ptaxi_policy_serialized ps;
	ps.policy = policy;
	ptaxi_add_raw_policy(ps.regs.a, ps.regs.b, ps.regs.c);
}

#endif
