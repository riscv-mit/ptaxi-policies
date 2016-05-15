#ifndef _PTAXI_POLICY_DEBUG_CALL_H
#define _PTAXI_POLICY_DEBUG_CALL_H

#include <stdlib.h>

#include "ptaxi_common.h"
#include "ptaxi_user.h"

void ptaxi_policy_debug_call() {
  struct ptaxi_policy_t default_policy, policy;
  memset(&default_policy, 0, sizeof(default_policy));

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_JAL;
  policy.action = PTAXI_ACTION_DEBUG_LINE;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_JALR;
  policy.action = PTAXI_ACTION_DEBUG_LINE;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_RETURN;
  policy.action = PTAXI_ACTION_DEBUG_LINE;
  ptaxi_add_policy(policy);
}

#endif
