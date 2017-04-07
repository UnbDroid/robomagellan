; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude StampedBool.msg.html

(cl:defclass <StampedBool> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass StampedBool (<StampedBool>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedBool>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedBool)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<StampedBool> is deprecated: use raspberry_msgs-msg:StampedBool instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedBool>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:id-val is deprecated.  Use raspberry_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedBool>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:data-val is deprecated.  Use raspberry_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedBool>) ostream)
  "Serializes a message object of type '<StampedBool>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'data) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedBool>) istream)
  "Deserializes a message object of type '<StampedBool>"
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
    (cl:setf (cl:slot-value msg 'data) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedBool>)))
  "Returns string type for a message object of type '<StampedBool>"
  "raspberry_msgs/StampedBool")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedBool)))
  "Returns string type for a message object of type 'StampedBool"
  "raspberry_msgs/StampedBool")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedBool>)))
  "Returns md5sum for a message object of type '<StampedBool>"
  "1ea8d20576980505756a7dfb61228350")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedBool)))
  "Returns md5sum for a message object of type 'StampedBool"
  "1ea8d20576980505756a7dfb61228350")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedBool>)))
  "Returns full string definition for message of type '<StampedBool>"
  (cl:format cl:nil "int64 id~%bool data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedBool)))
  "Returns full string definition for message of type 'StampedBool"
  (cl:format cl:nil "int64 id~%bool data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedBool>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedBool>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedBool
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
