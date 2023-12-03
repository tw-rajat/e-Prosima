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

// class FDS_SystemTime
// {

// private:
//     SystemTime n_systemTime;
//     DomainParticipantFactory *factory = nullptr;
//     DomainParticipant *dp = nullptr;

//     Subscriber *sub = nullptr;
//     Publisher *pub = nullptr;
//     Topic *topic = nullptr;
//     DataReader *dr = nullptr;
//     DataWriter *dw = nullptr;
//     TypeSupport type;

//     class SubListener : public DataReaderListener
//     {
//     public:
//         SubListener() : matched_(){};
//         ~SubListener() override = default;

//         void on_data_available(DataReader *reader) override
//         {
//             SampleInfo info;
//             if (reader->read_next_sample(&m_systemTime, &info) == ReturnCode_t::RETCODE_OK)
//             {
//                 if (info.valid_data)
//                 {
//                     matched_++;
//                     std::cout
//                         << m_systemTime.year() << "|" << m_systemTime.month() << "|" << m_systemTime.day()
//                         << "\ntime_" << m_systemTime.hour() << ":" << m_systemTime.minute()
//                         << "\nmode_" << m_systemTime.mode() << std::endl;
//                 }
//             }
//         }

//         SystemTime m_systemTime;
//         std::atomic_int matched_{};
//     };
//     SubListener Sub_listener_;

//     class PubListener : public DataWriterListener
//     {
//     public:
//         PubListener() : matched_(){};
//         ~PubListener() override = default;

//         std::atomic_int matched_{};
//     };
//     PubListener Pub_listener_;

// public:
//     FDS_SystemTime() : dp(),
//                        pub(),
//                        topic(),
//                        dw(),
//                        dr(),
//                        type(new SystemTimePubSubType()) {}

//     virtual ~FDS_SystemTime()
//     {
//         if (dr != nullptr)
//         {
//             sub->delete_datareader(dr);
//         }
//         if (dw != nullptr)
//         {
//             pub->delete_datawriter(dw);
//         }
//         if (sub != nullptr)
//         {
//             dp->delete_subscriber(sub);
//         }
//         if (pub != nullptr)
//         {
//             dp->delete_publisher(pub);
//         }
//         if (topic != nullptr)
//         {
//             dp->delete_topic(topic);
//         }
//         DomainParticipantFactory::get_instance()->delete_participant(dp);
//     }

//     bool init()
//     {
//         factory = DomainParticipantFactory::get_instance();
//         // DomainParticipantQos participantQos;
//         // participantQos.name("Participant_publisher");
//         RTPS_DllAPI::ReturnCode_t ret =
//             factory->load_XML_profiles_file("/home/rajat/Downloads/eProsima_CODE/ePro_RW/qos.xml");
//         if (ret == RTPS_DllAPI::ReturnCode_t::RETCODE_ERROR)
//         {
//             std::cout << "RETCODE_ERROR" << std::endl;
//         }
//         else
//         {
//             std::cout << "RETCODE_OK" << std::endl;
//         }

//         // dp = DomainParticipantFactory::get_instance()->create_participant(51, participantQos);
//         dp = factory->create_participant(51, PARTICIPANT_QOS_DEFAULT);
//         if (dp == nullptr)
//         {
//             return false;
//         }

//         // Register the Type
//         type.register_type(dp);

//         // Create the publications Topic
//         // topic = dp->create_topic("newWorldTopic", "newWorld", TOPIC_QOS_DEFAULT);
//         topic = dp->create_topic_with_profile("SystemTimeTopic", "SystemTime", "topic_qos");
//         if (topic == nullptr)
//         {
//             return false;
//         }

//         //// Create the PubListener
//         pub = dp->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

//         // Create the SubListener
//         sub = dp->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
//         if (sub == nullptr)
//         {
//             return false;
//         }

//         //// Create the DataWriter
//         dw = pub->create_datawriter_with_profile(topic, "writer_qos", &Pub_listener_);
//         if (dw == nullptr)
//         {
//             return false;
//         }

//         // Create the DataWriter
//         dr = sub->create_datareader_with_profile(topic, "reader_qos", &Sub_listener_);
//         if (dr == nullptr)
//         {
//             return false;
//         }

//         return true;
//     }

//     void getData(uint32_t yr, uint32_t mnt, uint32_t dy, uint32_t hr, uint32_t min)
//     {
//         n_systemTime.year(yr);
//         n_systemTime.month(mnt);
//         n_systemTime.day(dy);
//         n_systemTime.hour(hr);
//         n_systemTime.minute(min);
//         n_systemTime.mode(NavigationModeEnum::SYSTEM);
//     }

//     bool publish_()
//     {
//         bool ret = true;
//         dw->write(&n_systemTime);
//         return ret;
//     }

//     // run pub
//     void runPub(uint32_t samples)
//     {
//         uint32_t samples_sent = 0;
//         while (samples_sent < samples)
//         {
//             if (publish_())
//             {
//                 samples_sent++;
//                 std::cout << n_systemTime.year() << n_systemTime.month() << n_systemTime.day() << n_systemTime.hour() << n_systemTime.minute() << n_systemTime.mode() << std::endl;
//             }
//             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         }
//     }

//     void runSub(uint32_t samples) const
//     {
//         std::cout << "Inside func: " << __FUNCTION__ << std::endl;
//         while (Sub_listener_.matched_ < samples)
//         {
//             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//         }
//     }
// };

// int main(int argc, char **argv)
// {
//     std::cout << "Sub Started" << std::endl;
//     auto myOBJ = std::make_unique<FDS_SystemTime>();

//     for (auto i = 0; i < 11; i++)
//     {
//         myOBJ->getData(2023, 10, 06, 16, 25);
//         myOBJ->init();
//         myOBJ->runPub(10);
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         myOBJ->runSub(10);
//     }

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     // if (myOBJ->init())
//     // {
//     //     myOBJ->runSub(10);
//     // }
//     return 0;
// }
