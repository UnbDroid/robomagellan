; Auto-generated. Do not edit!


(cl:in-package raspberry_msgs-msg)


;//! \htmlinclude GPS.msg.html

(cl:defclass <GPS> (roslisp-msg-protocol:ros-message)
  ((valid
    :reader valid
    :initarg :valid
    :type cl:boolean
    :initform cl:nil)
   (lat
    :reader lat
    :initarg :lat
    :type cl:float
    :initform 0.0)
   (lng
    :reader lng
    :initarg :lng
    :type cl:float
    :initform 0.0)
   (alt
    :reader alt
    :initarg :alt
    :type cl:float
    :initform 0.0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:float
    :initform 0.0)
   (hdop
    :reader hdop
    :initarg :hdop
    :type cl:float
    :initform 0.0)
   (vdop
    :reader vdop
    :initarg :vdop
    :type cl:float
    :initform 0.0)
   (pdop
    :reader pdop
    :initarg :pdop
    :type cl:float
    :initform 0.0))
)

(cl:defclass GPS (<GPS>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GPS>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GPS)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name raspberry_msgs-msg:<GPS> is deprecated: use raspberry_msgs-msg:GPS instead.")))

(cl:ensure-generic-function 'valid-val :lambda-list '(m))
(cl:defmethod valid-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:valid-val is deprecated.  Use raspberry_msgs-msg:valid instead.")
  (valid m))

(cl:ensure-generic-function 'lat-val :lambda-list '(m))
(cl:defmethod lat-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:lat-val is deprecated.  Use raspberry_msgs-msg:lat instead.")
  (lat m))

(cl:ensure-generic-function 'lng-val :lambda-list '(m))
(cl:defmethod lng-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:lng-val is deprecated.  Use raspberry_msgs-msg:lng instead.")
  (lng m))

(cl:ensure-generic-function 'alt-val :lambda-list '(m))
(cl:defmethod alt-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:alt-val is deprecated.  Use raspberry_msgs-msg:alt instead.")
  (alt m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:speed-val is deprecated.  Use raspberry_msgs-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'hdop-val :lambda-list '(m))
(cl:defmethod hdop-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:hdop-val is deprecated.  Use raspberry_msgs-msg:hdop instead.")
  (hdop m))

(cl:ensure-generic-function 'vdop-val :lambda-list '(m))
(cl:defmethod vdop-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:vdop-val is deprecated.  Use raspberry_msgs-msg:vdop instead.")
  (vdop m))

(cl:ensure-generic-function 'pdop-val :lambda-list '(m))
(cl:defmethod pdop-val ((m <GPS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader raspberry_msgs-msg:pdop-val is deprecated.  Use raspberry_msgs-msg:pdop instead.")
  (pdop m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GPS>) ostream)
  "Serializes a message object of type '<GPS>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'valid) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'lat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'lng))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'alt))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'hdop))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vdop))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pdop))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GPS>) istream)
  "Deserializes a message object of type '<GPS>"
    (cl:setf (cl:slot-value msg 'valid) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lat) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lng) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'alt) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'speed) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'hdop) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vdop) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pdop) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GPS>)))
  "Returns string type for a message object of type '<GPS>"
  "raspberry_msgs/GPS")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GPS)))
  "Returns string type for a message object of type 'GPS"
  "raspberry_msgs/GPS")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GPS>)))
  "Returns md5sum for a message object of type '<GPS>"
  "eb3a7471d9a50e828ab96794f4a00013")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GPS)))
  "Returns md5sum for a message object of type 'GPS"
  "eb3a7471d9a50e828ab96794f4a00013")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GPS>)))
  "Returns full string definition for message of type '<GPS>"
  (cl:format cl:nil "bool valid~%float64 lat~%float64 lng~%float64 alt~%float64 speed~%float32 hdop~%float32 vdop~%float32 pdop~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GPS)))
  "Returns full string definition for message of type 'GPS"
  (cl:format cl:nil "bool valid~%float64 lat~%float64 lng~%float64 alt~%float64 speed~%float32 hdop~%float32 vdop~%float32 pdop~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GPS>))
  (cl:+ 0
     1
     8
     8
     8
     8
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GPS>))
  "Converts a ROS message object to a list"
  (cl:list 'GPS
    (cl:cons ':valid (valid msg))
    (cl:cons ':lat (lat msg))
    (cl:cons ':lng (lng msg))
    (cl:cons ':alt (alt msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':hdop (hdop msg))
    (cl:cons ':vdop (vdop msg))
    (cl:cons ':pdop (pdop msg))
))
