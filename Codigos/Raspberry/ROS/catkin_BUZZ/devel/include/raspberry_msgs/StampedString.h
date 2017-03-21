// Generated by gencpp from file raspberry_msgs/StampedString.msg
// DO NOT EDIT!


#ifndef RASPBERRY_MSGS_MESSAGE_STAMPEDSTRING_H
#define RASPBERRY_MSGS_MESSAGE_STAMPEDSTRING_H


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
struct StampedString_
{
  typedef StampedString_<ContainerAllocator> Type;

  StampedString_()
    : id(0)
    , data()  {
    }
  StampedString_(const ContainerAllocator& _alloc)
    : id(0)
    , data(_alloc)  {
  (void)_alloc;
    }



   typedef int64_t _id_type;
  _id_type id;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _data_type;
  _data_type data;




  typedef boost::shared_ptr< ::raspberry_msgs::StampedString_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::raspberry_msgs::StampedString_<ContainerAllocator> const> ConstPtr;

}; // struct StampedString_

typedef ::raspberry_msgs::StampedString_<std::allocator<void> > StampedString;

typedef boost::shared_ptr< ::raspberry_msgs::StampedString > StampedStringPtr;
typedef boost::shared_ptr< ::raspberry_msgs::StampedString const> StampedStringConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::raspberry_msgs::StampedString_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::raspberry_msgs::StampedString_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace raspberry_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'raspberry_msgs': ['/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::StampedString_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::StampedString_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::StampedString_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::StampedString_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::StampedString_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::StampedString_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::raspberry_msgs::StampedString_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4bafb97ed0a8c81f1b100a4686090002";
  }

  static const char* value(const ::raspberry_msgs::StampedString_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4bafb97ed0a8c81fULL;
  static const uint64_t static_value2 = 0x1b100a4686090002ULL;
};

template<class ContainerAllocator>
struct DataType< ::raspberry_msgs::StampedString_<ContainerAllocator> >
{
  static const char* value()
  {
    return "raspberry_msgs/StampedString";
  }

  static const char* value(const ::raspberry_msgs::StampedString_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::raspberry_msgs::StampedString_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 id\n\
string data\n\
";
  }

  static const char* value(const ::raspberry_msgs::StampedString_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::raspberry_msgs::StampedString_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StampedString_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::raspberry_msgs::StampedString_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::raspberry_msgs::StampedString_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<int64_t>::stream(s, indent + "  ", v.id);
    s << indent << "data: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RASPBERRY_MSGS_MESSAGE_STAMPEDSTRING_H
