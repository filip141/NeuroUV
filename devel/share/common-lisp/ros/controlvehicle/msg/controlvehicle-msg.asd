
(cl:in-package :asdf)

(defsystem "controlvehicle-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ardu_imu" :depends-on ("_package_ardu_imu"))
    (:file "_package_ardu_imu" :depends-on ("_package"))
    (:file "Maxsonar" :depends-on ("_package_Maxsonar"))
    (:file "_package_Maxsonar" :depends-on ("_package"))
    (:file "joy_control_msg" :depends-on ("_package_joy_control_msg"))
    (:file "_package_joy_control_msg" :depends-on ("_package"))
    (:file "temperature" :depends-on ("_package_temperature"))
    (:file "_package_temperature" :depends-on ("_package"))
  ))