//
// Copyright 2012-2014 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_AD9361_CTRL_HPP
#define INCLUDED_AD9361_CTRL_HPP

#include <zero_copy.hpp>
#include <pax_iface.h>
#include <ranges.hpp>
#include <serial.hpp>
#include <sensors.hpp>
#include <exception.hpp>
#include <boost/shared_ptr.hpp>
#include <ad9361_device.h>
#include <string>
#include <complex>
#include <filters.hpp>
#include <vector>
#include <usrp2_fifo_ctrl.hpp>
#include <spi_wb_iface.hpp>

namespace pax { namespace usrp {

/*! AD936x Control Interface
 *
 * This is a convenient way to access the AD936x RF IC.
 * It basically encodes knowledge of register values etc. into
 * accessible API calls.
 *
 * \section ad936x_which The `which` parameter
 *
 * Many function calls require a `which` parameter to select
 * the RF frontend. Valid values for `which` are:
 * - RX1, RX2
 * - TX1, TX2
 *
 * Frontend numbering is as designed by the AD9361.
 */
enum CALIBRATION_MODE
{
    CALIBRATION_ON=1,
    CALIBRATION_OFF=3
};

//class PAX_API filter_bank; // PH

class ad9361_ctrl : public boost::noncopyable
{
public:
    typedef boost::shared_ptr<ad9361_ctrl> sptr;

    virtual ~ad9361_ctrl(void) {}

    //! make a new codec control object
    static sptr make_spi(ad9361_params::sptr client_settings, spi_wb_iface::sptr spi_iface, boost::uint32_t slave_num, int SW, adf4351::sptr ext_synth);

    //! Get a list of gain names for RX or TX
    static std::vector<std::string> get_gain_names(const std::string &/*which*/)
    {
        return std::vector<std::string>(1, "PGA");
    }

    //! get the gain range for a particular gain element
    static pax::meta_range_t get_gain_range(const std::string &which)
    {
        if(which[0] == 'R') {
            return pax::meta_range_t(0.0, 76.0, 1.0);
        } else {
            return pax::meta_range_t(0.0, 89.75, 0.25);
        }
    }

    //! get the freq range for the frontend which
    static pax::meta_range_t get_rf_freq_range(void)
    {
        return pax::meta_range_t(47e6, 9e9);
    }

    //! get the filter range for the frontend which
    static pax::meta_range_t get_bw_filter_range(const std::string &/*which*/)
    {
        return pax::meta_range_t(200e3, 56e6);
    }

    //! get the clock rate range for the frontend
    static pax::meta_range_t get_clock_rate_range(void)
    {
        //return pax::meta_range_t(220e3, 61.44e6);
        return pax::meta_range_t(5e6, ad9361_device_t::AD9361_MAX_CLOCK_RATE); //5 MHz DCM low end
    }

    virtual void set_filter_bank(boost::shared_ptr<filter_bank> flt) = 0; // PH

    //! set the filter bandwidth for the frontend's analog low pass
    virtual double set_bw_filter(const std::string &/*which*/, const double /*bw*/) = 0;

    //! set the gain for a particular gain element
    virtual double set_gain(const std::string &which, const double value) = 0;

    //! Enable or disable the AGC module
    virtual void set_agc(const std::string &which, bool enable) = 0;

    //! configure the AGC module to slow or fast mode
    virtual void set_agc_mode(const std::string &which, const std::string &mode) = 0;

    //! set a new clock rate, return the exact value
    virtual double set_clock_rate(const double rate) = 0;

    //! set which RX and TX chains/antennas are active
    virtual void set_active_chains(bool tx1, bool tx2, bool rx1, bool rx2) = 0;

    //! tune the given frontend, return the exact value
    virtual double tune(const std::string &which, const double value, bool set_filter_bank = true) = 0;

    //! set the DC offset for I and Q manually
    void set_dc_offset(const std::string &, const std::complex<double>)
    {
        //This feature should not be used according to Analog Devices
        throw pax::runtime_error("ad9361_ctrl::set_dc_offset this feature is not supported on this device.");
    }

    //! enable or disable the BB/RF DC tracking feature
    virtual void set_dc_offset_auto(const std::string &which, const bool on) = 0;

    //! set the IQ correction value manually
    void set_iq_balance(const std::string &, const std::complex<double>)
    {
        //This feature should not be used according to Analog Devices
        throw pax::runtime_error("ad9361_ctrl::set_iq_balance this feature is not supported on this device.");
    }

    //! enable or disable the quadrature calibration
    virtual void set_iq_balance_auto(const std::string &which, const bool on) = 0;

    //! get the current frequency for the given frontend
    virtual double get_freq(const std::string &which) = 0;

    //! turn on/off Catalina's data port loopback
    virtual void data_port_loopback(const bool on) = 0;

    //! read internal RSSI sensor
    virtual sensor_value_t get_rssi(const std::string &which) = 0;

    //! read the internal temp sensor
    virtual sensor_value_t get_temperature() = 0;

    //! List all available filters by name
    virtual std::vector<std::string> get_filter_names(const std::string &which) = 0;

    //! Return a list of all filters
    virtual filter_info_base::sptr get_filter(const std::string &which, const std::string &filter_name) = 0;

    //! Write back a filter
    virtual void set_filter(const std::string &which, const std::string &filter_name, const filter_info_base::sptr) = 0;

    virtual void output_digital_test_tone(bool enb) = 0;

    virtual void output_digital_test_prbs(bool enb) = 0;
     virtual void  set_delay(boost::int32_t clk, boost::int32_t data)=0;

    ///SBM

    //! Select LO generation mode
    virtual void set_clk_mux_parent(bool extint) = 0;

    //! force into alert state
    virtual void ensm_force_alert() = 0;

    //! force into fdd state
    virtual void ensm_force_fdd() = 0;

    //! Do one step of Multi-Chip Synchronization (MCS)
    virtual void do_mcs(boost::uint32_t step) = 0;

    //! fast tune the given frontend
    virtual double tunef(const std::string &which, const double value) = 0;

    //! GPO manual set
    virtual void GPO_manual_set(uint8_t GPO_channel,bool set_valu) = 0;

    virtual void swap_iq(const std::string &which,bool enable) = 0;
};

}}

#endif /* INCLUDED_AD9361_CTRL_HPP */
