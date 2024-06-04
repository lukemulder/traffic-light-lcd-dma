/*****************************************************************************
* | File        :   hal_lcd_types.h
* | Author      :   Luke Mulder
* | Function    :   HAL Type Definitions for ST7789V LCD Controller
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2024-05-24
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _HAL_LCD_TYPES_H_
#define _HAL_LCD_TYPES_H_

#include <stdint.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define TO_BIG_ENDIAN_16(x) __builtin_bswap16(x)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define TO_BIG_ENDIAN_16(x) (x)
#endif

// System Function Command Table 1

#define LCD_CMD_ADDR_NOP           (uint8_t)0x00
#define LCD_CMD_ADDR_SWRESET       (uint8_t)0x01

#define LCD_CMD_ADDR_RDD_ID        (uint8_t)0x04
#define LCD_CMD_ADDR_RDD_ST        (uint8_t)0x09
#define LCD_CMD_ADDR_RDD_PM        (uint8_t)0x0A
#define LCD_CMD_ADDR_RDD_MADCTL    (uint8_t)0x0B
#define LCD_CMD_ADDR_RDD_COLMOD    (uint8_t)0x0C
#define LCD_CMD_ADDR_RDD_IM        (uint8_t)0x0D
#define LCD_CMD_ADDR_RDD_SM        (uint8_t)0x0E
#define LCD_CMD_ADDR_RDD_SDR       (uint8_t)0x0F

#define LCD_CMD_ADDR_SLP_IN        (uint8_t)0x10
#define LCD_CMD_ADDR_SLP_OUT       (uint8_t)0x11

#define LCD_CMD_ADDR_PTL_ON        (uint8_t)0x12
#define LCD_CMD_ADDR_NOR_ON        (uint8_t)0x13
#define LCD_CMD_ADDR_INV_OFF       (uint8_t)0x20
#define LCD_CMD_ADDR_INV_ON        (uint8_t)0x21

#define LCD_CMD_ADDR_GAMSET        (uint8_t)0x26
#define LCD_CMD_ADDR_DISP_OFF      (uint8_t)0x28
#define LCD_CMD_ADDR_DISP_ON       (uint8_t)0x29
#define LCD_CMD_ADDR_COL_ADDR_SET  (uint8_t)0x2A

#define LCD_CMD_ADDR_ROW_ADDR_SET  (uint8_t)0x2B
#define LCD_CMD_ADDR_ROW_ADDR_MWR  (uint8_t)0x2C
#define LCD_CMD_ADDR_ROW_ADDR_MRD  (uint8_t)0x2E
#define LCD_CMD_ADDR_PARTIAL_AREA  (uint8_t)0x30

#define LCD_CMD_ADDR_V_SCROLL_DEF  (uint8_t)0x33
#define LCD_CMD_ADDR_TEAR_EFF_OFF  (uint8_t)0x34
#define LCD_CMD_ADDR_TEAR_EFF_ON   (uint8_t)0x35
#define LCD_CMD_ADDR_M_ACCESS_CTL  (uint8_t)0x36

#define LCD_CMD_ADDR_V_SCR_ST_ADDR (uint8_t)0x37
#define LCD_CMD_ADDR_IDLE_MODE_OFF (uint8_t)0x38
#define LCD_CMD_ADDR_IDLE_MODE_ON  (uint8_t)0x39
#define LCD_CMD_ADDR_COL_MODE      (uint8_t)0x3A

#define LCD_CMD_ADDR_ROW_ADDR_WRC  (uint8_t)0x3C
#define LCD_CMD_ADDR_ROW_ADDR_RDC  (uint8_t)0x3E
#define LCD_CMD_ADDR_SET_TEAR_SCNL (uint8_t)0x44
#define LCD_CMD_ADDR_RD_TEAR_SCNL  (uint8_t)0x45

#define LCD_CMD_ADDR_WR_DISP_BV    (uint8_t)0x51
#define LCD_CMD_ADDR_RD_DISP_BV    (uint8_t)0x52
#define LCD_CMD_ADDR_WR_CTRL_DISP  (uint8_t)0x53
#define LCD_CMD_ADDR_RD_CTRL_DISP  (uint8_t)0x54

#define LCD_CMD_ADDR_WR_CABC_CE    (uint8_t)0x55
#define LCD_CMD_ADDR_RD_CABC       (uint8_t)0x56
#define LCD_CMD_ADDR_WR_CABC_MINB  (uint8_t)0x5E
#define LCD_CMD_ADDR_RD_CABC_MINB  (uint8_t)0x5F

#define LCD_CMD_ADDR_RD_ABC_SDR    (uint8_t)0x68
#define LCD_CMD_ADDR_RD_ID1        (uint8_t)0xDA
#define LCD_CMD_ADDR_RD_ID2        (uint8_t)0xDB
#define LCD_CMD_ADDR_RD_ID3        (uint8_t)0xDC

// System Function Command Table 2

#define LCD_CMD_ADDR_RAM_CTRL      (uint8_t)0xB0
#define LCD_CMD_ADDR_RGB_CTRL      (uint8_t)0xB1
#define LCD_CMD_ADDR_PORCH_CTRL    (uint8_t)0xB2
#define LCD_CMD_ADDR_FR_CTRL1      (uint8_t)0xB3

#define LCD_CMD_ADDR_PAR_CTRL      (uint8_t)0xB5
#define LCD_CMD_ADDR_GATE_V_CTRL   (uint8_t)0xB7
#define LCD_CMD_ADDR_GATE_ADJ      (uint8_t)0xB8
#define LCD_CMD_ADDR_DGM_EN        (uint8_t)0xBA

#define LCD_CMD_ADDR_VCOM_SET      (uint8_t)0xBB
#define LCD_CMD_ADDR_POW_SAVE      (uint8_t)0xBC
#define LCD_CMD_ADDR_DLP_OFF_SAVE  (uint8_t)0xBD
#define LCD_CMD_ADDR_LCM_CTRL      (uint8_t)0xC0

#define LCD_CMD_ADDR_ID_SET        (uint8_t)0xC1
#define LCD_CMD_ADDR_VDV_VRH_EN    (uint8_t)0xC2
#define LCD_CMD_ADDR_VRH_SET       (uint8_t)0xC3
#define LCD_CMD_ADDR_VDV_SET       (uint8_t)0xC4

#define LCD_CMD_ADDR_VCOM_OFFSET   (uint8_t)0xC5
#define LCD_CMD_ADDR_FR_CTRL_2     (uint8_t)0xC6
#define LCD_CMD_ADDR_CABC_CTRL     (uint8_t)0xC7
#define LCD_CMD_ADDR_REG_SEL_1     (uint8_t)0xC8

#define LCD_CMD_ADDR_REG_SEL_2     (uint8_t)0xCA
#define LCD_CMD_ADDR_PWM_FQ_SEL    (uint8_t)0xCC
#define LCD_CMD_ADDR_PW_CTRL_1     (uint8_t)0xD0
#define LCD_CMD_ADDR_VAP_VAN_EN    (uint8_t)0xD2

#define LCD_CMD_ADDR_CMD_2_EN_0    (uint8_t)0xDF
#define LCD_CMD_ADDR_CMD_2_EN_1    (uint8_t)0x5A
#define LCD_CMD_ADDR_CMD_2_EN_2    (uint8_t)0x69
#define LCD_CMD_ADDR_CMD_2_EN_3    (uint8_t)0x02

#define LCD_CMD_ADDR_POS_V_GAM_CTL (uint8_t)0xE0
#define LCD_CMD_ADDR_NEG_V_GAM_CTL (uint8_t)0xE1
#define LCD_CMD_ADDR_D_GAM_LUT_R   (uint8_t)0xE2
#define LCD_CMD_ADDR_D_GAM_LUT_B   (uint8_t)0xE3

#define LCD_CMD_ADDR_GATE_CTRL     (uint8_t)0xE4
#define LCD_CMD_ADDR_SPI2_EN       (uint8_t)0xE7
#define LCD_CMD_ADDR_PW_CTRL_2     (uint8_t)0xE8
#define LCD_CMD_ADDR_EQ_TIME_CTRL  (uint8_t)0xE9

#define LCD_CMD_ADDR_PROG_CTRL     (uint8_t)0xEC
#define LCD_CMD_ADDR_PROG_MODE_EN  (uint8_t)0xFA
#define LCD_CMD_ADDR_NVM_SET       (uint8_t)0xFC
#define LCD_CMD_ADDR_PROG_ACT      (uint8_t)0xFE

typedef union {
    struct __attribute__((packed)) {
        uint8_t reserved: 2; // D1, D0: Reserved bits
        uint8_t MH: 1;       // D2: Display Data Latch Order
        uint8_t RGB: 1;      // D3: RGB/BGR Order
        uint8_t ML: 1;       // D4: Line Address Order
        uint8_t MV: 1;       // D5: Page/Column Order
        uint8_t MX: 1;       // D6: Column Address Order
        uint8_t MY: 1;       // D7: Page Address Order
    } regs;
    uint8_t data;
} HAL_LCD_MADCTL_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t CTRL_INTF_CL_FORMAT: 3; // D2-D0: Control Interface Color Format
        uint8_t reserved1:           1; // D3: Reserved
        uint8_t RGB_INTF_CL_FORMAT:  3; // D6-D4: RGB Interface Color Format
        uint8_t reserved0:           1; // D7: Reserved
    } regs;
    uint8_t data;
} HAL_LCD_COLMOD_REG_t;


#define COLMOD_RGB_INTERFACE_65K  0b101 // 65K of RGB Interface
#define COLMOD_RGB_INTERFACE_262K 0b110 // 262K of RGB Interface

#define COLMOD_CTRL_12B_PER_PIXEL 0b011 // 12 Bits Per Pixel
#define COLMOD_CTRL_16B_PER_PIXEL 0b101 // 16 Bits Per Pixel
#define COLMOD_CTRL_18B_PER_PIXEL 0b110 // 18 Bits Per Pixel
#define COLMOD_CTRL_16M_TRUNCATED 0b111 // 16 Truncated Bits Per Pixel

typedef union {
    struct __attribute__((packed)) {
        uint16_t COL_START; // Column Start Index
        uint16_t COL_END; // Column End Index
    } regs;
    uint8_t data[4];
} HAL_LCD_CASET_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint16_t ROW_START; // Row Start Index
        uint16_t ROW_END; // Row End Index
    } regs;
    uint8_t data[4];
} HAL_LCD_RASET_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t BPA:       7; // D0-D6: Back porch setting in normal mode. Minimum is 0x01
        uint8_t reserved0: 1; // D7: Reserved

        uint8_t FPA:       7; // D0-D6: Front porch setting in normal mode. Minimum is 0x01
        uint8_t reserved1: 1; // D7: Reserved

        uint8_t PSEN:      1; // D0: Enable separate porch control (0 disable, 1 enable)
        uint8_t reserved2: 7; // D1-D7: Reserved

        uint8_t FPB:       4; // D4-D7: Front porch setting in idle mode. Minimum is 0x01
        uint8_t BPB:       4; // D0-D3: Back porch setting in idle mode. Minimum is 0x01

        uint8_t FPC:       4; // D4-D7: Front porch setting in partial mode. Minimum is 0x01
        uint8_t BPC:       4; // D0-D3: Back porch setting in partial mode. Minimum is 0x01
    } regs;
    uint8_t data[5];
} HAL_LCD_PORCTRL_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t VGLS:      3; // Voltage Gate Low Setting
        uint8_t reserved0: 1;
        uint8_t VGHS:      3; // Voltage Gate High Setting 
        uint8_t reserved1: 1;
    } regs;
    uint8_t data;  // Total size should be 1 byte
} HAL_LCD_GCTRL_REG_t;

#define GCTRL_VGH_12_20V 0x0
#define GCTRL_VGH_12_54V 0x1
#define GCTRL_VGH_12_89V 0x2
#define GCTRL_VGH_13_26V 0x3
#define GCTRL_VGH_13_65V 0x4
#define GCTRL_VGH_14_06V 0x5
#define GCTRL_VGH_14_50V 0x6
#define GCTRL_VGH_14_97V 0x7

#define GCTRL_VGL_NEG_07_16V 0x0
#define GCTRL_VGL_NEG_07_67V 0x1
#define GCTRL_VGL_NEG_08_23V 0x2
#define GCTRL_VGL_NEG_08_87V 0x3
#define GCTRL_VGL_NEG_09_60V 0x4
#define GCTRL_VGL_NEG_10_43V 0x5
#define GCTRL_VGL_NEG_11_38V 0x6
#define GCTRL_VGL_NEG_12_50V 0x7

typedef union {
    struct __attribute__((packed)) {
        uint8_t VCOM:      6; // Common Voltage for LCD
        uint8_t reserved:  2;
    } regs;
    uint8_t data;
} HAL_LCD_VCOMS_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t XGS:       1; // D0: XOR GS setting, adjusts gray scale inversion
        uint8_t XMV:       1; // D1: XOR MV setting, changes row/column exchange
        uint8_t XMH:       1; // D2: This bit can reverse source output order and only supports RGB interface without RAM mode
        uint8_t XMX:       1; // D3: XOR MX setting, mirrors the display horizontally
        uint8_t XINV:      1; // D4: XOR inverse setting, inverts the display colors
        uint8_t XBGR:      1; // D5: XOR RGB setting, switches between RGB and BGR color order
        uint8_t XMY:       1; // D6: XOR MY setting, mirrors the display vertically
        uint8_t reserved:  1; // D7: Reserved
    } regs;
    uint8_t data;
} HAL_LCD_LCMCTRL_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t CMDEN:    1; // VDV and VRH command write enable
        uint8_t reserved: 7; // D1-D7: Reserved
    } regs;
    uint8_t data;
} HAL_LCD_VDVVRHEN_REG_t;

#define VDVVRHEN_SET_REG_FROM_NVM    0
#define VDVVRHEN_SET_REG_FROM_CMD_WR 1

typedef union {
    struct __attribute__((packed)) {
        uint8_t VRHS:     6; // VRH Setting
        uint8_t reserved: 2;
    } regs;
    uint8_t data;
} HAL_LCD_VRHS_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t VDVS:     6; // VDV Setting
        uint8_t reserved: 2;
    } regs;
    uint8_t data;
} HAL_LCD_VDVS_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t RTNA:  5;  // Frame rate control in normal mode
        uint8_t NLA:   3;  // Inversion selection in normal mode
    } regs;
    uint8_t data;
} HAL_LCD_FRCTRL2_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t DEFAULT;  // Default write of A4 must be written

        uint8_t VDS:       2;  // Drain-Source Voltage
        uint8_t reserved1: 2;  // Unused bits
        uint8_t AVCL:      2;  // Analog Voltage Ground Setting
        uint8_t AVDD:      2;  // Analog Voltage Supply Setting
    } regs;
    uint8_t data[2];  // Total size should be 2 bytes
} HAL_LCD_PWCTRL1_REG_t;

// Definitions for AVDD (Analog Power Supply Voltage)
#define AVDD_6_4V   0x0  // 6.4 Volts
#define AVDD_6_6V   0x1  // 6.6 Volts
#define AVDD_6_8V   0x2  // 6.8 Volts

// Definitions for AVCL (Analog Ground Voltage)
#define AVCL_NEG_4_4V 0x0  // -4.4 Volts
#define AVCL_NEG_4_6V 0x1  // -4.6 Volts
#define AVCL_NEG_4_8V 0x2  // -4.8 Volts
#define AVCL_NEG_5_0V 0x3  // -5.0 Volts

// Definitions for VDS (Drain-Source Voltage)
#define VDS_2_19V 0x0  // 2.19 Volts
#define VDS_2_3V  0x1  // 2.3 Volts
#define VDS_2_4V  0x2  // 2.4 Volts
#define VDS_2_51V 0x3  // 2.51 Volts

typedef union {
    struct __attribute__((packed)) {
        uint8_t VP0       : 4; // VP0[3:0]
        uint8_t VP63      : 4; // VP63[3:0]

        uint8_t VP1       : 6; // VP1[5:0]
        uint8_t reserved1 : 2; // Reserved

        uint8_t VP2       : 6; // VP2[5:0]
        uint8_t reserved2 : 2; // Unused bits

        uint8_t VP4       : 5; // VP4[4:0]
        uint8_t reserved3 : 3; // Unused bits

        uint8_t VP6       : 5; // VP6[4:0]
        uint8_t reserved4 : 3; // Unused bits

        uint8_t VP13      : 4; // VP13[3:0]
        uint8_t JP0       : 2; // JP0[1:0]
        uint8_t reserved5 : 2; // Unused bits

        uint8_t VP20      : 7; // VP20[6:0]
        uint8_t reserved6 : 1; // Unused bits

        uint8_t VP27      : 3; // VP27[2:0]
        uint8_t reserved7 : 1; // Unused bits
        uint8_t VP36      : 3; // VP36[2:0]
        uint8_t reserved8 : 1; // Unused bits

        uint8_t VP43      : 7; // VP43[6:0]
        uint8_t reserved9 : 1; // Unused bits

        uint8_t VP50      : 4; // VP50[3:0]
        uint8_t JP1       : 2; // JP1[1:0]
        uint8_t reserved10: 2; // Unused bits

        uint8_t VP57      : 5; // VP57[4:0]
        uint8_t reserved11: 3; // Unused bits

        uint8_t VP59      : 5; // VP59[4:0]
        uint8_t reserved12: 3; // Unused bits

        uint8_t VP61      : 6; // VP61[5:0]
        uint8_t reserved13: 2; // Unused bits

        uint8_t VP62      : 6; // VP62[5:0]
        uint8_t reserved14: 2; // Unused bits
    } regs;
    uint8_t data[14];
} HAL_LCD_PVGAMCTRL_REG_t;

typedef union {
    struct __attribute__((packed)) {
        uint8_t VN0       : 4; // VN0[3:0]
        uint8_t VN63      : 4; // VN63[3:0]

        uint8_t VN1       : 6; // VN1[5:0]
        uint8_t reserved1 : 2; // Unused bits to align to 8 bits

        uint8_t VN2       : 6; // VN2[5:0]
        uint8_t reserved2 : 2; // Unused bits

        uint8_t VN4       : 5; // VN4[4:0]
        uint8_t reserved3 : 3; // Unused bits

        uint8_t VN6       : 5; // VN6[4:0]
        uint8_t reserved4 : 3; // Unused bits

        uint8_t VN13      : 4; // VN13[3:0]
        uint8_t JN0       : 2; // JN0[1:0]
        uint8_t reserved5 : 2; // Unused bits

        uint8_t VN20      : 7; // VN20[6:0]
        uint8_t reserved6 : 1; // Unused bits

        uint8_t VN27      : 3; // VN27[2:0]
        uint8_t reserved7 : 1; // Unused bits
        uint8_t VN36      : 3; // VN36[2:0]
        uint8_t reserved8 : 1; // Unused bits

        uint8_t VN43      : 7; // VN43[6:0]
        uint8_t reserved9 : 1; // Unused bits

        uint8_t VN50      : 4; // VN50[3:0]
        uint8_t JN1       : 2; // JN1[1:0]
        uint8_t reserved10: 2; // Unused bits

        uint8_t VN57      : 5; // VN57[4:0]
        uint8_t reserved11: 3; // Unused bits

        uint8_t VN59      : 5; // VN59[4:0]
        uint8_t reserved12: 3; // Unused bits

        uint8_t VN61      : 6; // VN61[5:0]
        uint8_t reserved13: 2; // Unused bits

        uint8_t VN62      : 6; // VN62[5:0]
        uint8_t reserved14: 2; // Unused bits
    } regs;
    uint8_t data[14];
} HAL_LCD_NVGAMCTRL_REG_t;

#endif