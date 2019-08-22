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
public:
    /***********************************************************************
 * Structors
 **********************************************************************/

    filter_bank_impl(std::vector<pax::usrp::ad9361_ctrl::sptr>& _vAD9361, pax_iface::sptr _wb_iface,
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




};

}

#endif /* INCLUDED_PAX_SYNC_HPP */
