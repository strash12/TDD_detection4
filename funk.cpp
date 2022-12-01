#include "header.h"
#include "PSS_Normal.h"
#include "PSS_Extended.h"

funk::funk(tch::FullTusurCommonConfig _config,_parametrs *parametrs)
{
    _band = _config.bandwidth;
    _cp_mode = _config.cp_mode;
    funk::set_prefix(parametrs);
}



void funk::normal(_parametrs *parametrs)
{
 switch (_band)
    {
    case 1:
        parametrs->fftsize       = 128;
        parametrs->cp1           = 10;
        parametrs->cp            = 9;
        parametrs->fs            = 1.92e6;
        parametrs->Nrb           = 6;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;              
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 75;
        parametrs->adreses1       = 0x020110DC;
        parametrs ->MMCM            = 0x00000080;
        parametrs->windowing     = parametrs->fs/1000;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B1.txt";
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++)
                {
                    for(int j=0;j<parametrs->fftsize+parametrs->cp;j++)
                        {
                            parametrs->PSSreal[i][j]=PSS128real[i][j]*1000000;
                            parametrs->PSSimag[i][j]=PSS128imag[i][j]*1000000;
                        }
                }


    break;
    
    case 3:
        parametrs->fftsize       = 256;
        parametrs->cp1           = 20;
        parametrs->cp            = 18;
        parametrs->fs            = 3.84e6;
        parametrs->Nrb           = 15;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;              
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 150;
        parametrs->adreses1       = 0x010210D2;
        parametrs ->MMCM            = 0x00000040;
        parametrs->windowing     = parametrs->fs/1000;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B2.txt";
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS256real[i][j]*1000000;
        parametrs->PSSimag[i][j]=PSS256imag[i][j]*1000000;
            }
        }

    break;
    
    case 7:
        parametrs->fftsize       = 512;
        parametrs->cp1           = 40;
        parametrs->cp            = 36;
        parametrs->fs            = 7.68e6;
        parametrs->Nrb           = 25;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;             
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;            
        parametrs->Ns            = 20;
        parametrs->OSC           = 300;
        parametrs->adreses1       = 0x00031136;
        parametrs ->MMCM            = 0x00000020;
        parametrs->windowing     = parametrs->fs/1000;
parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B3.txt";
       memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS512real[i][j]*1000000;
        parametrs->PSSimag[i][j]=PSS512imag[i][j]*1000000;
            }
        }
    break;
    
    case 15:
        parametrs->fftsize       = 1024;
        parametrs->cp1           = 80;
        parametrs->cp            = 72;
        parametrs->fs            = 15.36e6;
        parametrs->Nrb           = 50;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs-> fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs-> fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;             
        parametrs->Nrb_Max       = 110;           
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 600;
        parametrs->adreses1       = 0x000411D2;
        parametrs ->MMCM            = 0x00000010;
        parametrs->windowing     = parametrs->fs/1000;
parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B4.txt";

        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS1024real[i][j]*1000000;
        parametrs->PSSimag[i][j]=PSS1024imag[i][j]*1000000;
            }
        }
    break;

    case 23:
        parametrs->fftsize       = 1536;
        parametrs->cp1           = 120;
        parametrs->cp            = 108;
        parametrs->fs            = 23.04e6;
        parametrs->Nrb           = 75;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs-> fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs-> fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 900;
        parametrs->adreses1       = 0x000511A4;
        parametrs ->MMCM            = 0x00029A0A;
        parametrs->windowing     = parametrs->fs/2000;
parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B5.txt";

        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS1536real[i][j]*1000000;
        parametrs->PSSimag[i][j]=PSS1536imag[i][j]*1000000;
            }
        }
    break;

    case 30:
        parametrs->fftsize       = 2048;
        parametrs->cp1           = 160;
        parametrs->cp            = 144;
        parametrs->fs            = 30.72e6;
        parametrs->Nrb           = 100;
        parametrs->Lb            = 7;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 1200;
        parametrs->adreses1       = 0x000611AE;
        parametrs ->MMCM            = 0x00000008;
        
        parametrs->windowing     = parametrs->fs/2000;
parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B6.txt";

        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS2048real[i][j]*1000000;
        parametrs->PSSimag[i][j]=PSS2048imag[i][j]*1000000;
            }
        }
    break;
    default:
        std::cout<<"Error::"<<std::endl;
    break;
    }

    
}

void funk::extetended(_parametrs *parametrs)
{
    parametrs->Lb            = 6;
    switch (_band)
    {
    case 1:
         parametrs-> fftsize      = 128;
         parametrs-> cp1          = 32;
         parametrs-> cp           = 32;
         parametrs-> fs           = 1.92e6;
         parametrs->Nrb           = 6;
         parametrs-> i1start      = parametrs->fftsize/2-31;
         parametrs-> i1fin        = parametrs->fftsize/2-1;
         parametrs-> i2start      = parametrs->fftsize/2+1;
         parametrs-> i2fin        = parametrs->fftsize/2+31;
         parametrs->Nc            = 1600;             
         parametrs->Nsc           = 12;               
         parametrs->Nrb_Max       = 110;            
         parametrs->Nrb_Min       = 6;             
         parametrs->Ns            = 20;
         parametrs->OSC           = 75;
         parametrs->adreses1       = 0x000110DC;
         parametrs ->MMCM            = 0x00000080;
         parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B1.txt";
         parametrs->windowing     = parametrs->fs/1000;
         
        memory_alloc(parametrs);
            
            for (int i = 0; i < 3; i++){
                for(int j = 0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j] = PSS128real_e[i][j];
        parametrs->PSSimag[i][j] = PSS128imag_e[i][j];
            }
        }
         
    break;
    
    case 3:
        parametrs->fftsize        = 256;
        parametrs->cp1            = 64;
        parametrs->cp             = 64;
        parametrs->fs             = 3.84e6;
        parametrs->Nrb            = 15;
        parametrs->i1start        = parametrs->fftsize/2-31;
        parametrs->i1fin          = parametrs->fftsize/2-1;
        parametrs->i2start        = parametrs->fftsize/2+1;
        parametrs->i2fin          = parametrs->fftsize/2+31;
        parametrs->Nc             = 1600;             
        parametrs->Nsc            = 12;               
        parametrs->Nrb_Max        = 110;            
        parametrs->Nrb_Min        = 6;             
        parametrs->Ns             = 20;
        parametrs->OSC           = 150;
        parametrs->adreses1       = 0x000210D2;
        parametrs ->MMCM            = 0x00000040;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B2.txt";
        parametrs->windowing     = parametrs->fs/2000;
       memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS256real_e[i][j];
        parametrs->PSSimag[i][j]=PSS256imag_e[i][j];
            }
        }
        
        
    break;

    case 7:
        parametrs->fftsize       = 512;
        parametrs->cp1           = 128;
        parametrs->cp            = 128;
        parametrs->fs            = 7.68e6;
        parametrs->Nrb           =  25;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 300;
        parametrs->adreses1       = 0x00031136;
         parametrs ->MMCM            = 0x00000020;
         parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B3.txt";
        parametrs->windowing     = parametrs->fs/2000;
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS512real_e[i][j];
        parametrs->PSSimag[i][j]=PSS512imag_e[i][j];
            }
        }
        
    break;

    case 15:
        parametrs->fftsize       = 1024;
        parametrs->cp1           = 256;
        parametrs->cp            = 256;
        parametrs->fs            = 15.36e6;
        parametrs->Nrb           = 50;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 600;
        parametrs->adreses1       = 0x000411D2;
        parametrs ->MMCM            = 0x00000010;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B4.txt";
        parametrs->windowing     = parametrs->fs/1000;
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS1024real[i][j];
        parametrs->PSSimag[i][j]=PSS1024imag[i][j];
            }
        }
        
    break;

    case 23:
        parametrs->fftsize       = 1536;
        parametrs->cp1           = 384;
        parametrs->cp            = 384;
        parametrs->fs            = 23.04e6;
        parametrs->Nrb           = 75;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs->fftsize/2+1;
        parametrs->i2fin         = parametrs->fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 900;
        parametrs->adreses1       = 0x000511A4;
        parametrs ->MMCM            = 0x00029A0A;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B5.txt";
        parametrs->windowing     = parametrs->fs/1000;
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS1536real_e[i][j];
        parametrs->PSSimag[i][j]=PSS1536imag_e[i][j];
            }
        }
        
    break;

    case 30:
        parametrs->fftsize       = 2048;
        parametrs->cp1           = 512;
        parametrs->cp            = 512;
        parametrs->fs            = 30.72e6;
        parametrs->Nrb           = 10;
        parametrs->i1start       = parametrs->fftsize/2-31;
        parametrs->i1fin         = parametrs->fftsize/2-1;
        parametrs->i2start       = parametrs-> fftsize/2+1;
        parametrs->i2fin         = parametrs-> fftsize/2+31;
        parametrs->Nc            = 1600;             
        parametrs->Nsc           = 12;               
        parametrs->Nrb_Max       = 110;            
        parametrs->Nrb_Min       = 6;             
        parametrs->Ns            = 20;
        parametrs->OSC           = 1200;
        parametrs->adreses1       = 0x000611AE;
        parametrs ->MMCM            = 0x00000008;
        parametrs->path   = "/root/test/tusur/TDD_detection2/signal/SSS_array_B6.txt";
        parametrs->windowing     = parametrs->fs/2000;
        memory_alloc(parametrs);
            for (int i = 0; i < 3; i++){
                for(int j=0;j<parametrs->fftsize+parametrs->cp;j++){
        parametrs->PSSreal[i][j]=PSS2048real_e[i][j];
        parametrs->PSSimag[i][j]=PSS2048imag_e[i][j];
            }
        }
       
    default:
        std::cout<<"Error::"<<std::endl;
    break;
    }
}

void funk::set_prefix(_parametrs *p1)
{
    if(_cp_mode == tch::CpMode::Normal)
    {   
        normal(p1);
        p1->cyclic = 1;
    }
    else
    {
        extetended(p1);
        p1->cyclic = 2;
    }
}

void funk::memory_alloc(_parametrs *p1)
{
    try
        {
        p1->PSSreal = new double*[3];
	
            for (int i = 0; i < 3; ++i)
        p1->PSSreal[i] = new double[p1->fftsize+p1->cp];
        p1->PSSimag = new double*[3];
            for (int i = 0; i < 3; ++i)
        p1->PSSimag[i] = new double[p1->fftsize+p1->cp];
        }

        catch (std::bad_alloc ba)
        {
            std::cout<<"no memory allocated"<<std::endl;
            std::cout<<ba.what()<<std::endl;
        }
}

void funk::clear_memory(_parametrs *p1)
{
    for(int i = 0; i<3; i ++)
    {
        delete[] p1->PSSreal[i];
        delete[] p1->PSSimag[i];
    }

    delete[] p1->PSSreal;
    delete[] p1->PSSimag;
}

funk::~funk()
{
}