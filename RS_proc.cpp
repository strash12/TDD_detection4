#include "header.h"
#include <iterator>

RS_proc::RS_proc(_parametrs _param,int first,std::vector<int16_t> real,std::vector<int16_t> imag,int Cellid)
:REAL(real),IMAG(imag)
{
cellid = Cellid;
 param   = _param;
 Frame_size = param.fs/100;
 Slot_size = param.fs/2000;
 sub = param.fs/1e3;   

 fr1 = first - 2*param.fftsize  -param.cp- sub-param.cp;
 fr2 = first - 2*param.fftsize - param.cp - param.cp1 - sub + sub*10-1;
 fr3 = first + 12*param.fftsize + param.cp1 + 11*param.cp - 1 + 8*sub + sub*10+1;
 fr4 = first - 2*param.fftsize - param.cp - param.cp1 - sub-1;
 fr5 = first + 12*param.fftsize + param.cp1 + 11*param.cp - 1 + 8*sub+1;

rs_signal_fixed_real = new float*[2*param.Nrb];
     for(int i = 0; i <2*param.Nrb;i++)
     {
        rs_signal_fixed_real[i] = new float [param.Ns*2];
     }
     
    rs_signal_fixed_imag = new float*[2*param.Nrb];
     for(int i = 0; i <2*param.Nrb;i++)
     {
        rs_signal_fixed_imag[i] = new float [param.Ns*2];
     }
     
    rs_space_index = new int*[2*param.Nrb];
     for(int i = 0; i <2*param.Nrb;i++)
     {
        rs_space_index[i] = new int [param.Ns*2];
     }

}






void RS_proc::Frame_cut()
{

std::vector <int16_t> Frame_real(Frame_size);
std::vector <int16_t> Frame_imag(Frame_size);
   if (fr1 < 1)
{
	std::copy(REAL.begin()+fr2,REAL.begin()+fr3,Frame_real.begin());
	std::copy(IMAG.begin()+fr2,IMAG.begin()+fr3,Frame_imag.begin());
	
}
  
else if(fr1>1)
   
{

	std::copy(REAL.begin()+fr4,REAL.begin()+fr5,Frame_real.begin());
	std::copy(IMAG.begin()+fr4,IMAG.begin()+fr5,Frame_imag.begin());
 	
}
   Slot_cut(Frame_real,Frame_imag);
    
}

void RS_proc::Slot_cut(std::vector <int16_t> Frame_real,std::vector <int16_t> Frame_imag)
{
std::vector <int16_t> Slot_real(Slot_size);
std::vector <int16_t> Slot_imag(Slot_size);
std::vector <int16_t> slot_sig_real_1(param.fftsize);
std::vector <int16_t> slot_sig_imag_1(param.fftsize);
std::vector <int16_t> slot_sig_real_2(param.fftsize);
std::vector <int16_t> slot_sig_imag_2(param.fftsize);

std::vector <double> slot_sig_real_1_fft(param.fftsize);
std::vector <double> slot_sig_imag_1_fft(param.fftsize);
std::vector <double> slot_sig_real_2_fft(param.fftsize);
std::vector <double> slot_sig_imag_2_fft(param.fftsize);

int16_t frame_sig_real [param.fftsize][40];
int16_t frame_sig_imag [param.fftsize][40];
int16_t framesigrealRS [param.OSC][param.Ns*2];
int16_t framesigimagRS [param.OSC][param.Ns*2];


int16_t framesigRSreal [param.Nrb*2][param.Ns*2];
int16_t framesigRSimag [param.Nrb*2][param.Ns*2];

    for (int i = 0 ; i < 20; i++)
        {
            if(param.fftsize == 1536)
            {
                std::copy(Frame_real.begin()+(i*11520),Frame_real.begin()+((i+1)*11520),Slot_real.begin());
                std::copy(Frame_imag.begin()+(i*11520),Frame_imag.begin()+((i+1)*11520),Slot_imag.begin());
            }
            else
            {
                std::copy(Frame_real.begin()+(i*Slot_size),Frame_real.begin()+((i+1)*Slot_size),Slot_real.begin());
                std::copy(Frame_imag.begin()+(i*Slot_size),Frame_imag.begin()+((i+1)*Slot_size),Slot_imag.begin());
            }

        
        // ok 

        std::copy(Slot_real.begin()+param.cp1,Slot_real.begin()+(param.cp1+param.fftsize),slot_sig_real_1.begin());
        std::copy(Slot_imag.begin()+param.cp1,Slot_imag.begin()+(param.cp1+param.fftsize),slot_sig_imag_1.begin());
        //ok

        std::copy(Slot_real.begin()+(param.cp1+4*(param.fftsize+param.cp)),Slot_real.begin()+(param.cp1+5*(param.fftsize+param.cp)-param.cp),slot_sig_real_2.begin());
        std::copy(Slot_imag.begin()+(param.cp1+4*(param.fftsize+param.cp)),Slot_imag.begin()+(param.cp1+5*(param.fftsize+param.cp)-param.cp),slot_sig_imag_2.begin());


        //ok        
        
     
        FFT_TRANS FFT1(param.fftsize);
        FFT1.FFT(slot_sig_real_1,slot_sig_imag_1,slot_sig_real_1_fft,slot_sig_imag_1_fft);
        FFT1.FFT(slot_sig_real_2,slot_sig_imag_2,slot_sig_real_2_fft,slot_sig_imag_2_fft);
            
        
   for (int j = 0;j<param.fftsize;j++)
    {
        frame_sig_real[j][i*2] = slot_sig_real_1_fft[j];
        frame_sig_imag[j][i*2] = slot_sig_imag_1_fft[j];
        frame_sig_real[j][i*2+1] = slot_sig_real_2_fft[j];
        frame_sig_imag[j][i*2+1] = slot_sig_imag_2_fft[j];
    }

}


int k =0;
for (int i=param.fftsize/2-(2*param.Nrb)*3;i<param.fftsize/2+(2*param.Nrb)*3+1;i++)
{
     if(i==512)
    {
        continue;
    }
    for (int j =0;j<40;j++)
    {
    framesigrealRS[k][j]= frame_sig_real[i][j];
    framesigimagRS[k][j]= frame_sig_imag[i][j];
    }
        k++;
}

NRS_GEN RS(param,cellid);
RS.NRC(param,rs_signal_fixed_real,rs_signal_fixed_imag,rs_space_index);

int count;

    for(int j=0;j<param.Ns*2;j++)
    {
        for (int i=0;i<param.Nrb*2; i++)
        {
            count = rs_space_index[i][j];
            framesigRSreal[i][j] = framesigrealRS[count-1][j];
            framesigRSimag[i][j] = framesigimagRS[count-1][j];
        }
    }


    





    int CorRe = 0;
int CorIm = 0;
int Corlvln1[40]{{0}} ;

    for(int i=0;i<40;i++)
    {
        for (int d = 0; d<param.Nrb*2 ; d++)
        {
     CorRe += framesigRSreal[d][i]*rs_signal_fixed_real[d][i]+framesigRSimag[d][i]*rs_signal_fixed_imag[d][i];
     CorIm += framesigRSimag[d][i]*rs_signal_fixed_real[d][i]-framesigRSreal[d][i]*rs_signal_fixed_imag[d][i];

        }
        Corlvln1[i] += sqrt(pow(CorRe,2)+pow(CorIm,2));
        CorRe = 0;
        CorIm = 0;
    }


int fincor[10]{{0}};
    for(int i = 0;i<10;i++){

       fincor [i] = Corlvln1[i*4]+Corlvln1[i*4+1]+Corlvln1[i*4+2]+Corlvln1[i*4+3];
    }
 


int maximume=0;

for(int i=0;i<10;i++){
    if (fincor[i]>maximume)
    {
       maximume =fincor[i];
    }
    }

for (int i = 0;i<10;i++)
{

    if (fincor[i]<(maximume/5))
    {
        TDD_conf[i] = 0;
    }

    else
    {
        TDD_conf[i] = 1;
    }
}



}

void RS_proc::TDD_config(int& TDD_config)
{
std::array< int ,10> TDD0 = {1,1,0,0,0,1,1,0,0,0};
std::array< int ,10> TDD1 = {1,1,0,0,1,1,1,0,0,1};
std::array< int ,10> TDD2 = {1,1,0,1,1,1,1,0,1,1};
std::array< int ,10> TDD3 = {1,1,0,0,0,1,1,1,1,1};
std::array< int ,10> TDD4 = {1,1,0,0,1,1,1,1,1,1};
std::array< int ,10> TDD5 = {1,1,0,1,1,1,1,1,1,1};
std::array< int ,10> TDD6 = {1,1,0,0,0,1,1,0,0,1};


if(TDD_conf == TDD0)
    {
        TDD_config = 0;
    }
else if(TDD_conf == TDD1)
    {
        TDD_config = 1;
    }
else if(TDD_conf == TDD2)
    {
        TDD_config = 2;
    }
else if(TDD_conf == TDD3)
    {
       TDD_config = 3;
    }
else if(TDD_conf == TDD4)
    {
        TDD_config = 4;
    }
else if(TDD_conf == TDD5)
    {
        TDD_config = 5;
    }
else if(TDD_conf == TDD6)
    {
        TDD_config = 6;
    }
}







RS_proc::~RS_proc()
{


}