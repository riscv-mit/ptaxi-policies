#ifndef _PTAXI_BASE_POLICY_H
#define _PTAXI_BASE_POLICY_H

void ptaxi_base_policy_propatgate_by_type(uint8_t tagbit, enum ptaxi_insn_type_t insn_type) {
  struct ptaxi_policy_t default_policy, policy;
  memset(&default_policy, 0, sizeof(default_policy));
  default_policy.tag_out_tomodify = tagbit;

  policy = default_policy;
  policy.insn_type = insn_type;
  policy.tag_arg1_mask = tagbit;
  policy.tag_arg1_match = tagbit;
  policy.tag_out_set = tagbit;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = insn_type;
  policy.tag_arg1_mask = tagbit;
  policy.tag_arg1_match = 0;
  policy.tag_out_set = 0;
  ptaxi_add_policy(policy);
}

void ptaxi_base_policy_clear_by_type(uint8_t tagbit, enum ptaxi_insn_type_t insn_type) {
  struct ptaxi_policy_t policy;
  memset(&policy, 0, sizeof(policy));
  policy.tag_out_tomodify = tagbit;
  policy.insn_type = insn_type;
  policy.tag_out_set = 0;
  ptaxi_add_policy(policy);
}

#endif
