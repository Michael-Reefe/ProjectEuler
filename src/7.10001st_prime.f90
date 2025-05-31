program ten_thousand_first_prime

    use utils
    implicit none
    integer(iwp), parameter :: search_target=10001
    integer(iwp)            :: prime_numbers(search_target)
    integer(iwp)            :: n1, chunk_size

    print *, '----------------------------------'
    print *, 'Problem 7: 10,001st Prime Number  '
    print *, 'https://projecteuler.net/problem=7'
    print *, '----------------------------------'

    ! We need to find the 10,001st prime number.

    ! To do so, we can make use of the Sieve of Eratosthenes,
    ! which is a pretty efficient way to mark all of the prime
    ! numbers below some value n.

    ! Unfortunately, we don't know what n should be here, since
    ! we don't know how large the 10,001st prime is (that's the
    ! whole point of the problem). 

    ! So instead what we can do is iteratively call the Sieve
    ! of Eratosthenes on chunks of numbers and count up how many
    ! primes we find until we reach the 10,001st.

    ! "n1" holds the first number in the chunk of numbers to be
    ! searched
    n1 = 1
    chunk_size = search_target / 10
    ! We first do the initial iteration with the regular 
    ! Sieve of Eratosthenes:
    call sieve_of_eratosthenes(chunk_size, prime_numbers, search_target)
    ! From here, we do an infinite loop until prime_numbers has a
    ! length of 10,001
    do while (prime_numbers(search_target) == 0)
        n1 = n1 + chunk_size
        call segmented_sieve_step(n1, chunk_size, prime_numbers, search_target)
    end do

    ! Print the results
    print *, 'Answer:', prime_numbers(search_target)

contains

    ! Sieve of Eratosthenes: Generates all prime numbers less than n
    subroutine sieve_of_eratosthenes(n, primes, buffer_size)
        integer(iwp), intent(in)    :: n, buffer_size
        integer(iwp), intent(out)   :: primes(buffer_size)
        integer(iwp)                :: i, j, primelimit
        logical(1)                  :: primemask(n)

        ! initialize everything as prime at first (except 1)
        primemask = .true.
        primemask(1) = .false.

        ! this is a well known algorithm that works by marking all of the
        ! multiples of every number less than sqrt(n) as composite, thereby
        ! leaving the remaining numbers as the primes
        primelimit = int(sqrt(real(n, rwp)), iwp)
        do i=2,primelimit
            if (primemask(i)) then 
                do j=i**2,n,i
                    primemask(j) = .false.
                end do
            end if 
        end do

        ! now we fill in the list of primes using the mask
        primes = 0
        j=1
        do i=1,n
            if (primemask(i)) then 
                if (j > buffer_size) then
                    print *, 'WARNING: buffer_size not large enough in sieve_of_eratosthenes'
                    exit
                end if
                primes(j) = i
                j = j + 1
            end if
        end do

    end subroutine sieve_of_eratosthenes

    ! an iteration of the segmented sieve algorithm
    subroutine segmented_sieve_step(n, delta, primes, buffer_size)
        ! n is the first integer to check
        integer(iwp), intent(in)    :: n, delta, buffer_size
        ! primes holds the previously found primes 
        integer(iwp), intent(inout) :: primes(buffer_size)
        integer(iwp)                :: i, j, p, m, primelimit
        logical(1)                  :: primemask(delta)

        ! m is the last integer to check
        m = n + delta - 1
        ! initialize everything as prime at first like the regular sieve
        primemask = .true.
        primelimit = int(sqrt(real(m, rwp)), iwp)

        do i=1,size(primes)
            p = primes(i)
            if (p > primelimit) exit
            ! j enumerates the multiples of p within the range (n, m)
            do j=n-mod(n,p),m-mod(m,p),p
                if (j < n) cycle
                primemask(j-n+1) = .false.
            end do
        end do

        ! append the newly found prime numbers to the "primes" array
        j = maxloc(primes, 1) + 1
        do i=1,size(primemask)
            if (primemask(i)) then
                if (j > buffer_size) then 
                    print *, 'WARNING: buffer_size not large enough in segmented_sieve_step'
                    exit 
                end if
                primes(j) = i+n-1
                j = j+1
            end if
        end do

    end subroutine segmented_sieve_step

end program ten_thousand_first_prime