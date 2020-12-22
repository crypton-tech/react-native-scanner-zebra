/******************************************************************************
 *
 *       Copyright Zebra Technologies Corporation. 2014 - 2015
 *
 *       The copyright notice above does not evidence any
 *       actual or intended publication of such source code.
 *       The code contains Zebra Technologies
 *       Confidential Proprietary Information.
 *
 *
 *  Description:   RMDAttributes.h
 *
 *  Notes:
 *
 ******************************************************************************/

#ifndef __RMD_ATTRIBUTES_H__
#define __RMD_ATTRIBUTES_H__

/* nrv364: in accordance with Motorola Scanner SDK Attribute Data Dictionary 72E-149786-01 */
/* attribute identifiers */
#define RMD_ATTR_MODEL_NUMBER                           533
#define RMD_ATTR_SERIAL_NUMBER                          534
#define RMD_ATTR_ID_SERIAL_NUMBER                       0x0216
#define RMD_ATTR_ID_NAME                                0x025F
#define RMD_ATTR_BEEPER_VOLUME                          140
#define RMD_ATTR_BEEPER_FREQUENCY                       145
#define RMD_ATTR_ACTION_BEEPER_LED                      6000
#define RMD_ATTR_SYM_UPC_A                              1
#define RMD_ATTR_SYM_UPC_E                              2
#define RMD_ATTR_SYM_UPC_E_1                            12
#define RMD_ATTR_SYM_EAN_8_JAN_8                        4
#define RMD_ATTR_SYM_EAN_13_JAN_13                      3
#define RMD_ATTR_SYM_BOOKLAND_EAN                       83
#define RMD_ATTR_SYM_CODE_128                           8
#define RMD_ATTR_SYM_UCC_EAN_128                        14
#define RMD_ATTR_SYM_CODE_39                            0
#define RMD_ATTR_SYM_CODE_93                            9
#define RMD_ATTR_SYM_CODE_11                            10
#define RMD_ATTR_SYM_INTERLEAVED_2_OF_5                 6
#define RMD_ATTR_SYM_DISCRETE_2_OF_5                    5
#define RMD_ATTR_SYM_CHINESE_2_OF_5                     408
#define RMD_ATTR_SYM_CODABAR                            7
#define RMD_ATTR_SYM_MSI                                11
#define RMD_ATTR_SYM_DATAMATRIXQR                       292
#define RMD_ATTR_SYM_PDF                                15
#define RMD_ATTR_SYM_ISBT_128                           84
#define RMD_ATTR_UCC_COUPEN_EXTENDED_CODE               85
#define RMD_ATTR_FRMWR_VERSION                       20012
#define RMD_ATTR_MFD                                   535
#define RMD_ATTR_REBOOT_AND_UNPAIR                     6045

#define RMD_ATTR_SYM_US_Postnet                         89
#define RMD_ATTR_SYM_US_Planet                          90
#define RMD_ATTR_SYM_UK_POST                            91
#define RMD_ATTR_SYM_US_POSTAL_CHECK_DIGIT              95
#define RMD_ATTR_SYM_UK_POSTAL_CHECK_DIGIT              96
#define RMD_ATTR_SYM_JAPAN_POST                        290
#define RMD_ATTR_SYM_AUS_POST                          291
#define RMD_ATTR_SYM_Netherlands_KIX                   326
#define RMD_ATTR_SYM_UPU_FICS                          611
#define RMD_ATTR_SYM_USPS_4CB_ONECODE_INTELLIGENT_MAIL 592

#define RMD_ATTR_SYM_GS1_DATABAR_14                    338
#define RMD_ATTR_SYM_GS1_DATABAR_LIMITED               339
#define RMD_ATTR_SYM_GS1_DATABAR_EXPANDED              340

#define RMD_ATTR_SYM_MICRO_PDF                         227
#define RMD_ATTR_SYM_MAXI_CODE                         294
#define RMD_ATTR_ISSN_EAN                              617
#define RMD_ATTR_MATRIX_2_OF_5                         618
#define RMD_ATTR_KOREAN_3_OF_5                         581
#define RMD_ATTR_QR_CODE                               293
#define RMD_ATTR_MICRO_QR                              573
#define RMD_ATTR_AZTEC                                 574
#define RMD_ATTR_HANXIN                               1167
#define RMD_ATTR_COMPOSITE_CC_C                        341
#define RMD_ATTR_COMPOSITE_CC_A_B                      342
#define RMD_ATTR_COMPOSITE_TLC_39                      371

/* attribute values */
#define RMD_ATTR_VALUE_BEEPER_VOLUME_LOW                2
#define RMD_ATTR_VALUE_BEEPER_VOLUME_MEDIUM             1
#define RMD_ATTR_VALUE_BEEPER_VOLUME_HIGH               0

#define RMD_ATTR_VALUE_BEEPER_FREQ_LOW                  2
#define RMD_ATTR_VALUE_BEEPER_FREQ_MEDIUM               1
#define RMD_ATTR_VALUE_BEEPER_FREQ_HIGH                 0

#define RMD_ATTR_VALUE_ACTION_HIGH_SHORT_BEEP_1         0
#define RMD_ATTR_VALUE_ACTION_HIGH_SHORT_BEEP_2         1
#define RMD_ATTR_VALUE_ACTION_HIGH_SHORT_BEEP_3         2
#define RMD_ATTR_VALUE_ACTION_HIGH_SHORT_BEEP_4         3
#define RMD_ATTR_VALUE_ACTION_HIGH_SHORT_BEEP_5         4
#define RMD_ATTR_VALUE_ACTION_LOW_SHORT_BEEP_1          5
#define RMD_ATTR_VALUE_ACTION_LOW_SHORT_BEEP_2          6
#define RMD_ATTR_VALUE_ACTION_LOW_SHORT_BEEP_3          7
#define RMD_ATTR_VALUE_ACTION_LOW_SHORT_BEEP_4          8
#define RMD_ATTR_VALUE_ACTION_LOW_SHORT_BEEP_5          9
#define RMD_ATTR_VALUE_ACTION_HIGH_LONG_BEEP_1          10
#define RMD_ATTR_VALUE_ACTION_HIGH_LONG_BEEP_2          11
#define RMD_ATTR_VALUE_ACTION_HIGH_LONG_BEEP_3          12
#define RMD_ATTR_VALUE_ACTION_HIGH_LONG_BEEP_4          13
#define RMD_ATTR_VALUE_ACTION_HIGH_LONG_BEEP_5          14
#define RMD_ATTR_VALUE_ACTION_LOW_LONG_BEEP_1           15
#define RMD_ATTR_VALUE_ACTION_LOW_LONG_BEEP_2           16
#define RMD_ATTR_VALUE_ACTION_LOW_LONG_BEEP_3           17
#define RMD_ATTR_VALUE_ACTION_LOW_LONG_BEEP_4           18
#define RMD_ATTR_VALUE_ACTION_LOW_LONG_BEEP_5           19
#define RMD_ATTR_VALUE_ACTION_FAST_WARBLE_BEEP          20
#define RMD_ATTR_VALUE_ACTION_SLOW_WARBLE_BEEP          21
#define RMD_ATTR_VALUE_ACTION_HIGH_LOW_BEEP             22
#define RMD_ATTR_VALUE_ACTION_LOW_HIGH_BEEP             23
#define RMD_ATTR_VALUE_ACTION_HIGH_LOW_HIGH_BEEP        24
#define RMD_ATTR_VALUE_ACTION_LOW_HIGH_LOW_BEEP         25
#define RMD_ATTR_VALUE_ACTION_HIGH_HIGH_LOW_LOW_BEEP    26
#define RMD_ATTR_VALUE_ACTION_LED_GREEN_OFF             42
#define RMD_ATTR_VALUE_ACTION_LED_GREEN_ON              43
#define RMD_ATTR_VALUE_ACTION_LED_YELLOW_ON             45
#define RMD_ATTR_VALUE_ACTION_LED_YELLOW_OFF            46
#define RMD_ATTR_VALUE_ACTION_LED_RED_ON                47
#define RMD_ATTR_VALUE_ACTION_LED_RED_OFF               48
#define RMD_ATTR_VALUE_ACTION_FAST_BLINK                85
#define RMD_ATTR_VALUE_ACTION_FAST_BLINK_OFF            90
#define RMD_ATTR_VALUE_ACTION_REBOOT_AND_UNPAIR         1

#endif /* __RMD_ATTRIBUTES_H__ */
