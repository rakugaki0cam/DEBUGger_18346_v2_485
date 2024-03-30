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
 * 2019.09.07   ver.1.01    Matrix_18346����쐬    
 * 2019.09.07   ver.1.02    SD�J�[�h�ǉ��@fatfs�͖����݂���
 * 2019.09.08   ver.1.03    �L�[���͕������ǒ�
 * 2019.09.11   ver.1.04    �X�N���[���ł���
 * 2019.09.12   ver.1.05    ����� �^�C�g���A�F�R�[�h
 * 2019.09.16   ver.1.06    9600->115200bps�e�X�g
 * 2019.09.21   ver.1.07    ���������Z�b�g
 * 2019.09.22   ver.1.10    �e�L�X�g�\���̍�����
 * 2019.09.25   ver.1.21    �A�Z���u���ō����`��
 * 2019.09.26   ver.1.22    �e�L�X�gcls���A�Z���u����
 * 2020.11.01   ver.1.30    5V�Ή��B3.3V���M�����[�^�A���x���ϊ����W���[���ǉ�
 *                          (UART�ŏ���1���������΍��50k���v���_�E���ǉ� -> ������������)
 * 2020.12.13   ver.1.31    �N�����ԒZ�k�@�N����ʂƃN���A���J�b�g
 * 2021.01.03   ver.1.32    �w�b�_�t�@�C�����@�C��(�w�b�_���ł͒�`���Ȃ�)
 * 2022.10.25   ver.1.40    MCCcore v4.75 -> v4.85.1�B�@SD�J�[�h�Ȃ��BRS485�Ή�RB4��TXDE�ǉ�
 *                          �R���p�C���G���[����������ł邯��OK�݂���???�@�@�@XC8v2.32����̓R���p�C���ł��Ȃ��B
 * 2023.01.09   ver.1.41    'B'�L�[�������Ń{�[���[�g�ύX
 * 2023.01.30               �ԈႦ��RS485�����̕��փ{�[���[�g�ύX��t�������Ă��܂��Ă���
 * 
 * MCC��SDA1-RB4��warning�ł邯��ǃo�O�̂悤�Ȃ̂ł��̂܂�generate����΃I�b�P�[
 *�@�@SDA�̊���t����RA6�Ƃ������s���ɂ���warning�͂łȂ��Ȃ����B
 * 
*/

#include "header.h"


uint8_t     title[] =  " DeBUGger  ver.1.41  ";
uint8_t     data[256];              //�Ǎ��f�[�^�ꎞ�o�b�t�@
uint8_t     rx_interrupt_flag;      //��M�f�[�^�L��t���O
uint8_t     matrix_x_on;            //�}�g���b�N�X�L�[��output Xch
uint8_t     reset_key;              //���������Z�b�g�L�[�̃t���O
//.asm
uint8_t     font_add[3];


void main(void)
{
    // initialize the device
    
    SYSTEM_Initialize();
    
    //EUSART_SetOverrunErrorHandler(overrun_error);

    LCD_CS_SetHigh();               //LCD�I���I�t
    LCD_DC_SetHigh();               //LCD DC�I���@�f�[�^
    
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
                //�G�X�P�[�v�V�[�P���X�̃`�F�b�N
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
    //RS485�ŏ�������
    TXDE_SetHigh();
    EUSART_Write(d);              //USART Tx��1�����o��
    while(!EUSART_is_tx_done()){
        //���M�����҂�
    }
    TXDE_SetLow();
}



/**
 End of File
*/
