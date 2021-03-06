#include "recorder.hpp"


recorder::sptr recorder::make(boost::shared_ptr<pax::transport::sph::recv_packet_streamer> stream, int number, mb_container_type tester, int num_log)
{
    return sptr(new recorder_impl(stream, number, num_log, tester));
}

recorder_impl::recorder_impl(boost::shared_ptr<pax::transport::sph::recv_packet_streamer> stream,int number, int num_log, mb_container_type tester):
    stream(stream),number(number),num_log(num_log), tester(tester)
{
    std::string io="dataa"+boost::lexical_cast<std::string>(number)+".bin";
    myFile=boost::shared_ptr< std::ofstream>(new std::ofstream(io.c_str(), std::ios::out | std::ios::binary));
}
void recorder_impl::run()
{
    std::cout<<"run thread for stream" <<number<<std::endl;
    pax::rx_metadata_t md;
    std::vector<uint32_t> buffs(num_log);
    //size_t num_requested_samples=8192;
    int max_save = num_log;
   // while(max_save > 0)
    while(1)
    {
        std::vector<double> phases;
        for(int i = 0; i < 8; i++)
            phases.push_back(tester.sync->read_phase_loc_ant(i));
        for(int i = 0; i < 8; i++)
            std::cout << i << " :     " << phases[4]- phases[i] << std::endl;
        std::cout << "---------------------" << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        size_t num_rx_samps = stream->recv(&buffs[0], max_save, md, 3, false);
        myFile->write((const char*)&buffs[0], num_rx_samps*4);
   //     std::cout << number << ": " << num_rx_samps << std::endl;
        //max_save-=num_rx_samps;

    }
}
