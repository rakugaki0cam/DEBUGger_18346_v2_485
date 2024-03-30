/*
 * matrixKey.c
 * 
 * 
 * 2019.09.03  
 * 
 * TMR2�����Ł@10msec���ƂɃL�[�X�L����-->�p�~
 * Y0-3ch input��negative�����ŃL�[�I�����o
 * �E��̃L�[X3Y0 �hRed�h ������5�b�Ń��Z�b�g
 * "B"�L�[�������Ń{�[���[�g�ύX9600<->115200bps
 * 
 * 
 * 
 */

#include "header.h"
#include "matrixKey.h"

//�L�[����t��
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
    //�����n���h���[�̒�`
    //TMR2_SetInterruptHandler(matrix_scan);//�p�~
    IOCAF5_SetInterruptHandler(matrix_scan);
    IOCCF3_SetInterruptHandler(matrix_scan);
    IOCCF5_SetInterruptHandler(matrix_scan);
    IOCCF7_SetInterruptHandler(matrix_scan);
    
    //X�o�͂�S�ăI�t(�I�[�v��)//�p�~
    //matrixX0_SetHigh();
    //matrixX1_SetHigh();
    //matrixX2_SetHigh();
    //matrixX3_SetHigh();   
    matrixX0_SetLow();      //���荞�݂����邽��
    matrixX1_SetLow();      //GND��
    matrixX2_SetLow();
    matrixX3_SetLow(); 
    //TMR2_StartTimer();      //�L�[�X�L�����̎�������//�p�~
}

void matrix_scan(void){
    uint8_t x;
    uint8_t key[4];
    matrixX0_SetHigh();     //�X�L��������O�ɑS�ăI�[�v��
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
    //bit�z�u�@�ォ��
    //bit15                                                                      bit0
    //X3Y3,X3Y2,X3Y1,X3Y0,X2Y3,X2Y2,X2Y1,X2Y0,X1Y3,X1Y2,X1Y1,X1Y0,X0Y3,X0Y2,X0Y1,X0Y0 
    
    matrixX0_SetLow();      //���荞�݂����邽��
    matrixX1_SetLow();
    matrixX2_SetLow();
    matrixX3_SetLow(); 
    PIR0bits.IOCIF = 0;     //���荞�݃t���O�N���A
    IOCAFbits.IOCAF5 = 0;
    IOCCFbits.IOCCF3 = 0;
    IOCCFbits.IOCCF5 = 0;
    IOCCFbits.IOCCF7 = 0;
}


void matrix_key(void){
    //4 x 4 = 16�L�[ �}�g���N�X
    uint8_t d;
    uint8_t tmp_x, tmp_y;
    
    //printf("%04X\n", TMR1_ReadTimer());     //DEBUG/////
    //__delay_ms(20);
    
    if(PIR1bits.TMR1IF == 1){
        //���Z�b�g���s�@(R)������
        cursor_xc = 0;
        cursor_yc = 19;
        uint8_t string1[] = " *** R E S E T ***";
        text_print(string1);
        __delay_ms(1500);
        RESET();                            //���Z�b�g Pickit�ł�Halt����B
    }
    
    if (inkey == inkey_last){
        //�O��Ɠ����ꍇ�Aprintf�\���X�V���Ȃ�
        //�L�[�������������Ă��邱�Ƃ̏����͂�����
        if (((inkey >> 7) & 0x0001) == 1){
            key_b();
        }
    }else {
        //�L�[���ω�������
        if(((inkey >> 12) & 0x0001) == 0){
            //R�̃L�[��������Ă��Ȃ����̓^�C�}�[�X�g�b�v
            TMR1_StopTimer();
            //printf("\nؾ�Ķ��� �į��\n");         //DEBUG/////
        }
        if (((inkey >> 12) & 0x0001) == 1){
            //R�̃L�[�@�������Ń��Z�b�g
            TMR1_Reload();             
            TMR1_StartTimer();                  //�^�C�}�[�X�^�[�g
            //printf("\ؾ�Ķ��� ����\n");         //DEBUG///// 
        }
        tmp_x = cursor_xc;          //�J�[�\���ʒu�ޔ�
        tmp_y = cursor_yc;
        d = matrix_chr(inkey);
        if (d <= 0x20){
            d = 0x20;
        }
        text_locate_font(0, 19, d);     //�L�[�̕\��            
        cursor_xc = tmp_x;
        cursor_yc = tmp_y;
    
        //printf("key=%04x\n",inkey);     //USART Tx��key�f�[�^�\��
        if (d > 0x20){
            RS485_Write(d);                 //RS485��1�����o��
            //EUSART_Write(d);              //USART Tx��1�����o��
        }
        inkey_last = inkey;
    }
}

uint8_t matrix_chr(uint16_t k){
    //�L�[�t���O���當���֕ϊ�
    //2�ȏ�̃L�[��������Ă��鎞�͂܂��^�^�^�^�^�^�^�^�^�^�^�^�^
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
    //�fB'�L�[������->�{�[���[�g�ύX
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
    //����������
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
        //�L�[�𗣂��܂ő҂�
    }
    text_print(stringclear);
    cursor_xc = 0;
    cursor_yc = 1;
    
}