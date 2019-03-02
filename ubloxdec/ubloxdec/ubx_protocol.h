#ifndef _UBX_PROTOCOL_H_
#define _UBX_PROTOCOL_H_

#include "ubx_struct.h"

#define MAX_PROTOCOL_NAME 64

int is_ubx_ack_ack(struct ubx_header *header);

int is_ubx_ack_nak(struct ubx_header *header);

int is_ubx_aid_alm(struct ubx_header *header);

int is_ubx_aid_aop(struct ubx_header *header);

int is_ubx_aid_eph(struct ubx_header *header);

int is_ubx_aid_hui(struct ubx_header *header);

int is_ubx_aid_ini(struct ubx_header *header);

int is_ubx_cfg_ant(struct ubx_header *header);

int is_ubx_cfg_cfg(struct ubx_header *header);

int is_ubx_cfg_dat(struct ubx_header *header);

int is_ubx_cfg_dgnss(struct ubx_header *header);

int is_ubx_cfg_dosc(struct ubx_header *header);

int is_ubx_cfg_dynseed(struct ubx_header *header);

int is_ubx_cfg_esrc(struct ubx_header *header);

int is_ubx_cfg_fixseed(struct ubx_header *header);

int is_ubx_cfg_geofence(struct ubx_header *header);

int is_ubx_esf_ins(struct ubx_header *header);

int is_ubx_esf_meas(struct ubx_header *header);

int is_ubx_esf_raw(struct ubx_header *header);

int is_ubx_esf_status(struct ubx_header *header);

int is_ubx_hnr_pvt(struct ubx_header *header);

int is_ubx_inf_debug(struct ubx_header *header);

int is_ubx_inf_error(struct ubx_header *header);

int is_ubx_inf_notice(struct ubx_header *header);

int is_ubx_inf_test(struct ubx_header *header);

int is_ubx_inf_warning(struct ubx_header *header);

int is_ubx_log_create(struct ubx_header *header);

int is_ubx_log_erase(struct ubx_header *header);

int is_ubx_log_findtime(struct ubx_header *header);

int is_ubx_log_info(struct ubx_header *header);

int is_ubx_log_retrieve(struct ubx_header *header);

int is_ubx_log_string(struct ubx_header *header);

int is_ubx_mga_ack(struct ubx_header *header);

int is_ubx_mga_ano(struct ubx_header *header);

int is_ubx_mga_bds(struct ubx_header *header);

int is_ubx_mga_dbd(struct ubx_header *header);

int is_ubx_mga_flash(struct ubx_header *header);

int is_ubx_mga_gal(struct ubx_header *header);

int is_ubx_mga_glo(struct ubx_header *header);

int is_ubx_mga_gps(struct ubx_header *header);

int is_ubx_mga_ini(struct ubx_header *header);

int is_ubx_mon_gnss(struct ubx_header *header);

int is_ubx_mon_hw(struct ubx_header *header);

int is_ubx_mon_io(struct ubx_header *header);

int is_ubx_mon_msgpp(struct ubx_header *header);

int is_ubx_mon_patch(struct ubx_header *header);

int is_ubx_mon_rxbuf(struct ubx_header *header);

int is_ubx_mon_rxr(struct ubx_header *header);

int is_ubx_mon_smgr(struct ubx_header *header);

int is_ubx_nav_aopstatus(struct ubx_header *header);

int is_ubx_nav_att(struct ubx_header *header);

int is_ubx_nav_clock(struct ubx_header *header);

int is_ubx_nav_dgps(struct ubx_header *header);

int is_ubx_nav_dop(struct ubx_header *header);

int is_ubx_nav_eoe(struct ubx_header *header);

int is_ubx_nav_geofence(struct ubx_header *header);

int is_ubx_nav_hpposecef(struct ubx_header *header);

int is_ubx_nav_hpposllh(struct ubx_header *header);

int is_ubx_rxm_imes(struct ubx_header *header);

int is_ubx_rxm_measx(struct ubx_header *header);

int is_ubx_rxm_pmreq(struct ubx_header *header);

int is_ubx_rxm_rawx(struct ubx_header *header);

int is_ubx_rxm_rlm(struct ubx_header *header);

int is_ubx_rxm_rtcm(struct ubx_header *header);

int is_ubx_rxm_sfrbx(struct ubx_header *header);

int is_ubx_rxm_svsi(struct ubx_header *header);

int is_ubx_sec_sign(struct ubx_header *header);

int is_ubx_sec_uniqid(struct ubx_header *header);

int is_ubx_tim_dosc(struct ubx_header *header);

int is_ubx_tim_fchg(struct ubx_header *header);

int is_ubx_tim_hoc(struct ubx_header *header);

int is_ubx_tim_smeas(struct ubx_header *header);

int is_ubx_tim_svin(struct ubx_header *header);

int is_ubx_tim_tos(struct ubx_header *header);

int is_ubx_tim_tp(struct ubx_header *header);

int is_ubx_tim_vcocal(struct ubx_header *header);

int is_ubx_upd_sos(struct ubx_header *header);

void sprint_protocol_name(char *buf, struct ubx_header *header);

void fprint_protocol_name(FILE *fp, struct ubx_header *header);

#endif