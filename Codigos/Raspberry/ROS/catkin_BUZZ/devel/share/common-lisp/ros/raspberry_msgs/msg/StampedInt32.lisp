; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude StampedInt32.msg.html

(cl:defclass <StampedInt32> (roslisp-msg-protocol:ros-message)
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

(cl:defclass StampedInt32 (<StampedInt32>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedInt32>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedInt32)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<StampedInt32> is deprecated: use raspberry_msgs-msg:StampedInt32 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedInt32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:id-val is deprecated.  Use raspberry_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedInt32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:data-val is deprecated.  Use raspberry_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedInt32>) ostream)
  "Serializes a message object of type '<StampedInt32>"
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
  (cl:let* ((signed (cl:slot-value msg 'data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedInt32>) istream)
  "Deserializes a message object of type '<StampedInt32>"
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
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedInt32>)))
  "Returns string type for a message object of type '<StampedInt32>"
  "raspberry_msgs/StampedInt32")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedInt32)))
  "Returns string type for a message object of type 'StampedInt32"
  "raspberry_msgs/StampedInt32")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedInt32>)))
  "Returns md5sum for a message object of type '<StampedInt32>"
  "34d8a4c3e901989cdd877a3b0dcd3207")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedInt32)))
  "Returns md5sum for a message object of type 'StampedInt32"
  "34d8a4c3e901989cdd877a3b0dcd3207")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedInt32>)))
  "Returns full string definition for message of type '<StampedInt32>"
  (cl:format cl:nil "int64 id~%int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedInt32)))
  "Returns full string definition for message of type 'StampedInt32"
  (cl:format cl:nil "int64 id~%int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedInt32>))
  (cl:+ 0
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedInt32>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedInt32
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
