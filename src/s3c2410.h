#ifndef __S3C2410_H___
#define __S3C2410_H___

#include <stdint.h>

//CLOCK & POWER MANAGEMENT
#define rLOCKTIME   (*(volatile unsigned *)0x07200000) //PLL lock time counter
#define rMPLLCON    (*(volatile unsigned *)0x07200004) //MPLL Control
#define rUPLLCON    (*(volatile unsigned *)0x07200008) //UPLL Control
#define rCLKCON     (*(volatile unsigned *)0x0720000c) //Clock generator control
#define rCLKSLOW    (*(volatile unsigned *)0x07200010) //Slow clock control
#define rCLKDIVN    (*(volatile unsigned *)0x07200014) //Clock divider control

//PPL输入频率,即主板晶振
#define FIN	12000000
#define CLK_PCLK	0
#define CLK_HCLK	1

#define Fld(Size, Shft)	(((Size) << 16) + (Shft))

#define fPLL_MDIV		Fld(8, 12)
#define fPLL_PDIV		Fld(6, 4)
#define fPLL_SDIV		Fld(2, 0)

#define UData(Data)	((uint64_t) (Data))
#define FSize(Field)	((Field) >> 16)
#define FShft(Field)	((Field) & 0x0000FFFF)
#define FAlnMsk(Field)	((UData (1) << FSize (Field)) - 1)

#define FExtr(Data, Field) ((UData (Data) >> FShft (Field)) & FAlnMsk (Field))

#define GET_MDIV(x)	FExtr(x, fPLL_MDIV)
#define GET_PDIV(x)	FExtr(x, fPLL_PDIV)
#define GET_SDIV(x)	FExtr(x, fPLL_SDIV)


uint64_t s3c2410_get_cpu_clk(void);
uint64_t s3c2410_get_bus_clk(uint32_t which);
				
#endif
