# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from raspberry_msgs/Gyro.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Gyro(genpy.Message):
  _md5sum = "fdbe35c96cc4518a9444f2526afab160"
  _type = "raspberry_msgs/Gyro"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 g_x
float32 g_y
float32 g_z
int64 time"""
  __slots__ = ['g_x','g_y','g_z','time']
  _slot_types = ['float32','float32','float32','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       g_x,g_y,g_z,time

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Gyro, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.g_x is None:
        self.g_x = 0.
      if self.g_y is None:
        self.g_y = 0.
      if self.g_z is None:
        self.g_z = 0.
      if self.time is None:
        self.time = 0
    else:
      self.g_x = 0.
      self.g_y = 0.
      self.g_z = 0.
      self.time = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3fq.pack(_x.g_x, _x.g_y, _x.g_z, _x.time))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.g_x, _x.g_y, _x.g_z, _x.time,) = _struct_3fq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3fq.pack(_x.g_x, _x.g_y, _x.g_z, _x.time))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.g_x, _x.g_y, _x.g_z, _x.time,) = _struct_3fq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3fq = struct.Struct("<3fq")
