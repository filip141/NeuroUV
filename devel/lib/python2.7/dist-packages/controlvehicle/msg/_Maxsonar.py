"""autogenerated by genpy from controlvehicle/Maxsonar.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Maxsonar(genpy.Message):
  _md5sum = "2f513f8756037fca86f700a692eb93b6"
  _type = "controlvehicle/Maxsonar"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """
float32 sonar1
float32 sonar2
float32 sonar3
float32 sonar4


"""
  __slots__ = ['sonar1','sonar2','sonar3','sonar4']
  _slot_types = ['float32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       sonar1,sonar2,sonar3,sonar4

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Maxsonar, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.sonar1 is None:
        self.sonar1 = 0.
      if self.sonar2 is None:
        self.sonar2 = 0.
      if self.sonar3 is None:
        self.sonar3 = 0.
      if self.sonar4 is None:
        self.sonar4 = 0.
    else:
      self.sonar1 = 0.
      self.sonar2 = 0.
      self.sonar3 = 0.
      self.sonar4 = 0.

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
      buff.write(_struct_4f.pack(_x.sonar1, _x.sonar2, _x.sonar3, _x.sonar4))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 16
      (_x.sonar1, _x.sonar2, _x.sonar3, _x.sonar4,) = _struct_4f.unpack(str[start:end])
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
      buff.write(_struct_4f.pack(_x.sonar1, _x.sonar2, _x.sonar3, _x.sonar4))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

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
      end += 16
      (_x.sonar1, _x.sonar2, _x.sonar3, _x.sonar4,) = _struct_4f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_4f = struct.Struct("<4f")