#include "header.h"

create_mark::create_mark(_parametrs _param, tch::FullTusurCommonConfig _config)
    :plis_configure(_param)
{
    cor_lvl = _config.correlation_level;
    automatic = _config.automatic_threshold;
	param = _param;
    create_mark::config_all();
    
}

create_mark::~create_mark()
{
}

void create_mark::config_all()
{
     
    configure_pss();
    signal = load_signal_with_dma();
    PSS_CORR();
    SSS_proc();
    SSS_upload(CellID,param);
    shift();
    
    
    TDD_configure(TDD_config);

    signal.clear();
    auto msg = "Frame = " + std::to_string(Frame) + "\n" + "CellId = " + std::to_string(CellID)+ " \n first = "+std::to_string(first) + "\n angle = " + std::to_string(angle)
    + "\n TDD config = " + std::to_string(TDD_config);
    tch::write_common(msg);
}



void create_mark::configure_pss()
{
    cofigure_plis();
}


std::vector<int32_t> create_mark::load_signal_with_dma()
{
    auto samples = dmac::read<int32_t>(800000);
    
    return samples;
}

void create_mark::PSS_CORR()
{
    
    PSS_corr PSS(param);
    
    first = PSS.Primary_sync_signal_corr(signal,param);
}

void create_mark::SSS_proc()
{
 
    SSS_PROC SSS(param,first,signal);
    SSS.CUT_SSS(Frame,CellID);
if(Frame == 2){first = first + param.fs * 0.005;}
}

void create_mark::shift()
{
    freq_shift freq(signal,param,first);
    angle = freq.angle();
   
}

void create_mark::TDD_configure(int &TDD_config)
{
    TDD_detection TDD(first,angle,param,signal,CellID);
    TDD.TDD_calculation(TDD_config);
}