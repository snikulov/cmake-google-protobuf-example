#include <iostream>
#include "msg.pb.h"

using namespace std;

void add_param(demo::params_map* elm, unsigned long key, unsigned long val)
{
    elm->set_key(key);
    elm->mutable_nvalue()->add_elements(val);
}

void add_param(demo::params_map* elm, unsigned long key, const std::string& val)
{
    elm->set_key(key);
    elm->mutable_svalue()->add_elements(val);
}

void show_demo_message(const demo::demo_msg& msg)
{
    std::cout << "cmd=" << msg.cmd() << " seq_num=" << msg.seq_num() << " src_id="<< msg.src_id() << std::endl;
    for(int i = 0; i < msg.params_size(); ++i)
    {
        std::cout << "param element " << i+1 << std::endl;
        std::cout << "key=" << msg.params(i).key() << " {";
        int elm_size = msg.params(i).nvalue().elements_size();
        for(int j=0; j < elm_size; ++j)
        {
            std::cout << msg.params(i).nvalue().elements(j) << (j < elm_size-1 ? "," : "");
        }

        elm_size = msg.params(i).svalue().elements_size();
        for(int j=0; j < elm_size; ++j)
        {
            std::cout << msg.params(i).svalue().elements(j) << (j < elm_size-1 ? "," : "");
        }
        std::cout << "}" << std::endl;
    }
}

int main(int argc, char** argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    demo::demo_msg message;

    message.set_cmd(1);
    message.set_src_id(3456);
    message.set_seq_num(1111);

    demo::params_map* elm = message.add_params();
    add_param(elm, 1, 1);
    add_param(elm, 1, 2);
    add_param(elm, 1, 3);

    elm = message.add_params();
    add_param(elm, 2, "one");
    add_param(elm, 2, "two");
    add_param(elm, 2, "three");

    std::cout << "Message size in bytes: " << message.ByteSize() << std::endl;

    std::string data(message.SerializeAsString());

    std::cout << data << std::endl;

    demo::demo_msg m1;
    m1.ParseFromString(data);

    show_demo_message(m1);

    return 0;
}
