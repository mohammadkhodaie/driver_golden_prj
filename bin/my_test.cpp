#include "recorder.hpp"
#include <pax_reload.hpp>
#include <string>

int main(int argc, char* argv[])
{
    (void)argc;
    (void) argv;

        mb_container_type tester;
        std::vector<boost::shared_ptr<pax::transport::sph::recv_packet_streamer> > streamers=pax_init(tester,8);



        //tester.filter_bank[4]->set_filter_path_simulator(1000e6, "RX", false);
        //std::cout << "ok!";


//        while(1){
//            for(int i = 0; i < 3000; i++)
//                for(int j = 2; j < 4; j++)
//                    tester.ad_9361[j]->tune("RX",(50+i)*1e6);
//        }
        /*pax::flash_vec_t x = tester.iface->read_uid_flash();
        std::cout << "%%%%%%%%" << std::endl;

        for(int i = 0; i < x.size(); i++)
            std::cout << x[i] << std::endl;*/

        //tester.iface->erase_flash(0x0,10);
        //tester.iface->write_flash(0x5,582);
        //pax::flash_vec_t uid = tester.iface->read_uid_flash();//PH


        //pax::pax_reload::sptr reloader = pax::pax_reload::make(tester.iface);
        //reloader->burn_fpga_image(0,"/home/parto/Desktop/pax/PAX8/Pax8V7/PAX8_V7/PAX8_V7_fw_UNLOCK_.bit");

        //tester.iface->_bpi_write_reg(5,666);
        //std::cout << "****" << tester.iface->_bpi_read_reg(5);

        /*{

            tester.iface->cfi_read_all_device_ident();
            tester.iface->cfi_queries();
            tester.iface->cfi_unlock_and_erase_block(0);


            tester.iface->_bpi_write_reg(5,666);
            std::cout << "************" << tester.iface->_bpi_read_reg(0xE01004E) << std::endl;


            std::cout << "begin: " << std::endl;
            clock_t begin = clock();
            for(int i=0; i<8; i++) {
                tester.iface->cfi_data_write_32bits(0x00000000 + 4*i, 0x000c0000 + i);
            }
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "write time: " << elapsed_secs<<std::endl;

            begin = clock();
            for(int i=0; i<8; i++) {
                uint32_t t1 = tester.iface->cfi_read_16_bits(0x00000000 +4*i);
                uint32_t t2 = tester.iface->cfi_read_16_bits(0x00000000 +4*i+2);
                uint32_t res = t2 + (t1 << 16);
                if(res != (0x000c0000 + i))
                    std::cout << t1 << "    ___   " << t2 << std::endl;
            }
            end = clock();
            std::cout << "end: " << std::endl;
            elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "read time: " << elapsed_secs<<std::endl;
            uint32_t time = tester.iface->cfi_read_32_bits(32*1024*4);
            std::cout<<time<<std::endl;

        }*/













//       tester.iface->poke32(U2_REG_SR_ADDR(1022),0);
//        tester.iface->poke32(U2_REG_SR_ADDR(1023),65535);

//        while(true){
//        tester.iface->poke32(U2_REG_SR_ADDR(101),0x0);
//        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
//        tester.iface->poke32(U2_REG_SR_ADDR(101),0x1);
//        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

//}


//        while(1){
//            std::cout << tester.iface->peek32(U2_REG_SR_ADDR(101)) << std::endl;
//            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
//        }
        //tester.sync->PAX8V7_calibration();
        //      tester.iface->poke32(U2_REG_SR_ADDR(100),8); //GO TO 12V


        //        typedef enum {low_pass_40MHz=0,low_pass_100MHz,low_pass_250MHz,low_pass_450MHz,low_pass_900MHz,low_pass_2200MHz,low_pass_6000MHz} FILTER_PATH_virtex;



        int which_9364 = 0;
        long int freq = 500e6;
        int gain = 65.5;


        for (uint32_t i=0; i<(tester.N_AD9361 + tester.N_AD9364); i++){
            if(i != which_9364){
            tester.ad_9361[i]->set_active_chains(false,false,false,false);
            tester.ad_9361[i]->tune("TX",freq,true);
            tester.ad_9361[i]->set_gain("TX1",0);
            tester.ad_9361[i]->output_digital_test_tone(false);
            }
        }

        tester.ad_9361[which_9364]->set_active_chains(true,false,false,false);
        tester.ad_9361[which_9364]->tune("TX",freq,true);
        tester.ad_9361[which_9364]->set_gain("TX1",gain);
        tester.ad_9361[which_9364]->output_digital_test_tone(true);


        // enable clock from ad93611
        tester.iface->poke32(U2_REG_SR_ADDR(SR_ADC_CLK_EN), 0xff);

        std::cout<<"1";

        while(true){
            /*tester.filter_bank[0]->set_filter_path_simulator(900e6,"TX",false);
            tester.ad_9361[0]->tune("TX",50e6,false);
            tester.ad_9361[0]->tune("TX",500e6,false);
            tester.ad_9361[0]->tune("TX",1000e6,false);
            tester.filter_bank[0]->set_filter_path_simulator(2200e6,"TX",false);
            tester.ad_9361[0]->tune("TX",50e6,false);
            tester.ad_9361[0]->tune("TX",1000e6,false);
            tester.ad_9361[0]->tune("TX",2400e6,false);

            tester.filter_bank[2]->set_filter_path_simulator(100e6,"TX",false);
            tester.ad_9361[2]->tune("TX",50e6,false);
            tester.ad_9361[2]->tune("TX",90e6,false);
            tester.ad_9361[2]->tune("TX",130e6,false);
            tester.filter_bank[2]->set_filter_path_simulator(200e6,"TX",false);
            tester.ad_9361[2]->tune("TX",50e6,false);
            tester.ad_9361[2]->tune("TX",100e6,false);
            tester.ad_9361[2]->tune("TX",264e6,false);
            tester.filter_bank[2]->set_filter_path_simulator(300e6,"TX",false);
            tester.ad_9361[2]->tune("TX",50e6,false);
            tester.ad_9361[2]->tune("TX",200e6,false);
            tester.ad_9361[2]->tune("TX",470e6,false);
            tester.filter_bank[2]->set_filter_path_simulator(500e6,"TX",false);
            tester.ad_9361[2]->tune("TX",50e6,false);
            tester.ad_9361[2]->tune("TX",500e6,false);
            tester.ad_9361[2]->tune("TX",1000e6,false);



            tester.filter_bank[4]->set_filter_path_simulator(900e6,"TX",false);
            tester.ad_9361[4]->tune("TX",50e6,false);
            tester.ad_9361[4]->tune("TX",500e6,false);
            tester.ad_9361[4]->tune("TX",1000e6,false);
            tester.filter_bank[4]->set_filter_path_simulator(2200e6,"TX",false);
            tester.ad_9361[4]->tune("TX",50e6,false);
            tester.ad_9361[4]->tune("TX",1000e6,false);
            tester.ad_9361[4]->tune("TX",2400e6,false);*/

        /*while(1){
            //for(int i = 1; i < 8; i+=4){
            int i = 1;

            tester.ad_9361[1]->tune("RX",60e6,true);
            tester.ad_9361[1]->tune("RX",450e6,true);
            tester.ad_9361[1]->tune("RX",60e6,true);




                tester.filter_bank[i]->do_rx_attenuation(0);
                tester.filter_bank[i]->set_filter_path_simulator(60e6, "RX", false);
//                tester.filter_bank[i]->set_rx_path_throw_outside_flt(true);
//                tester.filter_bank[i]->set_rx_path_throw_outside_flt(false);
                tester.filter_bank[i]->set_filter_path_simulator(130e6, "RX", false);
//                for(uint8_t j = 0; j<50;j+=3)
//                    tester.filter_bank[i]->do_rx_attenuation(j);
//                tester.filter_bank[i]->do_rx_attenuation(0);
                tester.filter_bank[i]->set_filter_path_simulator(264e6, "RX", false);
                tester.filter_bank[i]->set_filter_path_simulator(470e6, "RX", false);
                tester.filter_bank[i]->set_filter_path_simulator(1000e6, "RX", false);
                tester.filter_bank[i]->set_filter_path_simulator(2400e6, "RX", false);
                tester.filter_bank[i]->set_filter_path_simulator(3000e6, "RX", false);
            }*/
        }


//        uint32_t    temp =  tester.iface->peek32(READBACK_BASE + 4*1);
//        tester.iface->poke32(U2_REG_SR_ADDR(1001),0x1FFF);
//        tester.iface->poke32(U2_REG_SR_ADDR(1000),3);
//        tester.iface->poke32(U2_REG_SR_ADDR(1000),2);
//        tester.iface->poke32(U2_REG_SR_ADDR(1000),1);

//        while (true){
//            tester.iface->poke32(U2_REG_SR_ADDR(1000),3);
//            tester.iface->poke32(U2_REG_SR_ADDR(1000),2);
//            tester.iface->poke32(U2_REG_SR_ADDR(1000),1);
//        }


//        tester.iface->poke32(U2_REG_SR_ADDR(101),1); //GO TO 12V
//        tester.iface->poke32(U2_REG_SR_ADDR(101),2); //GO TO 15V
//    while(true){
//        tester.iface->poke32(U2_REG_SR_ADDR(100),0);    //CH SW TO 0
//        tester.iface->poke32(U2_REG_SR_ADDR(100),1);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),2);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),3);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),4);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),5);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),6);
//        tester.iface->poke32(U2_REG_SR_ADDR(100),7);
//    }


//        while(true){
//            tester.time64->set_time_next_pps(pax::time_spec_t(0.00));
//            boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
//            pax::time_spec_t t =tester.time64->get_time_last_pps();
//            long long time = t.get_tick_count(DSP_CLOCK_RATE);
//            std::cout<< time <<std::endl;
//        }

//        tester.gps = pax::gps::make(tester.iface,2);
//        tester.gps->run();
//        tester.compass = pax::compass::make(tester.iface,3);
//        tester.compass->run();
//    while(true){
//        std::cout<<"HEADING   "<<tester.compass->get_heading() <<std::endl;
//        std::cout<<"LAT   "<<tester.gps->get_lat() <<std::endl;
//        std::cout<<"LON   "<<tester.gps->get_lon() <<std::endl;
//        std::cout<<"H   "<<tester.gps->get_GMT_hour() <<std::endl;
//        std::cout<<"M   "<<tester.gps->get_GMT_minute() <<std::endl;
//        std::cout<<"S   "<<tester.gps->get_GMT_second() <<std::endl;
//        std::cout<<"############"<<std::endl;

//        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
//    }

//        pax::flash_vec_t flash_vec;
//        for(uint32_t i=0;i<(1<<17);i++){
//            uint8_t oo=i;
//            flash_vec.push_back(255-oo);
//        }


//    tester.iface->erase_flash(0,flash_vec.size());
//    tester.iface->write_flash(0,flash_vec);
//    tester.iface->read_flash(0,flash_vec,flash_vec.size());


//    for(uint32_t i=0;i<(1<<17);i++){
//        uint8_t oo=i;
//        if(flash_vec[i] != (255-oo))
//            throw "FUCK";
//    }
//    throw "FUCK";


//    tester.iface->erase_otp_flash(pax::flash::BPI_S29GL01GS_256_WORD_OTP_REG_SEC_1);
//    tester.iface->write_otp_flash(0,flash_vec,pax::flash::BPI_S29GL01GS_256_WORD_OTP_REG_SEC_1);
//    tester.iface->read_otp_flash(0,flash_vec,20,pax::flash::BPI_S29GL01GS_256_WORD_OTP_REG_SEC_1);
//    tester.iface->read_otp_flash(0,flash_vec,20,pax::flash::BPI_S29GL01GS_256_WORD_OTP_REG_SEC_1);
//    flash_vec = tester.iface->read_uid_flash();


//    find_all_pax_ip();
//    pax::pax_reload::sptr reloader = pax::pax_reload::make(tester.iface);
//    reloader->burn_fpga_image(0,"/home/parto/Desktop/pax/PAX2/pax2_k7/v2/PAX2K7/pax2_fw_lock.bit");


    return 0;
}



