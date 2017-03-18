; Auto-generated. Do not edit!


(cl:in-package arduino_msgs-msg)


;//! \htmlinclude StampedUint8.msg.html

(cl:defclass <StampedUint8> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type cl:fixnum
    :initform 0))
)

(cl:defclass StampedUint8 (<StampedUint8>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedUint8>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedUint8)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arduino_msgs-msg:<StampedUint8> is deprecated: use arduino_msgs-msg:StampedUint8 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedUint8>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:id-val is deprecated.  Use arduino_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedUint8>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:data-val is deprecated.  Use arduino_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedUint8>) ostream)
  "Serializes a message object of type '<StampedUint8>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'data)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedUint8>) istream)
  "Deserializes a message object of type '<StampedUint8>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'data)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedUint8>)))
  "Returns string type for a message object of type '<StampedUint8>"
  "arduino_msgs/StampedUint8")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedUint8)))
  "Returns string type for a message object of type 'StampedUint8"
  "arduino_msgs/StampedUint8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedUint8>)))
  "Returns md5sum for a message object of type '<StampedUint8>"
  "a7d5c555fbcf0be687d9e8535eaf6b30")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedUint8)))
  "Returns md5sum for a message object of type 'StampedUint8"
  "a7d5c555fbcf0be687d9e8535eaf6b30")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedUint8>)))
  "Returns full string definition for message of type '<StampedUint8>"
  (cl:format cl:nil "int64 id~%uint8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedUint8)))
  "Returns full string definition for message of type 'StampedUint8"
  (cl:format cl:nil "int64 id~%uint8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedUint8>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedUint8>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedUint8
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
