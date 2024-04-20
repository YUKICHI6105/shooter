#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <robomas_plugins/msg/robomas_frame.hpp>
#include <robomas_plugins/msg/robomas_target.hpp>
#include <shooter/robomas_utils.hpp>

class ShootNode : public rclcpp::Node
{
  private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasFrame>::SharedPtr frame_pub_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasTarget>::SharedPtr target_pub_;
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
  public:
    ShootNode() : Node("shoot_node")
    {
      sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&ShootNode::joy_callback, this, std::placeholders::_1));
      frame_pub_ = this->create_publisher<robomas_plugins::msg::RobomasFrame>("robomas_frame", 10);
      target_pub_ = this->create_publisher<robomas_plugins::msg::RobomasTarget>("robomas_target4", 10);
    }
};

void ShootNode::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg){
  if(msg->buttons[5] == 1){//RBボタン
    target_pub_->publish(robomas::get_target(15000));
  }
  if(msg->buttons[7] == 1){
    frame_pub_->publish(robomas::get_pos_frame(4,false));
  }
  if(msg->buttons[6] == 1){
    frame_pub_->publish(robomas::get_dis_frame(4));
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