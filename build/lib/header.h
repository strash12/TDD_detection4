#ifndef header
#define header
#include <iostream>
#include <fstream>
#include <cstring>
#include <complex.h>
#include <cstdlib>
#include <math.h>
#include "fftw3.h"
#include <bitset>
#include <string>
#include <ctime>
#include <vector>
#include "tch.hpp"
#include <iostream>
#include <unistd.h>
#include <memory>
#include "header.h"

struct _parametrs
{
        int fftsize,cp,cp1,Nrb,Lb,i1start,i1fin,i2start,i2fin,Nc,Nsc,Nrb_Max,Nrb_Min,Ns,OSC,fs,Cor_lvl,cyclic; 
        uint32_t adreses1,adreses2,adreses3;    
};

class funk
{
    private:
        int _band;
        
        tch::CpMode mode;
    public:
        funk(float a,_parametrs *p1);
        ~funk();
        void norm(_parametrs *p1);
        void exte(_parametrs *p1);
        void get(_parametrs *p1);
};


class configure_PLIS
{
private:
    int verefi;
    int bits;
public:
    configure_PLIS();
    ~configure_PLIS();
    void PSS(_parametrs param);
};






class PSS_corr
{
    private:
        int32_t** PSSreal;
        int32_t** PSSimag;
        int _band;
        int _cyclic;
    public:
        PSS_corr(_parametrs param);
        ~PSS_corr();
        int Primary_sync_signal_corr(int16_t* signal_Real, int16_t* signal_Imag,_parametrs param);
        void norm(int,int);
        void ext(int,int);
        void get(_parametrs param);
};

class FFT_TRANS
{
private:
    int _FFT_SIZE;
    fftw_complex* _in;
    fftw_complex* _out;
    int16_t* _real;
    int16_t* _imag;

public:
    FFT_TRANS(int fftsize,int16_t* real,int16_t* imag);
    FFT_TRANS(int fftsize,int16_t* real);
    FFT_TRANS(int fftsize, fftw_complex* in);
    ~FFT_TRANS();
    void FFT(fftw_complex* out);
    void IFFT(fftw_complex* out);
    void FFT_SHIFT(fftw_complex *in, fftw_complex* out);
};

class SSS_PROC
{
private:
    int _FFT_SIZE;
    int _FIRST;
    int start;
    int stop;
    int64_t maxSSS1 = 0;
    int64_t maxSSS2 = 0;
    int16_t* SSS_REAL;
    int16_t* SSS_IMAG;
    fftw_complex fftSSS[62];
public:
    SSS_PROC(_parametrs param,int first,int16_t* masr,int16_t* masi);
    ~SSS_PROC();
    void CUT_SSS(int& Frame,int& CellID);
    int SSS_CORELATE(fftw_complex*fftSSS,int (&SSS)[504][62],int64_t& maxSSS);
    void SEND_SSS(int16_t* masr,int16_t* masi,int fftsize,int CellID);
    void SSS_generate(int,int);
};



#endif