// Generated by gencpp from file tf2_msgs/LookupTransformResult.msg
// DO NOT EDIT!


#ifndef TF2_MSGS_MESSAGE_LOOKUPTRANSFORMRESULT_H
#define TF2_MSGS_MESSAGE_LOOKUPTRANSFORMRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/TransformStamped.h>
#include <tf2_msgs/TF2Error.h>

namespace tf2_msgs
{
template <class ContainerAllocator>
struct LookupTransformResult_
{
  typedef LookupTransformResult_<ContainerAllocator> Type;

  LookupTransformResult_()
    : transform()
    , error()  {
    }
  LookupTransformResult_(const ContainerAllocator& _alloc)
    : transform(_alloc)
    , error(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::TransformStamped_<ContainerAllocator>  _transform_type;
  _transform_type transform;

   typedef  ::tf2_msgs::TF2Error_<ContainerAllocator>  _error_type;
  _error_type error;




  typedef boost::shared_ptr< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> const> ConstPtr;

}; // struct LookupTransformResult_

typedef ::tf2_msgs::LookupTransformResult_<std::allocator<void> > LookupTransformResult;

typedef boost::shared_ptr< ::tf2_msgs::LookupTransformResult > LookupTransformResultPtr;
typedef boost::shared_ptr< ::tf2_msgs::LookupTransformResult const> LookupTransformResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tf2_msgs::LookupTransformResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace tf2_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg'], 'actionlib_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/common_msgs/actionlib_msgs/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'tf2_msgs': ['/home/pi/Documents/desenvolvimentoRos/src/tf2_msgs/msg', '/home/pi/Documents/desenvolvimentoRos/devel/share/tf2_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3fe5db6a19ca9cfb675418c5ad875c36";
  }

  static const char* value(const ::tf2_msgs::LookupTransformResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3fe5db6a19ca9cfbULL;
  static const uint64_t static_value2 = 0x675418c5ad875c36ULL;
};

template<class ContainerAllocator>
struct DataType< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tf2_msgs/LookupTransformResult";
  }

  static const char* value(const ::tf2_msgs::LookupTransformResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
geometry_msgs/TransformStamped transform\n\
tf2_msgs/TF2Error error\n\
\n\
================================================================================\n\
MSG: geometry_msgs/TransformStamped\n\
# This expresses a transform from coordinate frame header.frame_id\n\
# to the coordinate frame child_frame_id\n\
#\n\
# This message is mostly used by the \n\
# <a href=\"http://wiki.ros.org/tf\">tf</a> package. \n\
# See its documentation for more information.\n\
\n\
Header header\n\
string child_frame_id # the frame id of the child frame\n\
Transform transform\n\
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
MSG: geometry_msgs/Transform\n\
# This represents the transform between two coordinate frames in free space.\n\
\n\
Vector3 translation\n\
Quaternion rotation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: tf2_msgs/TF2Error\n\
uint8 NO_ERROR = 0\n\
uint8 LOOKUP_ERROR = 1\n\
uint8 CONNECTIVITY_ERROR = 2\n\
uint8 EXTRAPOLATION_ERROR = 3\n\
uint8 INVALID_ARGUMENT_ERROR = 4\n\
uint8 TIMEOUT_ERROR = 5\n\
uint8 TRANSFORM_ERROR = 6\n\
\n\
uint8 error\n\
string error_string\n\
";
  }

  static const char* value(const ::tf2_msgs::LookupTransformResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.transform);
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LookupTransformResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tf2_msgs::LookupTransformResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tf2_msgs::LookupTransformResult_<ContainerAllocator>& v)
  {
    s << indent << "transform: ";
    s << std::endl;
    Printer< ::geometry_msgs::TransformStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.transform);
    s << indent << "error: ";
    s << std::endl;
    Printer< ::tf2_msgs::TF2Error_<ContainerAllocator> >::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TF2_MSGS_MESSAGE_LOOKUPTRANSFORMRESULT_H
