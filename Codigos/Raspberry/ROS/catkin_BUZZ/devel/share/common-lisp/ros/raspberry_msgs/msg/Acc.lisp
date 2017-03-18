; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude Acc.msg.html

(cl:defclass <Acc> (roslisp-msg-protocol:ros-message)
  ((a_x
    :reader a_x
    :initarg :a_x
    :type cl:fixnum
    :initform 0)
   (a_y
    :reader a_y
    :initarg :a_y
    :type cl:fixnum
    :initform 0)
   (a_z
    :reader a_z
    :initarg :a_z
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Acc (<Acc>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Acc>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Acc)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<Acc> is deprecated: use raspberry_msgs-msg:Acc instead.")))

(cl:ensure-generic-function 'a_x-val :lambda-list '(m))
(cl:defmethod a_x-val ((m <Acc>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:a_x-val is deprecated.  Use raspberry_msgs-msg:a_x instead.")
  (a_x m))

(cl:ensure-generic-function 'a_y-val :lambda-list '(m))
(cl:defmethod a_y-val ((m <Acc>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:a_y-val is deprecated.  Use raspberry_msgs-msg:a_y instead.")
  (a_y m))

(cl:ensure-generic-function 'a_z-val :lambda-list '(m))
(cl:defmethod a_z-val ((m <Acc>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:a_z-val is deprecated.  Use raspberry_msgs-msg:a_z instead.")
  (a_z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Acc>) ostream)
  "Serializes a message object of type '<Acc>"
  (cl:let* ((signed (cl:slot-value msg 'a_x)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'a_y)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'a_z)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Acc>) istream)
  "Deserializes a message object of type '<Acc>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'a_x) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'a_y) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'a_z) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Acc>)))
  "Returns string type for a message object of type '<Acc>"
  "raspberry_msgs/Acc")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Acc)))
  "Returns string type for a message object of type 'Acc"
  "raspberry_msgs/Acc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Acc>)))
  "Returns md5sum for a message object of type '<Acc>"
  "5e828625e6cd4bb051f091c5afb51743")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Acc)))
  "Returns md5sum for a message object of type 'Acc"
  "5e828625e6cd4bb051f091c5afb51743")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Acc>)))
  "Returns full string definition for message of type '<Acc>"
  (cl:format cl:nil "int16 a_x~%int16 a_y~%int16 a_z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Acc)))
  "Returns full string definition for message of type 'Acc"
  (cl:format cl:nil "int16 a_x~%int16 a_y~%int16 a_z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Acc>))
  (cl:+ 0
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Acc>))
  "Converts a ROS message object to a list"
  (cl:list 'Acc
    (cl:cons ':a_x (a_x msg))
    (cl:cons ':a_y (a_y msg))
    (cl:cons ':a_z (a_z msg))
))
