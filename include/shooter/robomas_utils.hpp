#include <robomas_plugins/msg/frame.hpp>
#include <robomas_plugins/msg/robomas_frame.hpp>
#include <robomas_plugins/msg/robomas_target.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robomas
{
    static std::unique_ptr<robomas_plugins::msg::RobomasTarget> get_target(const float target_data)
    {
        auto target = std::make_unique<robomas_plugins::msg::RobomasTarget>();
        target->target = target_data;
        return target;
    }

    static std::unique_ptr<robomas_plugins::msg::RobomasFrame> get_berutyoku_frame(const uint16_t id, const float target_vel,const float target_pos) 
    {
        auto frame = std::make_unique<robomas_plugins::msg::RobomasFrame>();
        frame->mode = 3;
        frame->motor = id;
        frame->temp = 50;
        frame->velkp = 0.15;
        frame->velki = 9;
        frame->poskp = 0.5;
        frame->tyoku_vel_target = 450;
        frame->tyoku_pos_target = 5450;
        return frame;
    }

    static std::unique_ptr<robomas_plugins::msg::RobomasFrame> get_dis_frame(const uint16_t index) 
    {
        auto frame = std::make_unique<robomas_plugins::msg::RobomasFrame>();
        frame->mode = 0;
        frame->motor = index;
        frame->temp = 50;
        return frame;
    }
}

