#include "recorder.hpp"
#include <pax_reload.hpp>
#include <string>

int main(int argc, char* argv[])
{
    (void)argc;
    (void) argv;

        mb_container_type tester;
        std::vector<boost::shared_ptr<pax::transport::sph::recv_packet_streamer> > streamers=pax_init(tester,2);


//        tester.iface->poke32(U2_REG_SR_ADDR(1022),0);
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


//        for(uint8_t j = 0;j < 4;j++)
//            for(uint8_t w = 0; w < 2; w++)
//                for(uint8_t k = 0; k < 7; k++)
//                    tester.filter_bank[j]->set_filter_path_virtex(static_cast<pax::filter_bank::filter_bank_virtex_value::FILTER_PATH_virtex>(k));

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


        tester.iface->poke32(U2_REG_SR_ADDR(101),1); //GO TO 12V
        tester.iface->poke32(U2_REG_SR_ADDR(101),2); //GO TO 15V
    while(true){
        tester.iface->poke32(U2_REG_SR_ADDR(100),0);    //CH SW TO 0
        tester.iface->poke32(U2_REG_SR_ADDR(100),1);
        tester.iface->poke32(U2_REG_SR_ADDR(100),2);
        tester.iface->poke32(U2_REG_SR_ADDR(100),3);
        tester.iface->poke32(U2_REG_SR_ADDR(100),4);
        tester.iface->poke32(U2_REG_SR_ADDR(100),5);
        tester.iface->poke32(U2_REG_SR_ADDR(100),6);
        tester.iface->poke32(U2_REG_SR_ADDR(100),7);
    }


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



