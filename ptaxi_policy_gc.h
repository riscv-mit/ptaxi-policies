#ifndef _PTAXI_POLICY_GC_H
#define _PTAXI_POLICY_GC_H

#include <stdlib.h>

#include "ptaxi_common.h"
#include "ptaxi_user.h"

void ptaxi_policy_gc() {
  struct ptaxi_policy_t policy;
  memset(&policy, 0, sizeof(policy));
  policy.insn_type = PTAXI_INSN_TYPE_RETURN;
  policy.action = PTAXI_ACTION_GC;
  ptaxi_add_policy(policy);
}

#endif
