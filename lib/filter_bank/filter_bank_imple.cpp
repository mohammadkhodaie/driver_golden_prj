#include "filter_bank_imple.hpp"


PAX_API pax::filter_bank::sptr pax::filter_bank::make(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _iface, spi_wb_iface::sptr _spi_iface,pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE _filter_bank_interface){
    return pax::filter_bank::sptr(new pax::filter_bank_impl(_vAD9361,_iface, _spi_iface, _filter_bank_interface));
}



pax::filter_bank_impl::filter_bank_impl(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
                                        spi_wb_iface::sptr _spi_iface,
                                        pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE filter_bank_interface){
    vAD9361 = _vAD9361;
    iface = _wb_iface;
    spi_iface = _spi_iface;
    interface_type = filter_bank_interface;
    if(interface_type == filter_bank_interface::AD_9361_0_GPO)
        which_ad9361_ic=0;
    else if(interface_type == filter_bank_interface::AD_9361_1_GPO)
        which_ad9361_ic=1;
    else if(interface_type == filter_bank_interface::AD_9361_2_GPO)
        which_ad9361_ic=2;
    else if(interface_type == filter_bank_interface::AD_9361_3_GPO)
        which_ad9361_ic=3;
    else if(interface_type == filter_bank_interface::SPI_to_GPO0)
        which_ad9361_ic=0;
    else if(interface_type == filter_bank_interface::SPI_to_GPO1)
        which_ad9361_ic=1;
    else if(interface_type == filter_bank_interface::SPI_to_GPO2)
        which_ad9361_ic=2;
    else if(interface_type == filter_bank_interface::SPI_to_GPO3)
        which_ad9361_ic=3;
    else if(interface_type == filter_bank_interface::SPI_to_GPO4)
        which_ad9361_ic=4;
    else if(interface_type == filter_bank_interface::SPI_to_GPO5)
        which_ad9361_ic=5;
    else if(interface_type == filter_bank_interface::SPI_to_GPO6)
        which_ad9361_ic=6;
    else if(interface_type == filter_bank_interface::SPI_to_GPO7)
        which_ad9361_ic=7;

    sky_v2_filter_bank_init();
    virtex_filter_bank_init();
    hand_off_filter_bank_init();
    simulator_filter_bank_init();
}




 void pax::filter_bank_impl::sky_v2_filter_bank_init(){

    sky_v2_filter_pin_map[sky_v2_PIN_1]=SR_GPO_0;
    sky_v2_filter_pin_map[sky_v2_PIN_2]=SR_GPO_1;
    sky_v2_filter_pin_map[sky_v2_PIN_3]=SR_GPO_2;
    sky_v2_filter_pin_map[sky_v2_PIN_4]=SR_GPO_3;

}

void pax::filter_bank_impl::set_filter_path_sky_v2(float freq ,  bool set_ad9361){
    if(freq <= 60e6){
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_40MHz);
    } else if( freq <= 130e6) {
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_100MHz);
    } else if (freq <= 264e6){
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_250MHz);
    } else if (freq <= 470e6){
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_450MHz);
    } else if (freq <= 1000e6){
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_900MHz);
    } else if (freq <=2400e6){
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_2200MHz);
    }else {
        set_filter_path_sky_v2(filter_bank_sky_v2_value::low_pass_6000MHz);
    }
    if(set_ad9361){
        vAD9361[0]->tune("RX",freq, false);
    }
}

 void pax::filter_bank_impl::set_filter_path_sky_v2(pax::filter_bank::filter_bank_sky_v2_value::FILTER_PATH_SKY_V2 path){
        uint32_t temp=0;
        switch (path) {
        case filter_bank_sky_v2_value::low_pass_40MHz :{
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
        case filter_bank_sky_v2_value::low_pass_100MHz:   {
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
        case filter_bank_sky_v2_value::low_pass_250MHz:   {
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
        case filter_bank_sky_v2_value::low_pass_450MHz:
        {
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
        case filter_bank_sky_v2_value::low_pass_900MHz:   {
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
         case filter_bank_sky_v2_value::low_pass_2200MHz:  {
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
            case filter_bank_sky_v2_value::low_pass_6000MHz:  {
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_1]);
            temp |= (1) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_2]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_3]);
            temp |= (0) << static_cast<uint32_t>(sky_v2_filter_pin_map[sky_v2_PIN_4]);
        }break;
        default:
            throw value_error("wrong filter bank air v2 input");
            break;
        }


        iface->poke32(U2_REG_SR_ADDR(sr_filt_sw),temp);

    }


void pax::filter_bank_impl::hand_off_filter_bank_init(){
    hand_off_filter_pin_map[HAND_OFF_PIN_1]=ADGPO_0;
    hand_off_filter_pin_map[HAND_OFF_PIN_2]=ADGPO_1;
    hand_off_filter_pin_map[HAND_OFF_PIN_3]=ADGPO_2;
    hand_off_filter_pin_map[HAND_OFF_PIN_4]=ADGPO_3;

}





void pax::filter_bank_impl::set_filter_path_hand_off(pax::filter_bank::filter_bank_hand_off_value::FILTER_PATH_HAND_OFF path){

    switch (path) {
    case filter_bank_hand_off_value::low_pass_40MHz :{
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],1);
    }break;
    case filter_bank_hand_off_value::low_pass_100MHz:   {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],0);
    }break;
    case filter_bank_hand_off_value::low_pass_250MHz:   {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],1);
    }break;
    case filter_bank_hand_off_value::low_pass_450MHz:   {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],0);
    }break;
        case filter_bank_hand_off_value::low_pass_900MHz:   {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],0);
    }break;
        case filter_bank_hand_off_value::low_pass_2200MHz:  {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],0);
    }break;
        case filter_bank_hand_off_value::low_pass_6000MHz:  {
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_1],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_2],1);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_3],0);
        vAD9361[which_ad9361_ic]->GPO_manual_set(hand_off_filter_pin_map[HAND_OFF_PIN_4],0);
    }break;
    default:
        throw value_error("filter bank hand off input");
        break;
    }
}


void pax::filter_bank_impl::set_filter_path_hand_off(float freq ,  bool set_ad9361){
    if(freq <= 60e6){
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_40MHz);
    } else if( freq <= 130e6) {
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_100MHz);
    } else if (freq <= 264e6) {
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_250MHz);
    } else if (freq <= 470e6) {
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_450MHz);
    } else if (freq <= 1000e6){
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_900MHz);
    } else if (freq <=2400e6) {
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_2200MHz);
    } else {
        set_filter_path_hand_off(filter_bank_hand_off_value::low_pass_6000MHz);
    }
    if(set_ad9361){
        vAD9361[which_ad9361_ic]->tune("RX",freq, false);
    }
}



    void pax::filter_bank_impl::virtex_filter_bank_init(){
        virtex_filter_pin_map[VIRTEX_PIN_1]=VADGPO_0;
        virtex_filter_pin_map[VIRTEX_PIN_2]=VADGPO_1;
        virtex_filter_pin_map[VIRTEX_PIN_3]=VADGPO_2;
        virtex_filter_pin_map[VIRTEX_PIN_4]=VADGPO_3;

    }





    void pax::filter_bank_impl::set_filter_path_virtex(pax::filter_bank::filter_bank_virtex_value::FILTER_PATH_virtex path){

        switch (path) {
        case filter_bank_virtex_value::low_pass_40MHz :{
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],1);
        }break;
        case filter_bank_virtex_value::low_pass_100MHz:   {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],0);
        }break;
        case filter_bank_virtex_value::low_pass_250MHz:   {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],1);
        }break;
        case filter_bank_virtex_value::low_pass_450MHz:   {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],0);
        }break;
            case filter_bank_virtex_value::low_pass_900MHz:   {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],0);
        }break;
            case filter_bank_virtex_value::low_pass_2200MHz:  {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],0);
        }break;
            case filter_bank_virtex_value::low_pass_6000MHz:  {
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_1],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_2],1);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_3],0);
            vAD9361[which_ad9361_ic]->GPO_manual_set(virtex_filter_pin_map[VIRTEX_PIN_4],0);
        }break;
        default:
            throw value_error("filter bank virtex input");
            break;
        }
}

void pax::filter_bank_impl::set_filter_path_virtex(float freq ,  bool set_ad9361){
    if(freq <= 60e6){
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_40MHz);
    } else if( freq <= 130e6) {
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_100MHz);
    } else if (freq <= 264e6) {
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_250MHz);
    } else if (freq <= 470e6) {
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_450MHz);
    } else if (freq <= 1000e6){
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_900MHz);
    } else if (freq <=2400e6) {
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_2200MHz);
    } else {
        set_filter_path_virtex(filter_bank_virtex_value::low_pass_6000MHz);
    }
    if(set_ad9361){
        vAD9361[which_ad9361_ic]->tune("RX",freq, false);
    }
}

pax::filter_bank_impl::GPO_A_B_STAT pax::filter_bank_impl::sim_flt_status;
pax::spi_config_t pax::filter_bank_impl::conf;
bool pax::filter_bank_impl::have_initiated_simulator = false;

void pax::filter_bank_impl::simulator_filter_bank_init(){
    if (!have_initiated_simulator){
        have_initiated_simulator = true;
        conf.mosi_edge = conf.EDGE_RISE;
        spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x0A << 8) | 0x24, 24);
        spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x00 << 8) | 0x00, 24);
        spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x01 << 8) | 0x00, 24);
        spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x0C << 8) | 0xFF, 24);
        spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x0D << 8) | 0xFF, 24);
        spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x0A << 8) | 0x24, 24);
        spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x00 << 8) | 0x00, 24);
        spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x01 << 8) | 0x00, 24);
        spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x0C << 8) | 0xFF, 24);
        spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x0D << 8) | 0xFF, 24);
    }
    set_rx_path_throw_outside_flt(false);
    do_rx_attenuation(0);
}

void pax::filter_bank_impl::set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_30_6000MHz::sub_flt in){
    std::vector<uint8_t> vec = {0x3, 0x0, 0x1, 0x2, 0xc, 0x8, 0x4};
    uint8_t last = sim_flt_status.GPOA_CTRL_SW_RX;

    switch (which_ad9361_ic) {
    case 1:
    case 3:
        sim_flt_status.GPOA_CTRL_SW_RX &= 0xf0;
        sim_flt_status.GPOA_CTRL_SW_RX |= vec[static_cast<int>(in)] << 0;
        break;
    case 5:
    case 7:
        sim_flt_status.GPOA_CTRL_SW_RX &= 0x0f;
        sim_flt_status.GPOA_CTRL_SW_RX |= vec[static_cast<int>(in)] << 4;
        break;
    default:
        break;
    }
    if(last == sim_flt_status.GPOA_CTRL_SW_RX)
        return;
    spi_iface->write_spi((1 << 10), conf, ((1 << 6) << 16) | (0x12 << 8) | sim_flt_status.GPOA_CTRL_SW_RX, 24);
}

void pax::filter_bank_impl::set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_100_1000MHz::sub_flt in){
    std::vector<uint8_t> vec = {0x0, 0x1, 0x2, 0x3};
    uint8_t last = sim_flt_status.GPOB_CTRL_SW_TX;
    sim_flt_status.GPOB_CTRL_SW_TX &= 0xf3;
    sim_flt_status.GPOB_CTRL_SW_TX |= vec[static_cast<int>(in)] << 2;
    if(last == sim_flt_status.GPOB_CTRL_SW_TX)
        return;
    spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x13 << 8) | sim_flt_status.GPOB_CTRL_SW_TX, 24);
}

void pax::filter_bank_impl::set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_500_2500MHz::sub_flt in){
    std::vector<uint8_t> vec = {0x2, 0x1};
    uint8_t last = sim_flt_status.GPOB_CTRL_SW_TX;
    sim_flt_status.GPOB_CTRL_SW_TX &= 0xfc;
    sim_flt_status.GPOB_CTRL_SW_TX |= vec[static_cast<int>(in)] << 0;
    if(last == sim_flt_status.GPOB_CTRL_SW_TX)
        return;
    spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x13 << 8) | sim_flt_status.GPOB_CTRL_SW_TX, 24);
}

void pax::filter_bank_impl::set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_2000_6000MHz::sub_flt in){
    std::vector<uint8_t> vec = {0x1, 0x2};
    uint8_t last = sim_flt_status.GPOB_CTRL_SW_TX;
    sim_flt_status.GPOB_CTRL_SW_TX &= 0xcf;
    sim_flt_status.GPOB_CTRL_SW_TX |= vec[static_cast<int>(in)] << 4;
    if(last == sim_flt_status.GPOB_CTRL_SW_TX)
        return;
    spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x13 << 8) | sim_flt_status.GPOB_CTRL_SW_TX, 24);
}


void pax::filter_bank_impl::set_filter_path_simulator(float freq, std::string direction, bool set_ad9361){
    _get_direction_from_antenna(direction);

    if(direction_t == RX){
        switch (which_ad9361_ic) {
            case 1:
            case 3:
            case 5:
            case 7:
                if(freq <= 60e6){
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_40MHz);
                } else if( freq <= 130e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_100MHz);
                } else if (freq <= 264e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_250MHz);
                } else if (freq <= 470e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_450MHz);
                } else if (freq <= 1000e6){
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_900MHz);
                } else if (freq <=2400e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_2200MHz);
                } else {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_30_6000MHz::low_pass_6000MHz);
                }
                break;
            default:
                break;
        }
    }else if(direction_t == TX){
        switch (which_ad9361_ic) {
            case 4:
            case 5:
                if (freq <= 1000e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_500_2500MHz::low_pass_900MHz);
                } else {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_500_2500MHz::low_pass_2200MHz);
                }
                break;
            case 2:
            case 3:
                if( freq <= 130e6) {
                   set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_100_1000MHz::low_pass_100MHz);
                } else if (freq <= 264e6) {
                   set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_100_1000MHz::low_pass_250MHz);
                } else if (freq <= 470e6) {
                   set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_100_1000MHz::low_pass_450MHz);
                } else {
                   set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_100_1000MHz::low_pass_900MHz);
                }
                break;
            case 0:
            case 1:
                if (freq <= 1000e6) {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_2000_6000MHz::low_pass_900MHz);
                } else {
                    set_sub_filter_path_simulator(filter_bank_sim_value::FILTER_PATH_2000_6000MHz::low_pass_2200MHz);
                }
                break;
            default:
                break;
        }
    }
    if(set_ad9361){
        vAD9361[which_ad9361_ic]->tune(direction,freq, false);
    }

}


void pax::filter_bank_impl::_get_direction_from_antenna(const std::string direction)
{
    std::string sub = direction.substr(0, 2);
    if (sub == "RX") {
        direction_t = RX;
    } else if (sub == "TX") {
        direction_t = TX;
    } else {
        direction_t = RX;
        throw pax::runtime_error("filter_bank got an invalid channel string.");
    }
}

void pax::filter_bank_impl::set_rx_path_throw_outside_flt(bool throw_outside_amp){
    switch (which_ad9361_ic) {
    case 1:
    case 3:
        sim_flt_status.GPOA_FLT_OUTSIDE |= 0x11;
        sim_flt_status.GPOA_FLT_OUTSIDE &= ~(1 << 7);
        sim_flt_status.GPOA_FLT_OUTSIDE |= !throw_outside_amp << 7;
        break;
    case 5:
    case 7:
        sim_flt_status.GPOA_FLT_OUTSIDE |= 0x11;
        sim_flt_status.GPOA_FLT_OUTSIDE &= ~(1 << 3);
        sim_flt_status.GPOA_FLT_OUTSIDE |= !throw_outside_amp << 3;
        break;
    default:
        break;
    }

    spi_iface->write_spi((1 << 11), conf, ((1 << 6) << 16) | (0x12 << 8) | sim_flt_status.GPOA_FLT_OUTSIDE, 24);
}

void pax::filter_bank_impl::do_rx_attenuation(uint8_t value){
    if(value > 45)
        value = 45;

    value /= 3;
    value ^= 0xf;
    switch (which_ad9361_ic) {
    case 1:
    case 3:
        spi_iface->write_spi((1 << 13), conf, value, 4);
        break;
    case 5:
    case 7:
        spi_iface->write_spi((1 << 12), conf, value, 4);
        break;
    default:
        break;
    }
}

