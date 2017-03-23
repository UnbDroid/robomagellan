; Auto-generated. Do not edit!


(cl:in-package robo_virtual-msg)


;//! \htmlinclude Posicao.msg.html

(cl:defclass <Posicao> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0)
   (velocidade
    :reader velocidade
    :initarg :velocidade
    :type cl:float
    :initform 0.0))
)

(cl:defclass Posicao (<Posicao>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Posicao>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Posicao)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robo_virtual-msg:<Posicao> is deprecated: use robo_virtual-msg:Posicao instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Posicao>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robo_virtual-msg:x-val is deprecated.  Use robo_virtual-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Posicao>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robo_virtual-msg:y-val is deprecated.  Use robo_virtual-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <Posicao>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robo_virtual-msg:theta-val is deprecated.  Use robo_virtual-msg:theta instead.")
  (theta m))

(cl:ensure-generic-function 'velocidade-val :lambda-list '(m))
(cl:defmethod velocidade-val ((m <Posicao>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robo_virtual-msg:velocidade-val is deprecated.  Use robo_virtual-msg:velocidade instead.")
  (velocidade m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Posicao>) ostream)
  "Serializes a message object of type '<Posicao>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocidade))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Posicao>) istream)
  "Deserializes a message object of type '<Posicao>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocidade) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Posicao>)))
  "Returns string type for a message object of type '<Posicao>"
  "robo_virtual/Posicao")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Posicao)))
  "Returns string type for a message object of type 'Posicao"
  "robo_virtual/Posicao")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Posicao>)))
  "Returns md5sum for a message object of type '<Posicao>"
  "c80cbd8dfeeb8e79ddb6c3b83c556b03")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Posicao)))
  "Returns md5sum for a message object of type 'Posicao"
  "c80cbd8dfeeb8e79ddb6c3b83c556b03")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Posicao>)))
  "Returns full string definition for message of type '<Posicao>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 theta~%float32 velocidade~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Posicao)))
  "Returns full string definition for message of type 'Posicao"
  (cl:format cl:nil "float32 x~%float32 y~%float32 theta~%float32 velocidade~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Posicao>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Posicao>))
  "Converts a ROS message object to a list"
  (cl:list 'Posicao
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':theta (theta msg))
    (cl:cons ':velocidade (velocidade msg))
))
