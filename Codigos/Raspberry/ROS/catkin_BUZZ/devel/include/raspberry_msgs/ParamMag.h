// Generated by gencpp from file raspberry_msgs/ParamMag.msg
// DO NOT EDIT!


#ifndef RASPBERRY_MSGS_MESSAGE_PARAMMAG_H
#define RASPBERRY_MSGS_MESSAGE_PARAMMAG_H


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
struct ParamMag_
{
  typedef ParamMag_<ContainerAllocator> Type;

  ParamMag_()
    : bx(0.0)
    , by(0.0)
    , bz(0.0)
    , sx(0.0)
    , sy(0.0)
    , sz(0.0)  {
    }
  ParamMag_(const ContainerAllocator& _alloc)
    : bx(0.0)
    , by(0.0)
    , bz(0.0)
    , sx(0.0)
    , sy(0.0)
    , sz(0.0)  {
  (void)_alloc;
    }



   typedef double _bx_type;
  _bx_type bx;

   typedef double _by_type;
  _by_type by;

   typedef double _bz_type;
  _bz_type bz;

   typedef double _sx_type;
  _sx_type sx;

   typedef double _sy_type;
  _sy_type sy;

   typedef double _sz_type;
  _sz_type sz;




  typedef boost::shared_ptr< ::raspberry_msgs::ParamMag_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::raspberry_msgs::ParamMag_<ContainerAllocator> const> ConstPtr;

}; // struct ParamMag_

typedef ::raspberry_msgs::ParamMag_<std::allocator<void> > ParamMag;

typedef boost::shared_ptr< ::raspberry_msgs::ParamMag > ParamMagPtr;
typedef boost::shared_ptr< ::raspberry_msgs::ParamMag const> ParamMagConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::raspberry_msgs::ParamMag_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::raspberry_msgs::ParamMag_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::ParamMag_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::ParamMag_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::ParamMag_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f07ef5807ccc316d34a8d12ba22eff32";
  }

  static const char* value(const ::raspberry_msgs::ParamMag_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf07ef5807ccc316dULL;
  static const uint64_t static_value2 = 0x34a8d12ba22eff32ULL;
};

template<class ContainerAllocator>
struct DataType< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "raspberry_msgs/ParamMag";
  }

  static const char* value(const ::raspberry_msgs::ParamMag_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 bx\n\
float64 by\n\
float64 bz\n\
float64 sx\n\
float64 sy\n\
float64 sz\n\
";
  }

  static const char* value(const ::raspberry_msgs::ParamMag_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.bx);
      stream.next(m.by);
      stream.next(m.bz);
      stream.next(m.sx);
      stream.next(m.sy);
      stream.next(m.sz);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ParamMag_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::raspberry_msgs::ParamMag_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::raspberry_msgs::ParamMag_<ContainerAllocator>& v)
  {
    s << indent << "bx: ";
    Printer<double>::stream(s, indent + "  ", v.bx);
    s << indent << "by: ";
    Printer<double>::stream(s, indent + "  ", v.by);
    s << indent << "bz: ";
    Printer<double>::stream(s, indent + "  ", v.bz);
    s << indent << "sx: ";
    Printer<double>::stream(s, indent + "  ", v.sx);
    s << indent << "sy: ";
    Printer<double>::stream(s, indent + "  ", v.sy);
    s << indent << "sz: ";
    Printer<double>::stream(s, indent + "  ", v.sz);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RASPBERRY_MSGS_MESSAGE_PARAMMAG_H
