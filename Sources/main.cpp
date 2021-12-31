#include <ctime>
#include <iostream>
#include <string>

#include <google/protobuf/text_format.h>
#include <MyData.pb.h>

int main()
{
    MySchema::MyData data;
    data.mutable_user()->set_name("John");
    data.mutable_user()->set_age(21);
    data.mutable_create_time()->set_seconds(time(NULL));
    data.mutable_create_time()->set_nanos(0);

    std::cout << data.DebugString() << std::endl;
}
