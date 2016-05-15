#ifndef _PTAXI_BASE_POLICY_H
#define _PTAXI_BASE_POLICY_H

#define PTAXI_TAGCMD_PREFIX_GETTAG   100
#define PTAXI_TAGCMD_PREFIX_SETTAG   110
#define PTAXI_TAGCMD_PREFIX_CLEARTAG 120
#define PTAXI_TAGCMD_PREFIX_ENTER    130
#define PTAXI_TAGCMD_PREFIX_LEAVE    140

uint8_t log2bit(uint8_t tagbit) {
  uint8_t out = 0;
  while(tagbit != 0) {
    out++;
    tagbit = (tagbit >> 1);
  }
  return out;
}
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

void ptaxi_base_policy_create_settag(uint8_t tagbit) {
  struct ptaxi_policy_t policy;
  memset(&policy, 0, sizeof(policy));
  policy.tag_out_tomodify = tagbit;
  policy.insn_type = PTAXI_INSN_TYPE_TAGCMD;
  policy.rs1val_mask = 0b11111111;
  policy.rs1val_match = PTAXI_TAGCMD_PREFIX_SETTAG + log2bit(tagbit);
  policy.tag_out_set = tagbit;
  ptaxi_add_policy(policy);
}

void ptaxi_base_policy_create_cleartag(uint8_t tagbit) {
  struct ptaxi_policy_t policy;
  memset(&policy, 0, sizeof(policy));
  policy.tag_out_tomodify = tagbit;
  policy.insn_type = PTAXI_INSN_TYPE_TAGCMD;
  policy.rs1val_mask = 0b11111111;
  policy.rs1val_match = PTAXI_TAGCMD_PREFIX_CLEARTAG + log2bit(tagbit);
  policy.tag_out_set = 0;
  ptaxi_add_policy(policy);
}

void ptaxi_base_policy_create_gettag(uint8_t tagbit) {
  struct ptaxi_policy_t policy;
  memset(&policy, 0, sizeof(policy));
  policy.tag_out_tomodify = tagbit;
  policy.insn_type = PTAXI_INSN_TYPE_TAGCMD;
  policy.rs1val_mask = 0b11111111;
  policy.rs1val_match = PTAXI_TAGCMD_PREFIX_GETTAG + log2bit(tagbit);
  policy.tag_out_set = 0;
  policy.action = PTAXI_ACTION_GETTAG;
  ptaxi_add_policy(policy);
}

uint8_t ptaxi_base_policy_gettag(uint8_t tagbit, void *addr) {
  uint8_t out;
  uint8_t cmd = PTAXI_TAGCMD_PREFIX_GETTAG + log2bit(tagbit);
  uint64_t in = *((uint64_t *) addr);
  __asm__ volatile ("tagcmd %0,%1,%2" : "=r"(out) :"r"(cmd), "r"(in));
  return out;
}

// tagval is a boolean. True = set/False = clear
void ptaxi_base_policy_settag(uint8_t tagbit, void *addr, uint8_t tagval) {
  uint8_t cmd;
  if (tagval > 0) {
    cmd = PTAXI_TAGCMD_PREFIX_SETTAG + log2bit(tagbit);
  } else {
    cmd = PTAXI_TAGCMD_PREFIX_CLEARTAG + log2bit(tagbit);
  }
  uint64_t *raddr = (uint64_t *) addr;
  uint64_t in = *raddr;
  uint64_t out = 0;
  __asm__ volatile ("tagcmd %0,%1,%2" : "=r"(out) :"r"(cmd), "r"(in));
  *raddr = out;
}

void ptaxi_base_policy_settag_multi(uint8_t tagbit, void *addr, size_t size, uint8_t tagval) {
  size_t block = size/4;
  uint64_t* pos = (uint64_t *) addr;
  size_t i;
  for (i = 0; i < block; i++) {
    ptaxi_base_policy_settag(tagbit, addr, tagval);
    pos++;
  }
}
#endif
