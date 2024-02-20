#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <can_plugins2/msg/robomas_frame.hpp>
#include <can_plugins2/msg/robomas_target.hpp>
#include <shooter/robomas_utils.hpp>

class ShootNode : public rclcpp::Node
{
  private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
    rclcpp::Publisher<can_plugins2::msg::RobomasFrame>::SharedPtr frame_pub_;
    rclcpp::Publisher<can_plugins2::msg::RobomasTarget>::SharedPtr target_pub_;
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
  public:
    ShootNode() : Node("shoot_node")
    {
      sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&ShootNode::joy_callback, this, std::placeholders::_1));
      frame_pub_ = this->create_publisher<can_plugins2::msg::RobomasFrame>("robomaster", 10);
      target_pub_ = this->create_publisher<can_plugins2::msg::RobomasTarget>("robomas_target1", 10);
    }
};

void ShootNode::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg){
  if(msg->buttons[1] == 1){
    target_pub_->publish(robomas::get_target(1.0));
  }
  if(msg->buttons[2] == 1){
    frame_pub_->publish(robomas::get_berutyoku_frame(0,1,1));
  }
}

int main(int argc, char *argv[])
{
  // printf("hello world odom_check package\n");
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ShootNode>());
  rclcpp::shutdown();
  return 0;
}