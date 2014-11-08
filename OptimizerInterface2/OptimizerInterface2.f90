MODULE OptimizerInterface2
    USE ISO_C_BINDING
    USE ISO_FORTRAN_ENV

    IMPLICIT NONE
    
    ABSTRACT INTERFACE
        TYPE(C_PTR) FUNCTION evaluatorCallback(inputVector, length)&
            BIND(C, name='evaluatorCallback')
            USE, INTRINSIC :: ISO_C_BINDING
            TYPE(C_PTR), INTENT(IN), VALUE :: inputVector
            INTEGER(C_INT), INTENT(IN), VALUE :: length
        END FUNCTION
    END INTERFACE

    CONTAINS
    
    SUBROUTINE pauseOptimization(meh) BIND(C, name="pauseOptimization")
    !DEC$ ATTRIBUTES DLLEXPORT :: pauseOptimization
    LOGICAL(C_BOOL),INTENT(IN) :: meh
        PRINT *,meh
    END SUBROUTINE
    
    SUBROUTINE acceptCallback(boolean, callback) BIND(C,name="acceptCallback")
    !DEC$ ATTRIBUTES DLLEXPORT :: acceptCallback
    LOGICAL(C_BOOL),INTENT(IN) :: boolean
    PROCEDURE(evaluatorCallback), POINTER :: callback
        CALL callback
        PRINT *,boolean
    END SUBROUTINE

END MODULE OptimizerInterface2
