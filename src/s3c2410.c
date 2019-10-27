#include "s3c2410.h"

uint64_t s3c2410_get_cpu_clk(void) {
	uint64_t val = rMPLLCON;
	return (((GET_MDIV(val) + 8) * FIN) / ((GET_PDIV(val) + 2) * (1 << GET_SDIV(val))));
}

uint64_t s3c2410_get_bus_clk(uint32_t which) {
	uint64_t cpu_clk = s3c2410_get_cpu_clk();
	uint64_t ratio = rCLKDIVN;
    if(which == CLK_HCLK) {
        // HCLK
        if(ratio == 0 || ratio == 1) {
            return cpu_clk;
        }else if (ratio == 2 || ratio == 3) {
            return cpu_clk / 2;
        }else {
			return 0;
        }
    }else {
        // PCLK
        if(ratio == 0) {
            return cpu_clk;
        }else if (ratio == 1 || ratio == 2) {
            return cpu_clk / 2;
        }else if (ratio == 3) {
            return cpu_clk / 4;
        }else {
			return 0;
        }
    }
}
