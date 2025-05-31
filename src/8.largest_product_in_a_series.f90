program largest_product_in_a_series

    use utils
    implicit none

    integer, parameter :: window_size = 13
    integer            :: i, j, d
    integer(iwp)       :: testprod, maxprod
    ! obviously we can't store a 1000-digit integer,
    ! so I'm going to do what's called a "pro gamer move"
    ! and store it as a string instead:
    character(1000)    :: bignumber = '&
        &73167176531330624919225119674426574742355349194934&
        &96983520312774506326239578318016984801869478851843&
        &85861560789112949495459501737958331952853208805511&
        &12540698747158523863050715693290963295227443043557&
        &66896648950445244523161731856403098711121722383113&
        &62229893423380308135336276614282806444486645238749&
        &30358907296290491560440772390713810515859307960866&
        &70172427121883998797908792274921901699720888093776&
        &65727333001053367881220235421809751254540594752243&
        &52584907711670556013604839586446706324415722155397&
        &53697817977846174064955149290862569321978468622482&
        &83972241375657056057490261407972968652414535100474&
        &82166370484403199890008895243450658541227588666881&
        &16427171479924442928230863465674813919123162824586&
        &17866458359124566529476545682848912883142607690042&
        &24219022671055626321111109370544217506941658960408&
        &07198403850962455444362981230987879927244284909188&
        &84580156166097919133875499200524063689912560717606&
        &05886116467109405077541002256983155200055935729725&
        &71636269561882670428252483600823257530420752963450&
        &'

    print *, '--------------------------------------'
    print *, 'Problem 8: Largest Product in a Series'
    print *, 'https://projecteuler.net/problem=8    '
    print *, '--------------------------------------'

    ! Now all we have to do is scan through "bignumber" with
    ! a window size of 13 characters and find the largest 
    ! product of the digits
    maxprod = 0
    do i=1,len(bignumber)-window_size+1
        ! read in 13 digits from bignumber and multiply them
        testprod = 1
        do j=i,i+window_size-1
            read(bignumber(j:j), *) d
            testprod = testprod * d
        end do
        ! check if this is larger than the largest previously
        ! found product
        if (testprod > maxprod) maxprod = testprod
    end do

    print *, 'Answer:', maxprod

end program largest_product_in_a_series