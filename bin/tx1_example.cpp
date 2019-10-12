#include "recorder.hpp"
#include <eeprom.hpp>

int main(int argc, char* argv[])
{
    (void)argc;
    (void) argv;

    mb_container_type tester;
    std::vector<boost::shared_ptr<pax::transport::sph::recv_packet_streamer> > streamers=pax_init(tester,2);

#define _AD9361 1
#define _TEST_FREQ (70e6)
    // disable clock from ad9361
    tester.iface->poke32(U2_REG_SR_ADDR(SR_ADC_CLK_EN), 0x0);

    double ADSampleRate;

        for (uint32_t i=0; i<(tester.N_AD9361 + tester.N_AD9364); i++){
            tester.ad_9361[i]->set_active_chains(true,false,false,false);

            tester.ad_9361[i]->tune("TX",_TEST_FREQ);
            tester.ad_9361[i]->set_gain("TX1",50);
            tester.ad_9361[i]->set_gain("TX2",50);
            ADSampleRate=tester.ad_9361[i]->set_clock_rate(40e6);
    //          tester.ad_9361[i]->swap_iq("TX",true);
            tester.ad_9361[i]->output_digital_test_tone(false);
        }

        std::cout << "Actual sample rate = " << ADSampleRate << std::endl;

        // enable clock from ad93611
        tester.iface->poke32(U2_REG_SR_ADDR(SR_ADC_CLK_EN), 0xff);
        tester.sync->do_mcs();

        tester.sync->PAX8V7_rx_cal_mode(false);


    tester.iface->poke32(U2_REG_SR_ADDR(SR_RX_SW),1);

    std::vector<boost::uint32_t> dd(10000,0);
    std::complex<int16_t> *buffer = (std::complex<int16_t>*)malloc(10000*sizeof(std::complex<int16_t>));
    for(int i=0;i<10000;i++)
    {
    buffer[i].real(pax::htonx(((boost::uint16_t)(((float)(1<<7))*std::cos(.10*boost::math::constants::pi<double>()*(double)i/10.0)+.5))));
    buffer[i].imag(pax::htonx((((boost::uint16_t)(((float)(1<<7))*std::sin(.10*boost::math::constants::pi<double>()*(double)i/10.0)+.5)))));
  //  buffer[i].real(0xAABB);
   // buffer[i].imag(0xabcd);
    }



    // setup dds
    tester.iface->poke32(U2_REG_SR_ADDR(980),1);
    tester.iface->poke32(U2_REG_SR_ADDR(981),(0x000f<<16)|0x000f); // scale_0
    tester.iface->poke32(U2_REG_SR_ADDR(982),(0<<16)|32768>>1); // phase_0
    tester.iface->poke32(U2_REG_SR_ADDR(983),((32768>>10)<<16)|32768>>10); // incr_0
    //tester.iface->poke32(U2_REG_SR_ADDR(983),((0>>6)<<16)|0>>6); // incr_0
    tester.iface->poke32(U2_REG_SR_ADDR(984),(0<<16)|0); // scale_1
    tester.iface->poke32(U2_REG_SR_ADDR(985),(0<<16)|0); // phase_1
    tester.iface->poke32(U2_REG_SR_ADDR(986),(0<<16)|0); // incr_1
    tester.iface->poke32(U2_REG_SR_ADDR(980),0);

    tester.iface->poke32(U2_REG_SR_ADDR(255),0x0);

    tester.tx_dsp[3]->set_tick_rate(4*ADSampleRate);
    tester.tx_dsp[3]->set_link_rate(ADSampleRate);
    tester.tx_dsp[3]->set_host_rate(10e6);
    tester.tx_dsp[3]->set_freq(0.0e6);


    tester.time64->set_tick_rate(100e6);
    tester.time64->set_time_now(pax::time_spec_t(0.0f));

    tester.ad_9361[0]->set_iq_balance_auto("RX",true);
    boost::this_thread::sleep(boost::posix_time::milliseconds(0));

    pax::tx_metadata_t  md;
    md.start_of_burst = true;
        md.end_of_burst   = false;
        md.has_time_spec  = false;
        md.time_spec = pax::time_spec_t(1.0); //give us 0.1 seconds to fill the tx buffers
    while(1){
        tester.tx_streamers[0]->send(buffer,10000,md,3);
//       pax::transport::sph::send_packet_streamer::send()
        md.end_of_burst   = false;
        md.start_of_burst = false;
        md.has_time_spec  = false;
      //  std::cout<<incr++<<std::endl<<std::flush;

    }

    return 0;
}
