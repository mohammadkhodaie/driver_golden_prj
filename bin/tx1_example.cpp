#include "recorder.hpp"
#include <eeprom.hpp>

int main(int argc, char* argv[])
{
    (void)argc;
    (void) argv;

    mb_container_type tester;
    std::vector<boost::shared_ptr<pax::transport::sph::recv_packet_streamer> > streamers=pax_init(tester,4);

#define _AD9361 0
#define _TEST_FREQ (1575e6)
    // disable clock from ad9361
    tester.iface->poke32(U2_REG_SR_ADDR(SR_ADC_CLK_EN), 0x0);

    double ADSampleRate;

        for (uint32_t i=0; i<tester.ad_9361.size(); i++){
            tester.ad_9361[i]->set_active_chains(true,false,false,false);

            tester.ad_9361[i]->tune("TX",_TEST_FREQ);
            tester.ad_9361[i]->set_gain("TX1",89.75);
            tester.ad_9361[i]->set_gain("TX2",85);
            ADSampleRate=tester.ad_9361[i]->set_clock_rate(40e6);
    //          tester.ad_9361[i]->swap_iq("TX",true);
            tester.ad_9361[i]->output_digital_test_tone(true);
        }

        std::cout << "Actual sample rate = " << ADSampleRate << std::endl;

        // enable clock from ad93611
        tester.iface->poke32(U2_REG_SR_ADDR(SR_ADC_CLK_EN), 0xff);


    return 0;
}
