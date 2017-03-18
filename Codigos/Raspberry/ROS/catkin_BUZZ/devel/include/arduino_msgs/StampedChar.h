// Generated by gencpp from file arduino_msgs/StampedChar.msg
// DO NOT EDIT!


#ifndef ARDUINO_MSGS_MESSAGE_STAMPEDCHAR_H
#define ARDUINO_MSGS_MESSAGE_STAMPEDCHAR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace arduino_msgs
{
template <class ContainerAllocator>
struct StampedChar_
{
  typedef StampedChar_<ContainerAllocator> Type;

  StampedChar_()
    : id(0)
    , data(0)  {
    }
  StampedChar_(const ContainerAllocator& _alloc)
    : id(0)
    , data(0)  {
  (void)_alloc;
    }



   typedef int64_t _id_type;
  _id_type id;

   typedef uint8_t _data_type;
  _data_type data;




  typedef boost::shared_ptr< ::arduino_msgs::StampedChar_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::arduino_msgs::StampedChar_<ContainerAllocator> const> ConstPtr;

}; // struct StampedChar_

typedef ::arduino_msgs::StampedChar_<std::allocator<void> > StampedChar;

typedef boost::shared_ptr< ::arduino_msgs::StampedChar > StampedCharPtr;
typedef boost::shared_ptr< ::arduino_msgs::StampedChar const> StampedCharConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::arduino_msgs::StampedChar_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::arduino_msgs::StampedChar_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace arduino_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'arduino_msgs': ['/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::arduino_msgs::StampedChar_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::arduino_msgs::StampedChar_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::arduino_msgs::StampedChar_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::arduino_msgs::StampedChar_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::arduino_msgs::StampedChar_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::arduino_msgs::StampedChar_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::arduino_msgs::StampedChar_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6deb871728ba12dea9a57a7cbd60e013";
  }

  static const char* value(const ::arduino_msgs::StampedChar_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6deb871728ba12deULL;
  static const uint64_t static_value2 = 0xa9a57a7cbd60e013ULL;
};

template<class ContainerAllocator>
struct DataType< ::arduino_msgs::StampedChar_<ContainerAllocator> >
{
  static const char* value()
  {
    return "arduino_msgs/StampedChar";
  }

  static const char* value(const ::arduino_msgs::StampedChar_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::arduino_msgs::StampedChar_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 id\n\
char data\n\
";
  }

  static const char* value(const ::arduino_msgs::StampedChar_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::arduino_msgs::StampedChar_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StampedChar_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::arduino_msgs::StampedChar_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::arduino_msgs::StampedChar_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<int64_t>::stream(s, indent + "  ", v.id);
    s << indent << "data: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ARDUINO_MSGS_MESSAGE_STAMPEDCHAR_H
