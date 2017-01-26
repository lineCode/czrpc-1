#include <iostream>
#include <thread>
#include "czrpc/client/client.hpp"
#include "proto_message.pb.h"

using namespace czrpc::base;

czrpc::client::pub_client client;

void test_func()
{
    while (true)
    {
        try
        {
            auto message = std::make_shared<auto_weather_message>();
            message->set_city_name("ChengDu");
            message->set_weather("Good");
            /* client.publish("weather", message); */
            /* client.publish_raw("song", "My heart will go on"); */
            client.async_publish("weather", message);
            client.async_publish_raw("song", "My heart will go on");
        }
        catch (std::exception& e)
        {
            log_warn(e.what());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

int main()
{
    try
    {
        client.connect({ "127.0.0.1", 50051 }).timeout(3000).run();
    }
    catch (std::exception& e)
    {
        log_warn(e.what());
        return 0;
    }

    std::thread t(test_func);
    std::thread t2(test_func);

    t.join();
    t2.join();

    return 0;
}