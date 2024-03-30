/*
 * printLCD.c
 * 1文字単位でのテキスト表示
 * カーソル位置で制御
 * 
 * 
 * 2019.09.11
 * 2019.09.22   speed up   SPI送信完了をSSP1STATbits.BFでやると速い
 * 2019.09.23   スクロール後の下側ライン消去を機械語モジュールで。結果遅い。
 * 2019.09.24   .cよりほんのちょっと速くなった
 * 2019.09.25   1文字描写機械語モジュール。1文字　1.5msec-->0.7msec  2倍以上速い
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

uint8_t     header_yc;              //スクロール時の固定ヘッダー行数
uint8_t     footer_yc;              //スクロール時の固定フッター行数
uint8_t     cursor_xc, cursor_yc;   //カーソル位置
int16_t     header_area_ym;         //負数との比較が出てくるのでsigned必要
int16_t     footer_area_ym;
int16_t     scroll_area_ym;
int16_t     locate_xm, locate_ym;   //printf用に変数保持
uint16_t    scroll_start_ym;            //スクロールスタートアドレスY
//.asm
uint8_t     clear_xy[3];

void text_init(void){
    //テキスト初期化
    //lcd_cls();                          //VRAM全クリア
    
    //ヘッダフッタの設定
    header_yc = 1;                                                  //ヘッダ行数
    footer_yc = 1;                                                  //フッタ行数
    //スクロールの設定
    header_area_ym = VRAM_YM_START + DISP_YM_START + header_yc * MOJI_Y_PIXEL;    //固定ヘッダ 上からライン数
    footer_area_ym = VRAM_YM_END - DISP_YM_END   + footer_yc * MOJI_Y_PIXEL;      //固定フッタ　下からライン数
    scroll_area_ym = DISP_Y_HEIGHT - (header_yc + footer_yc) * MOJI_Y_PIXEL;      //スクロール範囲
    
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_SCRLAR);
    lcd_spi_send_word(header_area_ym);
    lcd_spi_send_word(scroll_area_ym);
    lcd_spi_send_word(footer_area_ym);
    lcd_spi_close();
    
    text_color_set(BACKGROUND_COLOR, BLUE);
    text_color_set(OBJECT_COLOR, DARKGRAY);
    //uint8_t title1[] = "        ﾀｰﾐﾅﾙ        ";
    cursor_xc = 0;
    cursor_yc = 0;
    text_print(title);
    
    text_color_set(1, BLACK);           //背景色セット
    text_color_set(0, GREEN);           //文字色セット

    text_cls();                         //テキスト範囲クリア
}


//text spi直接操作　(高速処理対応　lcd_spiを使わない)
void text_spi_RAMwrite(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
    //アドレスをセットしてRAMへ書き込むコマンドまで送信
    LCD_CS_SetLow();                        //LCDチップを選択オン
    spi1_open(LCDmaster0_CONFIG);           //spiオープンは同じで
    
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
    
    //つづいてデータを書き込む　オープンのまま
}

void text_spi_close(void){
    //データ書き込み後のクロース
    while(!SSP1STATbits.BF);
    SSP1CON1bits.SSPEN = 0;
    LCD_CS_SetHigh();                       //LCDチップ選択をオフ
}


//text 画面の操作
void text_cls(void){
     //テキスト範囲内のみクリア　ヘッダフッタはクリアしない    
    clear_xy[0] = DISP_X_WIDTH;         //クリアxドット数
    clear_xy[1] = scroll_area_ym;       //クリアyドット数
    text_spi_RAMwrite(DISP_XM_START, DISP_XM_END, header_area_ym, header_area_ym + scroll_area_ym);  
    spi_scroll_clearline();              //機械語ルーチンへ
    text_spi_close();

    cursor_xc = 0;                      //カーソル位置ホームへ
    cursor_yc = header_yc;              
    scroll_start_ym = header_area_ym;             //スクロールスタートアドレスリセット
}

void text_locate_font(uint16_t xc, uint16_t yc, uint8_t asc){
    //カーソル位置にフォントを上書き    
    cursor_xc = xc;                          //カーソル座標をセット
    cursor_yc = yc;
    
    //ヘッダ、フッタ内の時とスクロール範囲内の時でわける 
    //スクロールスタートアドレスに ヘッダ行を引いた行数分のロウをプラス   
    //スタートアドレスの範囲より大きくなった時は、スタートアドレス最大値分をマイナス
    //スタートアドレスの最大値と最小値はループのようにつながっている ( = リングバッファ?) 
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
    draw_chr(asc);                      //機械語で1文字上書き描写
    text_spi_close();
}

void text_cursor_plus(void){
    //1文字分カーソルを進める
    cursor_xc++;
    if (cursor_xc > TEXT_XC_END){
        text_enter();               //復帰改行
    } 
}

void text_enter(void){
    cursor_xc = 0;
    cursor_yc++;
    
    //printf("curY:%02d   locYm:%03d\n", cursor_yc, locate_ym);   // DEBUG ///////////////
    //__delay_ms(20);

    if (cursor_yc > (TEXT_YC_END - footer_yc)){
        cursor_yc--;                //スクロールウインドウ内の最終行へもどす
        //text_scroll(MOJI_Y_PIXEL);        //スクロール
        text_scroll(8);        //スクロール
    }
}

void text_scroll(uint8_t scroll_y){
    //上へ1行スクロール   scroll_yはドット数
    int16_t clear_line_ym;          //scroll_start_ymが0の時に-1になるので　signed必要

    //スクロールスタートアドレスがスクロール範囲の最上段のアドレスとなる。
    //スクロールを始めるとヘッダとの境目でアドレスが連続では無くなる。
    //(だんだん離れていく)
    //フッタとの境目もアドレスは不連続
    //アドレス変化範囲は、header_area_ym値 ～ (header_area_ym + scroll_area_ym)値
    scroll_start_ym += scroll_y;
    if (scroll_start_ym >= (header_area_ym + scroll_area_ym)){
        scroll_start_ym =  header_area_ym;
    }
    
    //スクロールエリア最下段の1ラインをクリア。　スクロールスタートアドレスの一つ前が最下段のライン
    //値がヘッダ内( 0 ~ header_area_my-1 )に入ってしまう時は
    //アドレスが最小値=アドレスが全て連続　= スクロールさせる前と同じ状態なので、
    //クリアするラインのアドレスはスクロールアドレス範囲の最大値
    //1ラインごとスクロールの時はscroll_yのところを1に
    clear_line_ym = scroll_start_ym - scroll_y;
    if (clear_line_ym < header_area_ym){
        clear_line_ym = header_area_ym + scroll_area_ym - scroll_y;
    }
    //スクロールスタートアドレスセット
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
    
    clear_xy[0] = DISP_X_WIDTH;         //xドット数
    clear_xy[1] = scroll_y;             //yドット数
    //clear_xy[2]はasmのカウント用
    text_spi_RAMwrite(DISP_XM_START, DISP_XM_END, clear_line_ym, clear_line_ym + scroll_y - 1);
    spi_scroll_clearline();              //機械語ルーチンへ
    text_spi_close();
}
    
void text_color_set(uint8_t bg, uint8_t cc){
    //カラーコードから文字色をセット
    //bg=0:OBJECT_COLOR
    //bg=1:BACKGROUND_COLOR
    uint8_t red, green, blue;
    red   = ColorData[cc][0];
    green = ColorData[cc][1];
    blue  = ColorData[cc][2];
    lcd_color_set(bg, red, green, blue);
}

void text_print(uint8_t *string){
    //カーソル位置に文字列を表示
    while(*string) {
        text_locate_font(cursor_xc, cursor_yc, *string++);
        //text_font(*string++);
        text_cursor_plus();
    }
}

void text_chr(uint8_t d){
    //カーソル位置に1文字表示
    text_locate_font(cursor_xc,cursor_yc, d);
    text_cursor_plus();
}

uint8_t text_esc(uint8_t esc){
    //エスケープシーケンスのチェック
    if (esc >= 0x20){
        return 0;
    }
    switch (esc){
        case 0x08:
            //1文字戻る
            cursor_xc -= 1;
            break;
        case 0x0a:
            //改行復帰
            text_enter();
            break;
        case 0x0c:
            //改ページ(クリアホーム)
            text_cls();
            break;    
        case 0x0d:
            //先頭
            cursor_xc = 0;
            break;
        case 0x1b:
            text_print_esc();
        default:
            //ESCなし
            break;
    }
    return 1;
}

//test
void text_print_test(void){
    uint16_t i;
    // カラーコードのテスト
    uint8_t e;
    e = sizeof(ColorData) / 3;
    for(i = 0; i < e; i++){
        text_color_set(1, i);               //bg=White
        text_color_set(0, BLACK);               //文字色セット
        cursor_xc = 0;
        cursor_yc = i;
        uint8_t string1[] = "   abc           ";
        text_print(string1);
    }
    __delay_ms(4000);
    
    //文字書き込みテスト
    uint8_t asc = 0x20;    
    text_color_set(1, RED);                //////debug　文字の背景色を別な色に//////
    lcd_cls();
    //ヘッダフッタの設定
    header_yc = 0;                                                      //ヘッダ行数
    footer_yc = 0;                                                      //フッタ行数
    //スクロールの設定
    header_area_ym = VRAM_YM_START + DISP_YM_START + header_yc * MOJI_Y_PIXEL;   //固定ヘッダ 上からライン数
    footer_area_ym = VRAM_YM_END - DISP_YM_END   + footer_yc * MOJI_Y_PIXEL;   //固定フッタ　下からライン数
    scroll_area_ym = DISP_Y_HEIGHT - (header_yc + footer_yc) * MOJI_Y_PIXEL;   //スクロール範囲
    
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_SCRLAR);
    lcd_spi_send_word(header_area_ym);
    lcd_spi_send_word(scroll_area_ym);
    lcd_spi_send_word(footer_area_ym);
    lcd_spi_close();
 
    text_color_set(0, BLACK);              //文字色セット
    cursor_xc = 0;
    cursor_yc = 0;
    i = 0;
    while(i < 2000){
        //if (TEXT_esc(b) == 1) return;  //エスケープシーケンスのチェック
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
