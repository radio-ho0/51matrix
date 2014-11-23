#include <at89x52.h>

__sbit __at 0x90 LCD_RS;
__sbit __at 0x91 LCD_RW;
__sbit __at 0x92 LCD_E;
__sfr  __at 0xa0  LCD_Data;

void WriteDataLCD(char WDLCD);
void WriteCommandLCD(char WCLCD);

void LCDInit(void);
void ChangeCursor(char X, char Y);
void DisplayListChar(char *DData);

void delay_us(unsigned int t);

// to show  string
char str1[] = " Hello World!!! ";	
char str2[] = "Practice mk perfect";

void main(void)
{
	LCDInit();	

    DisplayListChar(str1);
    WriteCommandLCD(0x80 + 0x40);	// start next line
    DisplayListChar(str2);

    for(;;){

        DisplayListChar(ACC); // display random char
        WriteCommandLCD(0x80 + 0x40);	
        DisplayListChar(ACC); 


    }
}



void WriteDataLCD(char WDLCD)
{
	LCD_Data = WDLCD;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;		
	delay_us(100);
	LCD_E = 0;
	delay_us(100);
}

void WriteCommandLCD(char WCLCD)
{
	LCD_Data = WCLCD;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	delay_us(100);	
	LCD_E = 0;
	delay_us(100);
}

void LCDInit(void)	
{
	WriteCommandLCD(0x38);	
	WriteCommandLCD(0x06);
	WriteCommandLCD(0x0F);	// blink cursor 

	WriteCommandLCD(0x01);	//  clear screen
	delay_us(5000);
}

void DisplayListChar(char *DData)
{
	char x;
	x = 0;
	while (DData[x] != 0)
	{
		WriteDataLCD(DData[x]);
		x++;
	}
}

void delay_us(unsigned int t)
{  int  i;
   TMOD = 0x01;        
   for(i=0;i<20;i++)  
    {
      TH0 = (65536-t) / 256; 
      TL0 = (65536-t) % 256;
      TR0 = 1;       
	  while(TF0 == 0);
	  TF0 = 0;       
      TR0 = 0;      
    }
}
