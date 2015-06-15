; Auto-generated. Do not edit!


(cl:in-package controlvehicle-msg)


;//! \htmlinclude temperature.msg.html

(cl:defclass <temperature> (roslisp-msg-protocol:ros-message)
  ((pressure
    :reader pressure
    :initarg :pressure
    :type cl:integer
    :initform 0)
   (tem
    :reader tem
    :initarg :tem
    :type cl:float
    :initform 0.0))
)

(cl:defclass temperature (<temperature>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <temperature>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'temperature)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name controlvehicle-msg:<temperature> is deprecated: use controlvehicle-msg:temperature instead.")))

(cl:ensure-generic-function 'pressure-val :lambda-list '(m))
(cl:defmethod pressure-val ((m <temperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:pressure-val is deprecated.  Use controlvehicle-msg:pressure instead.")
  (pressure m))

(cl:ensure-generic-function 'tem-val :lambda-list '(m))
(cl:defmethod tem-val ((m <temperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:tem-val is deprecated.  Use controlvehicle-msg:tem instead.")
  (tem m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <temperature>) ostream)
  "Serializes a message object of type '<temperature>"
  (cl:let* ((signed (cl:slot-value msg 'pressure)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tem))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <temperature>) istream)
  "Deserializes a message object of type '<temperature>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pressure) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tem) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<temperature>)))
  "Returns string type for a message object of type '<temperature>"
  "controlvehicle/temperature")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'temperature)))
  "Returns string type for a message object of type 'temperature"
  "controlvehicle/temperature")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<temperature>)))
  "Returns md5sum for a message object of type '<temperature>"
  "497bf7bb8f1746bcbb7992d334657900")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'temperature)))
  "Returns md5sum for a message object of type 'temperature"
  "497bf7bb8f1746bcbb7992d334657900")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<temperature>)))
  "Returns full string definition for message of type '<temperature>"
  (cl:format cl:nil "~%int32 pressure~%float32 tem~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'temperature)))
  "Returns full string definition for message of type 'temperature"
  (cl:format cl:nil "~%int32 pressure~%float32 tem~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <temperature>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <temperature>))
  "Converts a ROS message object to a list"
  (cl:list 'temperature
    (cl:cons ':pressure (pressure msg))
    (cl:cons ':tem (tem msg))
))
