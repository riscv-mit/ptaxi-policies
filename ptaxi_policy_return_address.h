#ifndef _PTAXI_POLICY_RETURN_ADDRESS_H
#define _PTAXI_POLICY_RETURN_ADDRESS_H

#include <stdlib.h>

#include "ptaxi_common.h"
#include "ptaxi_user.h"
#include "ptaxi_base_policy.h"

void ptaxi_policy_return_address(uint8_t tagbit) {
  struct ptaxi_policy_t default_policy, policy;
  memset(&default_policy, 0, sizeof(default_policy));
  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_JAL;
  policy.tag_out_tomodify = tagbit;
  policy.tag_out_set = tagbit;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_RETURN;
  policy.tag_arg1_mask = tagbit;
  policy.tag_arg1_match = 0;
  policy.action |= PTAXI_ACTION_BLOCK;
  policy.ignore_count = 4;
  ptaxi_add_policy(policy);

  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_STORE64, 1, 0);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_LOAD64, 1, 0);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_COPY, 1, 0);
  ptaxi_base_policy_clear_by_type(tagbit, PTAXI_INSN_TYPE_STORE);
  ptaxi_base_policy_clear_by_type(tagbit, PTAXI_INSN_TYPE_LOAD);
  ptaxi_base_policy_clear_by_type(tagbit, PTAXI_INSN_TYPE_OP);
  ptaxi_base_policy_clear_by_type(tagbit, PTAXI_INSN_TYPE_OPIMM);
}

#endif
