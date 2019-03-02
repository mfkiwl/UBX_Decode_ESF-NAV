#include "ubx_protocol.h"

static const struct ubx_header UBX_ACK_ACK_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x05,
	.id = 0x01,
};

static const struct ubx_header UBX_ACK_NAK_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x05,
	.id = 0x00,
};

static const struct ubx_header UBX_AID_ALM_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0B,
	.id = 0x30,
};

static const struct ubx_header UBX_AID_AOP_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0B,
	.id = 0x33,
};

static const struct ubx_header UBX_AID_EPH_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0B,
	.id = 0x31,
};

static const struct ubx_header UBX_AID_HUI_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0B,
	.id = 0x02,
};

static const struct ubx_header UBX_AID_INI_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0B,
	.id = 0x01,
};

static const struct ubx_header UBX_CFG_ANT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x13,
};

static const struct ubx_header UBX_CFG_CFG_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x09,
};

static const struct ubx_header UBX_CFG_DAT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x06,
};

static const struct ubx_header UBX_CFG_DGNSS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x70,
};

static const struct ubx_header UBX_CFG_DOSC_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x61,
};

static const struct ubx_header UBX_CFG_DYNSEED_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x85,
};

static const struct ubx_header UBX_CFG_ESRC_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x60,
};

static const struct ubx_header UBX_CFG_FIXSEED_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x84,
};

static const struct ubx_header UBX_CFG_GEOFENCE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x69,
};

static const struct ubx_header UBX_ESF_INS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x10,
	.id = 0x15,
};

static const struct ubx_header UBX_ESF_MEAS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x10,
	.id = 0x02,
};

static const struct ubx_header UBX_ESF_RAW_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x10,
	.id = 0x03,
};

static const struct ubx_header UBX_ESF_STATUS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x10,
	.id = 0x10,
};

static const struct ubx_header UBX_HNR_PVT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x28,
	.id = 0x00,
};

static const struct ubx_header UBX_INF_DEBUG_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x04,
	.id = 0x04,
};

static const struct ubx_header UBX_INF_ERROR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x04,
	.id = 0x00,
};

static const struct ubx_header UBX_INF_NOTICE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x04,
	.id = 0x02,
};

static const struct ubx_header UBX_INF_TEST_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x04,
	.id = 0x03,
};

static const struct ubx_header UBX_INF_WARNING_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x04,
	.id = 0x01,
};

static const struct ubx_header UBX_LOG_CREATE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x07,
};

static const struct ubx_header UBX_LOG_ERASE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x03,
};

static const struct ubx_header UBX_LOG_FINDTIME_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x0E,
};

static const struct ubx_header UBX_LOG_INFO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x08,
};

static const struct ubx_header UBX_LOG_RETRIEVE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x09,
};

static const struct ubx_header UBX_LOG_STRING_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x21,
	.id = 0x04,
};

static const struct ubx_header UBX_MGA_ACK_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x60,
};

static const struct ubx_header UBX_MGA_ANO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x20,
};

static const struct ubx_header UBX_MGA_BDS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x03,
};

static const struct ubx_header UBX_MGA_DBD_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x80,
};

static const struct ubx_header UBX_MGA_FLASH_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x21,
};

static const struct ubx_header UBX_MGA_GAL_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x02,
};

static const struct ubx_header UBX_MGA_GLO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x06,
};

static const struct ubx_header UBX_MGA_GPS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x00,
};

static const struct ubx_header UBX_MGA_INI_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x40,
};

static const struct ubx_header UBX_MON_GNSS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x28,
};

static const struct ubx_header UBX_MON_HW_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x09,
};

static const struct ubx_header UBX_MON_IO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x02,
};

static const struct ubx_header UBX_MON_MSGPP_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x06,
};

static const struct ubx_header UBX_MON_PATCH_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x27,
};

static const struct ubx_header UBX_MON_RXBUF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x07,
};

static const struct ubx_header UBX_MON_RXR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x21,
};

static const struct ubx_header UBX_MON_SMGR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x2E,
};

static const struct ubx_header UBX_NAV_AOPSTATUS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x60,
};

static const struct ubx_header UBX_NAV_ATT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x05,
};

static const struct ubx_header UBX_NAV_CLOCK_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x22,
};

static const struct ubx_header UBX_NAV_DGPS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x31,
};

static const struct ubx_header UBX_NAV_DOP_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x04,
};

static const struct ubx_header UBX_NAV_EOE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x61,
};

static const struct ubx_header UBX_NAV_GEOFENCE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x39,
};

static const struct ubx_header UBX_NAV_HPPOSECEF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x13,
};

static const struct ubx_header UBX_NAV_HPPOSLLH_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x14,
};

static const struct ubx_header UBX_RXM_IMES_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x61,
};

static const struct ubx_header UBX_RXM_MEASX_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x14,
};

static const struct ubx_header UBX_RXM_PMREQ_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x41,
};

static const struct ubx_header UBX_RXM_RAWX_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x15,
};

static const struct ubx_header UBX_RXM_RLM_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x59,
};

static const struct ubx_header UBX_RXM_RTCM_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x32,
};

static const struct ubx_header UBX_RXM_SFRBX_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x13,
};

static const struct ubx_header UBX_RXM_SVSI_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x02,
	.id = 0x20,
};

static const struct ubx_header UBX_SEC_SIGN_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x27,
	.id = 0x01,
};

static const struct ubx_header UBX_SEC_UNIQID_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x27,
	.id = 0x03,
};

static const struct ubx_header UBX_TIM_DOSC_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x11,
};

static const struct ubx_header UBX_TIM_FCHG_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x16,
};

static const struct ubx_header UBX_TIM_HOC_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x17,
};

static const struct ubx_header UBX_TIM_SMEAS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x13,
};

static const struct ubx_header UBX_TIM_SVIN_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x04,
};

static const struct ubx_header UBX_TIM_TOS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x12,
};

static const struct ubx_header UBX_TIM_TP_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x01,
};

static const struct ubx_header UBX_TIM_VCOCAL_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x15,
};

static const struct ubx_header UBX_UPD_SOS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x09,
	.id = 0x14,
};

int is_ubx_ack_ack(struct ubx_header *header)
{
	if (header->klass == UBX_ACK_ACK_HEADER.klass &&
	    header->id == UBX_ACK_ACK_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_ack_nak(struct ubx_header *header)
{
	if (header->klass == UBX_ACK_NAK_HEADER.klass &&
	    header->id == UBX_ACK_NAK_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_aid_alm(struct ubx_header *header)
{
	if (header->klass == UBX_AID_ALM_HEADER.klass &&
	    header->id == UBX_AID_ALM_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_aid_aop(struct ubx_header *header)
{
	if (header->klass == UBX_AID_AOP_HEADER.klass &&
	    header->id == UBX_AID_AOP_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_aid_eph(struct ubx_header *header)
{
	if (header->klass == UBX_AID_EPH_HEADER.klass &&
	    header->id == UBX_AID_EPH_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_aid_hui(struct ubx_header *header)
{
	if (header->klass == UBX_AID_HUI_HEADER.klass &&
	    header->id == UBX_AID_HUI_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_aid_ini(struct ubx_header *header)
{
	if (header->klass == UBX_AID_INI_HEADER.klass &&
	    header->id == UBX_AID_INI_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_ant(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_ANT_HEADER.klass &&
	    header->id == UBX_CFG_ANT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_cfg(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_CFG_HEADER.klass &&
	    header->id == UBX_CFG_CFG_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_dat(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_DAT_HEADER.klass &&
	    header->id == UBX_CFG_DAT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_dgnss(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_DGNSS_HEADER.klass &&
	    header->id == UBX_CFG_DGNSS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_dosc(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_DOSC_HEADER.klass &&
	    header->id == UBX_CFG_DOSC_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_dynseed(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_DYNSEED_HEADER.klass &&
	    header->id == UBX_CFG_DYNSEED_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_esrc(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_ESRC_HEADER.klass &&
	    header->id == UBX_CFG_ESRC_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_fixseed(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_FIXSEED_HEADER.klass &&
	    header->id == UBX_CFG_FIXSEED_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_geofence(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_GEOFENCE_HEADER.klass &&
	    header->id == UBX_CFG_GEOFENCE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_esf_ins(struct ubx_header *header)
{
	if (header->klass == UBX_ESF_INS_HEADER.klass &&
	    header->id == UBX_ESF_INS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_esf_meas(struct ubx_header *header)
{
	if (header->klass == UBX_ESF_MEAS_HEADER.klass &&
	    header->id == UBX_ESF_MEAS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_esf_raw(struct ubx_header *header)
{
	if (header->klass == UBX_ESF_RAW_HEADER.klass &&
	    header->id == UBX_ESF_RAW_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_esf_status(struct ubx_header *header)
{
	if (header->klass == UBX_ESF_STATUS_HEADER.klass &&
	    header->id == UBX_ESF_STATUS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_hnr_pvt(struct ubx_header *header)
{
	if (header->klass == UBX_HNR_PVT_HEADER.klass &&
	    header->id == UBX_HNR_PVT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_inf_debug(struct ubx_header *header)
{
	if (header->klass == UBX_INF_DEBUG_HEADER.klass &&
	    header->id == UBX_INF_DEBUG_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_inf_error(struct ubx_header *header)
{
	if (header->klass == UBX_INF_ERROR_HEADER.klass &&
	    header->id == UBX_INF_ERROR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_inf_notice(struct ubx_header *header)
{
	if (header->klass == UBX_INF_NOTICE_HEADER.klass &&
	    header->id == UBX_INF_NOTICE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_inf_test(struct ubx_header *header)
{
	if (header->klass == UBX_INF_TEST_HEADER.klass &&
	    header->id == UBX_INF_TEST_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_inf_warning(struct ubx_header *header)
{
	if (header->klass == UBX_INF_WARNING_HEADER.klass &&
	    header->id == UBX_INF_WARNING_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_create(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_CREATE_HEADER.klass &&
	    header->id == UBX_LOG_CREATE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_erase(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_ERASE_HEADER.klass &&
	    header->id == UBX_LOG_ERASE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_findtime(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_FINDTIME_HEADER.klass &&
	    header->id == UBX_LOG_FINDTIME_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_info(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_INFO_HEADER.klass &&
	    header->id == UBX_LOG_INFO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_retrieve(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_RETRIEVE_HEADER.klass &&
	    header->id == UBX_LOG_RETRIEVE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_log_string(struct ubx_header *header)
{
	if (header->klass == UBX_LOG_STRING_HEADER.klass &&
	    header->id == UBX_LOG_STRING_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_ack(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_ACK_HEADER.klass &&
	    header->id == UBX_MGA_ACK_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_ano(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_ANO_HEADER.klass &&
	    header->id == UBX_MGA_ANO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_bds(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_BDS_HEADER.klass &&
	    header->id == UBX_MGA_BDS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_dbd(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_DBD_HEADER.klass &&
	    header->id == UBX_MGA_DBD_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_flash(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_FLASH_HEADER.klass &&
	    header->id == UBX_MGA_FLASH_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_gal(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_GAL_HEADER.klass &&
	    header->id == UBX_MGA_GAL_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_glo(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_GLO_HEADER.klass &&
	    header->id == UBX_MGA_GLO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_gps(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_GPS_HEADER.klass &&
	    header->id == UBX_MGA_GPS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mga_ini(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_INI_HEADER.klass &&
	    header->id == UBX_MGA_INI_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_gnss(struct ubx_header *header)
{
	if (header->klass == UBX_MON_GNSS_HEADER.klass &&
	    header->id == UBX_MON_GNSS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_hw(struct ubx_header *header)
{
	if (header->klass == UBX_MON_HW_HEADER.klass &&
	    header->id == UBX_MON_HW_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_io(struct ubx_header *header)
{
	if (header->klass == UBX_MON_IO_HEADER.klass &&
	    header->id == UBX_MON_IO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_msgpp(struct ubx_header *header)
{
	if (header->klass == UBX_MON_MSGPP_HEADER.klass &&
	    header->id == UBX_MON_MSGPP_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_patch(struct ubx_header *header)
{
	if (header->klass == UBX_MON_PATCH_HEADER.klass &&
	    header->id == UBX_MON_PATCH_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_rxbuf(struct ubx_header *header)
{
	if (header->klass == UBX_MON_RXBUF_HEADER.klass &&
	    header->id == UBX_MON_RXBUF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_rxr(struct ubx_header *header)
{
	if (header->klass == UBX_MON_RXR_HEADER.klass &&
	    header->id == UBX_MON_RXR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_smgr(struct ubx_header *header)
{
	if (header->klass == UBX_MON_SMGR_HEADER.klass &&
	    header->id == UBX_MON_SMGR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_aopstatus(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_AOPSTATUS_HEADER.klass &&
	    header->id == UBX_NAV_AOPSTATUS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_att(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_ATT_HEADER.klass &&
	    header->id == UBX_NAV_ATT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_clock(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_CLOCK_HEADER.klass &&
	    header->id == UBX_NAV_CLOCK_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_dgps(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_DGPS_HEADER.klass &&
	    header->id == UBX_NAV_DGPS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_dop(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_DOP_HEADER.klass &&
	    header->id == UBX_NAV_DOP_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_eoe(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_EOE_HEADER.klass &&
	    header->id == UBX_NAV_EOE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_geofence(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_GEOFENCE_HEADER.klass &&
	    header->id == UBX_NAV_GEOFENCE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_hpposecef(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_HPPOSECEF_HEADER.klass &&
	    header->id == UBX_NAV_HPPOSECEF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_hpposllh(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_HPPOSLLH_HEADER.klass &&
	    header->id == UBX_NAV_HPPOSLLH_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_imes(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_IMES_HEADER.klass &&
	    header->id == UBX_RXM_IMES_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_measx(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_MEASX_HEADER.klass &&
	    header->id == UBX_RXM_MEASX_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_pmreq(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_PMREQ_HEADER.klass &&
	    header->id == UBX_RXM_PMREQ_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_rawx(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_RAWX_HEADER.klass &&
	    header->id == UBX_RXM_RAWX_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_rlm(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_RLM_HEADER.klass &&
	    header->id == UBX_RXM_RLM_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_rtcm(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_RTCM_HEADER.klass &&
	    header->id == UBX_RXM_RTCM_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_sfrbx(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_SFRBX_HEADER.klass &&
	    header->id == UBX_RXM_SFRBX_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_rxm_svsi(struct ubx_header *header)
{
	if (header->klass == UBX_RXM_SVSI_HEADER.klass &&
	    header->id == UBX_RXM_SVSI_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_sec_sign(struct ubx_header *header)
{
	if (header->klass == UBX_SEC_SIGN_HEADER.klass &&
	    header->id == UBX_SEC_SIGN_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_sec_uniqid(struct ubx_header *header)
{
	if (header->klass == UBX_SEC_UNIQID_HEADER.klass &&
	    header->id == UBX_SEC_UNIQID_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_dosc(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_DOSC_HEADER.klass &&
	    header->id == UBX_TIM_DOSC_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_fchg(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_FCHG_HEADER.klass &&
	    header->id == UBX_TIM_FCHG_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_hoc(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_HOC_HEADER.klass &&
	    header->id == UBX_TIM_HOC_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_smeas(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_SMEAS_HEADER.klass &&
	    header->id == UBX_TIM_SMEAS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_svin(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_SVIN_HEADER.klass &&
	    header->id == UBX_TIM_SVIN_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_tos(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_TOS_HEADER.klass &&
	    header->id == UBX_TIM_TOS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_tp(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_TP_HEADER.klass &&
	    header->id == UBX_TIM_TP_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_tim_vcocal(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_VCOCAL_HEADER.klass &&
	    header->id == UBX_TIM_VCOCAL_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_upd_sos(struct ubx_header *header)
{
	if (header->klass == UBX_UPD_SOS_HEADER.klass &&
	    header->id == UBX_UPD_SOS_HEADER.id)
	    return 1;
	return 0;
}

void sprint_protocol_name(char *buf, struct ubx_header *header)
{

	if (is_ubx_ack_ack(header)) {
		sprintf(buf, "UBX-ACK-ACK");
		return;
	}

	if (is_ubx_ack_nak(header)) {
		sprintf(buf, "UBX-ACK-NAK");
		return;
	}

	if (is_ubx_aid_alm(header)) {
		sprintf(buf, "UBX-AID-ALM");
		return;
	}

	if (is_ubx_aid_aop(header)) {
		sprintf(buf, "UBX-AID-AOP");
		return;
	}

	if (is_ubx_aid_eph(header)) {
		sprintf(buf, "UBX-AID-EPH");
		return;
	}

	if (is_ubx_aid_hui(header)) {
		sprintf(buf, "UBX-AID-HUI");
		return;
	}

	if (is_ubx_aid_ini(header)) {
		sprintf(buf, "UBX-AID-INI");
		return;
	}

	if (is_ubx_cfg_ant(header)) {
		sprintf(buf, "UBX-CFG-ANT");
		return;
	}

	if (is_ubx_cfg_cfg(header)) {
		sprintf(buf, "UBX-CFG-CFG");
		return;
	}

	if (is_ubx_cfg_dat(header)) {
		sprintf(buf, "UBX-CFG-DAT");
		return;
	}

	if (is_ubx_cfg_dgnss(header)) {
		sprintf(buf, "UBX-CFG-DGNSS");
		return;
	}

	if (is_ubx_cfg_dosc(header)) {
		sprintf(buf, "UBX-CFG-DOSC");
		return;
	}

	if (is_ubx_cfg_dynseed(header)) {
		sprintf(buf, "UBX-CFG-DYNSEED");
		return;
	}

	if (is_ubx_cfg_esrc(header)) {
		sprintf(buf, "UBX-CFG-ESRC");
		return;
	}

	if (is_ubx_cfg_fixseed(header)) {
		sprintf(buf, "UBX-CFG-FIXSEED");
		return;
	}

	if (is_ubx_cfg_geofence(header)) {
		sprintf(buf, "UBX-CFG-GEOFENCE");
		return;
	}

	if (is_ubx_esf_ins(header)) {
		sprintf(buf, "UBX-ESF-INS");
		return;
	}

	if (is_ubx_esf_meas(header)) {
		sprintf(buf, "UBX-ESF-MEAS");
		return;
	}

	if (is_ubx_esf_raw(header)) {
		sprintf(buf, "UBX-ESF-RAW");
		return;
	}

	if (is_ubx_esf_status(header)) {
		sprintf(buf, "UBX-ESF-STATUS");
		return;
	}

	if (is_ubx_hnr_pvt(header)) {
		sprintf(buf, "UBX-HNR-PVT");
		return;
	}

	if (is_ubx_inf_debug(header)) {
		sprintf(buf, "UBX-INF-DEBUG");
		return;
	}

	if (is_ubx_inf_error(header)) {
		sprintf(buf, "UBX-INF-ERROR");
		return;
	}

	if (is_ubx_inf_notice(header)) {
		sprintf(buf, "UBX-INF-NOTICE");
		return;
	}

	if (is_ubx_inf_test(header)) {
		sprintf(buf, "UBX-INF-TEST");
		return;
	}

	if (is_ubx_inf_warning(header)) {
		sprintf(buf, "UBX-INF-WARNING");
		return;
	}

	if (is_ubx_log_create(header)) {
		sprintf(buf, "UBX-LOG-CREATE");
		return;
	}

	if (is_ubx_log_erase(header)) {
		sprintf(buf, "UBX-LOG-ERASE");
		return;
	}

	if (is_ubx_log_findtime(header)) {
		sprintf(buf, "UBX-LOG-FINDTIME");
		return;
	}

	if (is_ubx_log_info(header)) {
		sprintf(buf, "UBX-LOG-INFO");
		return;
	}

	if (is_ubx_log_retrieve(header)) {
		sprintf(buf, "UBX-LOG-RETRIEVE");
		return;
	}

	if (is_ubx_log_string(header)) {
		sprintf(buf, "UBX-LOG-STRING");
		return;
	}

	if (is_ubx_mga_ack(header)) {
		sprintf(buf, "UBX-MGA-ACK");
		return;
	}

	if (is_ubx_mga_ano(header)) {
		sprintf(buf, "UBX-MGA-ANO");
		return;
	}

	if (is_ubx_mga_bds(header)) {
		sprintf(buf, "UBX-MGA-BDS");
		return;
	}

	if (is_ubx_mga_dbd(header)) {
		sprintf(buf, "UBX-MGA-DBD");
		return;
	}

	if (is_ubx_mga_flash(header)) {
		sprintf(buf, "UBX-MGA-FLASH");
		return;
	}

	if (is_ubx_mga_gal(header)) {
		sprintf(buf, "UBX-MGA-GAL");
		return;
	}

	if (is_ubx_mga_glo(header)) {
		sprintf(buf, "UBX-MGA-GLO");
		return;
	}

	if (is_ubx_mga_gps(header)) {
		sprintf(buf, "UBX-MGA-GPS");
		return;
	}

	if (is_ubx_mga_ini(header)) {
		sprintf(buf, "UBX-MGA-INI");
		return;
	}

	if (is_ubx_mon_gnss(header)) {
		sprintf(buf, "UBX-MON-GNSS");
		return;
	}

	if (is_ubx_mon_hw(header)) {
		sprintf(buf, "UBX-MON-HW");
		return;
	}

	if (is_ubx_mon_io(header)) {
		sprintf(buf, "UBX-MON-IO");
		return;
	}

	if (is_ubx_mon_msgpp(header)) {
		sprintf(buf, "UBX-MON-MSGPP");
		return;
	}

	if (is_ubx_mon_patch(header)) {
		sprintf(buf, "UBX-MON-PATCH");
		return;
	}

	if (is_ubx_mon_rxbuf(header)) {
		sprintf(buf, "UBX-MON-RXBUF");
		return;
	}

	if (is_ubx_mon_rxr(header)) {
		sprintf(buf, "UBX-MON-RXR");
		return;
	}

	if (is_ubx_mon_smgr(header)) {
		sprintf(buf, "UBX-MON-SMGR");
		return;
	}

	if (is_ubx_nav_aopstatus(header)) {
		sprintf(buf, "UBX-NAV-AOPSTATUS");
		return;
	}

	if (is_ubx_nav_att(header)) {
		sprintf(buf, "UBX-NAV-ATT");
		return;
	}

	if (is_ubx_nav_clock(header)) {
		sprintf(buf, "UBX-NAV-CLOCK");
		return;
	}

	if (is_ubx_nav_dgps(header)) {
		sprintf(buf, "UBX-NAV-DGPS");
		return;
	}

	if (is_ubx_nav_dop(header)) {
		sprintf(buf, "UBX-NAV-DOP");
		return;
	}

	if (is_ubx_nav_eoe(header)) {
		sprintf(buf, "UBX-NAV-EOE");
		return;
	}

	if (is_ubx_nav_geofence(header)) {
		sprintf(buf, "UBX-NAV-GEOFENCE");
		return;
	}

	if (is_ubx_nav_hpposecef(header)) {
		sprintf(buf, "UBX-NAV-HPPOSECEF");
		return;
	}

	if (is_ubx_nav_hpposllh(header)) {
		sprintf(buf, "UBX-NAV-HPPOSLLH");
		return;
	}

	if (is_ubx_rxm_imes(header)) {
		sprintf(buf, "UBX-RXM-IMES");
		return;
	}

	if (is_ubx_rxm_measx(header)) {
		sprintf(buf, "UBX-RXM-MEASX");
		return;
	}

	if (is_ubx_rxm_pmreq(header)) {
		sprintf(buf, "UBX-RXM-PMREQ");
		return;
	}

	if (is_ubx_rxm_rawx(header)) {
		sprintf(buf, "UBX-RXM-RAWX");
		return;
	}

	if (is_ubx_rxm_rlm(header)) {
		sprintf(buf, "UBX-RXM-RLM");
		return;
	}

	if (is_ubx_rxm_rtcm(header)) {
		sprintf(buf, "UBX-RXM-RTCM");
		return;
	}

	if (is_ubx_rxm_sfrbx(header)) {
		sprintf(buf, "UBX-RXM-SFRBX");
		return;
	}

	if (is_ubx_rxm_svsi(header)) {
		sprintf(buf, "UBX-RXM-SVSI");
		return;
	}

	if (is_ubx_sec_sign(header)) {
		sprintf(buf, "UBX-SEC-SIGN");
		return;
	}

	if (is_ubx_sec_uniqid(header)) {
		sprintf(buf, "UBX-SEC-UNIQID");
		return;
	}

	if (is_ubx_tim_dosc(header)) {
		sprintf(buf, "UBX-TIM-DOSC");
		return;
	}

	if (is_ubx_tim_fchg(header)) {
		sprintf(buf, "UBX-TIM-FCHG");
		return;
	}

	if (is_ubx_tim_hoc(header)) {
		sprintf(buf, "UBX-TIM-HOC");
		return;
	}

	if (is_ubx_tim_smeas(header)) {
		sprintf(buf, "UBX-TIM-SMEAS");
		return;
	}

	if (is_ubx_tim_svin(header)) {
		sprintf(buf, "UBX-TIM-SVIN");
		return;
	}

	if (is_ubx_tim_tos(header)) {
		sprintf(buf, "UBX-TIM-TOS");
		return;
	}

	if (is_ubx_tim_tp(header)) {
		sprintf(buf, "UBX-TIM-TP");
		return;
	}

	if (is_ubx_tim_vcocal(header)) {
		sprintf(buf, "UBX-TIM-VCOCAL");
		return;
	}

	if (is_ubx_upd_sos(header)) {
		sprintf(buf, "UBX-UPD-SOS");
		return;
	}

}

void fprint_protocol_name(FILE *fp, struct ubx_header *header)
{
	char name[MAX_PROTOCOL_NAME];
	sprint_protocol_name(name, header);
	fprintf(fp, "%s", name);
}