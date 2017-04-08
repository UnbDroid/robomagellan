; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude StampedInt8.msg.html

(cl:defclass <StampedInt8> (roslisp-msg-protocol:ros-message)
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

(cl:defclass StampedInt8 (<StampedInt8>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedInt8>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedInt8)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<StampedInt8> is deprecated: use raspberry_msgs-msg:StampedInt8 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedInt8>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:id-val is deprecated.  Use raspberry_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedInt8>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:data-val is deprecated.  Use raspberry_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedInt8>) ostream)
  "Serializes a message object of type '<StampedInt8>"
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
  (cl:let* ((signed (cl:slot-value msg 'data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedInt8>) istream)
  "Deserializes a message object of type '<StampedInt8>"
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
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedInt8>)))
  "Returns string type for a message object of type '<StampedInt8>"
  "raspberry_msgs/StampedInt8")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedInt8)))
  "Returns string type for a message object of type 'StampedInt8"
  "raspberry_msgs/StampedInt8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedInt8>)))
  "Returns md5sum for a message object of type '<StampedInt8>"
  "9bacc5a7a0842fe6c35d0f5da065e43f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedInt8)))
  "Returns md5sum for a message object of type 'StampedInt8"
  "9bacc5a7a0842fe6c35d0f5da065e43f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedInt8>)))
  "Returns full string definition for message of type '<StampedInt8>"
  (cl:format cl:nil "int64 id~%int8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedInt8)))
  "Returns full string definition for message of type 'StampedInt8"
  (cl:format cl:nil "int64 id~%int8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedInt8>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedInt8>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedInt8
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
