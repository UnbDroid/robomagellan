# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from raspberry_msgs/Mag.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Mag(genpy.Message):
  _md5sum = "0462b2824ebe44c25937b0cc174267f0"
  _type = "raspberry_msgs/Mag"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64 m_x
float64 m_y
float64 m_z
int64 tempo"""
  __slots__ = ['m_x','m_y','m_z','tempo']
  _slot_types = ['float64','float64','float64','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       m_x,m_y,m_z,tempo

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Mag, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.m_x is None:
        self.m_x = 0.
      if self.m_y is None:
        self.m_y = 0.
      if self.m_z is None:
        self.m_z = 0.
      if self.tempo is None:
        self.tempo = 0
    else:
      self.m_x = 0.
      self.m_y = 0.
      self.m_z = 0.
      self.tempo = 0

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
      buff.write(_struct_3dq.pack(_x.m_x, _x.m_y, _x.m_z, _x.tempo))
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
      end += 32
      (_x.m_x, _x.m_y, _x.m_z, _x.tempo,) = _struct_3dq.unpack(str[start:end])
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
      buff.write(_struct_3dq.pack(_x.m_x, _x.m_y, _x.m_z, _x.tempo))
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
      end += 32
      (_x.m_x, _x.m_y, _x.m_z, _x.tempo,) = _struct_3dq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3dq = struct.Struct("<3dq")
