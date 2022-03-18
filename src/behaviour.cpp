#include "ros/ros.h"
#include <qi/applicationsession.hpp>
#include <qi/os.hpp>
#include "pepper_behaviour_srvs/MoveHead.h"
#include "pepper_behaviour_srvs/MoveArm.h"
#include "pepper_behaviour_srvs/Speak.h"
#include <boost/uuid/uuid.hpp>

qi::SessionPtr session;

bool move_head(pepper_behaviour_srvs::MoveHead::Request &req,
              pepper_behaviour_srvs::MoveHead::Response &res){
              qi::AnyObject motion_service = session->service("ALMotion");

              motion_service.call<void>("setStiffnesses", 1.0f);
              std::vector<std::string> names =  {"HeadYaw", "HeadPitch"};
              std::vector<double> joint_poses = req.positions;
              float fractionMaxSpeed = 0.2;

              motion_service.call<void>("setAngles", names, joint_poses, fractionMaxSpeed);
              qi::os::sleep(1.0f);
              motion_service.call<void>("setStiffnesses", 0.0f);
              res.msg = "ok";

              return true;
              }

bool speak(pepper_behaviour_srvs::Speak::Request &req,
            pepper_behaviour_srvs::Speak::Response &res){
              qi::AnyObject tts = session->service("ALTextToSpeech");

              tts.call<void>("say", req.text);
              res.msg = "ok";
              return true;
}

bool move_arm(pepper_behaviour_srvs::MoveArm::Request &req,
              pepper_behaviour_srvs::MoveArm::Response &res){
                qi::AnyObject motion_service = session->service("ALMotion");
                motion_service.call<void>("setStiffnesses", 1.0f);

                std::vector<std::string> names = req.names;
                std::vector<double> joint_poses = req.positions;
                float fractionMaxSpeed = 0.2;

                motion_service.call<void>("setAngles", names, joint_poses, fractionMaxSpeed);
                qi::os::sleep(1.0f);
                motion_service.call<void>("setStiffnesses", 0.0f);
                res.msg = "ok";
                return true;

              }

int main(int argc, char** argv){
   ros::init(argc, argv, "pepper_behaviour");
   ros::NodeHandle n;

  // boost::uuids::ns::url url = "tcp://127.0.0.1:9559";
   qi::Url url = qi::Url("tcp://127.0.0.1:9559");
   qi::ApplicationSession app(argc, argv, 0, url=url);
   app.start();
   session = app.session();

   ros::ServiceServer service = n.advertiseService("move_head", move_head);
   ros::ServiceServer service2 = n.advertiseService("speak", speak);
   ros::ServiceServer service3 = n.advertiseService("move_arm", move_arm);
   ros::spin();

   return 0;

}
