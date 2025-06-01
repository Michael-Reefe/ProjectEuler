# Activate the package
using Pkg
Pkg.activate(@__DIR__)

using PackageCompiler

# Create a sysimage
create_sysimage(["ProjectEulerJulia"]; sysimage_path="PEJ.so",
                precompile_execution_file="src/precompile.jl")

