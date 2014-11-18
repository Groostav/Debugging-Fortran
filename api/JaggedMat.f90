module JaggedMat
implicit none

   type :: Row 
      integer :: d
      real*8, dimension(:), allocatable :: vector
   end type Row

   !type(Row),dimension(:),allocatable :: mymatrix

end module JaggedMat
