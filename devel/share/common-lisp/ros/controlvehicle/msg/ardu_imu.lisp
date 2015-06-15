; Auto-generated. Do not edit!


(cl:in-package controlvehicle-msg)


;//! \htmlinclude ardu_imu.msg.html

(cl:defclass <ardu_imu> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gyroValues
    :reader gyroValues
    :initarg :gyroValues
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (accValues
    :reader accValues
    :initarg :accValues
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (magValues
    :reader magValues
    :initarg :magValues
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass ardu_imu (<ardu_imu>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ardu_imu>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ardu_imu)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name controlvehicle-msg:<ardu_imu> is deprecated: use controlvehicle-msg:ardu_imu instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ardu_imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:header-val is deprecated.  Use controlvehicle-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gyroValues-val :lambda-list '(m))
(cl:defmethod gyroValues-val ((m <ardu_imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:gyroValues-val is deprecated.  Use controlvehicle-msg:gyroValues instead.")
  (gyroValues m))

(cl:ensure-generic-function 'accValues-val :lambda-list '(m))
(cl:defmethod accValues-val ((m <ardu_imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:accValues-val is deprecated.  Use controlvehicle-msg:accValues instead.")
  (accValues m))

(cl:ensure-generic-function 'magValues-val :lambda-list '(m))
(cl:defmethod magValues-val ((m <ardu_imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader controlvehicle-msg:magValues-val is deprecated.  Use controlvehicle-msg:magValues instead.")
  (magValues m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ardu_imu>) ostream)
  "Serializes a message object of type '<ardu_imu>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gyroValues) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'accValues) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'magValues) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ardu_imu>) istream)
  "Deserializes a message object of type '<ardu_imu>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gyroValues) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'accValues) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'magValues) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ardu_imu>)))
  "Returns string type for a message object of type '<ardu_imu>"
  "controlvehicle/ardu_imu")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ardu_imu)))
  "Returns string type for a message object of type 'ardu_imu"
  "controlvehicle/ardu_imu")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ardu_imu>)))
  "Returns md5sum for a message object of type '<ardu_imu>"
  "956c793ef60c822d69ca53a1f4eaa0f4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ardu_imu)))
  "Returns md5sum for a message object of type 'ardu_imu"
  "956c793ef60c822d69ca53a1f4eaa0f4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ardu_imu>)))
  "Returns full string definition for message of type '<ardu_imu>"
  (cl:format cl:nil "Header header~%~%geometry_msgs/Vector3 gyroValues~%geometry_msgs/Vector3 accValues~%geometry_msgs/Vector3 magValues~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ardu_imu)))
  "Returns full string definition for message of type 'ardu_imu"
  (cl:format cl:nil "Header header~%~%geometry_msgs/Vector3 gyroValues~%geometry_msgs/Vector3 accValues~%geometry_msgs/Vector3 magValues~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ardu_imu>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gyroValues))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'accValues))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'magValues))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ardu_imu>))
  "Converts a ROS message object to a list"
  (cl:list 'ardu_imu
    (cl:cons ':header (header msg))
    (cl:cons ':gyroValues (gyroValues msg))
    (cl:cons ':accValues (accValues msg))
    (cl:cons ':magValues (magValues msg))
))
