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
#include "devmem.hpp"
#include "dmac.hpp"
#include <cstdlib>
struct _parametrs
{
        int fftsize,cp,cp1,Nrb,Lb,i1start,i1fin,i2start,i2fin,Nc,Nsc,Nrb_Max,Nrb_Min,Ns,OSC,fs,Cor_lvl,cyclic,shift,windowing; 
        uint32_t adreses1;
        uint32_t MMCM;
        uint32_t MMCM_2 = 0x00002004;
        double** PSSreal;
        double** PSSimag;
	std::string path;  
};

class funk
{
    private:
        int _band;
        tch::CpMode _cp_mode;
    public:
        funk(tch::FullTusurCommonConfig _config,_parametrs *p1);
        ~funk();
        void normal(_parametrs *p1);
        void extetended(_parametrs *p1);
        void set_prefix(_parametrs *p1);        
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
        int Primary_sync_signal_corr(std::vector<int32_t> mas,_parametrs param);
        void norm(int,int);
        void ext(int,int);
        void get(_parametrs param);
};

class FFT_TRANS
{
private:
    int _FFT_SIZE;
    fftw_complex*   _in;
    fftw_complex*   _out;
    fftw_complex*   out_shift;
public:
    FFT_TRANS(int fftsize);
    ~FFT_TRANS();
    void FFT(std::vector<int16_t> real,std::vector<int16_t> imag,std::vector<double>& real_shift,std::vector<double>& imag_shift);
    void FFT_SHIFT(fftw_complex *in, fftw_complex* out);
    void clear_memory();
};

class SSS_PROC
{
private:
    int SSS_size = 62;
    int _FFT_SIZE;
    int _FIRST;
    int start;
    int stop;
    char name[10] = "real1.txt";
    std::vector<double> SSS_FFT_REAL ; 
    std::vector<double> SSS_FFT_IMAG ;
   
    std::vector<int16_t> SSS_REAL_Corr ;
    std::vector<int16_t> SSS_IMAG_Corr ;
    
    std::vector<int32_t> SSS;
    std::vector<int32_t> _signal;

    std::vector<double> SSS_62_real;
    std::vector<double> SSS_62_imag;

    int64_t maxSSS1 = 0;
    int64_t maxSSS2 = 0;
    


public:
    SSS_PROC(_parametrs param,int first,std::vector<int32_t>& signal);
    ~SSS_PROC();
    
    void CUT_SSS(int& Frame,int& CellID);

    int SSS_CORELATE(int (&SSS)[504][62],int64_t& maxSSS);
    void SSS_copy();
    void save_to_file();
    void sss_cut();
    void FFT_SSS();
    
};

class plis_configure
{
private:
    uint32_t config;
    int error;
    uint32_t bits;
    
public:

    plis_configure(_parametrs param);
    ~plis_configure();
    void cofigure_plis();
    void MMCM(_parametrs param);
    void SSS_upload(int,_parametrs param);
    bool validate();
};

class freq_shift
{
private:
    std::vector<int32_t> s1;
    std::vector<int32_t> s2;
    int start_cp1;
    int stop_cp1;
    int start_cp2;
    int stop_cp2;
    int cp;
    int32_t CorRe = 0,CorIm = 0;
public:
    freq_shift(std::vector<int32_t> signal,_parametrs param,int first);
    ~freq_shift();
    float angle();
};



class create_mark : public plis_configure
{
private:
std::vector<int32_t> signal;
std::vector<int32_t> signal_freq_shift_r;
std::vector<int32_t> signal_freq_shift_i;
_parametrs param;
int     cor_lvl;
bool    kind_PSS_SSS;
bool    automatic;
int     Frame ;
int     CellID;
int     first ;
float   angle;
int     TDD_config;

public:
    create_mark(_parametrs _param, tch::FullTusurCommonConfig _config);
    ~create_mark();
    void set_parametrs();
    void configure_pss( );
    void config_all( );
    std::vector<int32_t>load_signal_with_dma();
    void PSS_CORR( );
    void SSS_proc( );
    void shift( );
    void TDD_configure(int& TDD_config);

  

};
class TDD_detection
{
private:
    int _frame_size; 
    int _first;
    int _Cellid;
    float _angle;
    _parametrs _param;

    std::vector<int16_t> _signal_real ;
    std::vector<int16_t> _signal_imag ;
    std::vector<int32_t> _signal;
public:
    TDD_detection(int first,float angle,_parametrs param,std::vector<int32_t> &signal,int Cellid);
    ~TDD_detection();
    void TDD_calculation(int &TDD_config);
    void freq_shift_remove();
    void generate_pilot();
    void Frame_cut(int &TDD_config);
};

class NRS_GEN
{
protected:
    int M;
    int Ncp,Ns_fix,fix_1,C_init,C_init_fix,r,m_,Lb;
    int Ns = 20;
    int _CellId;
    int rs_space_1_fix_normal[40];
    int rs_space_1_fix_extended[40];
    int NS_1_normal[2];
    int NS_1_extended[2];


public:
    NRS_GEN(_parametrs param,int);
    ~NRS_GEN();
    void NRC(_parametrs param,float** rs_signal_fixed_real, float** rs_signal_fixed_imag, int** rs_space_index );
};

class RS_proc
{
private:
    int Frame_size,Slot_size,cellid;
    int sub;
    int point,fr1,fr2,fr3,fr4,fr5,size1,size2;
    _parametrs param;
    std::vector<int16_t> REAL;
    std::vector<int16_t> IMAG;      
    float** rs_signal_fixed_real;
    float** rs_signal_fixed_imag;
    int** rs_space_index;
    std::array<int,10> TDD_conf;
public:
    RS_proc(_parametrs _param,int first,std::vector<int16_t> real,std::vector<int16_t> imag,int Cellid);
    void Frame_cut();
    void Slot_cut(std::vector <int16_t> Frame_real,std::vector <int16_t> Frame_imag);
    void ST();
    void fin_cor(int16_t** framesigRSreal,int16_t** framesigRSimag);
    void TDD_config(int& TDD_config);
    ~RS_proc();
};
#endif