#include <chrono>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using namespace std;

struct Variables{
    int angka;
    string nama;
    string abin_message;
    int publish_count;

    string node_name;
    string publisher_name;
};

Variables initVariables(){
    Variables vars;
    vars.angka = 24;
    vars.publish_count = 0;
    vars.nama = "abin";
    vars.abin_message = "apcb";

    vars.node_name = "cpp_pub_node";
    vars.publisher_name = "that_one_cpp_publisher";
    return vars;
};


int main(int argc, char * argv[]){
    Variables vars = initVariables();

    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared(vars.publisher_name);
    auto publisher = node->create_publisher<std_msgs::msg::String>(vars.publisher_name,10);
    std_msgs::msg::String message;
    rclcpp::WallRate loop_rate(500ms);

    while (rclcpp::ok()){
        message.data = vars.abin_message + std::to_string(vars.publish_count++);
        publisher->publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}