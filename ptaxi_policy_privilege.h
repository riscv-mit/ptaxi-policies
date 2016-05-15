#ifndef _PTAXI_POLICY_PRIVILEGE_H
#define _PTAXI_POLICY_PRIVILEGE_H

void ptaxi_policy_privilege_enforce(uint8_t tagbit) {
  ptaxi_base_policy_create_settag(tagbit);
  ptaxi_base_policy_create_gettag(tagbit);
  ptaxi_base_policy_create_cleartag(tagbit);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_STORE64);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_LOAD64);
  ptaxi_base_policy_propatgate_by_type(tagbit, PTAXI_INSN_TYPE_COPY);
}

void ptaxi_policy_privilege_protect_data(uint8_t tagbit, uint8_t allow_read) {

}

void ptaxi_policy_privilege_enter(uint8_t tagbit) {

}

void ptaxi_policy_privilege_leave(uint8_t tagbit) {

}
#endif
