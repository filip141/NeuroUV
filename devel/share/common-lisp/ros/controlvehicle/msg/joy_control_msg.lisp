; Auto-generated. Do not edit!


(cl:in-package controlvehicle-msg)


;//! \htmlinclude joy_control_msg.msg.html

(cl:defclass <joy_control_msg> (roslisp-msg-protocol:ros-message)
  ((sequence
    :reader sequence
    :initarg :sequence
    :type cl:fixnum
    :initform 0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:fixnum
    :initform 0)
   (powerLR
    :reader powerLR
    :initarg :powerLR
    :type cl:fixnum
    :initform 0))
)

(cl:defclass joy_control_msg (<joy_control_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <joy_control_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'joy_control_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name controlvehicle-msg:<joy_control_msg> is deprecated: use controlvehicle-msg:joy_control_msg instead.")))

(cl:ensure-generic-function 'sequence-val :lambda-list '(m))
(cl:defmethod sequence-val ((m <joy_control_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:sequence-val is deprecated.  Use controlvehicle-msg:sequence instead.")
  (sequence m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <joy_control_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:speed-val is deprecated.  Use controlvehicle-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'powerLR-val :lambda-list '(m))
(cl:defmethod powerLR-val ((m <joy_control_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:powerLR-val is deprecated.  Use controlvehicle-msg:powerLR instead.")
  (powerLR m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <joy_control_msg>) ostream)
  "Serializes a message object of type '<joy_control_msg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sequence)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'powerLR)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <joy_control_msg>) istream)
  "Deserializes a message object of type '<joy_control_msg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sequence)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'speed) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'powerLR) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<joy_control_msg>)))
  "Returns string type for a message object of type '<joy_control_msg>"
  "controlvehicle/joy_control_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'joy_control_msg)))
  "Returns string type for a message object of type 'joy_control_msg"
  "controlvehicle/joy_control_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<joy_control_msg>)))
  "Returns md5sum for a message object of type '<joy_control_msg>"
  "499cf4e3d592166be607da2914a0e4a0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'joy_control_msg)))
  "Returns md5sum for a message object of type 'joy_control_msg"
  "499cf4e3d592166be607da2914a0e4a0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<joy_control_msg>)))
  "Returns full string definition for message of type '<joy_control_msg>"
  (cl:format cl:nil "uint8 sequence~%int8 speed~%int8 powerLR~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'joy_control_msg)))
  "Returns full string definition for message of type 'joy_control_msg"
  (cl:format cl:nil "uint8 sequence~%int8 speed~%int8 powerLR~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <joy_control_msg>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <joy_control_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'joy_control_msg
    (cl:cons ':sequence (sequence msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':powerLR (powerLR msg))
))
