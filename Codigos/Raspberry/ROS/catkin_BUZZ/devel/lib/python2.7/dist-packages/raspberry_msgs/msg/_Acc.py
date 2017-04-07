# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from raspberry_msgs/Acc.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Acc(genpy.Message):
  _md5sum = "79dbd4567e140183ab42121735f0a17c"
  _type = "raspberry_msgs/Acc"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 a_x
float32 a_y
float32 a_z
int64 time"""
  __slots__ = ['a_x','a_y','a_z','time']
  _slot_types = ['float32','float32','float32','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       a_x,a_y,a_z,time

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Acc, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.a_x is None:
        self.a_x = 0.
      if self.a_y is None:
        self.a_y = 0.
      if self.a_z is None:
        self.a_z = 0.
      if self.time is None:
        self.time = 0
    else:
      self.a_x = 0.
      self.a_y = 0.
      self.a_z = 0.
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
      buff.write(_struct_3fq.pack(_x.a_x, _x.a_y, _x.a_z, _x.time))
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
      (_x.a_x, _x.a_y, _x.a_z, _x.time,) = _struct_3fq.unpack(str[start:end])
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
      buff.write(_struct_3fq.pack(_x.a_x, _x.a_y, _x.a_z, _x.time))
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
      (_x.a_x, _x.a_y, _x.a_z, _x.time,) = _struct_3fq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3fq = struct.Struct("<3fq")
