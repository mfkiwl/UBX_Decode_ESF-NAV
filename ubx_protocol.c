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

static const struct ubx_header UBX_CFG_GNSS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x3E,
};

static const struct ubx_header UBX_CFG_HNR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x5C,
};

static const struct ubx_header UBX_CFG_INF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x02,
};

static const struct ubx_header UBX_CFG_ITFM_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x39,
};

static const struct ubx_header UBX_CFG_LOGFILTER_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x47,
};

static const struct ubx_header UBX_CFG_MSG_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x01,
};

static const struct ubx_header UBX_CFG_NAV5_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x24,
};

static const struct ubx_header UBX_CFG_NAVX5_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x23,
};

static const struct ubx_header UBX_CFG_NMEA_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x17,
};

static const struct ubx_header UBX_CFG_ODO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x1E,
};

static const struct ubx_header UBX_CFG_PM2_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x3B,
};

static const struct ubx_header UBX_CFG_PMS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x86,
};

static const struct ubx_header UBX_CFG_PRT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x00,
};

static const struct ubx_header UBX_CFG_PWR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x57,
};

static const struct ubx_header UBX_CFG_RATE_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x08,
};

static const struct ubx_header UBX_CFG_RINV_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x34,
};

static const struct ubx_header UBX_CFG_RST_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x04,
};

static const struct ubx_header UBX_CFG_RXM_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x11,
};

static const struct ubx_header UBX_CFG_SBAS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x16,
};

static const struct ubx_header UBX_CFG_SMGR_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x62,
};

static const struct ubx_header UBX_CFG_TMODE2_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x3D,
};

static const struct ubx_header UBX_CFG_TMODE3_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x71,
};

static const struct ubx_header UBX_CFG_TP5_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x31,
};

static const struct ubx_header UBX_CFG_TXSLOT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x53,
};

static const struct ubx_header UBX_CFG_USB_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x06,
	.id = 0x1B,
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

static const struct ubx_header UBX_MGA_QZSS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x13,
	.id = 0x05,
};

static const struct ubx_header UBX_MON_GNSS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x28,
};

static const struct ubx_header UBX_MON_HW2_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x0B,
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

static const struct ubx_header UBX_MON_TXBUF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x08,
};

static const struct ubx_header UBX_MON_VER_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0A,
	.id = 0x04,
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

static const struct ubx_header UBX_NAV_ODO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x09,
};

static const struct ubx_header UBX_NAV_ORB_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x34,
};

static const struct ubx_header UBX_NAV_POSECEF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x01,
};

static const struct ubx_header UBX_NAV_POSLLH_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x02,
};

static const struct ubx_header UBX_NAV_PVT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x07,
};

static const struct ubx_header UBX_NAV_RELPOSNED_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x3C,
};

static const struct ubx_header UBX_NAV_RESETODO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x10,
};

static const struct ubx_header UBX_NAV_SAT_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x35,
};

static const struct ubx_header UBX_NAV_SBAS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x32,
};

static const struct ubx_header UBX_NAV_SOL_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x06,
};

static const struct ubx_header UBX_NAV_STATUS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x03,
};

static const struct ubx_header UBX_NAV_SVINFO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x30,
};

static const struct ubx_header UBX_NAV_SVIN_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x3B,
};

static const struct ubx_header UBX_NAV_TIMEBDS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x24,
};

static const struct ubx_header UBX_NAV_TIMEGAL_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x25,
};

static const struct ubx_header UBX_NAV_TIMEGLO_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x23,
};

static const struct ubx_header UBX_NAV_TIMEGPS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x20,
};

static const struct ubx_header UBX_NAV_TIMELS_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x26,
};

static const struct ubx_header UBX_NAV_TIMEUTC_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x21,
};

static const struct ubx_header UBX_NAV_VELECEF_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x11,
};

static const struct ubx_header UBX_NAV_VELNED_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x01,
	.id = 0x12,
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

static const struct ubx_header UBX_TIM_TM2_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x03,
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

static const struct ubx_header UBX_TIM_VRFY_HEADER = {
	.sync = { 0xB5, 0x62 },
	.klass = 0x0D,
	.id = 0x06,
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

int is_ubx_cfg_gnss(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_GNSS_HEADER.klass &&
	    header->id == UBX_CFG_GNSS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_hnr(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_HNR_HEADER.klass &&
	    header->id == UBX_CFG_HNR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_inf(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_INF_HEADER.klass &&
	    header->id == UBX_CFG_INF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_itfm(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_ITFM_HEADER.klass &&
	    header->id == UBX_CFG_ITFM_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_logfilter(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_LOGFILTER_HEADER.klass &&
	    header->id == UBX_CFG_LOGFILTER_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_msg(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_MSG_HEADER.klass &&
	    header->id == UBX_CFG_MSG_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_nav5(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_NAV5_HEADER.klass &&
	    header->id == UBX_CFG_NAV5_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_navx5(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_NAVX5_HEADER.klass &&
	    header->id == UBX_CFG_NAVX5_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_nmea(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_NMEA_HEADER.klass &&
	    header->id == UBX_CFG_NMEA_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_odo(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_ODO_HEADER.klass &&
	    header->id == UBX_CFG_ODO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_pm2(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_PM2_HEADER.klass &&
	    header->id == UBX_CFG_PM2_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_pms(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_PMS_HEADER.klass &&
	    header->id == UBX_CFG_PMS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_prt(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_PRT_HEADER.klass &&
	    header->id == UBX_CFG_PRT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_pwr(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_PWR_HEADER.klass &&
	    header->id == UBX_CFG_PWR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_rate(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_RATE_HEADER.klass &&
	    header->id == UBX_CFG_RATE_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_rinv(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_RINV_HEADER.klass &&
	    header->id == UBX_CFG_RINV_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_rst(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_RST_HEADER.klass &&
	    header->id == UBX_CFG_RST_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_rxm(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_RXM_HEADER.klass &&
	    header->id == UBX_CFG_RXM_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_sbas(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_SBAS_HEADER.klass &&
	    header->id == UBX_CFG_SBAS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_smgr(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_SMGR_HEADER.klass &&
	    header->id == UBX_CFG_SMGR_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_tmode2(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_TMODE2_HEADER.klass &&
	    header->id == UBX_CFG_TMODE2_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_tmode3(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_TMODE3_HEADER.klass &&
	    header->id == UBX_CFG_TMODE3_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_tp5(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_TP5_HEADER.klass &&
	    header->id == UBX_CFG_TP5_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_txslot(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_TXSLOT_HEADER.klass &&
	    header->id == UBX_CFG_TXSLOT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_cfg_usb(struct ubx_header *header)
{
	if (header->klass == UBX_CFG_USB_HEADER.klass &&
	    header->id == UBX_CFG_USB_HEADER.id)
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

int is_ubx_mga_qzss(struct ubx_header *header)
{
	if (header->klass == UBX_MGA_QZSS_HEADER.klass &&
	    header->id == UBX_MGA_QZSS_HEADER.id)
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

int is_ubx_mon_hw2(struct ubx_header *header)
{
	if (header->klass == UBX_MON_HW2_HEADER.klass &&
	    header->id == UBX_MON_HW2_HEADER.id)
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

int is_ubx_mon_txbuf(struct ubx_header *header)
{
	if (header->klass == UBX_MON_TXBUF_HEADER.klass &&
	    header->id == UBX_MON_TXBUF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_mon_ver(struct ubx_header *header)
{
	if (header->klass == UBX_MON_VER_HEADER.klass &&
	    header->id == UBX_MON_VER_HEADER.id)
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

int is_ubx_nav_odo(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_ODO_HEADER.klass &&
	    header->id == UBX_NAV_ODO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_orb(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_ORB_HEADER.klass &&
	    header->id == UBX_NAV_ORB_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_posecef(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_POSECEF_HEADER.klass &&
	    header->id == UBX_NAV_POSECEF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_posllh(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_POSLLH_HEADER.klass &&
	    header->id == UBX_NAV_POSLLH_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_pvt(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_PVT_HEADER.klass &&
	    header->id == UBX_NAV_PVT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_relposned(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_RELPOSNED_HEADER.klass &&
	    header->id == UBX_NAV_RELPOSNED_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_resetodo(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_RESETODO_HEADER.klass &&
	    header->id == UBX_NAV_RESETODO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_sat(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_SAT_HEADER.klass &&
	    header->id == UBX_NAV_SAT_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_sbas(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_SBAS_HEADER.klass &&
	    header->id == UBX_NAV_SBAS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_sol(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_SOL_HEADER.klass &&
	    header->id == UBX_NAV_SOL_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_status(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_STATUS_HEADER.klass &&
	    header->id == UBX_NAV_STATUS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_svinfo(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_SVINFO_HEADER.klass &&
	    header->id == UBX_NAV_SVINFO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_svin(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_SVIN_HEADER.klass &&
	    header->id == UBX_NAV_SVIN_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timebds(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMEBDS_HEADER.klass &&
	    header->id == UBX_NAV_TIMEBDS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timegal(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMEGAL_HEADER.klass &&
	    header->id == UBX_NAV_TIMEGAL_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timeglo(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMEGLO_HEADER.klass &&
	    header->id == UBX_NAV_TIMEGLO_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timegps(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMEGPS_HEADER.klass &&
	    header->id == UBX_NAV_TIMEGPS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timels(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMELS_HEADER.klass &&
	    header->id == UBX_NAV_TIMELS_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_timeutc(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_TIMEUTC_HEADER.klass &&
	    header->id == UBX_NAV_TIMEUTC_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_velecef(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_VELECEF_HEADER.klass &&
	    header->id == UBX_NAV_VELECEF_HEADER.id)
	    return 1;
	return 0;
}

int is_ubx_nav_velned(struct ubx_header *header)
{
	if (header->klass == UBX_NAV_VELNED_HEADER.klass &&
	    header->id == UBX_NAV_VELNED_HEADER.id)
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

int is_ubx_tim_tm2(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_TM2_HEADER.klass &&
	    header->id == UBX_TIM_TM2_HEADER.id)
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

int is_ubx_tim_vrfy(struct ubx_header *header)
{
	if (header->klass == UBX_TIM_VRFY_HEADER.klass &&
	    header->id == UBX_TIM_VRFY_HEADER.id)
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

char *protocol_name(struct ubx_header *header)
{

	if (is_ubx_ack_ack(header)) {
		return ("UBX-ACK-ACK");
	}

	if (is_ubx_ack_nak(header)) {
		return ("UBX-ACK-NAK");
	}

	if (is_ubx_aid_alm(header)) {
		return ("UBX-AID-ALM");
	}

	if (is_ubx_aid_aop(header)) {
		return ("UBX-AID-AOP");
	}

	if (is_ubx_aid_eph(header)) {
		return ("UBX-AID-EPH");
	}

	if (is_ubx_aid_hui(header)) {
		return ("UBX-AID-HUI");
	}

	if (is_ubx_aid_ini(header)) {
		return ("UBX-AID-INI");
	}

	if (is_ubx_cfg_ant(header)) {
		return ("UBX-CFG-ANT");
	}

	if (is_ubx_cfg_cfg(header)) {
		return ("UBX-CFG-CFG");
	}

	if (is_ubx_cfg_dat(header)) {
		return ("UBX-CFG-DAT");
	}

	if (is_ubx_cfg_dgnss(header)) {
		return ("UBX-CFG-DGNSS");
	}

	if (is_ubx_cfg_dosc(header)) {
		return ("UBX-CFG-DOSC");
	}

	if (is_ubx_cfg_dynseed(header)) {
		return ("UBX-CFG-DYNSEED");
	}

	if (is_ubx_cfg_esrc(header)) {
		return ("UBX-CFG-ESRC");
	}

	if (is_ubx_cfg_fixseed(header)) {
		return ("UBX-CFG-FIXSEED");
	}

	if (is_ubx_cfg_geofence(header)) {
		return ("UBX-CFG-GEOFENCE");
	}

	if (is_ubx_cfg_gnss(header)) {
		return ("UBX-CFG-GNSS");
	}

	if (is_ubx_cfg_hnr(header)) {
		return ("UBX-CFG-HNR");
	}

	if (is_ubx_cfg_inf(header)) {
		return ("UBX-CFG-INF");
	}

	if (is_ubx_cfg_itfm(header)) {
		return ("UBX-CFG-ITFM");
	}

	if (is_ubx_cfg_logfilter(header)) {
		return ("UBX-CFG-LOGFILTER");
	}

	if (is_ubx_cfg_msg(header)) {
		return ("UBX-CFG-MSG");
	}

	if (is_ubx_cfg_nav5(header)) {
		return ("UBX-CFG-NAV5");
	}

	if (is_ubx_cfg_navx5(header)) {
		return ("UBX-CFG-NAVX5");
	}

	if (is_ubx_cfg_nmea(header)) {
		return ("UBX-CFG-NMEA");
	}

	if (is_ubx_cfg_odo(header)) {
		return ("UBX-CFG-ODO");
	}

	if (is_ubx_cfg_pm2(header)) {
		return ("UBX-CFG-PM2");
	}

	if (is_ubx_cfg_pms(header)) {
		return ("UBX-CFG-PMS");
	}

	if (is_ubx_cfg_prt(header)) {
		return ("UBX-CFG-PRT");
	}

	if (is_ubx_cfg_pwr(header)) {
		return ("UBX-CFG-PWR");
	}

	if (is_ubx_cfg_rate(header)) {
		return ("UBX-CFG-RATE");
	}

	if (is_ubx_cfg_rinv(header)) {
		return ("UBX-CFG-RINV");
	}

	if (is_ubx_cfg_rst(header)) {
		return ("UBX-CFG-RST");
	}

	if (is_ubx_cfg_rxm(header)) {
		return ("UBX-CFG-RXM");
	}

	if (is_ubx_cfg_sbas(header)) {
		return ("UBX-CFG-SBAS");
	}

	if (is_ubx_cfg_smgr(header)) {
		return ("UBX-CFG-SMGR");
	}

	if (is_ubx_cfg_tmode2(header)) {
		return ("UBX-CFG-TMODE2");
	}

	if (is_ubx_cfg_tmode3(header)) {
		return ("UBX-CFG-TMODE3");
	}

	if (is_ubx_cfg_tp5(header)) {
		return ("UBX-CFG-TP5");
	}

	if (is_ubx_cfg_txslot(header)) {
		return ("UBX-CFG-TXSLOT");
	}

	if (is_ubx_cfg_usb(header)) {
		return ("UBX-CFG-USB");
	}

	if (is_ubx_esf_ins(header)) {
		return ("UBX-ESF-INS");
	}

	if (is_ubx_esf_meas(header)) {
		return ("UBX-ESF-MEAS");
	}

	if (is_ubx_esf_raw(header)) {
		return ("UBX-ESF-RAW");
	}

	if (is_ubx_esf_status(header)) {
		return ("UBX-ESF-STATUS");
	}

	if (is_ubx_hnr_pvt(header)) {
		return ("UBX-HNR-PVT");
	}

	if (is_ubx_inf_debug(header)) {
		return ("UBX-INF-DEBUG");
	}

	if (is_ubx_inf_error(header)) {
		return ("UBX-INF-ERROR");
	}

	if (is_ubx_inf_notice(header)) {
		return ("UBX-INF-NOTICE");
	}

	if (is_ubx_inf_test(header)) {
		return ("UBX-INF-TEST");
	}

	if (is_ubx_inf_warning(header)) {
		return ("UBX-INF-WARNING");
	}

	if (is_ubx_log_create(header)) {
		return ("UBX-LOG-CREATE");
	}

	if (is_ubx_log_erase(header)) {
		return ("UBX-LOG-ERASE");
	}

	if (is_ubx_log_findtime(header)) {
		return ("UBX-LOG-FINDTIME");
	}

	if (is_ubx_log_info(header)) {
		return ("UBX-LOG-INFO");
	}

	if (is_ubx_log_retrieve(header)) {
		return ("UBX-LOG-RETRIEVE");
	}

	if (is_ubx_log_string(header)) {
		return ("UBX-LOG-STRING");
	}

	if (is_ubx_mga_ack(header)) {
		return ("UBX-MGA-ACK");
	}

	if (is_ubx_mga_ano(header)) {
		return ("UBX-MGA-ANO");
	}

	if (is_ubx_mga_bds(header)) {
		return ("UBX-MGA-BDS");
	}

	if (is_ubx_mga_dbd(header)) {
		return ("UBX-MGA-DBD");
	}

	if (is_ubx_mga_flash(header)) {
		return ("UBX-MGA-FLASH");
	}

	if (is_ubx_mga_gal(header)) {
		return ("UBX-MGA-GAL");
	}

	if (is_ubx_mga_glo(header)) {
		return ("UBX-MGA-GLO");
	}

	if (is_ubx_mga_gps(header)) {
		return ("UBX-MGA-GPS");
	}

	if (is_ubx_mga_ini(header)) {
		return ("UBX-MGA-INI");
	}

	if (is_ubx_mga_qzss(header)) {
		return ("UBX-MGA-QZSS");
	}

	if (is_ubx_mon_gnss(header)) {
		return ("UBX-MON-GNSS");
	}

	if (is_ubx_mon_hw2(header)) {
		return ("UBX-MON-HW2");
	}

	if (is_ubx_mon_hw(header)) {
		return ("UBX-MON-HW");
	}

	if (is_ubx_mon_io(header)) {
		return ("UBX-MON-IO");
	}

	if (is_ubx_mon_msgpp(header)) {
		return ("UBX-MON-MSGPP");
	}

	if (is_ubx_mon_patch(header)) {
		return ("UBX-MON-PATCH");
	}

	if (is_ubx_mon_rxbuf(header)) {
		return ("UBX-MON-RXBUF");
	}

	if (is_ubx_mon_rxr(header)) {
		return ("UBX-MON-RXR");
	}

	if (is_ubx_mon_smgr(header)) {
		return ("UBX-MON-SMGR");
	}

	if (is_ubx_mon_txbuf(header)) {
		return ("UBX-MON-TXBUF");
	}

	if (is_ubx_mon_ver(header)) {
		return ("UBX-MON-VER");
	}

	if (is_ubx_nav_aopstatus(header)) {
		return ("UBX-NAV-AOPSTATUS");
	}

	if (is_ubx_nav_att(header)) {
		return ("UBX-NAV-ATT");
	}

	if (is_ubx_nav_clock(header)) {
		return ("UBX-NAV-CLOCK");
	}

	if (is_ubx_nav_dgps(header)) {
		return ("UBX-NAV-DGPS");
	}

	if (is_ubx_nav_dop(header)) {
		return ("UBX-NAV-DOP");
	}

	if (is_ubx_nav_eoe(header)) {
		return ("UBX-NAV-EOE");
	}

	if (is_ubx_nav_geofence(header)) {
		return ("UBX-NAV-GEOFENCE");
	}

	if (is_ubx_nav_hpposecef(header)) {
		return ("UBX-NAV-HPPOSECEF");
	}

	if (is_ubx_nav_hpposllh(header)) {
		return ("UBX-NAV-HPPOSLLH");
	}

	if (is_ubx_nav_odo(header)) {
		return ("UBX-NAV-ODO");
	}

	if (is_ubx_nav_orb(header)) {
		return ("UBX-NAV-ORB");
	}

	if (is_ubx_nav_posecef(header)) {
		return ("UBX-NAV-POSECEF");
	}

	if (is_ubx_nav_posllh(header)) {
		return ("UBX-NAV-POSLLH");
	}

	if (is_ubx_nav_pvt(header)) {
		return ("UBX-NAV-PVT");
	}

	if (is_ubx_nav_relposned(header)) {
		return ("UBX-NAV-RELPOSNED");
	}

	if (is_ubx_nav_resetodo(header)) {
		return ("UBX-NAV-RESETODO");
	}

	if (is_ubx_nav_sat(header)) {
		return ("UBX-NAV-SAT");
	}

	if (is_ubx_nav_sbas(header)) {
		return ("UBX-NAV-SBAS");
	}

	if (is_ubx_nav_sol(header)) {
		return ("UBX-NAV-SOL");
	}

	if (is_ubx_nav_status(header)) {
		return ("UBX-NAV-STATUS");
	}

	if (is_ubx_nav_svinfo(header)) {
		return ("UBX-NAV-SVINFO");
	}

	if (is_ubx_nav_svin(header)) {
		return ("UBX-NAV-SVIN");
	}

	if (is_ubx_nav_timebds(header)) {
		return ("UBX-NAV-TIMEBDS");
	}

	if (is_ubx_nav_timegal(header)) {
		return ("UBX-NAV-TIMEGAL");
	}

	if (is_ubx_nav_timeglo(header)) {
		return ("UBX-NAV-TIMEGLO");
	}

	if (is_ubx_nav_timegps(header)) {
		return ("UBX-NAV-TIMEGPS");
	}

	if (is_ubx_nav_timels(header)) {
		return ("UBX-NAV-TIMELS");
	}

	if (is_ubx_nav_timeutc(header)) {
		return ("UBX-NAV-TIMEUTC");
	}

	if (is_ubx_nav_velecef(header)) {
		return ("UBX-NAV-VELECEF");
	}

	if (is_ubx_nav_velned(header)) {
		return ("UBX-NAV-VELNED");
	}

	if (is_ubx_rxm_imes(header)) {
		return ("UBX-RXM-IMES");
	}

	if (is_ubx_rxm_measx(header)) {
		return ("UBX-RXM-MEASX");
	}

	if (is_ubx_rxm_pmreq(header)) {
		return ("UBX-RXM-PMREQ");
	}

	if (is_ubx_rxm_rawx(header)) {
		return ("UBX-RXM-RAWX");
	}

	if (is_ubx_rxm_rlm(header)) {
		return ("UBX-RXM-RLM");
	}

	if (is_ubx_rxm_rtcm(header)) {
		return ("UBX-RXM-RTCM");
	}

	if (is_ubx_rxm_sfrbx(header)) {
		return ("UBX-RXM-SFRBX");
	}

	if (is_ubx_rxm_svsi(header)) {
		return ("UBX-RXM-SVSI");
	}

	if (is_ubx_sec_sign(header)) {
		return ("UBX-SEC-SIGN");
	}

	if (is_ubx_sec_uniqid(header)) {
		return ("UBX-SEC-UNIQID");
	}

	if (is_ubx_tim_dosc(header)) {
		return ("UBX-TIM-DOSC");
	}

	if (is_ubx_tim_fchg(header)) {
		return ("UBX-TIM-FCHG");
	}

	if (is_ubx_tim_hoc(header)) {
		return ("UBX-TIM-HOC");
	}

	if (is_ubx_tim_smeas(header)) {
		return ("UBX-TIM-SMEAS");
	}

	if (is_ubx_tim_svin(header)) {
		return ("UBX-TIM-SVIN");
	}

	if (is_ubx_tim_tm2(header)) {
		return ("UBX-TIM-TM2");
	}

	if (is_ubx_tim_tos(header)) {
		return ("UBX-TIM-TOS");
	}

	if (is_ubx_tim_tp(header)) {
		return ("UBX-TIM-TP");
	}

	if (is_ubx_tim_vcocal(header)) {
		return ("UBX-TIM-VCOCAL");
	}

	if (is_ubx_tim_vrfy(header)) {
		return ("UBX-TIM-VRFY");
	}

	if (is_ubx_upd_sos(header)) {
		return ("UBX-UPD-SOS");
	}

	return NOT_VALID_UBX_STR;
}