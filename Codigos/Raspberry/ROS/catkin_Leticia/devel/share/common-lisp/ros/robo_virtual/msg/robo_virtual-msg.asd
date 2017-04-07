
(cl:in-package :asdf)

(defsystem "robo_virtual-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Posicao" :depends-on ("_package_Posicao"))
    (:file "_package_Posicao" :depends-on ("_package"))
  ))