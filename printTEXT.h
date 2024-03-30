//
//  printTEXT.h
//
//  2019.09.03
//

#ifndef PRINTTEXT_H
#define PRINTTEXT_H

//色テーブル
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

//グローバル変数
extern uint8_t     header_yc;               //スクロール時の固定ヘッダー行数
extern uint8_t     footer_yc;               //スクロール時の固定フッター行数
extern uint8_t     cursor_xc, cursor_yc;    //カーソル位置



void    text_init(void);

//text spi 直接操作
void    text_spi_RAMwrite(uint16_t, uint16_t, uint16_t, uint16_t);
void    text_spi_close(void);

//text画面操作
void    text_cls(void);
void    text_locate_font(uint16_t, uint16_t, uint8_t);
void    draw_chr(uint8_t);                 //.asmアセンブラルーチン

void    text_cursor_plus(void);
void    text_enter(void);
void    text_scroll(uint8_t);
void    spi_scroll_clearline(void);         //.asmアセンブラルーチン

void    text_color_set(uint8_t, uint8_t);
void    text_print(uint8_t *);
void    text_chr(uint8_t );
uint8_t text_esc(uint8_t);

//test
void    text_print_test(void);


#endif