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

#include "rclcpp/rclcpp.hpp"

// note use of chrono literals
using namespace std::chrono_literals;

// Controller rate, 1Hz by default
const auto controller_rate = 1000ms;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("logger_node");

  rclcpp::Rate loop_rate(controller_rate);

  int counter = 0;
  while (rclcpp::ok()) {
    // ROS2 logging macro
    RCLCPP_INFO(node->get_logger(), "Hello %d", counter++);

    // `spin_some` returns as soon as there are no more messages left to process
    rclcpp::spin_some(node);
    // Process waits for given amount of time
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
