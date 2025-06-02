program lattice_paths

    use utils
    implicit none
    integer, parameter :: gridx = 20, gridy = 20
    integer            :: n, k

    print *, '-----------------------------------'
    print *, 'Problem 15: Lattice Paths          '
    print *, 'https://projecteuler.net/problem=15'
    print *, '-----------------------------------'

    ! the lattice paths can be counted by just using
    ! the binomial coefficient, AKA the "choose" function,
    ! where "n choose k" = n! / k!(n-k)!

    ! In this case, n is the total length of any path from
    ! the top-left to the bottom-right of the grid:
    n = gridx + gridy
    ! And since we only have 2 options to move at any grid
    ! point, once we have chosen all of the right movements,
    ! all of the down movements are fully constrained (and
    ! vice versa).  Therefore, since k represents the number
    ! of choices, we have:
    k = gridx

    ! So, the problem boils down to calculating 40 choose 20.
    ! There is a binomial coefficient function in the "utils"
    ! module.

    print *, 'Answer:', choose(n, k)

end program lattice_paths