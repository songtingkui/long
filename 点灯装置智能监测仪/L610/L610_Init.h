/*******************************************************************************
**                       @ Copyright 2014 - 2019                              **
**                           www.diysoon.com                                  **
**                                                                            **
*******************************************************************************/

#ifndef L610_INIT_H
#define L610_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

extern void l610_at_check(void);
extern void l610_cpin_check(void);
extern void l610_eps_check(void);
extern void l610_ip_allo(void);

extern void l610_MQTT_connect(void);
extern void l610_xinxi_shezhi(void);
extern void l610_dingyue_xiaoxi(void);
extern void l610_fabu_xiaoxi(char *data);
extern int  l610_get_dingyue(char *data, char **pOut);

#ifdef __cplusplus
}
#endif

#endif /*L610_Init_H */
