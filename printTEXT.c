/*
 * printLCD.c
 * 1�����P�ʂł̃e�L�X�g�\��
 * �J�[�\���ʒu�Ő���
 * 
 * 
 * 2019.09.11
 * 2019.09.22   speed up   SPI���M������SSP1STATbits.BF�ł��Ƒ���
 * 2019.09.23   �X�N���[����̉������C���������@�B�ꃂ�W���[���ŁB���ʒx���B
 * 2019.09.24   .c���ق�̂�����Ƒ����Ȃ���
 * 2019.09.25   1�����`�ʋ@�B�ꃂ�W���[���B1�����@1.5msec-->0.7msec  2�{�ȏ㑬��
 * 
 */
#include "header.h"
#include "printTEXT.h"


const uint8_t ColorData[17][3] = {
    {0x00, 0x00, 0x00},     //0:Black
    {0xff, 0x00, 0x00},     //1:Red
    {0xff, 0x7f, 0x00},     //2:Orenge
    {0xff, 0xff, 0x00},     //3:Yellow
    {0x7f, 0xff, 0x00},     //4:Chartreuse
    {0x00, 0xff, 0x00},     //5:Green
    {0x00, 0xff, 0x7f},     //6:SpringGreen
    {0x00, 0xff, 0xff},     //7:Cyan
    {0x00, 0x7f, 0xff},     //8:Azure
    {0x00, 0x00, 0xff},     //9:Blue
    {0x7f, 0x00, 0xff},     //10:Violet
    {0xff, 0x00, 0xff},     //11:Magenta
    {0xff, 0x00, 0x7f},     //12:Pink
    {0x3f, 0x3f, 0x3f},     //13:DarkGray
    {0x7f, 0x7f, 0x7f},     //14:Gray
    {0xbf, 0xbf, 0xbf},     //15:lightGray
    {0xff, 0xff, 0xff}      //16:White
};

uint8_t     header_yc;              //�X�N���[�����̌Œ�w�b�_�[�s��
uint8_t     footer_yc;              //�X�N���[�����̌Œ�t�b�^�[�s��
uint8_t     cursor_xc, cursor_yc;   //�J�[�\���ʒu
int16_t     header_area_ym;         //�����Ƃ̔�r���o�Ă���̂�signed�K�v
int16_t     footer_area_ym;
int16_t     scroll_area_ym;
int16_t     locate_xm, locate_ym;   //printf�p�ɕϐ��ێ�
uint16_t    scroll_start_ym;            //�X�N���[���X�^�[�g�A�h���XY
//.asm
uint8_t     clear_xy[3];

void text_init(void){
    //�e�L�X�g������
    //lcd_cls();                          //VRAM�S�N���A
    
    //�w�b�_�t�b�^�̐ݒ�
    header_yc = 1;                                                  //�w�b�_�s��
    footer_yc = 1;                                                  //�t�b�^�s��
    //�X�N���[���̐ݒ�
    header_area_ym = VRAM_YM_START + DISP_YM_START + header_yc * MOJI_Y_PIXEL;    //�Œ�w�b�_ �ォ�烉�C����
    footer_area_ym = VRAM_YM_END - DISP_YM_END   + footer_yc * MOJI_Y_PIXEL;      //�Œ�t�b�^�@�����烉�C����
    scroll_area_ym = DISP_Y_HEIGHT - (header_yc + footer_yc) * MOJI_Y_PIXEL;      //�X�N���[���͈�
    
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_SCRLAR);
    lcd_spi_send_word(header_area_ym);
    lcd_spi_send_word(scroll_area_ym);
    lcd_spi_send_word(footer_area_ym);
    lcd_spi_close();
    
    text_color_set(BACKGROUND_COLOR, BLUE);
    text_color_set(OBJECT_COLOR, DARKGRAY);
    //uint8_t title1[] = "        �����        ";
    cursor_xc = 0;
    cursor_yc = 0;
    text_print(title);
    
    text_color_set(1, BLACK);           //�w�i�F�Z�b�g
    text_color_set(0, GREEN);           //�����F�Z�b�g

    text_cls();                         //�e�L�X�g�͈̓N���A
}


//text spi���ڑ���@(���������Ή��@lcd_spi���g��Ȃ�)
void text_spi_RAMwrite(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
    //�A�h���X���Z�b�g����RAM�֏������ރR�}���h�܂ő��M
    LCD_CS_SetLow();                        //LCD�`�b�v��I���I��
    spi1_open(LCDmaster0_CONFIG);           //spi�I�[�v���͓�����
    
    LCD_DC_SetLow();
    SSP1BUF = LCD_CMD_CASET;
    while(!SSP1STATbits.BF);
    LCD_DC_SetHigh();
    SSP1BUF = (uint8_t)(x1 >> 8);
    while(!SSP1STATbits.BF);
    SSP1BUF = (uint8_t)x1;
    while(!SSP1STATbits.BF);   
    SSP1BUF = (uint8_t)(x2 >> 8);
    while(!SSP1STATbits.BF);
    SSP1BUF = (uint8_t)x2;
    while(!SSP1STATbits.BF);
    
    LCD_DC_SetLow();
    SSP1BUF = LCD_CMD_RASET;
    while(!SSP1STATbits.BF);
    LCD_DC_SetHigh(); 
    SSP1BUF = (uint8_t)(y1 >> 8);
    while(!SSP1STATbits.BF);
    SSP1BUF = (uint8_t)y1;
    while(!SSP1STATbits.BF);
    SSP1BUF = (uint8_t)(y2 >> 8);
    while(!SSP1STATbits.BF);
    SSP1BUF = (uint8_t)y2;
    while(!SSP1STATbits.BF);
    
    LCD_DC_SetLow();
    SSP1BUF = LCD_CMD_RAMWR;
    while(!SSP1STATbits.BF);
    LCD_DC_SetHigh();
    
    //�Â��ăf�[�^���������ށ@�I�[�v���̂܂�
}

void text_spi_close(void){
    //�f�[�^�������݌�̃N���[�X
    while(!SSP1STATbits.BF);
    SSP1CON1bits.SSPEN = 0;
    LCD_CS_SetHigh();                       //LCD�`�b�v�I�����I�t
}


//text ��ʂ̑���
void text_cls(void){
     //�e�L�X�g�͈͓��̂݃N���A�@�w�b�_�t�b�^�̓N���A���Ȃ�    
    clear_xy[0] = DISP_X_WIDTH;         //�N���Ax�h�b�g��
    clear_xy[1] = scroll_area_ym;       //�N���Ay�h�b�g��
    text_spi_RAMwrite(DISP_XM_START, DISP_XM_END, header_area_ym, header_area_ym + scroll_area_ym);  
    spi_scroll_clearline();              //�@�B�ꃋ�[�`����
    text_spi_close();

    cursor_xc = 0;                      //�J�[�\���ʒu�z�[����
    cursor_yc = header_yc;              
    scroll_start_ym = header_area_ym;             //�X�N���[���X�^�[�g�A�h���X���Z�b�g
}

void text_locate_font(uint16_t xc, uint16_t yc, uint8_t asc){
    //�J�[�\���ʒu�Ƀt�H���g���㏑��    
    cursor_xc = xc;                          //�J�[�\�����W���Z�b�g
    cursor_yc = yc;
    
    //�w�b�_�A�t�b�^���̎��ƃX�N���[���͈͓��̎��ł킯�� 
    //�X�N���[���X�^�[�g�A�h���X�� �w�b�_�s���������s�����̃��E���v���X   
    //�X�^�[�g�A�h���X�͈̔͂��傫���Ȃ������́A�X�^�[�g�A�h���X�ő�l�����}�C�i�X
    //�X�^�[�g�A�h���X�̍ő�l�ƍŏ��l�̓��[�v�̂悤�ɂȂ����Ă��� ( = �����O�o�b�t�@?) 
    locate_xm = DISP_XM_START + cursor_xc * MOJI_X_PIXEL;
    if ((cursor_yc <  header_yc) | (cursor_yc > (TEXT_YC_END - footer_yc))){    
        locate_ym = DISP_YM_START + cursor_yc * MOJI_Y_PIXEL;
    }else {                                                                                                    
        locate_ym = scroll_start_ym + (cursor_yc - header_yc) * MOJI_Y_PIXEL;            
        if (locate_ym >= (scroll_area_ym + header_area_ym)){  
            locate_ym -= scroll_area_ym;
        }
    }
    text_spi_RAMwrite(locate_xm, locate_xm + MOJI_X_PIXEL - 1, locate_ym, locate_ym + MOJI_Y_PIXEL - 1);
    draw_chr(asc);                      //�@�B���1�����㏑���`��
    text_spi_close();
}

void text_cursor_plus(void){
    //1�������J�[�\����i�߂�
    cursor_xc++;
    if (cursor_xc > TEXT_XC_END){
        text_enter();               //���A���s
    } 
}

void text_enter(void){
    cursor_xc = 0;
    cursor_yc++;
    
    //printf("curY:%02d   locYm:%03d\n", cursor_yc, locate_ym);   // DEBUG ///////////////
    //__delay_ms(20);

    if (cursor_yc > (TEXT_YC_END - footer_yc)){
        cursor_yc--;                //�X�N���[���E�C���h�E���̍ŏI�s�ւ��ǂ�
        //text_scroll(MOJI_Y_PIXEL);        //�X�N���[��
        text_scroll(8);        //�X�N���[��
    }
}

void text_scroll(uint8_t scroll_y){
    //���1�s�X�N���[��   scroll_y�̓h�b�g��
    int16_t clear_line_ym;          //scroll_start_ym��0�̎���-1�ɂȂ�̂Ł@signed�K�v

    //�X�N���[���X�^�[�g�A�h���X���X�N���[���͈͂̍ŏ�i�̃A�h���X�ƂȂ�B
    //�X�N���[�����n�߂�ƃw�b�_�Ƃ̋��ڂŃA�h���X���A���ł͖����Ȃ�B
    //(���񂾂񗣂�Ă���)
    //�t�b�^�Ƃ̋��ڂ��A�h���X�͕s�A��
    //�A�h���X�ω��͈͂́Aheader_area_ym�l �` (header_area_ym + scroll_area_ym)�l
    scroll_start_ym += scroll_y;
    if (scroll_start_ym >= (header_area_ym + scroll_area_ym)){
        scroll_start_ym =  header_area_ym;
    }
    
    //�X�N���[���G���A�ŉ��i��1���C�����N���A�B�@�X�N���[���X�^�[�g�A�h���X�̈�O���ŉ��i�̃��C��
    //�l���w�b�_��( 0 ~ header_area_my-1 )�ɓ����Ă��܂�����
    //�A�h���X���ŏ��l=�A�h���X���S�ĘA���@= �X�N���[��������O�Ɠ�����ԂȂ̂ŁA
    //�N���A���郉�C���̃A�h���X�̓X�N���[���A�h���X�͈͂̍ő�l
    //1���C�����ƃX�N���[���̎���scroll_y�̂Ƃ����1��
    clear_line_ym = scroll_start_ym - scroll_y;
    if (clear_line_ym < header_area_ym){
        clear_line_ym = header_area_ym + scroll_area_ym - scroll_y;
    }
    //�X�N���[���X�^�[�g�A�h���X�Z�b�g
    LCD_CS_SetLow();
    spi1_open(LCDmaster0_CONFIG);
    LCD_DC_SetLow();
    SSP1BUF = LCD_CMD_VSCSAD;
    while(!SSP1STATbits.BF);
    LCD_DC_SetHigh();
    SSP1BUF = 0x00;
    while(!SSP1STATbits.BF);
    SSP1BUF = scroll_start_ym;
    while(!SSP1STATbits.BF);
    SSP1CON1bits.SSPEN = 0;
    LCD_CS_SetHigh();     
    
    //printf("ScrollStAdd:%03d\n", scroll_start_ym);   // DEBUG ///////////////
    //__delay_ms(20);
    //printf("clearlineY :%03d\n", clear_line_ym);
    //__delay_ms(20);
    
    clear_xy[0] = DISP_X_WIDTH;         //x�h�b�g��
    clear_xy[1] = scroll_y;             //y�h�b�g��
    //clear_xy[2]��asm�̃J�E���g�p
    text_spi_RAMwrite(DISP_XM_START, DISP_XM_END, clear_line_ym, clear_line_ym + scroll_y - 1);
    spi_scroll_clearline();              //�@�B�ꃋ�[�`����
    text_spi_close();
}
    
void text_color_set(uint8_t bg, uint8_t cc){
    //�J���[�R�[�h���當���F���Z�b�g
    //bg=0:OBJECT_COLOR
    //bg=1:BACKGROUND_COLOR
    uint8_t red, green, blue;
    red   = ColorData[cc][0];
    green = ColorData[cc][1];
    blue  = ColorData[cc][2];
    lcd_color_set(bg, red, green, blue);
}

void text_print(uint8_t *string){
    //�J�[�\���ʒu�ɕ������\��
    while(*string) {
        text_locate_font(cursor_xc, cursor_yc, *string++);
        //text_font(*string++);
        text_cursor_plus();
    }
}

void text_chr(uint8_t d){
    //�J�[�\���ʒu��1�����\��
    text_locate_font(cursor_xc,cursor_yc, d);
    text_cursor_plus();
}

uint8_t text_esc(uint8_t esc){
    //�G�X�P�[�v�V�[�P���X�̃`�F�b�N
    if (esc >= 0x20){
        return 0;
    }
    switch (esc){
        case 0x08:
            //1�����߂�
            cursor_xc -= 1;
            break;
        case 0x0a:
            //���s���A
            text_enter();
            break;
        case 0x0c:
            //���y�[�W(�N���A�z�[��)
            text_cls();
            break;    
        case 0x0d:
            //�擪
            cursor_xc = 0;
            break;
        case 0x1b:
            text_print_esc();
        default:
            //ESC�Ȃ�
            break;
    }
    return 1;
}

//test
void text_print_test(void){
    uint16_t i;
    // �J���[�R�[�h�̃e�X�g
    uint8_t e;
    e = sizeof(ColorData) / 3;
    for(i = 0; i < e; i++){
        text_color_set(1, i);               //bg=White
        text_color_set(0, BLACK);               //�����F�Z�b�g
        cursor_xc = 0;
        cursor_yc = i;
        uint8_t string1[] = "   abc           ";
        text_print(string1);
    }
    __delay_ms(4000);
    
    //�����������݃e�X�g
    uint8_t asc = 0x20;    
    text_color_set(1, RED);                //////debug�@�����̔w�i�F��ʂȐF��//////
    lcd_cls();
    //�w�b�_�t�b�^�̐ݒ�
    header_yc = 0;                                                      //�w�b�_�s��
    footer_yc = 0;                                                      //�t�b�^�s��
    //�X�N���[���̐ݒ�
    header_area_ym = VRAM_YM_START + DISP_YM_START + header_yc * MOJI_Y_PIXEL;   //�Œ�w�b�_ �ォ�烉�C����
    footer_area_ym = VRAM_YM_END - DISP_YM_END   + footer_yc * MOJI_Y_PIXEL;   //�Œ�t�b�^�@�����烉�C����
    scroll_area_ym = DISP_Y_HEIGHT - (header_yc + footer_yc) * MOJI_Y_PIXEL;   //�X�N���[���͈�
    
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_SCRLAR);
    lcd_spi_send_word(header_area_ym);
    lcd_spi_send_word(scroll_area_ym);
    lcd_spi_send_word(footer_area_ym);
    lcd_spi_close();
 
    text_color_set(0, BLACK);              //�����F�Z�b�g
    cursor_xc = 0;
    cursor_yc = 0;
    i = 0;
    while(i < 2000){
        //if (TEXT_esc(b) == 1) return;  //�G�X�P�[�v�V�[�P���X�̃`�F�b�N
        text_locate_font(cursor_xc, cursor_yc, asc);
        text_cursor_plus();
        asc++;
        if (asc >= 0xe0){
            asc = 0x20;
        }
        __delay_ms(10);
        i++;
    }
    
    text_color_set(0, YELLOW);
    cursor_xc = 0;
    cursor_yc = 0;
    uint8_t string2[] = "Hello World!";
    text_print(string2);
    text_enter();    
    
    __delay_ms(4000);
    
    text_color_set(1, BLACK);
    lcd_cls(); 
}
