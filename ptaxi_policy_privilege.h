#ifndef _PTAXI_POLICY_PRIVILEGE_H
#define _PTAXI_POLICY_PRIVILEGE_H

void ptaxi_policy_privilege_init(uint8_t tagbit) {
  ptaxi_base_policy_create_settag(tagbit);
  ptaxi_base_policy_create_gettag(tagbit);
  ptaxi_base_policy_create_cleartag(tagbit);
  ptaxi_base_policy_create_setpriv(tagbit);
  ptaxi_base_policy_create_clearpriv(tagbit);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_STORE64, 1, 0);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_LOAD64, 1, 0);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_COPY, 1, 0);
}

void ptaxi_policy_privilege_protect_tag_from_nonprivilege(uint8_t tagbit) {

}

void ptaxi_policy_privilege_protect_data(uint8_t tagbit) {
  struct ptaxi_policy_t default_policy, policy;
  memset(&default_policy, 0, sizeof(default_policy));
  default_policy.priv_mask = tagbit;
  default_policy.priv_match = 0;
  default_policy.action = PTAXI_ACTION_BLOCK;

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_LOAD;
  policy.tag_arg1_mask = tagbit;
  policy.tag_arg1_match = tagbit;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_LOAD64;
  policy.tag_arg1_mask = tagbit;
  policy.tag_arg1_match = tagbit;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_STORE;
  policy.tag_out_mask = tagbit;
  policy.tag_out_match = tagbit;
  ptaxi_add_policy(policy);

  policy = default_policy;
  policy.insn_type = PTAXI_INSN_TYPE_STORE64;
  policy.tag_out_mask = tagbit;
  policy.tag_out_match = tagbit;
  ptaxi_add_policy(policy);
}

void ptaxi_policy_privilege_enter(uint8_t tagbit) {
  ptaxi_base_policy_setpriv(tagbit, 1);
}

void ptaxi_policy_privilege_leave(uint8_t tagbit) {
  ptaxi_base_policy_setpriv(tagbit, 0);

}
#endif
