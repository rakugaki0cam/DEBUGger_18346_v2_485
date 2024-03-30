/*
 * colorLCD.c
 * 
 * 1.8” 128x160
 * 
 * 2019.08.10
 * 2019.08.22   カラーモード　12、16、18ビット3種類に対応
 * 2019.09.07   DEBUGger_18346用に整理
 * 
 */

#include "header.h"
#include "colorLCD.h"


uint8_t     LCD_type[] = "1.8in 128x160 ST7735 Blue";
uint8_t     colormode_str[] = "18bit Color Mode";
uint8_t     CMD_MADCTL1;
uint8_t     pixel_color[2][3];      //[0]オブジェクト色 [1]背景色, 後ろの[3]はRGB


void lcd_color_title(void){
    uint8_t x = 0,
            y = 0,
            sq;
    uint8_t Rr = 0xff,
            Gg = 0xff,
            Bb = 0xff;
            //8ビットカラー
    
    if (DISP_X_WIDTH > DISP_Y_HEIGHT){            //sq:縦横狭い方の1/8
        sq = DISP_Y_HEIGHT >> 3;
    }else {
        sq = DISP_X_WIDTH >> 3;
    }
    lcd_color_set(OBJECT_COLOR, Rr, Gg, Bb);                    //White
    lcd_filled_box(x, y, (x + DISP_X_WIDTH - 1), (y + sq - 2));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, Rr,0,0);                        //Red
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, Rr,Gg,0);                       //Yellow
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, 0,Gg,0);                        //Green
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, 0,Gg,Bb);                       //Cyan
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, 0,0,Bb);                        //Blue
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, Rr,0,Bb);                       //Magenta
    lcd_filled_box(x, y, (x + sq - 1), (y + sq - 1));
    x += sq;
    y += sq;
    lcd_color_set(OBJECT_COLOR, 0, 0x20, 0);                    //Dark Green  
    lcd_put_sentence(6, 3, title);
    lcd_color_set(OBJECT_COLOR, Rr, (Gg >> 1), 0);                //Orange
    lcd_put_sentence(0, (y + 2), LCD_type);
    lcd_color_set(OBJECT_COLOR, Rr, 0, (Bb >> 1));                //Pink
    
    lcd_put_sentence(0, (y + 12), colormode_str);
    //__delay_ms(1000);
}

//LCD SPI関連
void lcd_spi_open(void){
    //コマンド操作するとき必要
    LCD_CS_SetLow();                        //LCDチップを選択オン
    spi1_open(LCDmaster0_CONFIG);
}

void lcd_spi_close(void){
    //CSが無いLCDでの誤作動防止対策付き
    lcd_spi_send_command(LCD_CMD_NOP);  //空コマンドを打って、メモリー書き込みを終える
    LCD_DC_SetHigh();                       //データ受信にしておけば　空読み込みとなる
    spi1_close();
    LCD_CS_SetHigh();                       //LCDチップ選択をオフ
}

void lcd_spi_send_command(uint8_t d){
    LCD_DC_SetLow();                        //コマンド
    spi1_exchangeByte(d);
}

void lcd_spi_send_byte(uint8_t d){
    LCD_DC_SetHigh();                       //8bitデータ
    spi1_exchangeByte(d);

}

void lcd_spi_send_word(uint16_t dd){
    LCD_DC_SetHigh();                       //16bitデータ
    spi1_exchangeByte((uint8_t)((dd >> 8) & 0x00FF));
    spi1_exchangeByte((uint8_t)(dd & 0x00FF));
}


//LCD操作 サブルーチン
void lcd_init(void){
    //LCD初期設定
    uint8_t i;
     
    lcd_color_set(BACKGROUND_COLOR, 0, 0, 0);              //背景色のセット->黒
    
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_SWREST);   //ソフトウェアリセット
    __delay_ms(120) ;
    lcd_spi_send_command(LCD_CMD_SLPOUT);   //スリープから復帰
    __delay_ms(120) ;
    lcd_spi_send_command(LCD_CMD_COLMOD);   //カラーモード
    lcd_spi_send_byte(COLORMODE) ;
    lcd_spi_send_command(LCD_CMD_MADCTL);   //メモリーデータアクセスコントロール
    lcd_spi_send_byte(CMD_MADCTL1 | LCD_RAMCONTROL);           
    lcd_spi_send_command(LCD_INVERSION);              //反転表示
    
    //LCD_SendCommand(0x51);                    //ディスプレイ明るさ
    //LCD_SendByte(0x10);                       //00:暗　ff:明

    // ディスプレイの表示方向を指定する処理//////////////////////////////まだ
    //LCD_DisplayDirection(4) ;

    lcd_spi_send_command(LCD_CMD_DISPON);   //ディスプレイオン 
    lcd_spi_close();
   
    lcd_cls() ;                                 //背景色でクリアする
    }

void lcd_cls(void){
    //画面クリア
    uint8_t  i;
    uint16_t mx, my;

    //メモリー全域をクリア
    lcd_spi_open();
    //メモリ全域クリア(表示内制限があるためLCD_address_setは使えない)
    lcd_spi_send_command(LCD_CMD_CASET);
    lcd_spi_send_word(VRAM_XM_START);
    lcd_spi_send_word(VRAM_XM_END);
    
    lcd_spi_send_command(LCD_CMD_RASET);
    lcd_spi_send_word(VRAM_YM_START);
    lcd_spi_send_word(VRAM_YM_END);     
    
    lcd_spi_send_command(LCD_CMD_RAMWR);
    LCD_DC_SetHigh();                          
    for (my = 0 ; my <= VRAM_YM_END ; my++) {
        for (mx = 0 ; mx <= VRAM_XM_END ; mx++) {
            spi1_exchangeByte(pixel_color[1][0]);
            spi1_exchangeByte(pixel_color[1][1]); 
            if (COLORMODE != Color_16bit){          //12bitのときには1.5倍多く書きすぎるけどOK
                spi1_exchangeByte(pixel_color[1][2]);
            }
        }
    }
    lcd_spi_close();
}

void lcd_color_set(uint8_t bg, uint8_t red, uint8_t green, uint8_t blue){
    //24ビットカラー値を書込データに変換
    //bg=0:OBJECT_COLOR
    //bg=1:BACKGROUND_COLOR
    switch (COLORMODE) {
        case Color_18bit:
            //1ドット3バイト　R6+欠2, G6+欠2, B6+欠2
            pixel_color[bg][0] = red    & 0xfc;
            pixel_color[bg][1] = green  & 0xfc;
            pixel_color[bg][2] = blue   & 0xfc;
            break;
        case Color_16bit:
            //1ドット2バイト　R5+G3upper, G3lower+B5
            pixel_color[bg][0] =  (red   & 0xf8)       | ((green & 0xe0) >> 5);
            pixel_color[bg][1] = ((green & 0x1c) << 3) |  (blue          >> 3);
            pixel_color[bg][2] = 0xff;
            break;
        case Color_12bit:
            //2ドット3バイト　aR4+aG4, aB4+bR4, bG4+bB4
            pixel_color[bg][0] =  (red   & 0xf0) | ((green & 0xf0) >> 4);
            pixel_color[bg][1] =  (blue  & 0xf0) | ((red   & 0xf0) >> 4);
            pixel_color[bg][2] =  (green & 0xf0) | ((blue  & 0xf0) >> 4);
    }      
}

void lcd_address_set(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
    //座標をセット
    //表示画面内に制限
    uint16_t tmp;
    
    if (x1 > x2){
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y1 > y2){
        tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    if (x2 > (DISP_X_WIDTH - 1)){
        x2 = DISP_X_WIDTH - 1;
    }
    if (y2 > (DISP_Y_HEIGHT - 1)){
        y2 = DISP_Y_HEIGHT - 1;
    }
    lcd_spi_open();
    
    lcd_spi_send_command(LCD_CMD_CASET);
    lcd_spi_send_word(DISP_XM_START + x1);
    lcd_spi_send_word(DISP_XM_START + x2);
    
    lcd_spi_send_command(LCD_CMD_RASET);
    lcd_spi_send_word(DISP_YM_START + y1);
    lcd_spi_send_word(DISP_YM_START + y2);
    
    lcd_spi_close();
}

void lcd_pixel(uint16_t x1, uint16_t y1){
    //1ドットうつ
    lcd_address_set(x1, x1, y1, y1);
    lcd_spi_open();
    LCD_DC_SetLow();
    spi1_exchangeByte(LCD_CMD_RAMWR);
    LCD_DC_SetHigh();
    spi1_exchangeByte(pixel_color[0][0]);      
    spi1_exchangeByte(pixel_color[0][1]);      
    if (COLORMODE == Color_18bit){
        spi1_exchangeByte(pixel_color[0][2]);
    }
    lcd_spi_close();
}

void lcd_filled_box(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    //左上(x1, y1) 右下(x2, y2)の塗りつぶし四角を描く
    uint16_t x , y;
    lcd_address_set(x1, x2, y1, y2);
    lcd_spi_open();
    lcd_spi_send_command(LCD_CMD_RAMWR);    //メモリーライトコマンド
    LCD_DC_SetHigh();                           //データ
    for (y = y1 ; y <= y2 ; y++){
        for (x = x1 ; x <= x2 ; x++) {
            spi1_exchangeByte(pixel_color[0][0]);
            spi1_exchangeByte(pixel_color[0][1]);
            if (COLORMODE != Color_16bit){
                spi1_exchangeByte(pixel_color[0][2]);
            }
        }
    }
    lcd_spi_close();
}

void lcd_put_font(uint16_t x1, uint16_t y1, uint8_t asc){
    //1文字を表示 5x7font
    //背景に重ねて表示
    uint8_t  x, y, fontdata;
   
    for (x = 0; x < 5; x++){
        fontdata = font5x7[asc][x];
        for (y = 0; y < 8; y++){
            if (((fontdata >> y) & 0x01) == 1){
                lcd_address_set((x1 + x), (x1 + x), (y1 + y), (y1 + y));
                //１ドットずつセット
                lcd_spi_open(); 
                LCD_DC_SetLow();
                spi1_exchangeByte(LCD_CMD_RAMWR);
                LCD_DC_SetHigh();
                spi1_exchangeByte(pixel_color[0][0]);
                spi1_exchangeByte(pixel_color[0][1]);
                if (COLORMODE != Color_16bit){
                    spi1_exchangeByte(pixel_color[0][2]);
                }
                lcd_spi_close();
            }
        }
    }
}

void lcd_put_sentence(uint16_t x1, uint16_t y1, uint8_t *string){
    //文字列を表示 文字間ピッチ6ドット
     while(*string) {
          lcd_put_font(x1, y1, *string++) ;
          x1 = x1 + MOJI_X_PIXEL ;             //文字ピッチ分進める
     }
}
