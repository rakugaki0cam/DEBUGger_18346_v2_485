/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18346
        Driver Version    :  2.00
 *
 *  
 * 
 * DEBUGger_18346
 * 
 * Matrix 16key
 * color LCD 1.8" 128x160 blue 8pin ST7735
 * 
 * 2019.09.07   ver.1.01    Matrix_18346から作成    
 * 2019.09.07   ver.1.02    SDカード追加　fatfsは無理みたい
 * 2019.09.08   ver.1.03    キー入力部分改良中
 * 2019.09.11   ver.1.04    スクロールできた
 * 2019.09.12   ver.1.05    ﾀｰﾐﾅﾙ タイトル、色コード
 * 2019.09.16   ver.1.06    9600->115200bpsテスト
 * 2019.09.21   ver.1.07    長押しリセット
 * 2019.09.22   ver.1.10    テキスト表示の高速化
 * 2019.09.25   ver.1.21    アセンブラで高速描写
 * 2019.09.26   ver.1.22    テキストclsもアセンブラで
 * 2020.11.01   ver.1.30    5V対応。3.3Vレギュレータ、レベル変換モジュール追加
 *                          (UART最初の1文字化け対策に50kΩプルダウン追加 -> おかしいかも)
 * 2020.12.13   ver.1.31    起動時間短縮　起動画面とクリアをカット
 * 2021.01.03   ver.1.32    ヘッダファイル文法修正(ヘッダ内では定義しない)
 * 2022.10.25   ver.1.40    MCCcore v4.75 -> v4.85.1。　SDカードなし。RS485対応RB4にTXDE追加
 *                          コンパイルエラーがたくさんでるけどOKみたい???　　　XC8v2.32より上はコンパイルできない。
 * 2023.01.09   ver.1.41    'B'キー長押しでボーレート変更
 * 2023.01.30               間違えてRS485無しの方へボーレート変更を付け足してしまっていた
 * 
 * MCCでSDA1-RB4でwarningでるけれどバグのようなのでそのままgenerateすればオッケー
 *　　SDAの割り付けをRA6とか無いピンにしてwarningはでなくなった。
 * 
*/

#include "header.h"


uint8_t     title[] =  " DeBUGger  ver.1.41  ";
uint8_t     data[256];              //読込データ一時バッファ
uint8_t     rx_interrupt_flag;      //受信データ有りフラグ
uint8_t     matrix_x_on;            //マトリックスキーのoutput Xch
uint8_t     reset_key;              //長押しリセットキーのフラグ
//.asm
uint8_t     font_add[3];


void main(void)
{
    // initialize the device
    
    SYSTEM_Initialize();
    
    //EUSART_SetOverrunErrorHandler(overrun_error);

    LCD_CS_SetHigh();               //LCD選択オフ
    LCD_DC_SetHigh();               //LCD DC選択　データ
    
    //while(1){}
    lcd_init(); 
    
    //lcd_color_title();
    //text_print_test();
    text_init();
    matrix_key_init();
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    uint8_t i = 0;
    
    while (1){
        if (EUSART_is_rx_ready()){
            data[i]= EUSART_Read();
            if (text_esc(data[i]) == 1){
                //エスケープシーケンスのチェック
            }else { 
                text_chr(data[i]);
                i++;
            }
        }
        matrix_key();  
    }
}
                

void overrun_error(void){
    // EUSART error - restart
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
    uint8_t string1[] = "overrun error";
    text_print(string1);
}


void RS485_Write(uint8_t d){
    //RS485で書き込み
    TXDE_SetHigh();
    EUSART_Write(d);              //USART Txへ1文字出力
    while(!EUSART_is_tx_done()){
        //送信完了待ち
    }
    TXDE_SetLow();
}



/**
 End of File
*/
