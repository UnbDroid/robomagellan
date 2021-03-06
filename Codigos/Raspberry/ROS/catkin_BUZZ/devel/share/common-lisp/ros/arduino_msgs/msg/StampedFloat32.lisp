; Auto-generated. Do not edit!


(cl:in-package arduino_msgs-msg)


;//! \htmlinclude StampedFloat32.msg.html

(cl:defclass <StampedFloat32> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type cl:float
    :initform 0.0))
)

(cl:defclass StampedFloat32 (<StampedFloat32>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StampedFloat32>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StampedFloat32)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arduino_msgs-msg:<StampedFloat32> is deprecated: use arduino_msgs-msg:StampedFloat32 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <StampedFloat32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:id-val is deprecated.  Use arduino_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <StampedFloat32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arduino_msgs-msg:data-val is deprecated.  Use arduino_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StampedFloat32>) ostream)
  "Serializes a message object of type '<StampedFloat32>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StampedFloat32>) istream)
  "Deserializes a message object of type '<StampedFloat32>"
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'data) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StampedFloat32>)))
  "Returns string type for a message object of type '<StampedFloat32>"
  "arduino_msgs/StampedFloat32")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StampedFloat32)))
  "Returns string type for a message object of type 'StampedFloat32"
  "arduino_msgs/StampedFloat32")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StampedFloat32>)))
  "Returns md5sum for a message object of type '<StampedFloat32>"
  "166b96779b23aaf8990132180f851a29")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StampedFloat32)))
  "Returns md5sum for a message object of type 'StampedFloat32"
  "166b96779b23aaf8990132180f851a29")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StampedFloat32>)))
  "Returns full string definition for message of type '<StampedFloat32>"
  (cl:format cl:nil "int64 id~%float32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StampedFloat32)))
  "Returns full string definition for message of type 'StampedFloat32"
  (cl:format cl:nil "int64 id~%float32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StampedFloat32>))
  (cl:+ 0
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StampedFloat32>))
  "Converts a ROS message object to a list"
  (cl:list 'StampedFloat32
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
