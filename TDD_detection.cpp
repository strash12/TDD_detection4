#include "header.h"
#include <cmath>
TDD_detection::TDD_detection(int first,float angle,_parametrs param,std::vector<int32_t> &signal,int Cellid)
:_signal(signal),_signal_real(param.fs/100*2),_signal_imag(param.fs/100*2)
{
    _Cellid = Cellid;
    _first = first;
    _angle = angle;
    _param = param;
    _frame_size = _param.fs/100*2;

   

}

TDD_detection::~TDD_detection()
{
}

void TDD_detection::TDD_calculation(int &TDD_config)
{
    freq_shift_remove();
    Frame_cut(TDD_config);
}

void TDD_detection::freq_shift_remove()
{
    if(_angle !=0)
    {
        for(int i = 0; i <_frame_size; i ++)
            {
                _signal_real[i] = (((int16_t)(_signal[i] & 0xffff) * cos(i*_angle/_param.fftsize)) - ((int16_t)(_signal[i]>>16)*sin(i*_angle/_param.fftsize)));
                _signal_imag[i] = (((int16_t)(_signal[i] & 0xffff) * sin(i*_angle/_param.fftsize)) + ((int16_t)(_signal[i]>>16)*cos(i*_angle/_param.fftsize)));
            }
    }

}

void TDD_detection::Frame_cut(int &TDD_config)
{
   RS_proc RS(_param,_first,_signal_real,_signal_imag,_Cellid);

   RS.Frame_cut();
   RS.TDD_config(TDD_config);

   
}