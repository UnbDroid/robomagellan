
(cl:in-package :asdf)

(defsystem "raspberry_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "StampedUint32" :depends-on ("_package_StampedUint32"))
    (:file "_package_StampedUint32" :depends-on ("_package"))
    (:file "ParamGyro" :depends-on ("_package_ParamGyro"))
    (:file "_package_ParamGyro" :depends-on ("_package"))
    (:file "ParamMag" :depends-on ("_package_ParamMag"))
    (:file "_package_ParamMag" :depends-on ("_package"))
    (:file "StampedInt16" :depends-on ("_package_StampedInt16"))
    (:file "_package_StampedInt16" :depends-on ("_package"))
    (:file "StampedChar" :depends-on ("_package_StampedChar"))
    (:file "_package_StampedChar" :depends-on ("_package"))
    (:file "Mag" :depends-on ("_package_Mag"))
    (:file "_package_Mag" :depends-on ("_package"))
    (:file "StampedString" :depends-on ("_package_StampedString"))
    (:file "_package_StampedString" :depends-on ("_package"))
    (:file "StampedInt64" :depends-on ("_package_StampedInt64"))
    (:file "_package_StampedInt64" :depends-on ("_package"))
    (:file "Acc" :depends-on ("_package_Acc"))
    (:file "_package_Acc" :depends-on ("_package"))
    (:file "StampedInt32" :depends-on ("_package_StampedInt32"))
    (:file "_package_StampedInt32" :depends-on ("_package"))
    (:file "GPS" :depends-on ("_package_GPS"))
    (:file "_package_GPS" :depends-on ("_package"))
    (:file "StampedUint8" :depends-on ("_package_StampedUint8"))
    (:file "_package_StampedUint8" :depends-on ("_package"))
    (:file "StampedBool" :depends-on ("_package_StampedBool"))
    (:file "_package_StampedBool" :depends-on ("_package"))
    (:file "StampedUint64" :depends-on ("_package_StampedUint64"))
    (:file "_package_StampedUint64" :depends-on ("_package"))
    (:file "Gyro" :depends-on ("_package_Gyro"))
    (:file "_package_Gyro" :depends-on ("_package"))
    (:file "ParamAcc" :depends-on ("_package_ParamAcc"))
    (:file "_package_ParamAcc" :depends-on ("_package"))
    (:file "StampedInt8" :depends-on ("_package_StampedInt8"))
    (:file "_package_StampedInt8" :depends-on ("_package"))
    (:file "StampedFloat32" :depends-on ("_package_StampedFloat32"))
    (:file "_package_StampedFloat32" :depends-on ("_package"))
    (:file "StampedFloat64" :depends-on ("_package_StampedFloat64"))
    (:file "_package_StampedFloat64" :depends-on ("_package"))
  ))