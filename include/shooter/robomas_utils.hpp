#include <can_plugins2/msg/frame.hpp>
#include <can_plugins2/msg/robomas_frame.hpp>
#include <can_plugins2/msg/robomas_target.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robomas
{
    static std::unique_ptr<can_plugins2::msg::RobomasTarget> get_target(const float target_data)
    {
        auto target = std::make_unique<can_plugins2::msg::RobomasTarget>();
        target->target = target_data;
        return target;
    }

    static std::unique_ptr<can_plugins2::msg::RobomasFrame> get_berutyoku_frame(const uint16_t id, const float target_vel,const float target_pos) 
    {
        auto frame = std::make_unique<can_plugins2::msg::RobomasFrame>();
        frame->mode = 3;
        frame->motor = id;
        frame->temp = 50;
        frame->velkp = 0.25;
        frame->velki = 10;
        frame->velkd = 0;
        frame->vellimitie = 0;
        frame->poskp = 500;
        frame->poski = 800;
        frame->poskd = 80;
        frame->poslimitie = 0;
        frame->tyoku_vel_target = 450;
        frame->tyoku_pos_target = 5450;
        return frame;
    }
}

