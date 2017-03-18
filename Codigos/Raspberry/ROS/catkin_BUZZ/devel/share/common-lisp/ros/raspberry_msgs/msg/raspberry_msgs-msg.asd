
(cl:in-package :asdf)

(defsystem "raspberry_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Acc" :depends-on ("_package_Acc"))
    (:file "_package_Acc" :depends-on ("_package"))
    (:file "StampedUint8" :depends-on ("_package_StampedUint8"))
    (:file "_package_StampedUint8" :depends-on ("_package"))
    (:file "StampedUint64" :depends-on ("_package_StampedUint64"))
    (:file "_package_StampedUint64" :depends-on ("_package"))
    (:file "StampedInt64" :depends-on ("_package_StampedInt64"))
    (:file "_package_StampedInt64" :depends-on ("_package"))
    (:file "StampedBool" :depends-on ("_package_StampedBool"))
    (:file "_package_StampedBool" :depends-on ("_package"))
    (:file "StampedUint32" :depends-on ("_package_StampedUint32"))
    (:file "_package_StampedUint32" :depends-on ("_package"))
    (:file "StampedString" :depends-on ("_package_StampedString"))
    (:file "_package_StampedString" :depends-on ("_package"))
    (:file "StampedFloat64" :depends-on ("_package_StampedFloat64"))
    (:file "_package_StampedFloat64" :depends-on ("_package"))
    (:file "Gyro" :depends-on ("_package_Gyro"))
    (:file "_package_Gyro" :depends-on ("_package"))
    (:file "StampedFloat32" :depends-on ("_package_StampedFloat32"))
    (:file "_package_StampedFloat32" :depends-on ("_package"))
    (:file "StampedInt8" :depends-on ("_package_StampedInt8"))
    (:file "_package_StampedInt8" :depends-on ("_package"))
    (:file "StampedChar" :depends-on ("_package_StampedChar"))
    (:file "_package_StampedChar" :depends-on ("_package"))
    (:file "StampedInt32" :depends-on ("_package_StampedInt32"))
    (:file "_package_StampedInt32" :depends-on ("_package"))
    (:file "StampedInt16" :depends-on ("_package_StampedInt16"))
    (:file "_package_StampedInt16" :depends-on ("_package"))
  ))