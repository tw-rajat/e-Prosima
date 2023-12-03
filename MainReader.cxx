// #include <fastdds/dds/domain/DomainParticipantFactory.hpp>
// #include <fastdds/dds/domain/DomainParticipant.hpp>
// #include <fastdds/dds/topic/TypeSupport.hpp>

// #include <fastdds/dds/subscriber/Subscriber.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>
// #include <fastdds/dds/subscriber/DataReaderListener.hpp>
// #include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
// #include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

// #include "CISPubSubTypes.h"

// using namespace eprosima::fastdds::dds;

// int main(int argc, char **argv)
// {

//     DomainParticipantFactory *factory = nullptr;
//     DomainParticipant *dp = nullptr;
//     Subscriber *sub = nullptr;
//     Topic *topic = nullptr;
//     DataReader *dr = nullptr;
//     TypeSupport type(new SystemTimePubSubType());
//     SystemTime m_systemTime;
//     std::atomic_int matched_{};

//     factory = DomainParticipantFactory::get_instance();
//     ReturnCode_t ret = factory->load_XML_profiles_file("/home/rajat/Downloads/eProsima_CODE/ePro_RW/qos.xml");
//     if (ret == ReturnCode_t::RETCODE_ERROR)
//     {
//         std::cout << "RETCODE_ERROR" << std::endl;
//     }

//     dp = factory->create_participant(1, PARTICIPANT_QOS_DEFAULT);
//     type.register_type(dp);
//     topic = dp->create_topic_with_profile("SystemTimeTopic", "SystemTime", "topic_qos");
//     sub = dp->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
//     dr = sub->create_datareader_with_profile(topic, "reader_qos", nullptr);

//     ///--------------------------------------------------------------------------------------///

//     std::cout << "Main Started" << std::endl;
//     auto n = 1;
//     while (n < 10)
//     {
//         SampleInfo info;
//         if (dr->read_next_sample(&m_systemTime, &info) == ReturnCode_t::RETCODE_OK)
//         {
//             if (info.valid_data)
//             {
//                 matched_++;
//                 std::cout << m_systemTime.year() << "|" << m_systemTime.month() << "|" << m_systemTime.day()
//                           << "\ntime_" << m_systemTime.hour() << ":" << m_systemTime.minute()
//                           << "\nmode_" << m_systemTime.mode() << std::endl;
//             }
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         n++;
//     }
    
//     // {
//     //     SampleInfo info;
//     //     SampleInfoSeq infoSeq;
//     //     LoanableSequence<SystemTime> LoanSysTime;
//     //     RTPS_DllAPI::ReturnCode_t retCode = RTPS_DllAPI::ReturnCode_t::RETCODE_OK;
//     //     ReturnCode_t ret_code = dr->read(LoanSysTime, infoSeq,
//     //                                          LENGTH_UNLIMITED,
//     //                                          ANY_SAMPLE_STATE,
//     //                                          ANY_VIEW_STATE,
//     //                                          ANY_INSTANCE_STATE);
//     //     if ( (retCode == ReturnCode_t::RETCODE_OK) && (info.valid_data) )
//     //     {
//     //         matched_++;
//     //         std::cout
//     //             << m_systemTime.year() << "|" << m_systemTime.month() << "|" << m_systemTime.day()
//     //             << "\ntime_" << m_systemTime.hour() << ":" << m_systemTime.minute()
//     //             << "\nmode_" << m_systemTime.mode() << std::endl;
//     //     }
//     //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//     //     n++;
//     // }
//     ///--------------------------------------------------------------------------------------///
//     if (dr != nullptr)
//     {
//         sub->delete_datareader(dr);
//     }
//     if (sub != nullptr)
//     {
//         dp->delete_subscriber(sub);
//     }
//     if (topic != nullptr)
//     {
//         dp->delete_topic(topic);
//     }
//     DomainParticipantFactory::get_instance()->delete_participant(dp);

//     return 0;
// }
