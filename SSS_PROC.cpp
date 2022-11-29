#include "header.h"
#include "SSS_Normal.h"
#include <math.h>
#include <array>


SSS_PROC::SSS_PROC(_parametrs param,int first,std::vector<int32_t>& signal):
_signal(signal),SSS(param.fftsize),SSS_REAL_Corr(param.fftsize),SSS_IMAG_Corr(param.fftsize),SSS_FFT_REAL(param.fftsize),
SSS_FFT_IMAG(param.fftsize),SSS_62_real(SSS_size),SSS_62_imag(SSS_size)
{
    _FFT_SIZE = param.fftsize;
    _FIRST = first;
    start = _FIRST - 2 * (_FFT_SIZE+param.cp)-_FFT_SIZE-1;
    stop  = _FIRST - 2 * _FFT_SIZE- 2* param.cp -1; 
}

void SSS_PROC::CUT_SSS(int& Frame,int& CellID)
{
    save_to_file();
    sss_cut();
    FFT_SSS();
    SSS_copy();      
    int Cellid1 = SSS_CORELATE(SSSn1,maxSSS1);
    int Cellid2 = SSS_CORELATE(SSSn2,maxSSS2);
    Frame = maxSSS1>maxSSS2?1:2;
    CellID = maxSSS1>maxSSS2?Cellid1:Cellid2;
}

int SSS_PROC::SSS_CORELATE(int (&SSS)[504][62],int64_t& maxSSS)
{
    int64_t CorRe = 0,CorIm = 0;
    int64_t Corlvln = 0;
    int Cellid = 0;       
        for ( int i = 0; i < 504;i++)
            {
                for (int j = 0; j<62 ; j++)
                    {
                        CorRe  += SSS_62_real[j]*SSS[i][j];
                        CorIm  += SSS_62_imag[j]*SSS[i][j];
                    }
            Corlvln =  abs(CorRe)+abs(CorIm);
                    if(Corlvln > maxSSS)
                        {
                            maxSSS = Corlvln;
                            Cellid = i;
                        }
            CorRe  = 0;
            CorIm  = 0; 
            }
    return Cellid;
}

void SSS_PROC::SSS_copy()
{
    int start_1_SSS = _FFT_SIZE/2-31;
    int stop_1_SSS  = _FFT_SIZE/2;
    int start_2_SSS = _FFT_SIZE/2+1;
    int stop_2_SSS  = _FFT_SIZE/2+32;
    
    std::copy(SSS_FFT_REAL.begin()+start_1_SSS,SSS_FFT_REAL.begin()+stop_1_SSS,SSS_62_real.begin());
    std::copy(SSS_FFT_REAL.begin()+start_2_SSS,SSS_FFT_REAL.begin()+stop_2_SSS,SSS_62_real.begin()+31);
    std::copy(SSS_FFT_IMAG.begin()+start_1_SSS,SSS_FFT_IMAG.begin()+stop_1_SSS,SSS_62_imag.begin());
    std::copy(SSS_FFT_IMAG.begin()+start_2_SSS,SSS_FFT_IMAG.begin()+stop_2_SSS,SSS_62_imag.begin()+31);

}

void SSS_PROC::save_to_file()
{
    std::FILE* file =fopen(name,"w");
    std::ofstream out;
    out.open(name);
        for(int i = 0 ; i<200000; i++)
            {
                out<<(int16_t)(_signal[i] & 0xffff)<<"  "<<(int16_t)(_signal[i] >>16)<<std::endl;
            }
    fclose(file);
    out.close();

}

void SSS_PROC::sss_cut()
{
    std::copy(_signal.begin()+start,_signal.begin()+stop,SSS.begin());
}

void SSS_PROC::FFT_SSS()
{
    for(int i = 0 ; i<_FFT_SIZE;i++)
        {
            SSS_REAL_Corr[i] = (int16_t)(SSS[i] & 0xffff);
            SSS_IMAG_Corr[i] = (int16_t)(SSS[i] >>16);
        }

    FFT_TRANS FFT2(_FFT_SIZE);
    FFT2.FFT(SSS_REAL_Corr,SSS_IMAG_Corr,SSS_FFT_REAL,SSS_FFT_IMAG);
}

SSS_PROC::~SSS_PROC()
{
_signal.clear();
SSS.clear();
SSS_REAL_Corr.clear();
SSS_IMAG_Corr.clear();
SSS_FFT_REAL.clear();
SSS_FFT_IMAG.clear();
SSS_62_real.clear();
SSS_62_imag.clear();
}