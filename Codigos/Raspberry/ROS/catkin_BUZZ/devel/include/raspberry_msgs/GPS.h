// Generated by gencpp from file raspberry_msgs/GPS.msg
// DO NOT EDIT!


#ifndef RASPBERRY_MSGS_MESSAGE_GPS_H
#define RASPBERRY_MSGS_MESSAGE_GPS_H


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
struct GPS_
{
  typedef GPS_<ContainerAllocator> Type;

  GPS_()
    : gpsFixOk(false)
    , gpsFix(0)
    , iTow(0.0)
    , ecefX(0.0)
    , ecefY(0.0)
    , ecefZ(0.0)
    , pAcc(0.0)
    , lat(0.0)
    , lng(0.0)
    , hAcc(0.0)
    , height(0.0)
    , vAcc(0.0)
    , velN(0.0)
    , velE(0.0)
    , velD(0.0)
    , speed3D(0.0)
    , speed2D(0.0)
    , heading(0.0)
    , cAcc(0.0)
    , sAcc(0.0)
    , tempo(0)
    , newPos(false)  {
    }
  GPS_(const ContainerAllocator& _alloc)
    : gpsFixOk(false)
    , gpsFix(0)
    , iTow(0.0)
    , ecefX(0.0)
    , ecefY(0.0)
    , ecefZ(0.0)
    , pAcc(0.0)
    , lat(0.0)
    , lng(0.0)
    , hAcc(0.0)
    , height(0.0)
    , vAcc(0.0)
    , velN(0.0)
    , velE(0.0)
    , velD(0.0)
    , speed3D(0.0)
    , speed2D(0.0)
    , heading(0.0)
    , cAcc(0.0)
    , sAcc(0.0)
    , tempo(0)
    , newPos(false)  {
  (void)_alloc;
    }



   typedef uint8_t _gpsFixOk_type;
  _gpsFixOk_type gpsFixOk;

   typedef int64_t _gpsFix_type;
  _gpsFix_type gpsFix;

   typedef double _iTow_type;
  _iTow_type iTow;

   typedef double _ecefX_type;
  _ecefX_type ecefX;

   typedef double _ecefY_type;
  _ecefY_type ecefY;

   typedef double _ecefZ_type;
  _ecefZ_type ecefZ;

   typedef double _pAcc_type;
  _pAcc_type pAcc;

   typedef double _lat_type;
  _lat_type lat;

   typedef double _lng_type;
  _lng_type lng;

   typedef double _hAcc_type;
  _hAcc_type hAcc;

   typedef double _height_type;
  _height_type height;

   typedef double _vAcc_type;
  _vAcc_type vAcc;

   typedef double _velN_type;
  _velN_type velN;

   typedef double _velE_type;
  _velE_type velE;

   typedef double _velD_type;
  _velD_type velD;

   typedef double _speed3D_type;
  _speed3D_type speed3D;

   typedef double _speed2D_type;
  _speed2D_type speed2D;

   typedef double _heading_type;
  _heading_type heading;

   typedef double _cAcc_type;
  _cAcc_type cAcc;

   typedef double _sAcc_type;
  _sAcc_type sAcc;

   typedef int64_t _tempo_type;
  _tempo_type tempo;

   typedef uint8_t _newPos_type;
  _newPos_type newPos;




  typedef boost::shared_ptr< ::raspberry_msgs::GPS_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::raspberry_msgs::GPS_<ContainerAllocator> const> ConstPtr;

}; // struct GPS_

typedef ::raspberry_msgs::GPS_<std::allocator<void> > GPS;

typedef boost::shared_ptr< ::raspberry_msgs::GPS > GPSPtr;
typedef boost::shared_ptr< ::raspberry_msgs::GPS const> GPSConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::raspberry_msgs::GPS_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::raspberry_msgs::GPS_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::raspberry_msgs::GPS_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raspberry_msgs::GPS_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::GPS_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raspberry_msgs::GPS_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::GPS_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raspberry_msgs::GPS_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::raspberry_msgs::GPS_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ce40b63f049129349999b8d09618a193";
  }

  static const char* value(const ::raspberry_msgs::GPS_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xce40b63f04912934ULL;
  static const uint64_t static_value2 = 0x9999b8d09618a193ULL;
};

template<class ContainerAllocator>
struct DataType< ::raspberry_msgs::GPS_<ContainerAllocator> >
{
  static const char* value()
  {
    return "raspberry_msgs/GPS";
  }

  static const char* value(const ::raspberry_msgs::GPS_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::raspberry_msgs::GPS_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool gpsFixOk\n\
int64 gpsFix\n\
\n\
float64 iTow\n\
float64 ecefX\n\
float64 ecefY\n\
float64 ecefZ\n\
float64 pAcc\n\
\n\
float64 lat\n\
float64 lng\n\
float64 hAcc\n\
float64 height\n\
float64 vAcc\n\
\n\
float64 velN\n\
float64 velE\n\
float64 velD\n\
float64 speed3D\n\
float64 speed2D\n\
float64 heading\n\
float64 cAcc\n\
float64 sAcc\n\
\n\
int64 tempo\n\
bool newPos\n\
";
  }

  static const char* value(const ::raspberry_msgs::GPS_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::raspberry_msgs::GPS_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.gpsFixOk);
      stream.next(m.gpsFix);
      stream.next(m.iTow);
      stream.next(m.ecefX);
      stream.next(m.ecefY);
      stream.next(m.ecefZ);
      stream.next(m.pAcc);
      stream.next(m.lat);
      stream.next(m.lng);
      stream.next(m.hAcc);
      stream.next(m.height);
      stream.next(m.vAcc);
      stream.next(m.velN);
      stream.next(m.velE);
      stream.next(m.velD);
      stream.next(m.speed3D);
      stream.next(m.speed2D);
      stream.next(m.heading);
      stream.next(m.cAcc);
      stream.next(m.sAcc);
      stream.next(m.tempo);
      stream.next(m.newPos);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GPS_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::raspberry_msgs::GPS_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::raspberry_msgs::GPS_<ContainerAllocator>& v)
  {
    s << indent << "gpsFixOk: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.gpsFixOk);
    s << indent << "gpsFix: ";
    Printer<int64_t>::stream(s, indent + "  ", v.gpsFix);
    s << indent << "iTow: ";
    Printer<double>::stream(s, indent + "  ", v.iTow);
    s << indent << "ecefX: ";
    Printer<double>::stream(s, indent + "  ", v.ecefX);
    s << indent << "ecefY: ";
    Printer<double>::stream(s, indent + "  ", v.ecefY);
    s << indent << "ecefZ: ";
    Printer<double>::stream(s, indent + "  ", v.ecefZ);
    s << indent << "pAcc: ";
    Printer<double>::stream(s, indent + "  ", v.pAcc);
    s << indent << "lat: ";
    Printer<double>::stream(s, indent + "  ", v.lat);
    s << indent << "lng: ";
    Printer<double>::stream(s, indent + "  ", v.lng);
    s << indent << "hAcc: ";
    Printer<double>::stream(s, indent + "  ", v.hAcc);
    s << indent << "height: ";
    Printer<double>::stream(s, indent + "  ", v.height);
    s << indent << "vAcc: ";
    Printer<double>::stream(s, indent + "  ", v.vAcc);
    s << indent << "velN: ";
    Printer<double>::stream(s, indent + "  ", v.velN);
    s << indent << "velE: ";
    Printer<double>::stream(s, indent + "  ", v.velE);
    s << indent << "velD: ";
    Printer<double>::stream(s, indent + "  ", v.velD);
    s << indent << "speed3D: ";
    Printer<double>::stream(s, indent + "  ", v.speed3D);
    s << indent << "speed2D: ";
    Printer<double>::stream(s, indent + "  ", v.speed2D);
    s << indent << "heading: ";
    Printer<double>::stream(s, indent + "  ", v.heading);
    s << indent << "cAcc: ";
    Printer<double>::stream(s, indent + "  ", v.cAcc);
    s << indent << "sAcc: ";
    Printer<double>::stream(s, indent + "  ", v.sAcc);
    s << indent << "tempo: ";
    Printer<int64_t>::stream(s, indent + "  ", v.tempo);
    s << indent << "newPos: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.newPos);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RASPBERRY_MSGS_MESSAGE_GPS_H
