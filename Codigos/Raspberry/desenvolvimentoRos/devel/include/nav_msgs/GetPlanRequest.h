// Generated by gencpp from file nav_msgs/GetPlanRequest.msg
// DO NOT EDIT!


#ifndef NAV_MSGS_MESSAGE_GETPLANREQUEST_H
#define NAV_MSGS_MESSAGE_GETPLANREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseStamped.h>

namespace nav_msgs
{
template <class ContainerAllocator>
struct GetPlanRequest_
{
  typedef GetPlanRequest_<ContainerAllocator> Type;

  GetPlanRequest_()
    : start()
    , goal()
    , tolerance(0.0)  {
    }
  GetPlanRequest_(const ContainerAllocator& _alloc)
    : start(_alloc)
    , goal(_alloc)
    , tolerance(0.0)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::PoseStamped_<ContainerAllocator>  _start_type;
  _start_type start;

   typedef  ::geometry_msgs::PoseStamped_<ContainerAllocator>  _goal_type;
  _goal_type goal;

   typedef float _tolerance_type;
  _tolerance_type tolerance;




  typedef boost::shared_ptr< ::nav_msgs::GetPlanRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nav_msgs::GetPlanRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetPlanRequest_

typedef ::nav_msgs::GetPlanRequest_<std::allocator<void> > GetPlanRequest;

typedef boost::shared_ptr< ::nav_msgs::GetPlanRequest > GetPlanRequestPtr;
typedef boost::shared_ptr< ::nav_msgs::GetPlanRequest const> GetPlanRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nav_msgs::GetPlanRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nav_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/common_msgs/nav_msgs/msg', '/home/pi/Documents/desenvolvimentoRos/devel/share/nav_msgs/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/common_msgs/actionlib_msgs/msg'], 'geometry_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nav_msgs::GetPlanRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nav_msgs::GetPlanRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nav_msgs::GetPlanRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e25a43e0752bcca599a8c2eef8282df8";
  }

  static const char* value(const ::nav_msgs::GetPlanRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe25a43e0752bcca5ULL;
  static const uint64_t static_value2 = 0x99a8c2eef8282df8ULL;
};

template<class ContainerAllocator>
struct DataType< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nav_msgs/GetPlanRequest";
  }

  static const char* value(const ::nav_msgs::GetPlanRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
\n\
geometry_msgs/PoseStamped start\n\
\n\
\n\
geometry_msgs/PoseStamped goal\n\
\n\
\n\
\n\
float32 tolerance\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PoseStamped\n\
# A Pose with reference coordinate frame and timestamp\n\
Header header\n\
Pose pose\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::nav_msgs::GetPlanRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.start);
      stream.next(m.goal);
      stream.next(m.tolerance);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetPlanRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nav_msgs::GetPlanRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nav_msgs::GetPlanRequest_<ContainerAllocator>& v)
  {
    s << indent << "start: ";
    s << std::endl;
    Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.start);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
    s << indent << "tolerance: ";
    Printer<float>::stream(s, indent + "  ", v.tolerance);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NAV_MSGS_MESSAGE_GETPLANREQUEST_H
