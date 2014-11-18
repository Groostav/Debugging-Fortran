MODULE OptimizerInterface2
    USE ISO_C_BINDING
    USE ISO_FORTRAN_ENV

    IMPLICIT NONE
    
    ABSTRACT INTERFACE
        TYPE(C_PTR) FUNCTION evaluatorCallback(length, aDouble) &
            BIND(C, name='evaluatorCallback')
            USE, INTRINSIC :: ISO_C_BINDING
            INTEGER(C_INT), INTENT(IN), VALUE :: length
            REAL(C_DOUBLE), INTENT(IN), VALUE :: aDouble
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
    
        PRINT *, "Hello from Fortran! calling the callback:"
        callbackResult = convertedCallback(20, 3.05)
    
        
    END SUBROUTINE

END MODULE OptimizerInterface2
