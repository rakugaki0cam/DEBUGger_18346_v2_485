/*
 *  colorLCD.h
 *  �J���[LCD TFT�f�B�X�v���[
 *  SPI 4��
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

//�f�B�X�v���[
#define     CHIP_TYPE           ST7735
//          LCD_type            "1.8in 128x160 ST7735 Blue";
#define     DISP_COLUMN_START   2
#define     DISP_COLUMN_END     129
#define     DISP_ROW_START      1 
#define     DISP_ROW_END        160 
#define     LCD_INVERSION       0x20    // ���]�\���I�t
#define     LCD_RAMCONTROL      0xd0    //�������A�N�Z�X MY=1,MX=1,MV=0,ML=1,RGB=0:RGB,MH=0,-,-   �������܁@�s������ML=1����X�N���[��

// �`�b�v VRAM �A�h���X
#define     VRAM_XM_START       0
#define     VRAM_YM_START       0
#define     VRAM_XM_END         131     //�������@������
#define     VRAM_YM_END         161     //�������@��������


//�f�B�X�v���C�\���T�C�Y (�P��pixel)
//�\���͈͂̐ݒ�
#define     DISP_XM_START   DISP_COLUMN_START       //���[�@
#define     DISP_XM_END     DISP_COLUMN_END         //�E�[�@
#define     DISP_YM_START   DISP_ROW_START          //��[
#define     DISP_YM_END     DISP_ROW_END            //���[
#define     DISP_X_WIDTH    (DISP_COLUMN_END - DISP_COLUMN_START + 1)    //���h�b�g��
#define     DISP_Y_HEIGHT   (DISP_ROW_END - DISP_ROW_START + 1)          //���h�b�g��

#define     TEXT_XC_START   0                                       //���[���W
#define     TEXT_XC_END     (DISP_X_WIDTH  / MOJI_X_PIXEL) - 1      //�E�[���Ww128:21
#define     TEXT_YC_START   0                                       //��[���W    
#define     TEXT_YC_END     (DISP_Y_HEIGHT / MOJI_Y_PIXEL) - 1      //���[���Ww160:19

//�J���[
#define     Color_12bit     3               //R:4 G:4 B:4
#define     Color_16bit     5               //R:5 G:6 B:5
#define     Color_18bit     6               //R:6 G:6 B:6
#define     COLORMODE       Color_18bit     //�J���[�I��

//ST7735 �R�}���h
#define     LCD_CMD_NOP         0x00    //�̂ăR�}���h
#define     LCD_CMD_SWREST      0x01    //�\�t�g�E�F�A���Z�b�g
#define     LCD_CMD_SLPIN       0x10    //�X���[�v
#define     LCD_CMD_SLPOUT      0x11    //�X���[�v���畜�A
#define     LCD_CMD_INVOFF      0x20    //���]�\���I�t
#define     LCD_CMD_INVON       0x21    //���]�\���I��
#define     LCD_CMD_DISPOFF     0x28    //�f�B�X�v���C���I�t
#define     LCD_CMD_DISPON      0x29    //�f�B�X�v���C�I��
#define     LCD_CMD_CASET       0x2A    //��A�h���X
#define     LCD_CMD_RASET       0x2B    //�s�A�h���X
#define     LCD_CMD_RAMWR       0x2C    //�������ɏ���
#define     LCD_CMD_SCRLAR      0x33    //�����X�N���[��
#define     LCD_CMD_MADCTL      0x36    //�������R���g���[��
#define     LCD_CMD_VSCSAD      0x37    //�����X�N���[���X�^�[�g�A�h���X
#define     LCD_CMD_COLMOD      0x3A    //�F�̊K���w��


#define     OBJECT_COLOR        0
#define     BACKGROUND_COLOR    1

void lcd_color_title(void);

//SPI�o�X�ւ̑���
void lcd_spi_open(void);
void lcd_spi_close(void);   
void lcd_spi_send_command(uint8_t);
void lcd_spi_send_byte(uint8_t);
void lcd_spi_send_word(uint16_t);

//LCD�\���̃T�u���[�`��
void lcd_init(void);
void lcd_cls(void);
void lcd_color_set(uint8_t, uint8_t, uint8_t, uint8_t);
void lcd_address_set(uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_pixel(uint16_t, uint16_t);
void lcd_filled_box(uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_put_font(uint16_t, uint16_t, uint8_t);
void lcd_put_sentence(uint16_t, uint16_t, uint8_t *);


#endif //COLORLCD_H