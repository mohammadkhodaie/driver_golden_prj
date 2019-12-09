//
// Copyright 2010-2016 Parto
//

#ifndef INCLUDE_FILTER_BANK_IMPLE_HPP
#define INCLUDE_FILTER_BANK_IMPLE_HPP

#include <filter_bank.hpp>

#include <device_addr.hpp>

#include <fw_common.h>
#include <exception.hpp>
#include <dict.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp> //used for htonl and ntohl
#include <boost/assign/list_of.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iostream>
#include <platform.hpp>
#include <tasks.hpp>
#include <pax_regs.hpp>
#include <boost/range/algorithm.hpp>
#include <exception>

namespace pax {

class PAX_API filter_bank_impl : public pax::filter_bank{
    typedef struct {
        uint8_t GPOA_CTRL_SW_RX;
        uint8_t GPOB_ATT_PUP;
        uint8_t GPOA_FLT_OUTSIDE;
        uint8_t GPOB_CTRL_SW_TX;
    }GPO_A_B_STAT;

public:
    /***********************************************************************
 * Structors
 **********************************************************************/

    filter_bank_impl(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
                     spi_wb_iface::sptr _spi_iface,
                     pax::filter_bank::filter_bank_interface::FILTER_BANK_INTERFACE filter_bank_interface);

    ~filter_bank_impl(void){}


    /***********************************************************************
     * air v2 metod
     **********************************************************************/

    virtual void sky_v2_filter_bank_init();
    virtual void set_filter_path_sky_v2(pax::filter_bank::filter_bank_sky_v2_value::FILTER_PATH_SKY_V2 in);
    virtual void set_filter_path_sky_v2(float freq , bool set_ad9361 = true);

    /***********************************************************************
     * handoff metod
     **********************************************************************/

    virtual void hand_off_filter_bank_init();

    virtual void set_filter_path_hand_off(pax::filter_bank::filter_bank_hand_off_value::FILTER_PATH_HAND_OFF in);
    virtual void set_filter_path_hand_off(float freq ,  bool set_ad9361);


    /***********************************************************************
     * virtex7 method
     **********************************************************************/

    virtual void virtex_filter_bank_init();
    virtual void set_filter_path_virtex(pax::filter_bank::filter_bank_virtex_value::FILTER_PATH_virtex in);
    virtual void set_filter_path_virtex(float freq , bool set_ad9361 = true);


    /***********************************************************************
     * simulator method
     **********************************************************************/

    virtual void simulator_filter_bank_init();
    virtual void set_filter_path_simulator(float freq, std::string direction, bool set_ad9361 = true);
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_30_6000MHz::sub_flt in);
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_100_1000MHz::sub_flt in);
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_500_2500MHz::sub_flt in);
    virtual void set_sub_filter_path_simulator(pax::filter_bank::filter_bank_sim_value::FILTER_PATH_2000_6000MHz::sub_flt in);
    virtual void set_rx_path_throw_outside_flt(bool throw_outside_amp = false);
    virtual void do_rx_attenuation(uint8_t value);
    void _get_direction_from_antenna(const std::string direction);

private:

    /***********************************************************************
     * air v2 parameter
     **********************************************************************/

    typedef enum {SR_GPO_0=0,SR_GPO_1=1,SR_GPO_2=2,SR_GPO_3=3} SETTING_REG_GPO_PIN_NUM;
    typedef enum {sky_v2_PIN_1=0,sky_v2_PIN_2,sky_v2_PIN_3,sky_v2_PIN_4} sky_v2_PIN_NUMBER;
    pax::dict<sky_v2_PIN_NUMBER,SETTING_REG_GPO_PIN_NUM> sky_v2_filter_pin_map;
    const uint32_t sr_filt_sw = 1021;

    /***********************************************************************
     * hand_off parameter
     **********************************************************************/

    typedef enum {ADGPO_0=0,ADGPO_1,ADGPO_2,ADGPO_3} AD_GPO_NUM;
    typedef enum {HAND_OFF_PIN_1=0,HAND_OFF_PIN_2,HAND_OFF_PIN_3,HAND_OFF_PIN_4} HAND_OFF_PIN_NUMBER;
    pax::dict<HAND_OFF_PIN_NUMBER,AD_GPO_NUM> hand_off_filter_pin_map;

    /***********************************************************************
     * virtex parameter
     **********************************************************************/

    typedef enum {VADGPO_0=0,VADGPO_1,VADGPO_2,VADGPO_3} VAD_GPO_NUM;
    typedef enum {VIRTEX_PIN_1=0,VIRTEX_PIN_2,VIRTEX_PIN_3,VIRTEX_PIN_4} VIRTEX_PIN_NUMBER;
    pax::dict<VIRTEX_PIN_NUMBER,VAD_GPO_NUM> virtex_filter_pin_map;

    /***********************************************************************
     * simulator parameter
     **********************************************************************/

    enum { RX = 0, TX } direction_t;
    static GPO_A_B_STAT sim_flt_status;
    static spi_config_t conf;
    static bool have_initiated_simulator;

};

}

#endif /* INCLUDED_PAX_SYNC_HPP */
