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

class ad9361_ctrl;

class PAX_API filter_bank
{
public:
    typedef boost::shared_ptr<filter_bank> sptr;

    typedef struct
    {
        typedef enum {AD_9361_0_GPO=0,
                      AD_9361_1_GPO,
                      AD_9361_2_GPO,
                      AD_9361_3_GPO,
                      PAX_GPIO,SETTING_REG_TO_PIN
                     ,SPI_to_GPO0
                     ,SPI_to_GPO1
                     ,SPI_to_GPO2
                     ,SPI_to_GPO3
                     ,SPI_to_GPO4
                     ,SPI_to_GPO5
                     ,SPI_to_GPO6
                     ,SPI_to_GPO7} FILTER_BANK_INTERFACE ; //add here any typeof interface you want
    }filter_bank_interface;



    static sptr  make(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
                      pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE _filter_bank_interface);



    typedef struct
    {
        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_HAND_OFF;
    }filter_bank_hand_off_value;
    virtual void hand_off_filter_bank_init()=0;
    virtual void set_filter_path_hand_off(filter_bank_hand_off_value::FILTER_PATH_HAND_OFF in)=0;
    virtual void set_filter_path_hand_off(float freq , bool set_ad9361 = true) = 0;

    typedef struct
    {
        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_SKY_V2;
    }filter_bank_sky_v2_value;

    typedef struct
    {
        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_virtex;
    }filter_bank_virtex_value;


    typedef struct
    {
        typedef struct
        {
            typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} sub_flt;
        }FILTER_PATH_30_6000MHz;

        typedef struct
        {
            typedef enum {low_pass_900MHz,low_pass_2200MHz} sub_flt;
        }FILTER_PATH_2000_6000MHz;

        typedef struct
        {
            typedef enum {low_pass_900MHz,low_pass_2200MHz} sub_flt;
        }FILTER_PATH_500_2500MHz;

        typedef struct
        {
            typedef enum {low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz} sub_flt;
        }FILTER_PATH_100_1000MHz;
    }filter_bank_sim_value;

    virtual void sky_v2_filter_bank_init() = 0;
    virtual void set_filter_path_sky_v2(filter_bank_sky_v2_value::FILTER_PATH_SKY_V2) = 0;
    virtual void set_filter_path_sky_v2(float freq , bool set_ad9361 = true) = 0;

    virtual void virtex_filter_bank_init() = 0;
    virtual void set_filter_path_virtex(pax::filter_bank::filter_bank_virtex_value::FILTER_PATH_virtex in) = 0;
    virtual void set_filter_path_virtex(float freq , bool set_ad9361 = true) = 0;

    virtual void simulator_filter_bank_init() = 0;
    virtual void set_filter_path_simulator(float freq ,std::string direction, bool set_ad9361 = true) = 0;
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_30_6000MHz::sub_flt in) = 0;
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_100_1000MHz::sub_flt in) = 0;
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_500_2500MHz::sub_flt in) = 0;
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_2000_6000MHz::sub_flt in) = 0;
    virtual void set_rx_path_throw_outside_flt(bool throw_outside_amp) = 0;
    virtual void do_rx_attenuation(uint8_t value) = 0;
protected :
    filter_bank_interface::FILTER_BANK_INTERFACE interface_type;
    std::vector<pax::usrp::ad9361_ctrl::sptr> vAD9361;
    pax_iface::sptr iface;
    uint8_t which_ad9361_ic;
};

}

#endif /* INCLUDED_PAX_SYNC_HPP */
