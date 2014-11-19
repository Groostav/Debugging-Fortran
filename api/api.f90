module api
    use ISO_C_BINDING
    use ISO_FORTRAN_ENV

    implicit none
    
    abstract interface
        real(C_DOUBLE) function NumEvaluator(length, aDouble) &
            bind(C, name='NumEvaluator')
            use, intrinsic :: ISO_C_BINDING
            integer(C_INT), intent(in), value :: length
            real(C_DOUBLE), intent(in), value :: aDouble
        end function
    end interface

        
    abstract interface
        real(C_DOUBLE) function ArrayEvaluator(length, aDouble, doubleArray) &
            bind(C, name='ArrayEvaluator')
            use, intrinsic :: ISO_C_BINDING
            integer(C_INT), intent(in), value :: length
            real(C_DOUBLE), intent(in), value :: aDouble
            real(C_DOUBLE), intent(in), dimension(*) :: doubleArray
            !by default fortran seems to do by-reference
        end function
    end interface
    
    TYPE, BIND(C) :: SomeStruct
        INTEGER(C_INT) :: someInt
        REAL(C_DOUBLE) :: someDouble
    END TYPE
    
    contains
    
    subroutine pauseOptimization(meh) bind(C, name="pauseOptimization")
    !DEC$ ATTRIBUTES DLLEXPORT :: pauseOptimization
    logical(C_BOOL), intent(in) :: meh
        print *,"fortran: got boolean: ", meh
    end subroutine
    
    subroutine acceptCallback(callback) bind(C,name="acceptCallback")
    !DEC$ ATTRIBUTES DLLEXPORT :: acceptCallback
    type(C_FUNPTR), value :: callback
        real(C_DOUBLE) :: callbackResult
        
        procedure(NumEvaluator), POINTER :: convertedCallback    
        call C_F_PROCPOINTER (callback, convertedCallback)
    
        print *, "fortran: Hello from Fortran! calling the callback:"
        callbackResult = convertedCallback(20, 3.05)
        print *, "fortran: Fortran again: got the result ", callbackResult
            
    end subroutine
    
    subroutine acceptArrayCallback(callback, inStruct) bind(C,name="acceptArrayCallback")
    !DEC$ ATTRIBUTES DLLEXPORT :: acceptArrayCallback
        type(C_FUNPTR), value :: callback
        type(SomeStruct) :: inStruct
        real(C_DOUBLE) :: callbackResult
        
        real(C_DOUBLE), dimension (0:4) :: dArray
        procedure(ArrayEvaluator), POINTER :: convertedCallback    
    
        print *, "fortran: Hello from Fortran!"
        print *, "fortran: got inStruct%someInt: ", inStruct%someInt
        print *, "fortran: got inStruct%someDouble: ", inStruct%someDouble
        
        dArray(1) = 42.0
        
        call C_F_PROCPOINTER (callback, convertedCallback)
        print *, "fortran: calling the callback:"
        callbackResult = convertedCallback(20, 3.05, dArray);
        print *, "fortran: got the result ", callbackResult, " from the callback"
            
    end subroutine


end module api
