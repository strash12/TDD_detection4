#include"header.h"                           
PSS_corr::PSS_corr(_parametrs param)
{
    _band = param.fftsize;
    _cyclic = param.cyclic;

}

PSS_corr::~PSS_corr()
{
}

int PSS_corr::Primary_sync_signal_corr(std::vector<int32_t> mas,_parametrs param)
{
int64_t Real_level   = 0 ;
int64_t Imag_level   = 0 ;
int64_t maximum      = 0 ;
int64_t level        = 0 ;
int     first        = 0 ;

        for (int k = 0; k < 3 ; k++)
        {
            for (int i = 0; i <param.windowing; i++)
                {
                    for (int j = 0; j<param.fftsize+param.cp ; j++)
                        {    
                            Real_level = Real_level + (int16_t)(mas[i+j]& 0xffff)*param.PSSreal[k][j]+(int16_t)(mas[i+j]>>16)*param.PSSimag[k][j];
                            Imag_level = Imag_level + (int16_t)(mas[i+j] >>16)*param.PSSreal[k][j]-(int16_t)(mas[i+j]& 0xffff)*param.PSSimag[k][j];

                        }                      
                            level = abs(Real_level)+ abs(Imag_level);
                                if (level > maximum)
                                    {
                                        maximum = level;
                                        first = i+1;
                                    }
                            Real_level = 0;
                            Imag_level = 0;
                    
                }

        }

    return first;

}
        
