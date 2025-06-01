program ten_thousand_first_prime

    use utils
    implicit none
    integer(iwp), parameter   :: search_target=10001
    integer(iwp), allocatable :: prime_numbers(:)
    integer(iwp)              :: n1, chunk_size

    print *, '----------------------------------'
    print *, 'Problem 7: 10,001st Prime Number  '
    print *, 'https://projecteuler.net/problem=7'
    print *, '----------------------------------'

    ! We need to find the 10,001st prime number.

    ! To do so, we can make use of the Sieve of Eratosthenes,
    ! which is a pretty efficient way to mark all of the prime
    ! numbers below some value n.
    ! (note: this function is contained in the utils module)

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
    call sieve_of_eratosthenes(chunk_size, prime_numbers)
    ! From here, we do an infinite loop until prime_numbers has a
    ! length of 10,001
    do while (size(prime_numbers) < search_target)
        n1 = n1 + chunk_size
        call segmented_sieve_step(n1, chunk_size, prime_numbers)
    end do

    ! Print the results
    print *, 'Answer:', prime_numbers(search_target)

contains


end program ten_thousand_first_prime