//
//  printTEXT.h
//
//  2019.09.03
//

#ifndef PRINTTEXT_H
#define PRINTTEXT_H

//�F�e�[�u��
enum ColorCode {
    BLACK,
    RED,
    ORANGE,
    YELLOW,
    CHARTREUSE,
    GREEN,
    SPRINGGREEN,
    CYAN,
    AZURE,
    BLUE,
    VIOLET,
    MAGENTA,
    PINK,
    DARKGRAY,
    GRAY,
    LIGHTGRAY,
    WHITE
};

//�O���[�o���ϐ�
extern uint8_t     header_yc;               //�X�N���[�����̌Œ�w�b�_�[�s��
extern uint8_t     footer_yc;               //�X�N���[�����̌Œ�t�b�^�[�s��
extern uint8_t     cursor_xc, cursor_yc;    //�J�[�\���ʒu



void    text_init(void);

//text spi ���ڑ���
void    text_spi_RAMwrite(uint16_t, uint16_t, uint16_t, uint16_t);
void    text_spi_close(void);

//text��ʑ���
void    text_cls(void);
void    text_locate_font(uint16_t, uint16_t, uint8_t);
void    draw_chr(uint8_t);                 //.asm�A�Z���u�����[�`��

void    text_cursor_plus(void);
void    text_enter(void);
void    text_scroll(uint8_t);
void    spi_scroll_clearline(void);         //.asm�A�Z���u�����[�`��

void    text_color_set(uint8_t, uint8_t);
void    text_print(uint8_t *);
void    text_chr(uint8_t );
uint8_t text_esc(uint8_t);

//test
void    text_print_test(void);


#endif