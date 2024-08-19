// Copyright 2021 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// ROS2 includes
#include "rclcpp/rclcpp.hpp"
// Header for std_msgs/msg/Int32
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
  : Node("robot_01_hearbeat_pub")
  {
    /*
		Instantiate publisher node, using the public interface of `rclcpp::Node`. The returned shared pointer is
		stored in the `publisher_` member. Arguments to `create_publisher` are a string that encodes the name of the
		topic and an instance of `rclcpp::QoS`. Note that instances of this class can be created directly from integer
		values, in this case the value `10` sets the size of the output message queue.
     */
    publisher_ = create_publisher<std_msgs::msg::Int32>("robot_01_hearbeat", 10);
    timer_ = create_wall_timer(
      500ms, std::bind(&PublisherNode::timer_callback, this));
  }

  void timer_callback()
  {
    // Every 500ms we increase the payload of the message object and send it for broadcast to any subscribers.
    message_.data += 1;
    message_.data %= 120;
    publisher_->publish(message_);
  }

private:
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std_msgs::msg::Int32 message_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<PublisherNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
