/*
 * OV2640 driver.
 *
 */
#ifndef __OV2640_H__
#define __OV2640_H__

#if MICROPY_HW_OV2640

#include "ov2640_regs.h"

#define OV2640_MID				0X7FA2
#define OV2640_PID				0X2642

//===========================================================================================
typedef enum {
    FRAMESIZE_INVALID = 0,
    // VGA Resolutions
    FRAMESIZE_QQQVGA,   // 80x60
    FRAMESIZE_QQVGA,    // 160x120
    FRAMESIZE_QVGA,     // 320x240
    FRAMESIZE_VGA,      // 640x480
    FRAMESIZE_WVGA,     // 720x480
    FRAMESIZE_XGA,      // 1024x768
    FRAMESIZE_UXGA,     // 1600x1200
    FRAMESIZE_END,
} framesize_t;

typedef enum {
	LCD43M = 1,
	LCD43R,
	LCD7R,
	LCD_END,
}display_lcd_t;

static const uint8_t default_regs[][2] = {
	{0xff, 0x00},
	{0x2c, 0xff},
	{0x2e, 0xdf},
	{0xff, 0x01},
	{0x3c, 0x32},

	{0x11, 0x01},
	{0x09, 0x02},
	//修改第6位，垂直翻转，或第7位，水平镜像。一共4个组合
	//{0x04, 0xD8},//水平镜像,垂直翻转
	{0x04,REG04_SET(REG04_HFLIP_IMG | REG04_HREF_EN)},
	{0x13, 0xe5},
	{0x14, 0x48},
	{0x2c, 0x0c},
	{0x33, 0x78},
	{0x3a, 0x33},
	{0x3b, 0xfB},

	{0x3e, 0x00},
	{0x43, 0x11},
	{0x16, 0x10},

	{0x39, 0x92},

	{0x35, 0xda},
	{0x22, 0x1a},
	{0x37, 0xc3},
	{0x23, 0x00},
	{0x34, 0xc0},
	{0x36, 0x1a},
	{0x06, 0x88},
	{0x07, 0xc0},
	{0x0d, 0x87},
	{0x0e, 0x41},
	{0x4c, 0x00},
 
	{0x48, 0x00},
	{0x5B, 0x00},
	{0x42, 0x03},
     
	{0x4a, 0x81},
	{0x21, 0x99},
    
	{0x24, 0x40},
	{0x25, 0x38},
	{0x26, 0x82},
	{0x5c, 0x00},
	{0x63, 0x00},
	{0x46, 0x00},
	{0x0c, 0x3c},

	{0x61, 0x70},
	{0x62, 0x80},
	{0x7c, 0x05},
    
	{0x20, 0x80},
	{0x28, 0x30},
	{0x6c, 0x00},
	{0x6d, 0x80},
	{0x6e, 0x00},
	{0x70, 0x02},
	{0x71, 0x94},
	{0x73, 0xc1}, 
	{0x3d, 0x34}, 
	//{0x3d, 0x38}, 
	{0x5a, 0x57},

	{0x12, 0x00},//UXGA 1600*1200

	{0x17, 0x11},
	{0x18, 0x75},
	{0x19, 0x01},
	{0x1a, 0x97},
	{0x32, 0x36},
	{0x03, 0x0f}, 
	{0x37, 0x40},
  
	{0x4f, 0xca},
	{0x50, 0xa8},
	{0x5a, 0x23},
	{0x6d, 0x00},
	{0x6d, 0x38},

	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0},
	{0x41, 0x24},
	{0xe0, 0x14},
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd5},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82},
      
	{0xc8, 0x08},
	{0xc9, 0x80},
       
	{0x7c, 0x00},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
      
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
     
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x05},
	{0x93, 0x05},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
     
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
 
	{0xc3, 0xef},
  
	{0xa4, 0x00},
	{0xa8, 0x00},
	{0xc5, 0x11},
	{0xc6, 0x51},
	{0xbf, 0x80},
	{0xc7, 0x10},
	{0xb6, 0x66},
	{0xb8, 0xA5},
	{0xb7, 0x64},
	{0xb9, 0x7C},
	{0xb3, 0xaf},
	{0xb4, 0x97},
	{0xb5, 0xFF},
	{0xb0, 0xC5},
	{0xb1, 0x94},
	{0xb2, 0x0f},
	{0xc4, 0x5c},
        
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x8c, 0x00},
	{0x86, 0x3d},
	{0x50, 0x00},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},

	{0x5a, 0x90},
	{0x5b, 0x2C},
	{0x5c, 0x05},
 
	{0xd3, 0x02},//auto设置要小心
       
	{0xc3, 0xed},
	{0x7f, 0x00},

	{0xda, 0x09},
  
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00},

};

static const uint8_t svga_regs[][2] = {
	{ 0xff, 0x00 },
	{ 0x2c, 0xff },
	{ 0x2e, 0xdf },
	{ 0xff, 0x01 },
	{ 0x3c, 0x32 },

	{ 0x11, 0x01 },
	{ 0x09, 0x02 },
	//{ 0x04, 0xD8 },//水平镜像,垂直翻转
	{0x04,REG04_SET(REG04_HFLIP_IMG | REG04_HREF_EN)},
	{ 0x13, 0xe5 },
	{ 0x14, 0x48 },
	{ 0x2c, 0x0c },
	{ 0x33, 0x78 },
	{ 0x3a, 0x33 },
	{ 0x3b, 0xfB },

	{ 0x3e, 0x00 },
	{ 0x43, 0x11 },
	{ 0x16, 0x10 },

	{ 0x39, 0x92 },

	{ 0x35, 0xda },
	{ 0x22, 0x1a },
	{ 0x37, 0xc3 },
	{ 0x23, 0x00 },
	{ 0x34, 0xc0 },
	{ 0x36, 0x1a },
	{ 0x06, 0x88 },
	{ 0x07, 0xc0 },
	{ 0x0d, 0x87 },
	{ 0x0e, 0x41 },
	{ 0x4c, 0x00 },
	{ 0x48, 0x00 },
	{ 0x5B, 0x00 },
	{ 0x42, 0x03 },

	{ 0x4a, 0x81 },
	{ 0x21, 0x99 },

	{ 0x24, 0x40 },
	{ 0x25, 0x38 },
	{ 0x26, 0x82 },
	{ 0x5c, 0x00 },
	{ 0x63, 0x00 },
	//{ 0x46, 0x22 },
	{ 0x2a, 0x00 },
	{ 0x2b, 0x00 },
	{ 0x46, 0x00 },
	{ 0x47, 0x00 },
	{ 0x0c, 0x3c },

	{ 0x61, 0x70 },
	{ 0x62, 0x80 },
	{ 0x7c, 0x05 },

	{ 0x20, 0x80 },
	{ 0x28, 0x30 },
	{ 0x6c, 0x00 },
	{ 0x6d, 0x80 },
	{ 0x6e, 0x00 },
	{ 0x70, 0x02 },
	{ 0x71, 0x94 },
	{ 0x73, 0xc1 },

	//{ 0x3d, 0x34 }, 
	{ 0x5a, 0x57 },
	 //根据分辨率不同而设置
	{ 0x12, 0x40 },//SVGA 800*600
	{ 0x17, 0x11 },
	{ 0x18, 0x43 },
	{ 0x19, 0x00 },
	{ 0x1a, 0x4b },
	{ 0x32, 0x09 },
	{ 0x37, 0xc0 },

	{ 0x4f, 0xca },
	{ 0x50, 0xa8 },
	{ 0x5a, 0x23 },
	{ 0x6d, 0x00 },
	{ 0x3d, 0x38 },

	{ 0xff, 0x00 },
	{ 0xe5, 0x7f },
	{ 0xf9, 0xc0 },
	{ 0x41, 0x24 },
	{ 0xe0, 0x14 },
	{ 0x76, 0xff },
	{ 0x33, 0xa0 },
	{ 0x42, 0x20 },
	{ 0x43, 0x18 },
	{ 0x4c, 0x00 },
	{ 0x87, 0xd5 },
	{ 0x88, 0x3f },
	{ 0xd7, 0x03 },
	{ 0xd9, 0x10 },
	{ 0xd3, 0x82 },

	{ 0xc8, 0x08 },
	{ 0xc9, 0x80 },

	{ 0x7c, 0x00 },
	{ 0x7d, 0x00 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x48 },
	{ 0x7d, 0x48 },
	{ 0x7c, 0x08 },
	{ 0x7d, 0x20 },
	{ 0x7d, 0x10 },
	{ 0x7d, 0x0e },

	{ 0x90, 0x00 },
	{ 0x91, 0x0e },
	{ 0x91, 0x1a },
	{ 0x91, 0x31 },
	{ 0x91, 0x5a },
	{ 0x91, 0x69 },
	{ 0x91, 0x75 },
	{ 0x91, 0x7e },
	{ 0x91, 0x88 },
	{ 0x91, 0x8f },
	{ 0x91, 0x96 },
	{ 0x91, 0xa3 },
	{ 0x91, 0xaf },
	{ 0x91, 0xc4 },
	{ 0x91, 0xd7 },
	{ 0x91, 0xe8 },
	{ 0x91, 0x20 },

	{ 0x92, 0x00 },
	{ 0x93, 0x06 },
	{ 0x93, 0xe3 },
	{ 0x93, 0x05 },
	{ 0x93, 0x05 },
	{ 0x93, 0x00 },
	{ 0x93, 0x04 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },
	{ 0x93, 0x00 },

	{ 0x96, 0x00 },
	{ 0x97, 0x08 },
	{ 0x97, 0x19 },
	{ 0x97, 0x02 },
	{ 0x97, 0x0c },
	{ 0x97, 0x24 },
	{ 0x97, 0x30 },
	{ 0x97, 0x28 },
	{ 0x97, 0x26 },
	{ 0x97, 0x02 },
	{ 0x97, 0x98 },
	{ 0x97, 0x80 },
	{ 0x97, 0x00 },
	{ 0x97, 0x00 },

	{ 0xc3, 0xed },
	{ 0xa4, 0x00 },
	{ 0xa8, 0x00 },
	{ 0xc5, 0x11 },
	{ 0xc6, 0x51 },
	{ 0xbf, 0x80 },
	{ 0xc7, 0x10 },
	{ 0xb6, 0x66 },
	{ 0xb8, 0xA5 },
	{ 0xb7, 0x64 },
	{ 0xb9, 0x7C },
	{ 0xb3, 0xaf },
	{ 0xb4, 0x97 },
	{ 0xb5, 0xFF },
	{ 0xb0, 0xC5 },
	{ 0xb1, 0x94 },
	{ 0xb2, 0x0f },
	{ 0xc4, 0x5c },
	//根据分辨 率不同而设置
	{ 0xc0, 0x64 },
	{ 0xc1, 0x4B },
	{ 0x8c, 0x00 },
	{ 0x86, 0x3D },
	{ 0x50, 0x00 },
	{ 0x51, 0xC8 },
	{ 0x52, 0x96 },
	{ 0x53, 0x00 },
	{ 0x54, 0x00 },
	{ 0x55, 0x00 },
	{ 0x5a, 0xC8 },
	{ 0x5b, 0x96 },
	{ 0x5c, 0x00 },

	{ 0xd3, 0x02 },//auto设置要小心

	{ 0xc3, 0xed },
	{ 0x7f, 0x00 },

	{ 0xda, 0x09 },

	{ 0xe5, 0x1f },
	{ 0xe1, 0x67 },
	{ 0xe0, 0x00 },
	{ 0xdd, 0x7f },
	{ 0x05, 0x00 },

};

static const uint8_t rgb565_regs[][2] = {

    { BANK_SEL, BANK_SEL_DSP },
		{ 0xDA, 0x09 },
		{ 0xD7, 0x03 },
		{ 0xDF, 0x02 },
		{ 0x33, 0xa0 },
		{ 0x3C, 0x00 },
		{ 0xe1, 0x67 },
		
		{ 0xff, 0x01 }, 
		{ 0xe0, 0x00 },
		{ 0xe1, 0x00 },
		{ 0xe5, 0x00 },
		{ 0xd7, 0x00 }, 
		{ 0xda, 0x00 },
		{ 0xe0, 0x00 }, 

        
};

static const uint8_t jpeg_regs[][2] = {
        { BANK_SEL, BANK_SEL_SENSOR },
        { SCCB_RESET,0x14},
        { 0xE1,     0x77 },
        { 0xE5,     0x1F },
        { 0xD7,     0x03 },
        { IMAGE_MODE, IMAGE_MODE_JPEG_EN },
        { SCCB_RESET, 0x00 },
};
static const uint8_t yuv422_regs[][2]= 
{
		{ 0xFF, 0x00 }, 
		{ 0xDA, 0x10 },
		{ 0xD7, 0x03 },
		{ 0xDF, 0x00 },
		{ 0x33, 0x80 },
		{ 0x3C, 0x40 },
		{ 0xe1, 0x77 },
		{ 0x00, 0x00 },

};

#define NUM_BRIGHTNESS_LEVELS (5)
static const uint8_t brightness_regs[NUM_BRIGHTNESS_LEVELS + 1][5] = {
    { BPADDR, BPDATA, BPADDR, BPDATA, BPDATA },
    { 0x00, 0x04, 0x09, 0x00, 0x00 }, /* -2 */
    { 0x00, 0x04, 0x09, 0x10, 0x00 }, /* -1 */
    { 0x00, 0x04, 0x09, 0x20, 0x00 }, /*  0 */
    { 0x00, 0x04, 0x09, 0x30, 0x00 }, /* +1 */
    { 0x00, 0x04, 0x09, 0x40, 0x00 }, /* +2 */
};

#define NUM_CONTRAST_LEVELS (5)
static const uint8_t contrast_regs[NUM_CONTRAST_LEVELS + 1][7] = {
    { BPADDR, BPDATA, BPADDR, BPDATA, BPDATA, BPDATA, BPDATA },
    { 0x00, 0x04, 0x07, 0x20, 0x18, 0x34, 0x06 }, /* -2 */
    { 0x00, 0x04, 0x07, 0x20, 0x1c, 0x2a, 0x06 }, /* -1 */
    { 0x00, 0x04, 0x07, 0x20, 0x20, 0x20, 0x06 }, /*  0 */
    { 0x00, 0x04, 0x07, 0x20, 0x24, 0x16, 0x06 }, /* +1 */
    { 0x00, 0x04, 0x07, 0x20, 0x28, 0x0c, 0x06 }, /* +2 */
};

#define NUM_SATURATION_LEVELS (5)
static const uint8_t saturation_regs[NUM_SATURATION_LEVELS + 1][5] = {
    { BPADDR, BPDATA, BPADDR, BPDATA, BPDATA },
    { 0x00, 0x02, 0x03, 0x28, 0x28 }, /* -2 */
    { 0x00, 0x02, 0x03, 0x38, 0x38 }, /* -1 */
    { 0x00, 0x02, 0x03, 0x48, 0x48 }, /*  0 */
    { 0x00, 0x02, 0x03, 0x58, 0x58 }, /* +1 */
    { 0x00, 0x02, 0x03, 0x58, 0x58 }, /* +2 */
};

//===========================================================================================
extern const mp_obj_type_t sensor_ov2640_type;

extern void sccb_deinit();
extern void jpeg_data_process(void);


extern void ov2640_init(void);
extern void (*dcmi_rx_callback)(void);//DCMI DMA接收回调函数
extern DMA_HandleTypeDef   DMADMCI_Handler;        //DMA句柄


#endif

#endif // __OV2640_H__
