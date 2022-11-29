#include "header.h"
#include <math.h>

freq_shift::freq_shift(std::vector<int32_t> signal,_parametrs param,int first)
{
    cp = param.cp;
    
    start_cp1 = first-1;
    stop_cp1 = first+cp-1;
    start_cp2 = first+param.fftsize-1;
    stop_cp2 = first+param.fftsize-1+cp;

s1.insert(s1.end(),signal.begin()+start_cp1,signal.begin()+stop_cp1);
s2.insert(s2.end(),signal.begin()+start_cp2,signal.begin()+stop_cp2);
 
    
}

freq_shift::~freq_shift()
{
}

float freq_shift::angle()
{
    for (int j = 0; j<cp ; j++)
        {
            CorRe =CorRe+ (int16_t)(s1[j]&0xffff) * (int16_t)(s2[j]& 0xffff) +    (int16_t)(s1[j]>>16)*      (int16_t)(s2[j]>>16);
            CorIm =CorIm+ (int16_t)(s1[j]>>16) *    (int16_t)(s2[j]& 0xffff) -    (int16_t)(s1[j]& 0xffff) * (int16_t)(s2[j]>>16);   
        }

float angle = atan2(CorIm,CorRe); 
return angle;
}