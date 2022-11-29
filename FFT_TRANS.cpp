#include "header.h"


FFT_TRANS::FFT_TRANS(int fft_size)
{
    _FFT_SIZE = fft_size;
    _in = new fftw_complex[_FFT_SIZE];
    _out = new fftw_complex[_FFT_SIZE];
    out_shift = new fftw_complex[_FFT_SIZE];
    
}





 void FFT_TRANS::FFT(std::vector<int16_t> real,std::vector<int16_t> imag,std::vector<double>& real_shift,std::vector<double>& imag_shift)
{
    for(int i = 0; i<_FFT_SIZE; i++)
        {
            _in[i][0] = real[i];
            _in[i][1] = imag[i];
        }

            fftw_plan plan = fftw_plan_dft_1d(_FFT_SIZE,_in,_out,FFTW_FORWARD,FFTW_MEASURE);
            fftw_execute(plan);
            fftw_destroy_plan(plan);
            FFT_SHIFT(_out,out_shift);

        
    for(int i = 0; i<_FFT_SIZE; i++)
        {
            real_shift[i] = out_shift[i][0] ;
            imag_shift[i] = out_shift[i][1]  ;
        }
        
            fftw_cleanup();
}

void FFT_TRANS::FFT_SHIFT(fftw_complex *in, fftw_complex* out)
{
    int pivot = (_FFT_SIZE % 2 == 0) ? (_FFT_SIZE / 2) : ((_FFT_SIZE -1) / 2);
    int rightHalf = _FFT_SIZE - pivot;
    int leftHalf = pivot;
    memcpy(out,in+pivot,sizeof(fftw_complex)*rightHalf);
    memcpy(out+rightHalf,in,sizeof(fftw_complex)*leftHalf);

}

FFT_TRANS::~FFT_TRANS()
{
    delete[] _in;
    delete[]  _out ;
    delete[]  out_shift;
}