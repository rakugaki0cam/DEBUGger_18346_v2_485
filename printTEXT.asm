/*
*   printTEXT.asm
*   
*   スクロールした後の下側を背景色でクリアする
*   フォントデータ読み込みし1文字表示
*
*   2019.09.23	きっちりやると遅い　背景色黒限定なら速い
*   2019.09.24	fsr1とmoviwを使って整理 Cコンパイラよりほんのちょっと速い
*   2019.09.25	1文字表示サブ  
*/
    
#include <xc.inc>
    
//サブルーチン    
GLOBAL	_spi_scroll_clearline
GLOBAL	_draw_chr

//変数    
GLOBAL	_clear_xy
GLOBAL	_font_add
GLOBAL	_pixel_color
GLOBAL  _font5x7
    
SIGNAT	scroll, 5555				//なくてもOKみたい。署名
PSECT	mytext, local, class = CODE, delta = 2	//重要な呪文!?
 
 
BF	equ	0				//SSP1STATbits.BF
Z	equ	2				//STATUSbits.Z

_spi_scroll_clearline:
//スクロール後の最下行をクリア
    
//再定義	
xs	    equ	    ((_clear_xy + 0) & 0x7f)    //x初期値　　xcに再代入用
yc	    equ	    ((_clear_xy + 1) & 0x7f)    //y初期値　　減算する
xc	    equ	    ((_clear_xy + 2) & 0x7f)    //xカウンタ　減算する
	    
    movlw   (_pixel_color & 0xff) + 3	    //背景色　[+3]
    movwf   FSR1L
    movlw   (_pixel_color >> 8) & 0x7f
    movwf   FSR1H
    
    BANKSEL _clear_xy
loopY:    
    movf    xs, w	    //loopX x値代入
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
//1文字描写(上書き)
    
//再定義	     
asc	    equ	    ((_font_add + 0) & 0x7f)
font_addL   equ	    ((_font_add + 1) & 0x7f)
font_addH   equ	    ((_font_add + 2) & 0x7f)
xf	    equ	    ((_clear_xy + 0) & 0x7f)
yf	    equ	    ((_clear_xy + 1) & 0x7f)
mask	    equ	    ((_clear_xy + 2) & 0x7f)
	
    //movf  _asc, w		    //引数としてｗレジスタに代入されてくる
    //5倍してフォントのアドレスを求める
    BANKSEL _font_add
    movwf   asc			    //保存
    movwf   font_addL
    clrf    font_addH
    clrw
    
    lslf    font_addH, f	    //addressH * 2
    lslf    font_addL, f	    //addressL * 2
    addwfc  font_addH, f	    //桁上がり
    
    lslf    font_addH, f	    //もう一回 * 2
    lslf    font_addL, f
    addwfc  font_addH, f
    
    movf    asc, w		    // + 1
    addwf   font_addL, f
    clrw
    addwfc  font_addH, f	    //桁上がり    
    
    //フォントデータ読み出し位置 FSR0
    movf    font_addL, w		//相対位置を代入
    movwf   FSR0L
    movf    font_addH, w
    movwf   FSR0H  
    movlw   (_font5x7 & 0xff)		//フォントデータ先頭アドレスをプラス
    addwf   FSR0L, f
    movlw   ((_font5x7 >> 8) & 0x7f | 0x80)	//program memory はbit7=1にする
    addwfc  FSR0H
    
    //pixel_color[0] 色データアドレス FSR1
    movlw   (_pixel_color & 0xff)	//カラーデータのアドレス
    movwf   FSR1L
    movlw   ((_pixel_color >> 8) & 0x7f)
    movwf   FSR1H
    
    BANKSEL _clear_xy
    movlw   8			//フォント縦ドット数
    movwf   yf
    movlw   1			//bit mask
    movwf   mask
    
loopYf:
    movlw   5			//フォント横ドット数
    movwf   xf
loopXf:    
    moviw   FSR0++
    andwf   mask, w		    //フォントデータのビット判定
    btfsc   STATUS, Z
    addfsr  FSR1, 3		    //背景色の時[+3]
    call    draw_1dot		    //ドット出力
    
    movlw   (_pixel_color & 0xff)   //カラーデータのアドレスにもどす
    movwf   FSR1L

    BANKSEL _clear_xy
    decfsz  xf
    bra	    loopXf
    
    //文字間のスペース1ドット
    addfsr  FSR1, 3		    ///背景色の時は+3
    call    draw_1dot
    movlw   (_pixel_color & 0xff)   //カラーデータのアドレスにもどす
    movwf   FSR1L
    
    BANKSEL _clear_xy
    decfsz  yf
    bra     mask_shift
    return
    
mask_shift:    
    lslf    mask, f		//ビットマスクを1ケタ動かす
    addfsr  FSR0, -5		//FSR0を先頭に戻す
    bra	    loopYf
   
    
    
//サブルーチン
draw_1dot:
//1ドット(3バイト)書き込み    
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
    
    