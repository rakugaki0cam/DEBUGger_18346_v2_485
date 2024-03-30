/*
 *  colorLCD.h
 *  カラーLCD TFTディスプレー
 *  SPI 4線
 * 
 *  CLK     SCK1 output
 *  MOSI    SDO1 output
 *  MISO    (SDI1 input)
 *  D/C     GPIO output
 *  CS      GPIO output
 *  RESET   GPIO output
 * 
 * 
 *  2019.09.11
 * 
*/
#ifndef COLORLCD_H
#define COLORLCD_H

#include "font.h"

//ディスプレー
#define     CHIP_TYPE           ST7735
//          LCD_type            "1.8in 128x160 ST7735 Blue";
#define     DISP_COLUMN_START   2
#define     DISP_COLUMN_END     129
#define     DISP_ROW_START      1 
#define     DISP_ROW_END        160 
#define     LCD_INVERSION       0x20    // 反転表示オフ
#define     LCD_RAMCONTROL      0xd0    //メモリアクセス MY=1,MX=1,MV=0,ML=1,RGB=0:RGB,MH=0,-,-   さかさま　ピンが上ML=1が上スクロール

// チップ VRAM アドレス
#define     VRAM_XM_START       0
#define     VRAM_YM_START       0
#define     VRAM_XM_END         131     //メモリ　幅方向
#define     VRAM_YM_END         161     //メモリ　高さ方向


//ディスプレイ表示サイズ (単位pixel)
//表示範囲の設定
#define     DISP_XM_START   DISP_COLUMN_START       //左端　
#define     DISP_XM_END     DISP_COLUMN_END         //右端　
#define     DISP_YM_START   DISP_ROW_START          //上端
#define     DISP_YM_END     DISP_ROW_END            //下端
#define     DISP_X_WIDTH    (DISP_COLUMN_END - DISP_COLUMN_START + 1)    //幅ドット数
#define     DISP_Y_HEIGHT   (DISP_ROW_END - DISP_ROW_START + 1)          //高ドット数

#define     TEXT_XC_START   0                                       //左端座標
#define     TEXT_XC_END     (DISP_X_WIDTH  / MOJI_X_PIXEL) - 1      //右端座標w128:21
#define     TEXT_YC_START   0                                       //上端座標    
#define     TEXT_YC_END     (DISP_Y_HEIGHT / MOJI_Y_PIXEL) - 1      //下端座標w160:19

//カラー
#define     Color_12bit     3               //R:4 G:4 B:4
#define     Color_16bit     5               //R:5 G:6 B:5
#define     Color_18bit     6               //R:6 G:6 B:6
#define     COLORMODE       Color_18bit     //カラー選択

//ST7735 コマンド
#define     LCD_CMD_NOP         0x00    //捨てコマンド
#define     LCD_CMD_SWREST      0x01    //ソフトウェアリセット
#define     LCD_CMD_SLPIN       0x10    //スリープ
#define     LCD_CMD_SLPOUT      0x11    //スリープから復帰
#define     LCD_CMD_INVOFF      0x20    //反転表示オフ
#define     LCD_CMD_INVON       0x21    //反転表示オン
#define     LCD_CMD_DISPOFF     0x28    //ディスプレイをオフ
#define     LCD_CMD_DISPON      0x29    //ディスプレイオン
#define     LCD_CMD_CASET       0x2A    //列アドレス
#define     LCD_CMD_RASET       0x2B    //行アドレス
#define     LCD_CMD_RAMWR       0x2C    //メモリに書込
#define     LCD_CMD_SCRLAR      0x33    //垂直スクロール
#define     LCD_CMD_MADCTL      0x36    //メモリコントロール
#define     LCD_CMD_VSCSAD      0x37    //垂直スクロールスタートアドレス
#define     LCD_CMD_COLMOD      0x3A    //色の階調指定


#define     OBJECT_COLOR        0
#define     BACKGROUND_COLOR    1

void lcd_color_title(void);

//SPIバスへの操作
void lcd_spi_open(void);
void lcd_spi_close(void);   
void lcd_spi_send_command(uint8_t);
void lcd_spi_send_byte(uint8_t);
void lcd_spi_send_word(uint16_t);

//LCD表示のサブルーチン
void lcd_init(void);
void lcd_cls(void);
void lcd_color_set(uint8_t, uint8_t, uint8_t, uint8_t);
void lcd_address_set(uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_pixel(uint16_t, uint16_t);
void lcd_filled_box(uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_put_font(uint16_t, uint16_t, uint8_t);
void lcd_put_sentence(uint16_t, uint16_t, uint8_t *);


#endif //COLORLCD_H