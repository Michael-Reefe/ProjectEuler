module utils
    implicit none

    ! make all entities private by default
    private                  
    ! explicitly declare public entities
    public iwp, rwp, minint32, maxint32
    public reallocate

    integer, parameter :: iwp = selected_int_kind(12)
    integer, parameter :: rwp = kind(0d0)
    integer, parameter :: minint32 = -2147483647, maxint32 = 2147483646

contains

    ! a little helper function that takes an allocated array and 
    ! reallocates it with a size n larger than it had before
    ! (n defaults to 1)
    subroutine reallocate(array, n)
        integer(iwp), intent(inout), allocatable :: array(:)
        integer(iwp), intent(in), optional       :: n
        integer(iwp), allocatable                :: tmp(:)

        ! make sure array is already allocated
        if (.not. allocated(array)) then 
            print *, 'ERROR: call to reallocate on unallocated array'
            stop
        end if
        ! first allocate tmp to the appropriate size
        if (present(n)) then 
            allocate(tmp(size(array)+n))
        else
            allocate(tmp(size(array)+1))
        end if
        ! then store a copy of array in tmp
        tmp(1:size(array)) = array(:)
        ! then we call move_alloc to move the allocation back into array
        call move_alloc(tmp, array)

    end subroutine reallocate


end module utils