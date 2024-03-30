/*
*   printTEXT.asm
*   
*   �X�N���[��������̉�����w�i�F�ŃN���A����
*   �t�H���g�f�[�^�ǂݍ��݂�1�����\��
*
*   2019.09.23	����������ƒx���@�w�i�F������Ȃ瑬��
*   2019.09.24	fsr1��moviw���g���Đ��� C�R���p�C�����ق�̂�����Ƒ���
*   2019.09.25	1�����\���T�u  
*/
    
#include <xc.inc>
    
//�T�u���[�`��    
GLOBAL	_spi_scroll_clearline
GLOBAL	_draw_chr

//�ϐ�    
GLOBAL	_clear_xy
GLOBAL	_font_add
GLOBAL	_pixel_color
GLOBAL  _font5x7
    
SIGNAT	scroll, 5555				//�Ȃ��Ă�OK�݂����B����
PSECT	mytext, local, class = CODE, delta = 2	//�d�v�Ȏ���!?
 
 
BF	equ	0				//SSP1STATbits.BF
Z	equ	2				//STATUSbits.Z

_spi_scroll_clearline:
//�X�N���[����̍ŉ��s���N���A
    
//�Ē�`	
xs	    equ	    ((_clear_xy + 0) & 0x7f)    //x�����l�@�@xc�ɍđ���p
yc	    equ	    ((_clear_xy + 1) & 0x7f)    //y�����l�@�@���Z����
xc	    equ	    ((_clear_xy + 2) & 0x7f)    //x�J�E���^�@���Z����
	    
    movlw   (_pixel_color & 0xff) + 3	    //�w�i�F�@[+3]
    movwf   FSR1L
    movlw   (_pixel_color >> 8) & 0x7f
    movwf   FSR1H
    
    BANKSEL _clear_xy
loopY:    
    movf    xs, w	    //loopX x�l���
    movwf   xc
loopX:
    call draw_1dot
    BANKSEL _clear_xy
    decfsz  xc, f
    bra	    loopX
    
    decfsz  yc, f
    bra	    loopY
    
    return


    
_draw_chr:
//1�����`��(�㏑��)
    
//�Ē�`	     
asc	    equ	    ((_font_add + 0) & 0x7f)
font_addL   equ	    ((_font_add + 1) & 0x7f)
font_addH   equ	    ((_font_add + 2) & 0x7f)
xf	    equ	    ((_clear_xy + 0) & 0x7f)
yf	    equ	    ((_clear_xy + 1) & 0x7f)
mask	    equ	    ((_clear_xy + 2) & 0x7f)
	
    //movf  _asc, w		    //�����Ƃ��Ă����W�X�^�ɑ������Ă���
    //5�{���ăt�H���g�̃A�h���X�����߂�
    BANKSEL _font_add
    movwf   asc			    //�ۑ�
    movwf   font_addL
    clrf    font_addH
    clrw
    
    lslf    font_addH, f	    //addressH * 2
    lslf    font_addL, f	    //addressL * 2
    addwfc  font_addH, f	    //���オ��
    
    lslf    font_addH, f	    //������� * 2
    lslf    font_addL, f
    addwfc  font_addH, f
    
    movf    asc, w		    // + 1
    addwf   font_addL, f
    clrw
    addwfc  font_addH, f	    //���オ��    
    
    //�t�H���g�f�[�^�ǂݏo���ʒu FSR0
    movf    font_addL, w		//���Έʒu����
    movwf   FSR0L
    movf    font_addH, w
    movwf   FSR0H  
    movlw   (_font5x7 & 0xff)		//�t�H���g�f�[�^�擪�A�h���X���v���X
    addwf   FSR0L, f
    movlw   ((_font5x7 >> 8) & 0x7f | 0x80)	//program memory ��bit7=1�ɂ���
    addwfc  FSR0H
    
    //pixel_color[0] �F�f�[�^�A�h���X FSR1
    movlw   (_pixel_color & 0xff)	//�J���[�f�[�^�̃A�h���X
    movwf   FSR1L
    movlw   ((_pixel_color >> 8) & 0x7f)
    movwf   FSR1H
    
    BANKSEL _clear_xy
    movlw   8			//�t�H���g�c�h�b�g��
    movwf   yf
    movlw   1			//bit mask
    movwf   mask
    
loopYf:
    movlw   5			//�t�H���g���h�b�g��
    movwf   xf
loopXf:    
    moviw   FSR0++
    andwf   mask, w		    //�t�H���g�f�[�^�̃r�b�g����
    btfsc   STATUS, Z
    addfsr  FSR1, 3		    //�w�i�F�̎�[+3]
    call    draw_1dot		    //�h�b�g�o��
    
    movlw   (_pixel_color & 0xff)   //�J���[�f�[�^�̃A�h���X�ɂ��ǂ�
    movwf   FSR1L

    BANKSEL _clear_xy
    decfsz  xf
    bra	    loopXf
    
    //�����Ԃ̃X�y�[�X1�h�b�g
    addfsr  FSR1, 3		    ///�w�i�F�̎���+3
    call    draw_1dot
    movlw   (_pixel_color & 0xff)   //�J���[�f�[�^�̃A�h���X�ɂ��ǂ�
    movwf   FSR1L
    
    BANKSEL _clear_xy
    decfsz  yf
    bra     mask_shift
    return
    
mask_shift:    
    lslf    mask, f		//�r�b�g�}�X�N��1�P�^������
    addfsr  FSR0, -5		//FSR0��擪�ɖ߂�
    bra	    loopYf
   
    
    
//�T�u���[�`��
draw_1dot:
//1�h�b�g(3�o�C�g)��������    
    BANKSEL SSP1BUF
    moviw   0[FSR1]	//(color[0] -> (w)
    movwf   SSP1BUF	//(w) -> (SSP1BUF)
wait0:
    btfss   SSP1STAT, BF
    bra	    wait0
   
    moviw   1[FSR1]	//(color[1] -> (w)
    movwf   SSP1BUF	//(w) -> (SSP1BUF)   
wait1:
    btfss   SSP1STAT, BF
    bra	    wait1
    
    moviw   2[FSR1]	//(color[2] -> (w)
    movwf   SSP1BUF	//(w) -> (SSP1BUF)
wait2:
    btfss   SSP1STAT, BF
    bra	    wait2
    
    return
    
    