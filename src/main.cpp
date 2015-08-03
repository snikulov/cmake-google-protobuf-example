#include <iostream>
#include "msg.pb.h"

using namespace std;

template <typename T1, typename T2, typename T3>
void add_param(T1* elm, T2 key, T3 val)
{
    elm->set_key(key);
    elm->mutable_value()->add_elements(val);
}

void show_demo_message(const demo::demo_msg& msg)
{
    std::cout << "cmd=" << msg.cmd() << " seq_num=" << msg.seq_num() << " src_id="<< msg.src_id() << std::endl;
    for(int i = 0; i < msg.sparams_size(); ++i)
    {
        std::cout << "param element " << i+1 << std::endl;
        std::cout << "key=" << msg.sparams(i).key() << " {";
        int elm_size = msg.sparams(i).value().elements_size();
        for(int j=0; j < elm_size; ++j)
        {
            std::cout << msg.sparams(i).value().elements(j) << (j < elm_size-1 ? "," : "");
        }
        std::cout << "}" << std::endl;
    }

    for(int i = 0; i < msg.nparams_size(); ++i)
    {
        std::cout << "param element " << i+1 << std::endl;
        std::cout << "key=" << msg.nparams(i).key() << " {";
        int elm_size = msg.nparams(i).value().elements_size();
        for(int j=0; j < elm_size; ++j)
        {
            std::cout << msg.nparams(i).value().elements(j) << (j < elm_size-1 ? "," : "");
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

    demo::num_params * elm = message.add_nparams();
    add_param(elm, 1, 1);
    add_param(elm, 1, 2);
    add_param(elm, 1, 3);

    elm = message.add_nparams();
    add_param(elm, 3, 1);
    add_param(elm, 3, 2);
    add_param(elm, 3, 3);

    demo::str_params * selm = message.add_sparams();
    add_param(selm, 2, "one");
    add_param(selm, 2, "two");
    add_param(selm, 2, "three");

    std::cout << "Message size in bytes: " << message.ByteSize() << std::endl;

    std::string data(message.SerializeAsString());

    std::cout << data << std::endl;

    demo::demo_msg m1;
    m1.ParseFromString(data);

    show_demo_message(m1);

    return 0;
}
