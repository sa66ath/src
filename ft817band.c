#include <stdio.h>

#include <stdint.h>

typedef enum {
    FT817BAND_THRU, 
    FT817BAND_1_9M, 
    FT817BAND_3_5M, 
    FT817BAND_7M, 
    FT817BAND_10M, 
    FT817BAND_14M, 
    FT817BAND_18M, 
    FT817BAND_21M, 
    FT817BAND_24_5M, 
    FT817BAND_28M, 
    FT817BAND_50M, 
    FT817BAND_144M, 
    FT817BAND_430M, 
    NUMOF_FT817BAND, 
} FT817BAND_t;


#define	BAND00_VOLT	0.0     // THRU
#define	BAND01_VOLT	0.33	// 1.9
#define	BAND02_VOLT	0.67	// 3.5
#define	BAND03_VOLT	1.0	// 7
#define	BAND04_VOLT	1.33	// 10
#define	BAND05_VOLT	1.67	// 14
#define	BAND06_VOLT	2.0	// 18
#define	BAND07_VOLT	2.33	// 21
#define	BAND08_VOLT	2.67	// 24.5
#define	BAND09_VOLT	3.0	// 28
#define	BAND10_VOLT	3.33	// 50
#define	BAND11_VOLT	3.67	// 144
#define	BAND12_VOLT	4.0	// 430

#define	THRE_HYSTERESIS	0.2/2   // persent

#define	FVR_VOLT	(4*1.024)	/* Fixed Voltage Reference (FVR) */
#define	ADC_MAX		0xFFC0



static const uint16_t upThre[] = {
    ((0.5 + THRE_HYSTERESIS)*BAND01_VOLT + (0.5 - THRE_HYSTERESIS)*BAND00_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND02_VOLT + (0.5 - THRE_HYSTERESIS)*BAND01_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND03_VOLT + (0.5 - THRE_HYSTERESIS)*BAND02_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND04_VOLT + (0.5 - THRE_HYSTERESIS)*BAND03_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND05_VOLT + (0.5 - THRE_HYSTERESIS)*BAND04_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND06_VOLT + (0.5 - THRE_HYSTERESIS)*BAND05_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND07_VOLT + (0.5 - THRE_HYSTERESIS)*BAND06_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND08_VOLT + (0.5 - THRE_HYSTERESIS)*BAND07_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND09_VOLT + (0.5 - THRE_HYSTERESIS)*BAND08_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND10_VOLT + (0.5 - THRE_HYSTERESIS)*BAND09_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND11_VOLT + (0.5 - THRE_HYSTERESIS)*BAND10_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 + THRE_HYSTERESIS)*BAND12_VOLT + (0.5 - THRE_HYSTERESIS)*BAND11_VOLT) /FVR_VOLT *ADC_MAX,
    ADC_MAX
};

static const uint16_t downThre[] = {
    0,
    ((0.5 - THRE_HYSTERESIS)*BAND01_VOLT + (0.5 + THRE_HYSTERESIS)*BAND00_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND02_VOLT + (0.5 + THRE_HYSTERESIS)*BAND01_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND03_VOLT + (0.5 + THRE_HYSTERESIS)*BAND02_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND04_VOLT + (0.5 + THRE_HYSTERESIS)*BAND03_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND05_VOLT + (0.5 + THRE_HYSTERESIS)*BAND04_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND06_VOLT + (0.5 + THRE_HYSTERESIS)*BAND05_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND07_VOLT + (0.5 + THRE_HYSTERESIS)*BAND06_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND08_VOLT + (0.5 + THRE_HYSTERESIS)*BAND07_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND09_VOLT + (0.5 + THRE_HYSTERESIS)*BAND08_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND10_VOLT + (0.5 + THRE_HYSTERESIS)*BAND09_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND11_VOLT + (0.5 + THRE_HYSTERESIS)*BAND10_VOLT) /FVR_VOLT *ADC_MAX,
    ((0.5 - THRE_HYSTERESIS)*BAND12_VOLT + (0.5 + THRE_HYSTERESIS)*BAND11_VOLT) /FVR_VOLT *ADC_MAX
};



size_t GetIndexWithHysteresis(size_t index, uint16_t val, const uint16_t* upTbl, const uint16_t* downTbl, size_t tblSize)
{
    index = (0 <= index)?	index:0;
    index = (index < tblSize)?	index:tblSize - 1;

    for( ; upTbl[index] < val; index++) { ; }
    for( ; val < downTbl[index]; index--) { ; }

    return index;
}


static uint16_t Volt2adData(double volt)
{
    double tmp = volt*ADC_MAX/FVR_VOLT; 
    if(ADC_MAX < tmp)	{ tmp = ADC_MAX; }
    
    return tmp;		
}

int main(int argc, char* argv[])
{
    int i;
    FT817BAND_t band = 0, newBand;

    double volt;

    while(EOF != scanf("%lf", &volt)) {
        if(band != (newBand = GetIndexWithHysteresis(band, Volt2adData(volt), upThre, downThre, sizeof(upThre)/sizeof(upThre[0])))) {
            band = newBand;
            printf("band = %d\n", band);
        }
    }

    return 0;
}

