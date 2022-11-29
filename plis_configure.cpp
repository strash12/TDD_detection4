#include "header.h"
#include <unistd.h>

plis_configure::plis_configure(_parametrs param)
{
    config  = param.adreses1;
    error   = 0;
}

plis_configure::~plis_configure()
{
}

void plis_configure::cofigure_plis()
{
    auto devmem = devmem::Devmem("/dev/mem", 0x83C20000, 2);
    auto devmem2 = devmem::Devmem("/dev/mem", 0x83C20004, 4);


    while (error<=5)
    {
        for(int i = 1; i < 4; i++ )
            {
                config = (config & 0xf0ffffff) | (i<<24); 
                devmem.write<uint8_t>(0, 0x1u);
                devmem2.write<uint32_t>(0, config);
                devmem.write<uint16_t>(0, 0x3u);
                devmem.write<uint16_t>(0, 0x1u);
                usleep(1000000);
                bool validate_bit = validate();
                if(validate_bit == 1){break;}
                if( i = 3){i = 1;}
            }
         if(error = 5)
            {
                std::string msg2 = "PSS found" ;
		        tch::write_common(msg2);
break;
            }
	error++;
    }
}

bool plis_configure::validate()
{
    auto devmem3 = devmem::Devmem("/dev/mem", 0x83C20008, 4);
    bits = devmem3.read<uint32_t>();
    int  verefi = bits>>28;
        if(verefi == 1)
            {
                std::string msg2 = "PSS found" ;
		        tch::write_common(msg2);
                return 1;
            }
        else{return 0;}
}

void plis_configure::SSS_upload(int CellId,_parametrs param)
{
    int numOfLines = 0;
    std::string digits;
    auto devmem = devmem::Devmem("/dev/mem", 0x83C20000, 2);
    auto devmem2 = devmem::Devmem("/dev/mem", 0x83C20004, 4);
    auto devmem3 = devmem::Devmem("/dev/mem", 0x83C20008, 4);

    config       = (config & 0x0fffffff);
    devmem2.write<uint32_t>(0, config);
    config       = (config & 0x0fffffff) | 1<<28;
    devmem2.write<uint32_t>(0,config);
    
    std::ifstream file;
    std::string fileName = "/root/test/tusur/TDD_detection2/SSS_array_B2.txt";
    file.open(param.path);

        if(!file.is_open())
        {
            std::cout<<"Error on open SSS file"<<std::endl;
            
        }
        
        while (numOfLines!=CellId && getline(file, digits))
        {
	numOfLines++;
        }
	
	for(int i = 0; i<param.fftsize;i++)
	{
            uint32_t SSS = 0x00000000;
   	    //SSS = (SSS & 0xfffffff0) | (digits[i]-0x30<<0) ;
//if(digits[i]>0x46)
  //  {
    //  std::cout<<"ERRRRRRRRRRRRRRRRRRRRROR"<<std::endl;
     // std::exit;
    //}
  // else
  if(digits[i]>0x39)
    {
      SSS = (SSS & 0xfffffff0) | (digits[i]-0x37);
    }
    else
    {
       SSS = (SSS & 0xfffffff0) | (digits[i]-0x30);
    }
		//std::cout<<std::hex<<SSS<<std::endl;
            
            devmem3.write<uint32_t>(0, SSS);
	    devmem.write<uint8_t>(0, 0x1u);
  	    devmem.write<uint16_t>(0, 0x3u);
            devmem.write<uint16_t>(0, 0x1u);
        
	}
}