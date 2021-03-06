// Generated by gencpp from file raspberry_msgs/StampedFloat32.msg
// DO NOT EDIT!


#ifndef RASPBERRY_MSGS_MESSAGE_STAMPEDFLOAT32_H
#define RASPBERRY_MSGS_MESSAGE_STAMPEDFLOAT32_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace raspberry_msgs
{
template <class ContainerAllocator>
struct StampedFloat32_
{
  typedef StampedFloat32_<ContainerAllocator> Type;

  StampedFloat32_()
    : id(0)
    , data(0.0)  {
    }
  StampedFloat32_(const ContainerAllocator& _alloc)
    : id(0)
    , data(0.0)  {
  (void)_alloc;
    }



   typedef int64_t _id_type;
  _id_type id;

   typedef float _data_type;
  _data_type data;




  typedef boost::shared_ptr< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> const> ConstPtr;

}; // struct StampedFloat32_

typedef ::raspberry_msgs::StampedFloat32_<std::allocator<void> > StampedFloat32;

typedef boost::shared_ptr< ::raspberry_msgs::StampedFloat32 > StampedFloat32Ptr;
typedef boost::shared_ptr< ::raspberry_msgs::StampedFloat32 const> StampedFloat32ConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::raspberry_msgs::StampedFloat32_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace raspberry_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'raspberry_msgs': ['/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
{
  static const char* value()
  {
    return "166b96779b23aaf8990132180f851a29";
  }

  static const char* value(const ::raspberry_msgs::StampedFloat32_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x166b96779b23aaf8ULL;
  static const uint64_t static_value2 = 0x990132180f851a29ULL;
};

template<class ContainerAllocator>
struct DataType< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
{
  static const char* value()
  {
    return "raspberry_msgs/StampedFloat32";
  }

  static const char* value(const ::raspberry_msgs::StampedFloat32_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 id\n\
float32 data\n\
";
  }

  static const char* value(const ::raspberry_msgs::StampedFloat32_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StampedFloat32_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::raspberry_msgs::StampedFloat32_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::raspberry_msgs::StampedFloat32_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<int64_t>::stream(s, indent + "  ", v.id);
    s << indent << "data: ";
    Printer<float>::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RASPBERRY_MSGS_MESSAGE_STAMPEDFLOAT32_H
