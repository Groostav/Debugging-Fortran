MODULE OptimizerInterface2
    USE JaggedMat
    USE ISO_C_BINDING
    USE ISO_FORTRAN_ENV

    IMPLICIT NONE

    CONTAINS
    
    SUBROUTINE pauseOptimization(meh) BIND(C, name="pauseOptimization")
    !DEC$ ATTRIBUTES DLLEXPORT :: pauseOptimization
    LOGICAL(C_BOOL),INTENT(IN) :: meh
    
    END SUBROUTINE

END MODULE OptimizerInterface2
