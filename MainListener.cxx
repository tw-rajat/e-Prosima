#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

#include "CISPubSubTypes.h"

using namespace eprosima::fastdds::dds;

class SubListener : public DataReaderListener
{
public:
    SubListener() : matched_(),
                    DataReaderListener()
    {
        std::cout << "Inside func: " << __FUNCTION__ << std::endl;
    };

    virtual ~SubListener(){};

    void on_data_available(DataReader *reader)
    {
        std::cout << "Inside func: " << __FUNCTION__ << std::endl;
        SampleInfo info;
        if (reader->read_next_sample(&m_systemTime, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
                matched_++;
                std::cout << m_systemTime.year() << "|" << m_systemTime.month() << "|" << m_systemTime.day()
                          << "\ntime_" << m_systemTime.hour() << ":" << m_systemTime.minute()
                          << "\nmode_" << m_systemTime.mode() << std::endl;
            }
        }
    }

    // void on_data_available(DataReader *reader)
    // {
    //     std::cout << "Inside func: " << __FUNCTION__ << std::endl;
    //     SampleInfo info;
    //     SampleInfoSeq infoSeq;
    //     LoanableSequence<SystemTime> LoanSysTime;
    //     std::string strSeq;
    //     RTPS_DllAPI::ReturnCode_t retCode = RTPS_DllAPI::ReturnCode_t::RETCODE_OK;
    //     ReturnCode_t ret_code = reader->read(LoanSysTime, infoSeq,
    //                                          LENGTH_UNLIMITED,
    //                                          ANY_SAMPLE_STATE,
    //                                          ANY_VIEW_STATE,
    //                                          ANY_INSTANCE_STATE);
    //     matched_++;
    //     std::cout
    //         << m_systemTime.year() << "|" << m_systemTime.month() << "|" << m_systemTime.day()
    //         << "\ntime_" << m_systemTime.hour() << ":" << m_systemTime.minute()
    //         << "\nmode_" << m_systemTime.mode() << std::endl;
    // }

    // void on_data_available(DataReader *reader) override
    // {
    //     static_cast<void>(reader);
    //     std::cout << "Received new data message" << std::endl;
    // }

    SystemTime m_systemTime;
    std::atomic_int matched_{};
};

void runSub(uint32_t samples)
{
    SubListener Sub_listener_;
    while (Sub_listener_.matched_ < samples)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char **argv)
{

    ///--------------------------------------------------------------------------------------///
    DomainParticipantFactory *factory = nullptr;
    DomainParticipant *dp = nullptr;

    Subscriber *sub = nullptr;
    SubscriberListener *subLis = nullptr;

    Topic *topic = nullptr;
    TopicListener *topLis = nullptr;

    DataReader *dr = nullptr;
    DataReaderListener *readerlistener{};

    StatusMask m_StatusMask = StatusMask::data_available();

    SystemTime m_systemTime;

    SubListener *Sub_listener_ = new SubListener();

    TypeSupport type(new SystemTimePubSubType());
    ///--------------------------------------------------------------------------------------///

    factory = DomainParticipantFactory::get_instance();
    ReturnCode_t ret = factory->load_XML_profiles_file("/home/rajat/Downloads/eProsima_CODE/ePro_RW/qos.xml");
    if (ret == ReturnCode_t::RETCODE_ERROR)
    {
        std::cout << "RETCODE_ERROR" << std::endl;
    }

    ///--------------------------------------------------------------------------------------///
    dp = factory->create_participant(1, PARTICIPANT_QOS_DEFAULT);
    type.register_type(dp);
    topic = dp->create_topic_with_profile("SystemTimeTopic", "SystemTime", "topic_qos", topLis, m_StatusMask);
    sub = dp->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
    dr = sub->create_datareader_with_profile(topic, "reader_qos",nullptr);
    dr->set_listener(Sub_listener_, m_StatusMask);
    ///--------------------------------------------------------------------------------------///

    ///--------------------------------------------------------------------------------------///
    std::cout << "Inside func: " << __FUNCTION__ << std::endl;

    auto n = 1;
    while (n < 10)
    {
        runSub(10);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        n++;
    }

    ///--------------------------------------------------------------------------------------///

    ///--------------------------------------------------------------------------------------///
    if (dr != nullptr)
    {
        sub->delete_datareader(dr);
    }
    if (sub != nullptr)
    {
        dp->delete_subscriber(sub);
    }
    if (topic != nullptr)
    {
        dp->delete_topic(topic);
    }
    DomainParticipantFactory::get_instance()->delete_participant(dp);
    ///--------------------------------------------------------------------------------------///

    return 0;
}