MODULE OptimizerInterface2
    USE ISO_C_BINDING
    USE ISO_FORTRAN_ENV

    IMPLICIT NONE
    
    ABSTRACT INTERFACE
        TYPE(C_PTR) FUNCTION evaluatorCallback(length) &
            BIND(C, name='evaluatorCallback')
            USE, INTRINSIC :: ISO_C_BINDING
            INTEGER(C_INT), INTENT(IN), VALUE :: length
        END FUNCTION
    END INTERFACE

    CONTAINS
    
    SUBROUTINE pauseOptimization(meh) BIND(C, name="pauseOptimization")
    !DEC$ ATTRIBUTES DLLEXPORT :: pauseOptimization
    LOGICAL(C_BOOL),INTENT(IN) :: meh
        PRINT *,meh
    END SUBROUTINE
    
    SUBROUTINE acceptCallback(callback) BIND(C,name="acceptCallback")
    !DEC$ ATTRIBUTES DLLEXPORT :: acceptCallback
    TYPE(C_FUNPTR), VALUE :: callback
        TYPE(C_PTR) :: callbackResult
        
        PROCEDURE(evaluatorCallback), POINTER :: convertedCallback    
        CALL C_F_PROCPOINTER (callback, convertedCallback)
        
        callbackResult = convertedCallback(20)
        
        print *, "Hello from Fortran!"
        
    END SUBROUTINE

END MODULE OptimizerInterface2
