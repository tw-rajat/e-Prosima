#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include "CISPubSubTypes.h"

using namespace eprosima::fastdds::dds;

int main(int argc, char **argv)
{

    SystemTime m_systemTime;
    DomainParticipantFactory *factory = nullptr;
    DomainParticipant *dp = nullptr;
    Publisher *pub = nullptr;
    Topic *topic = nullptr;
    DataWriter *dw = nullptr;
    TypeSupport type(new SystemTimePubSubType());
    std::atomic_int matched_{};

    factory = DomainParticipantFactory::get_instance();
    ReturnCode_t ret = factory->load_XML_profiles_file("/home/rajat/Downloads/eProsima_CODE/ePro_RW/qos.xml");
    if (ret == ReturnCode_t::RETCODE_ERROR)
    {
        std::cout << "RETCODE_ERROR" << std::endl;
    }
    else
    {
        std::cout << "RETCODE_OK" << std::endl;
    }

    dp = factory->create_participant(1, PARTICIPANT_QOS_DEFAULT);
    type.register_type(dp);
    topic = dp->create_topic_with_profile("SystemTimeTopic", "SystemTime", "topic_qos");
    pub = dp->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    dw = pub->create_datawriter_with_profile(topic, "writer_qos", nullptr);

    ///--------------------------------------------------------------------------------------///

    std::cout << "Main Started" << std::endl;
    auto n = 1;
while (n<10)
{

    m_systemTime.year(1998);
    m_systemTime.month(05);
    m_systemTime.day(03);
    m_systemTime.hour(15);
    m_systemTime.minute(45);
    m_systemTime.mode(NavigationModeEnum::SYSTEM);
    dw->write(&m_systemTime);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    n++;
}

    ///--------------------------------------------------------------------------------------///
    if (dw != nullptr)
    {
        pub->delete_datawriter(dw);
    }
    if (pub != nullptr)
    {
        dp->delete_publisher(pub);
    }
    if (topic != nullptr)
    {
        dp->delete_topic(topic);
    }
    DomainParticipantFactory::get_instance()->delete_participant(dp);

    return 0;
}