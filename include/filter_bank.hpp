//
// Copyright 2010-2017 Parto
//

#ifndef INCLUDED_FILTER_BANK_HPP
#define INCLUDED_FILTER_BANK_HPP

#include <serial.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <wb_iface.hpp>
#include <string>
#include <wb_iface.hpp>
#include <ad9361_ctrl.hpp>
namespace pax {

/*!
 * The pax synchronization class:
 * Provides a set of functions to implementation layer.
 * Including spi, peek, poke, control...
 */
class PAX_API filter_bank
{
public:
    typedef boost::shared_ptr<filter_bank> sptr;

    typedef struct
    {
        typedef enum {AD_9361_0_GPO=0,AD_9361_1_GPO,PAX_GPIO,SETTING_REG_TO_PIN} FILTER_BANK_INTERFACE ; //add here any typeof interface you want
    }filter_bank_interface;



    static sptr  make(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
                      pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE _filter_bank_interface);



    typedef struct
    {
        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_HAND_OFF;
    }filter_bank_hand_off_value;
    virtual void hand_off_filter_bank_init()=0;
    virtual void set_filter_path_hand_off(filter_bank_hand_off_value::FILTER_PATH_HAND_OFF in)=0;

    typedef struct
    {
        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_SKY_V2;
    }filter_bank_sky_v2_value;
    virtual void sky_v2_filter_bank_init() = 0;
    virtual void set_filter_path_sky_v2(filter_bank_sky_v2_value::FILTER_PATH_SKY_V2) = 0;
    virtual void set_filter_path_sky_v2(float freq , bool set_ad9361 = true) = 0;



protected :
    filter_bank_interface::FILTER_BANK_INTERFACE interface_type;
    std::vector<pax::usrp::ad9361_ctrl::sptr> vAD9361;
    pax_iface::sptr iface;
    uint8_t wich_ad9361_ic;
};

}

#endif /* INCLUDED_PAX_SYNC_HPP */