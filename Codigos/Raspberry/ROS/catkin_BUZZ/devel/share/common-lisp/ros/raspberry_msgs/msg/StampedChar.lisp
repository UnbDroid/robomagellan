; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude StampedChar.msg.html

(cl:defclass <StampedChar> (roslisp-msg-protocol:ros-message)
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

(cl:defclass StampedChar (<StampedChar>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedChar>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedChar)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<StampedChar> is deprecated: use raspberry_msgs-msg:StampedChar instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedChar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:id-val is deprecated.  Use raspberry_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedChar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:data-val is deprecated.  Use raspberry_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedChar>) ostream)
  "Serializes a message object of type '<StampedChar>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedChar>) istream)
  "Deserializes a message object of type '<StampedChar>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedChar>)))
  "Returns string type for a message object of type '<StampedChar>"
  "raspberry_msgs/StampedChar")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedChar)))
  "Returns string type for a message object of type 'StampedChar"
  "raspberry_msgs/StampedChar")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedChar>)))
  "Returns md5sum for a message object of type '<StampedChar>"
  "6deb871728ba12dea9a57a7cbd60e013")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedChar)))
  "Returns md5sum for a message object of type 'StampedChar"
  "6deb871728ba12dea9a57a7cbd60e013")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedChar>)))
  "Returns full string definition for message of type '<StampedChar>"
  (cl:format cl:nil "int64 id~%char data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedChar)))
  "Returns full string definition for message of type 'StampedChar"
  (cl:format cl:nil "int64 id~%char data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedChar>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedChar>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedChar
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
