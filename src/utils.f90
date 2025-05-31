module utils
    implicit none

    ! make all entities private by default
    private                  
    ! explicitly declare public entities
    public iwp, rwp, minint32, maxint32
    public reallocate,& 
        primefactorize, &
        sieve_of_eratosthenes, &
        segmented_sieve_step

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


    ! compute the prime factorization of a number 
    subroutine primefactorize(number, output)

        integer(iwp), intent(in)               :: number            ! input number to factorize
        integer(iwp), intent(out), allocatable :: output(:,:)
        integer(iwp), allocatable              :: primefactors(:)
        integer(iwp), allocatable              :: exponents(:)
        integer(iwp)                           :: nreduced, candidate, primelimit
        ! output(:,1) gives the actual prime factors
        ! output(:,2) gives the exponents of each prime factor

        ! Edge cases 
        if (number < 2) then 
            allocate(output(0,2))
            return
        end if

        ! Set a running division product
        nreduced = number

        ! remove factors of 2 first
        if (mod(nreduced, 2) == 0) then
            allocate(primefactors(1))
            allocate(exponents(1))
            primefactors(1) = 2
            exponents(1) = 0
            do while (mod(nreduced, 2) == 0)
                nreduced = nreduced / 2
                exponents(1) = exponents(1) + 1
            end do
        end if

        ! We will find the prime factors by trial division, in other words
        ! just checking every number to see if it evenly divides the target.
        candidate  = 3_iwp
        primelimit = int(sqrt(real(number, rwp)), iwp)
        if (.not. allocated(primefactors)) allocate(primefactors(0))
        if (.not. allocated(exponents)) allocate(exponents(0))

        do 
            ! once nreduced reaches 1, we can stop the loop
            if (nreduced == 1) exit
            ! if candidate ever exceeds primelimit, then we know that
            ! the remaining "nreduced" must be a prime, so we can stop
            if (candidate > primelimit + 1) then
                call reallocate(primefactors)
                call reallocate(exponents)
                primefactors(size(primefactors)) = nreduced
                exponents(size(exponents))       = 1
                exit 
            end if
            ! see if candidate evenly divides number 
            if (mod(nreduced, candidate) == 0) then
                ! update the primefactors and exponents
                call reallocate(primefactors)
                call reallocate(exponents)
                primefactors(size(primefactors)) = candidate
                exponents(size(exponents))       = 0
                do while (mod(nreduced, candidate) == 0)
                    ! update the running division result
                    nreduced = nreduced / candidate
                    exponents(size(exponents)) = exponents(size(exponents)) + 1
                end do
                ! but don't increment candidate in case the number
                ! is multiply divisible by it; just skip to the next
                ! loop iteration
                primelimit = int(sqrt(real(nreduced, rwp)), iwp)
            end if
            ! update the candidate -
            ! we only need to check odd numbers since we already removed
            ! factors of 2
            candidate = candidate + 2
        end do

        ! concatenate the results into primefactorize
        allocate(output(size(primefactors),2))
        output(:,1) = primefactors(:)
        output(:,2) = exponents(:)

        deallocate(primefactors)
        deallocate(exponents)

    end subroutine primefactorize


    ! Sieve of Eratosthenes: Generates all prime numbers less than n
    subroutine sieve_of_eratosthenes(n, primes)
        integer(iwp), intent(in)                 :: n
        integer(iwp), intent(out), allocatable   :: primes(:)
        integer(iwp)                             :: i, j, primelimit, nprimes
        integer                                  :: primemask(n)

        ! initialize everything as prime at first (except 1)
        primemask = 1
        primemask(1) = 0

        ! this is a well known algorithm that works by marking all of the
        ! multiples of every number less than sqrt(n) as composite, thereby
        ! leaving the remaining numbers as the primes
        primelimit = int(sqrt(real(n, rwp)), iwp)
        do i=2,primelimit
            if (primemask(i) == 1) then 
                do j=i**2,n,i
                    primemask(j) = 0
                end do
            end if 
        end do

        ! now we can allocate an array to hold the prime numbers found so far
        nprimes = sum(primemask)
        allocate(primes(nprimes))
        j=1
        do i=1,n
            if (primemask(i) == 1) then 
                primes(j) = i
                j = j + 1
            end if
        end do

    end subroutine sieve_of_eratosthenes


    ! an iteration of the segmented sieve algorithm
    subroutine segmented_sieve_step(n, delta, primes)
        ! n is the first integer to check
        integer(iwp), intent(in)                 :: n, delta
        ! primes holds the previously found primes 
        integer(iwp), intent(inout), allocatable :: primes(:)
        integer(iwp)                             :: i, j, p, m, primelimit, newprimes
        integer                                  :: primemask(delta)

        ! m is the last integer to check
        m = n + delta - 1
        ! initialize everything as prime at first like the regular sieve
        primemask = 1
        primelimit = int(sqrt(real(m, rwp)), iwp)

        do i=1,size(primes)
            p = primes(i)
            if (p > primelimit) exit
            ! j enumerates the multiples of p within the range (n, m)
            do j=n-mod(n,p),m-mod(m,p),p
                if (j < n) cycle
                primemask(j-n+1) = 0
            end do
        end do

        ! append the newly found prime numbers to the "primes" array
        j = size(primes) + 1
        newprimes = sum(primemask)
        call reallocate(primes, newprimes)
        do i=1,size(primemask)
            if (primemask(i) == 1) then
                primes(j) = i+n-1
                j = j+1
            end if
        end do

    end subroutine segmented_sieve_step

end module utils