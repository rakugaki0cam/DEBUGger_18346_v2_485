/*
 * matrixKey.c
 * 
 * 
 * 2019.09.03  
 * 
 * TMR2割込で　10msecごとにキースキャン-->廃止
 * Y0-3ch inputをnegative割込でキーオン検出
 * 右上のキーX3Y0 ”Red” 長押し5秒でリセット
 * "B"キー長押しでボーレート変更9600<->115200bps
 * 
 * 
 * 
 */

#include "header.h"
#include "matrixKey.h"

//キー割り付け
uint8_t KeyCode[]= 
{
    '7',
    '4', 
    '1',
    '0',
            
    '8',
    '5',
    '2',
    'B',//Blue
            
    '9',
    '6',
    '3',
    'G',//Green
            
    'R',//Red
    'O',//Orange
    'Y',//Yellow
    'W' //White
};

uint8_t matrix_x_on;
uint16_t inkey;
uint16_t inkey_last;


void matrix_key_init(void){
    //割込ハンドラーの定義
    //TMR2_SetInterruptHandler(matrix_scan);//廃止
    IOCAF5_SetInterruptHandler(matrix_scan);
    IOCCF3_SetInterruptHandler(matrix_scan);
    IOCCF5_SetInterruptHandler(matrix_scan);
    IOCCF7_SetInterruptHandler(matrix_scan);
    
    //X出力を全てオフ(オープン)//廃止
    //matrixX0_SetHigh();
    //matrixX1_SetHigh();
    //matrixX2_SetHigh();
    //matrixX3_SetHigh();   
    matrixX0_SetLow();      //割り込みを見るため
    matrixX1_SetLow();      //GNDへ
    matrixX2_SetLow();
    matrixX3_SetLow(); 
    //TMR2_StartTimer();      //キースキャンの周期割込//廃止
}

void matrix_scan(void){
    uint8_t x;
    uint8_t key[4];
    matrixX0_SetHigh();     //スキャンする前に全てオープン
    matrixX1_SetHigh();
    matrixX2_SetHigh();
    matrixX3_SetHigh();   
    __delay_ms(3);
    
    for (x = 0; x <= 3; x++){
        key[x] = 0;
        switch (x) {
            case 0:
                matrixX0_SetLow();
                break;
            case 1:
                matrixX1_SetLow();
                break;
            case 2:
                matrixX2_SetLow();
                break;
            case 3:
                matrixX3_SetLow();
                break;
        }
        if (matrixY0_GetValue() == 0){key[x] = key[x] | 0b0001;}
        if (matrixY1_GetValue() == 0){key[x] = key[x] | 0b0010;}
        if (matrixY2_GetValue() == 0){key[x] = key[x] | 0b0100;}
        if (matrixY3_GetValue() == 0){key[x] = key[x] | 0b1000;}
        switch (x) {
            case 0:
                matrixX0_SetHigh();
                break;
            case 1:
                matrixX1_SetHigh();
                break;
            case 2:
                matrixX2_SetHigh();
                break;
            case 3:
                matrixX3_SetHigh();
                break;
        }  
    }
    inkey = (key[3] << 12) | (key[2] << 8) | (key[1] << 4) | key[0];
    //bit配置　上から
    //bit15                                                                      bit0
    //X3Y3,X3Y2,X3Y1,X3Y0,X2Y3,X2Y2,X2Y1,X2Y0,X1Y3,X1Y2,X1Y1,X1Y0,X0Y3,X0Y2,X0Y1,X0Y0 
    
    matrixX0_SetLow();      //割り込みを見るため
    matrixX1_SetLow();
    matrixX2_SetLow();
    matrixX3_SetLow(); 
    PIR0bits.IOCIF = 0;     //割り込みフラグクリア
    IOCAFbits.IOCAF5 = 0;
    IOCCFbits.IOCCF3 = 0;
    IOCCFbits.IOCCF5 = 0;
    IOCCFbits.IOCCF7 = 0;
}


void matrix_key(void){
    //4 x 4 = 16キー マトリクス
    uint8_t d;
    uint8_t tmp_x, tmp_y;
    
    //printf("%04X\n", TMR1_ReadTimer());     //DEBUG/////
    //__delay_ms(20);
    
    if(PIR1bits.TMR1IF == 1){
        //リセット実行　(R)長押し
        cursor_xc = 0;
        cursor_yc = 19;
        uint8_t string1[] = " *** R E S E T ***";
        text_print(string1);
        __delay_ms(1500);
        RESET();                            //リセット PickitではHaltする。
    }
    
    if (inkey == inkey_last){
        //前回と同じ場合、printf表示更新しない
        //キーが押し続けられていることの処理はここで
        if (((inkey >> 7) & 0x0001) == 1){
            key_b();
        }
    }else {
        //キーが変化した時
        if(((inkey >> 12) & 0x0001) == 0){
            //Rのキーが押されていない時はタイマーストップ
            TMR1_StopTimer();
            //printf("\nﾘｾｯﾄｶｳﾝﾄ ｽﾄｯﾌﾟ\n");         //DEBUG/////
        }
        if (((inkey >> 12) & 0x0001) == 1){
            //Rのキー　長押しでリセット
            TMR1_Reload();             
            TMR1_StartTimer();                  //タイマースタート
            //printf("\ﾘｾｯﾄｶｳﾝﾄ ｽﾀｰﾄ\n");         //DEBUG///// 
        }
        tmp_x = cursor_xc;          //カーソル位置退避
        tmp_y = cursor_yc;
        d = matrix_chr(inkey);
        if (d <= 0x20){
            d = 0x20;
        }
        text_locate_font(0, 19, d);     //キーの表示            
        cursor_xc = tmp_x;
        cursor_yc = tmp_y;
    
        //printf("key=%04x\n",inkey);     //USART Txへkeyデータ表示
        if (d > 0x20){
            RS485_Write(d);                 //RS485で1文字出力
            //EUSART_Write(d);              //USART Txへ1文字出力
        }
        inkey_last = inkey;
    }
}

uint8_t matrix_chr(uint16_t k){
    //キーフラグから文字へ変換
    //2つ以上のキーが押されている時はまだ／／／／／／／／／／／／／
    uint8_t i = 0;
    uint8_t asc;
    
    if (k == 0){
        return 0;
    }
    while(i < 16){
        if ((k & 0x0001) == 1){
            asc = KeyCode[i];
            return asc;
        }
        k = k >> 1;
        i++;
    }
    return 0;   
}

void key_b(void){
    //’B'キー長押し->ボーレート変更
    uint8_t i;
    static bool br;
    uint8_t string115200[] = "BaudRate ->115200bps ";
    uint8_t string9600[]   = "BaudRate ->  9600bps ";
    uint8_t stringclear[]  = "                     ";


    for(i = 0; i < 20; i++){
        __delay_ms(100);
        if (((inkey >> 7) & 0x0001) == 0){
            return;
        }
    }
    //長押し成立
    cursor_xc = 0;
    cursor_yc = 19;
    if (br == 0){
        text_print(string115200);
        SP1BRGL = 0x44;
        SP1BRGH = 0x00;
        br = 1;
    }else{
        text_print(string9600);
        SP1BRGL = 0x40;
        SP1BRGH = 0x03;
        br = 0;
    }
    __delay_ms(2000);
    while((((inkey >> 7) & 0x0001) == 1)){
        //キーを離すまで待つ
    }
    text_print(stringclear);
    cursor_xc = 0;
    cursor_yc = 1;
    
}