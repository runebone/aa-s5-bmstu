#ifndef __COLORS__H__
#define __COLORS__H__

/*
Colors:              
   R - red              
   G - green            
   B - blue             

   C - cyan
   M - magenta          
   Y - yellow           
   K - blacK            
   W - white

Styles:
   N - normal
   B - bold
   I - italic

   U - underline
   S - strikethrough
   T - change tone
*/

// Text colors (TC)
#define TCK L"\033[30m"
#define TCR L"\033[31m"
#define TCG L"\033[32m"
#define TCY L"\033[33m"
#define TCB L"\033[34m"
#define TCM L"\033[35m"
#define TCC L"\033[36m"
#define TCW L"\033[37m"

// Background colors (BC)
#define BCK L"\033[40m"
#define BCR L"\033[41m"
#define BCG L"\033[42m"
#define BCY L"\033[43m"
#define BCB L"\033[44m"
#define BCM L"\033[45m"
#define BCC L"\033[46m"
#define BCW L"\033[47m"

// Text styles (TS)
#define TSN L"\033[0m"
#define TSB L"\033[1m"
#define TST L"\033[2m"
#define TSI L"\033[3m"
#define TSU L"\033[4m"
#define TSS L"\033[9m"

// Reset color (RC) "\033[TS;TC;BCm"
#define RC L"\033[0;0;0m"

// Usage: printf(TSB TCG BCR "Hello World!\n" RC);

#endif
