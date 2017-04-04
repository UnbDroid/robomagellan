; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude Gyro.msg.html

(cl:defclass <Gyro> (roslisp-msg-protocol:ros-message)
  ((g_x
    :reader g_x
    :initarg :g_x
    :type cl:float
    :initform 0.0)
   (g_y
    :reader g_y
    :initarg :g_y
    :type cl:float
    :initform 0.0)
   (g_z
    :reader g_z
    :initarg :g_z
    :type cl:float
    :initform 0.0)
   (time
    :reader time
    :initarg :time
    :type cl:integer
    :initform 0))
)

(cl:defclass Gyro (<Gyro>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Gyro>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Gyro)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<Gyro> is deprecated: use raspberry_msgs-msg:Gyro instead.")))

(cl:ensure-generic-function 'g_x-val :lambda-list '(m))
(cl:defmethod g_x-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:g_x-val is deprecated.  Use raspberry_msgs-msg:g_x instead.")
  (g_x m))

(cl:ensure-generic-function 'g_y-val :lambda-list '(m))
(cl:defmethod g_y-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:g_y-val is deprecated.  Use raspberry_msgs-msg:g_y instead.")
  (g_y m))

(cl:ensure-generic-function 'g_z-val :lambda-list '(m))
(cl:defmethod g_z-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:g_z-val is deprecated.  Use raspberry_msgs-msg:g_z instead.")
  (g_z m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:time-val is deprecated.  Use raspberry_msgs-msg:time instead.")
  (time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Gyro>) ostream)
  "Serializes a message object of type '<Gyro>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'g_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'g_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'g_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Gyro>) istream)
  "Deserializes a message object of type '<Gyro>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'g_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'g_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'g_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'time) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Gyro>)))
  "Returns string type for a message object of type '<Gyro>"
  "raspberry_msgs/Gyro")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Gyro)))
  "Returns string type for a message object of type 'Gyro"
  "raspberry_msgs/Gyro")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Gyro>)))
  "Returns md5sum for a message object of type '<Gyro>"
  "fdbe35c96cc4518a9444f2526afab160")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Gyro)))
  "Returns md5sum for a message object of type 'Gyro"
  "fdbe35c96cc4518a9444f2526afab160")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Gyro>)))
  "Returns full string definition for message of type '<Gyro>"
  (cl:format cl:nil "float32 g_x~%float32 g_y~%float32 g_z~%int64 time~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Gyro)))
  "Returns full string definition for message of type 'Gyro"
  (cl:format cl:nil "float32 g_x~%float32 g_y~%float32 g_z~%int64 time~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Gyro>))
  (cl:+ 0
     4
     4
     4
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Gyro>))
  "Converts a ROS message object to a list"
  (cl:list 'Gyro
    (cl:cons ':g_x (g_x msg))
    (cl:cons ':g_y (g_y msg))
    (cl:cons ':g_z (g_z msg))
    (cl:cons ':time (time msg))
))
