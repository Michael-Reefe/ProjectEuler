program largest_product_in_a_grid

    implicit none
    integer, parameter :: ni=20, nj=20, window_size=4
    integer            :: i, j, wi, p1, p2, testprod, maxprod
    integer            :: stat=1, grid(ni,nj)

    print *, '-------------------------------------'
    print *, 'Problem 11: Largest Product in a Grid'
    print *, 'https://projecteuler.net/problem=11  '
    print *, '-------------------------------------'

    ! read in the grid from the data file
    open(1, file='../data/11.grid.dat', status='old', &
         iostat=stat, action='read')
    ! make sure the file was read in without issue
    if (stat /= 0) then 
        print *, 'ERROR: Could not read ../data/11.grid.dat'
        stop 
    end if
    ! fill in the grid
    do i=1,ni
        read(1,*) grid(i,:) 
    end do

    ! now we need to check rows, columns, and diagonals
    maxprod = 0

    ! loop through every position
    do i=1,ni
        do j=1,nj
            ! check the row, if in range:
            if (j <= nj-window_size+1) then 
                testprod = product(grid(i,j:j+window_size-1))
                if (testprod > maxprod) maxprod = testprod
            end if
            ! check the column, if in range:
            if (i <= ni-window_size+1) then 
                testprod = product(grid(i:i+window_size-1,j))
                if (testprod > maxprod) maxprod = testprod
            end if
            ! check the diagonals, if in range:
            if (i <= ni-window_size+1 .and. j <= nj-window_size+1) then
                p1 = 1
                p2 = 1
                do wi=0,window_size-1
                    p1 = p1 * grid(i+wi,j+wi)
                    p2 = p2 * grid(i+window_size-1-wi,j+wi)
                end do
                testprod = max(p1, p2)
                if (testprod > maxprod) maxprod = testprod
            end if
        end do
    end do

    print *, 'Answer:', maxprod

end program largest_product_in_a_grid