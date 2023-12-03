// #include <fastdds/dds/domain/DomainParticipantFactory.hpp>
// #include <fastdds/dds/domain/DomainParticipant.hpp>
// #include <fastdds/dds/topic/TypeSupport.hpp>

// #include <fastdds/dds/subscriber/Subscriber.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>
// #include <fastdds/dds/subscriber/DataReaderListener.hpp>
// #include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
// #include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

// #include <fastdds/dds/publisher/Publisher.hpp>
// #include <fastdds/dds/publisher/DataWriter.hpp>
// #include <fastdds/dds/publisher/DataWriterListener.hpp>
// #include <fastdds/dds/publisher/qos/PublisherQos.hpp>
// #include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

// #include "CISPubSubTypes.h"

// using namespace eprosima::fastdds::dds;

// int main(int argc, char **argv)
// {

//     SystemTime m_systemTime;
//     DomainParticipantFactory *factory = nullptr;
//     DomainParticipant *dp = nullptr;
//     Subscriber *sub = nullptr;
//     Publisher *pub = nullptr;
//     Topic *topic = nullptr;
//     DataReader *dr = nullptr;
//     DataWriter *dw = nullptr;
//     TypeSupport type(new SystemTimePubSubType());
//     std::atomic_int matched_{};

//     factory = DomainParticipantFactory::get_instance();
//     ReturnCode_t ret = factory->load_XML_profiles_file("/home/wesee/ePro_RW/qos.xml");
//     if (ret == ReturnCode_t::RETCODE_ERROR)
//     {
//         std::cout << "RETCODE_ERROR" << std::endl;
//     }
//     else
//     {
//         std::cout << "RETCODE_OK" << std::endl;
//     }

//     dp = factory->create_participant(1, PARTICIPANT_QOS_DEFAULT);
//     type.register_type(dp);
//     topic = dp->create_topic_with_profile("SystemTimeTopic", "SystemTime", "topic_qos");
//     pub = dp->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
//     sub = dp->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
//     dw = pub->create_datawriter_with_profile(topic, "writer_qos", nullptr);
//     dr = sub->create_datareader_with_profile(topic, "reader_qos", nullptr);

//     ///--------------------------------------------------------------------------------------///

//     std::cout << "Main Started" << std::endl;

//     m_systemTime.year(1998);
//     m_systemTime.month(05);
//     m_systemTime.day(03);
//     m_systemTime.hour(15);
//     m_systemTime.minute(45);
//     m_systemTime.mode(NavigationModeEnum::SYSTEM);
//     dw->write(&m_systemTime);

//     SampleInfo info;
//     if (dr->read_next_sample(&m_systemTime, &info) == ReturnCode_t::RETCODE_OK)
//     {
//         if (info.valid_data)
//         {
//             matched_++;
//             std::cout << m_systemTime.year()    << "|"  << m_systemTime.month()   << "|"    << m_systemTime.day()
//                       << "\ntime_" << m_systemTime.hour()  << ":"  << m_systemTime.minute()
//                       << "\nmode_" << m_systemTime.mode()    << std::endl;
//         }
//     }

//     ///--------------------------------------------------------------------------------------///
//     if (dr != nullptr)
//     {
//         sub->delete_datareader(dr);
//     }
//     if (dw != nullptr)
//     {
//         pub->delete_datawriter(dw);
//     }
//     if (sub != nullptr)
//     {
//         dp->delete_subscriber(sub);
//     }
//     if (pub != nullptr)
//     {
//         dp->delete_publisher(pub);
//     }
//     if (topic != nullptr)
//     {
//         dp->delete_topic(topic);
//     }
//     DomainParticipantFactory::get_instance()->delete_participant(dp);

//     return 0;
// }