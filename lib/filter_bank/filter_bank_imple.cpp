#include "filter_bank_imple.hpp"



PAX_API pax::filter_bank::sptr pax::filter_bank::make(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _iface,pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE _filter_bank_interface){
    return pax::filter_bank::sptr(new pax::filter_bank_impl(_vAD9361,_iface,_filter_bank_interface));
}



pax::filter_bank_impl::filter_bank_impl(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
                                   pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE filter_bank_interface){
    vAD9361 = _vAD9361;
    iface = _wb_iface;
    interface_type = filter_bank_interface;
    if(interface_type == filter_bank_interface::AD_9361_0_GPO)
        which_ad9361_ic=0;
    else if(interface_type == filter_bank_interface::AD_9361_1_GPO)
        which_ad9361_ic=1;
    else if(interface_type == filter_bank_interface::AD_9361_2_GPO)
        which_ad9361_ic=2;
    else if(interface_type == filter_bank_interface::AD_9361_3_GPO)
        which_ad9361_ic=3;

    sky_v2_filter_bank_init();
    virtex_filter_bank_init();
    hand_off_filter_bank_init();

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

