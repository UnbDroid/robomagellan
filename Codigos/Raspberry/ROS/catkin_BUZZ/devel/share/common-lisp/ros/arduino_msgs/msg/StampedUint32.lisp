; Auto-generated. Do not edit!


(cl:in-package arduino_msgs-msg)


;//! \htmlinclude StampedUint32.msg.html

(cl:defclass <StampedUint32> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type cl:integer
    :initform 0))
)

(cl:defclass StampedUint32 (<StampedUint32>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedUint32>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedUint32)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arduino_msgs-msg:<StampedUint32> is deprecated: use arduino_msgs-msg:StampedUint32 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedUint32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:id-val is deprecated.  Use arduino_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedUint32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:data-val is deprecated.  Use arduino_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedUint32>) ostream)
  "Serializes a message object of type '<StampedUint32>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'data)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'data)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'data)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedUint32>) istream)
  "Deserializes a message object of type '<StampedUint32>"
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
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'data)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'data)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'data)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedUint32>)))
  "Returns string type for a message object of type '<StampedUint32>"
  "arduino_msgs/StampedUint32")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedUint32)))
  "Returns string type for a message object of type 'StampedUint32"
  "arduino_msgs/StampedUint32")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedUint32>)))
  "Returns md5sum for a message object of type '<StampedUint32>"
  "c8aa5d8d37856a61d8e6896b996b033f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedUint32)))
  "Returns md5sum for a message object of type 'StampedUint32"
  "c8aa5d8d37856a61d8e6896b996b033f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedUint32>)))
  "Returns full string definition for message of type '<StampedUint32>"
  (cl:format cl:nil "int64 id~%uint32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedUint32)))
  "Returns full string definition for message of type 'StampedUint32"
  (cl:format cl:nil "int64 id~%uint32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedUint32>))
  (cl:+ 0
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedUint32>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedUint32
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
