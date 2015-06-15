; Auto-generated. Do not edit!


(cl:in-package controlvehicle-msg)


;//! \htmlinclude Maxsonar.msg.html

(cl:defclass <Maxsonar> (roslisp-msg-protocol:ros-message)
  ((sonar1
    :reader sonar1
    :initarg :sonar1
    :type cl:float
    :initform 0.0)
   (sonar2
    :reader sonar2
    :initarg :sonar2
    :type cl:float
    :initform 0.0)
   (sonar3
    :reader sonar3
    :initarg :sonar3
    :type cl:float
    :initform 0.0)
   (sonar4
    :reader sonar4
    :initarg :sonar4
    :type cl:float
    :initform 0.0))
)

(cl:defclass Maxsonar (<Maxsonar>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Maxsonar>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Maxsonar)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name controlvehicle-msg:<Maxsonar> is deprecated: use controlvehicle-msg:Maxsonar instead.")))

(cl:ensure-generic-function 'sonar1-val :lambda-list '(m))
(cl:defmethod sonar1-val ((m <Maxsonar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:sonar1-val is deprecated.  Use controlvehicle-msg:sonar1 instead.")
  (sonar1 m))

(cl:ensure-generic-function 'sonar2-val :lambda-list '(m))
(cl:defmethod sonar2-val ((m <Maxsonar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:sonar2-val is deprecated.  Use controlvehicle-msg:sonar2 instead.")
  (sonar2 m))

(cl:ensure-generic-function 'sonar3-val :lambda-list '(m))
(cl:defmethod sonar3-val ((m <Maxsonar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:sonar3-val is deprecated.  Use controlvehicle-msg:sonar3 instead.")
  (sonar3 m))

(cl:ensure-generic-function 'sonar4-val :lambda-list '(m))
(cl:defmethod sonar4-val ((m <Maxsonar>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:sonar4-val is deprecated.  Use controlvehicle-msg:sonar4 instead.")
  (sonar4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Maxsonar>) ostream)
  "Serializes a message object of type '<Maxsonar>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sonar1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sonar2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sonar3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sonar4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Maxsonar>) istream)
  "Deserializes a message object of type '<Maxsonar>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sonar1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sonar2) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sonar3) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sonar4) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Maxsonar>)))
  "Returns string type for a message object of type '<Maxsonar>"
  "controlvehicle/Maxsonar")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Maxsonar)))
  "Returns string type for a message object of type 'Maxsonar"
  "controlvehicle/Maxsonar")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Maxsonar>)))
  "Returns md5sum for a message object of type '<Maxsonar>"
  "2f513f8756037fca86f700a692eb93b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Maxsonar)))
  "Returns md5sum for a message object of type 'Maxsonar"
  "2f513f8756037fca86f700a692eb93b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Maxsonar>)))
  "Returns full string definition for message of type '<Maxsonar>"
  (cl:format cl:nil "~%float32 sonar1~%float32 sonar2~%float32 sonar3~%float32 sonar4~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Maxsonar)))
  "Returns full string definition for message of type 'Maxsonar"
  (cl:format cl:nil "~%float32 sonar1~%float32 sonar2~%float32 sonar3~%float32 sonar4~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Maxsonar>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Maxsonar>))
  "Converts a ROS message object to a list"
  (cl:list 'Maxsonar
    (cl:cons ':sonar1 (sonar1 msg))
    (cl:cons ':sonar2 (sonar2 msg))
    (cl:cons ':sonar3 (sonar3 msg))
    (cl:cons ':sonar4 (sonar4 msg))
))
