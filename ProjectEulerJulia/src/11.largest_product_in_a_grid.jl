function euler11(window_size::Integer=4)

    # read in the grid from the data file
    grid = readdlm(joinpath(@__DIR__, "..", "data", "11.grid.dat"), ' ', Int, '\n')
    ni, nj = size(grid)

    # now we need to check rows, columns, and diagonals
    maxprod = 0

    # loop through every position
    for i ∈ 1:ni
        for j ∈ 1:nj
            # check the row, if in range:
            if j ≤ nj-window_size+1
                testprod = prod(@view grid[i,j:j+window_size-1])
                if testprod > maxprod 
                    maxprod = testprod
                end
            end
            # check the column, if in range:
            if i ≤ ni-window_size+1
                testprod = prod(@view grid[i:i+window_size-1,j])
                if testprod > maxprod
                    maxprod = testprod
                end
            end
            # check the diagonals, if in range:
            if (i ≤ ni-window_size+1) && (j ≤ nj-window_size+1)
                p1 = 1
                p2 = 1
                for wi ∈ 0:window_size-1
                    p1 = p1 * grid[i+wi,j+wi]
                    p2 = p2 * grid[i+window_size-1-wi,j+wi]
                end
                testprod = max(p1, p2)
                if testprod > maxprod
                    maxprod = testprod
                end
            end
        end
    end

    maxprod
end

if abspath(PROGRAM_FILE) == @__FILE__
    println("Problem 11: $(euler11())")
end