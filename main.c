#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "stdio.h"
#include "keypad.h"



void process_keypad(void);
void odpocet(void);
void zobraz_pocitadlo(void);
void zobraz_sekundy(void);
void bombtimer(void);
void FinalStage(void);
void vstup(void);
void kontrola(void);
void sirenka(void);
void ledka(void);
uint16_t blink_period1=640;
const uint16_t perioda01=1000;
uint16_t posledni_cas=0;
uint16_t lasttime=0;
uint8_t text[32];
uint16_t bombnumber=0;
uint16_t pocetcisel=0;
uint16_t cas_bomby=40;
uint16_t pocitani=40;
uint16_t rezim=0;
uint16_t stisknuto;
uint8_t stav=0;
void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz z interního RC oscilátoru
GPIO_Init(GPIOB,GPIO_PIN_7,GPIO_MODE_OUT_PP_HIGH_SLOW);
GPIO_Init(GPIOG,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_SLOW);
init_milis();
lcd_init();		
keypad_init();
rezim = 1;
stav=1;
lcd_gotoxy(0,0);
	lcd_puts("insert code");
  while (1){
		process_keypad(); // obsluhujeme klávesnici
		if(bombnumber==34){
			bombtimer();
			FinalStage();
			sirenka();
			ledka();
		}
if(stav==1){
	lcd_gotoxy(0,0);
	lcd_puts("insert code");
	GPIO_WriteHigh(GPIOB,GPIO_PIN_7);
	GPIO_WriteHigh(GPIOG,GPIO_PIN_2);
	}
	
		
	}
}
void process_keypad(void){
static uint8_t minule_stisknuto=0;	
static uint16_t last_time=0; 

	if(milis()-last_time > 20){ 
		last_time = milis();
		stisknuto=keypad_scan(); 
		if(minule_stisknuto == 0 && stisknuto != 0){
			minule_stisknuto = stisknuto;
			
			
			
			if(stisknuto < 13){
			pocetcisel = pocetcisel + 1;
			vstup();
			
				}
			}
		}			
		if(stisknuto == 0){minule_stisknuto=0;}
	


}
void bombtimer(void){
static uint16_t posledni_cas=0;
if(milis() - posledni_cas >= perioda01){
posledni_cas = milis();
cas_bomby = cas_bomby - 1;
lcd_gotoxy(0,1);
sprintf(text,"%02u",cas_bomby);
lcd_puts(text);
blink_period1 = blink_period1 - 16;
}
}
void FinalStage(void){
	if(cas_bomby<= 0){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("BOMB EXPLODED");
	delay_ms(1000);
	lcd_gotoxy(0,0);
	lcd_clear();
	lcd_puts("TERRORISTS");
	lcd_gotoxy(0,1);
	lcd_puts("WIN");
	bombnumber = 0;
	pocetcisel =0;
	delay_ms(2000);
	lcd_clear();
	cas_bomby = 40;
	rezim =1;
	blink_period1 = 1000;	
	stav=1;
	}
	}
void vstup(void){
if(rezim==1)	{
if(pocetcisel==1 && stisknuto == 7){
	lcd_clear();
	stav = 0;
	bombnumber = bombnumber + 7;
	lcd_gotoxy(0,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);
	}
	
if(pocetcisel ==1 && stisknuto != 7){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==2 && stisknuto == 3){
	bombnumber = bombnumber + 3;
	lcd_gotoxy(1,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
}
if(pocetcisel ==2 && stisknuto != 3){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==3 && stisknuto == 5){
	bombnumber = bombnumber + 5;
	lcd_gotoxy(2,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
}
if(pocetcisel ==3 && stisknuto !=5 ){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==4 && stisknuto == 5){
	bombnumber = bombnumber + 5;
	lcd_gotoxy(3,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
}
if(pocetcisel ==4 && stisknuto != 5){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==5 && stisknuto == 6){
	bombnumber = bombnumber + 6;
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
}
if(pocetcisel ==5 && stisknuto != 6){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==6 && stisknuto == 1){
	bombnumber = bombnumber + 1;
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
}
if(pocetcisel ==6 && stisknuto != 1){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
	lcd_clear();
}
if(pocetcisel==7 && stisknuto == 7){
	bombnumber = bombnumber + 7;
	lcd_gotoxy(6,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);
	delay_ms(1000);
	lcd_clear();
	lcd_gotoxy(3,1);
	lcd_puts("seconds left");
	pocetcisel=0;
	rezim=2;				
}
if(pocetcisel ==7 && stisknuto != 7){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	pocetcisel = 0;
	bombnumber = 0;
	delay_ms(1000);
  lcd_clear();
				
}
}		
if(rezim==2)	{
if(pocetcisel==1 && stisknuto == 7){
	lcd_gotoxy(0,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);
	}	
if(pocetcisel==1 && stisknuto != 7){
	kontrola();
	cas_bomby = cas_bomby - 10;
}
if(pocetcisel==2 && stisknuto == 3){
	lcd_gotoxy(1,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
	
}
if(pocetcisel==2 && stisknuto != 3){
	kontrola();
	cas_bomby = cas_bomby - 10;
	}
if(pocetcisel==3 && stisknuto == 5){
	lcd_gotoxy(2,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
	
}
if(pocetcisel==3 && stisknuto != 5){
	kontrola();
	cas_bomby = cas_bomby - 10;
}
if(pocetcisel==4 && stisknuto == 5){
	lcd_gotoxy(3,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
	
}
if(pocetcisel==4 && stisknuto != 5){
	kontrola();
	cas_bomby = cas_bomby - 10;
	
}
if(pocetcisel==5 && stisknuto == 6){
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	

}
if(pocetcisel==5 && stisknuto != 6){
	kontrola();
	cas_bomby = cas_bomby - 10;
	
	
	
}
if(pocetcisel==6 && stisknuto == 1){
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);	
	
}
if(pocetcisel==6 && stisknuto != 1){
	kontrola();
	cas_bomby = cas_bomby - 10;
}
if(pocetcisel==7 && stisknuto == 7){
	lcd_gotoxy(6,0);
	sprintf(text,"%1u",stisknuto);
	lcd_puts(text);
	delay_ms(1000);
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("BOMB HAS BEEN");
	lcd_gotoxy(0,1);
	lcd_puts("DEFUSED");
	delay_ms(2000);
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("COUNTER");
	lcd_gotoxy(0,1);
	lcd_puts("TERRORISTS WIN");
	rezim=1;
	bombnumber = 0;
	cas_bomby =40;
	blink_period1 = 1000;
	pocetcisel = 0;
	delay_ms(2000);
	lcd_clear();
	stav=1;
	
	
}
if(pocetcisel==7 && stisknuto != 7){
	kontrola();
	cas_bomby = cas_bomby - 10;
	
}
}		
}
void kontrola(void){
if(cas_bomby > 10){
	lcd_gotoxy(0,0);
	lcd_puts("incorrect code");
	blink_period1 = blink_period1 - 160;
	pocetcisel = 0;
	delay_ms(1000);
	lcd_clear();
	lcd_gotoxy(3,1);
	lcd_puts("seconds left");
}
if(cas_bomby < 10){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("BOMB EXPLODED");
	delay_ms(2000);
	lcd_gotoxy(0,0);
	lcd_clear();
	lcd_puts("TERRORISTS");
	lcd_gotoxy(0,1);
	lcd_puts("WIN");
	GPIO_WriteHigh(GPIOB,GPIO_PIN_7);
	bombnumber = 0;
	pocetcisel =0;
	delay_ms(2000);
	lcd_clear();
	cas_bomby = 40;
	rezim =1;
	blink_period1 = 1000;
	stav=1;
}
}
void sirenka(void){
	
	static uint16_t posledni_cas=0;	
		if(milis() - posledni_cas >= blink_period1){
			posledni_cas = milis();
			GPIO_WriteReverse(GPIOG,GPIO_PIN_2);
	
}
}
void ledka(void){
	static uint16_t posledni_cas=0;	
		if(milis() - posledni_cas >= blink_period1){
			posledni_cas = milis();
			GPIO_WriteReverse(GPIOB,GPIO_PIN_7);
	
}
}
// pod tímto komentáøem nic nemìòte 
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */                                                
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */                               
  while (1)
  {
  }
}
#endif