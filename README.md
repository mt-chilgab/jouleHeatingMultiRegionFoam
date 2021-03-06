# _jouleHeatingMultiRegion\*Foam_
Multi-region conjugated heat transfer solver with time-independent Joule heating consideration in solid regions and temperature dependent electrical conductance, for OpenFOAM v2.3.1.
 
**Both PIMPLE(_jouleHeatingMultiRegionFoam_) and SIMPLE(_jouleHeatingMultiRegionSimpleFoam_) version exists.**

## Changes from _chtMultiRegion\*Foam_
### solid/interpolateProperties.H
Implements temperature dependent electrical conductance $\sigma$ with built-in interpolation library, interpolateXY.
### solid/VEqn.H
Defines and solves continuity equation below to get electric potential distribution.

<p align="center">
$\large \nabla\cdot \left( \sigma\nabla V \right) = 0 \boldsymbol{\longrightarrow}$ <code>fvm::laplacian(sigma,elpot) == 0</code>
</p>

### solid/solveSolid.H
Energy equation in solid regions consider Joule heating per unit volume,
$\mathbf{E} \cdot \mathbf{J} = -\nabla V \cdot \left(-\sigma \nabla V \right) = \sigma |\nabla V|^2$. This heat source term is added on the RHS of the energy equation.

<p align="center">
$\large \sigma |\nabla V|^2 \boldsymbol{\longrightarrow}$ <code>sigma*((fvc::grad(elpot))&(fvc::grad(elpot)))</code>
</p>

## Compiling the Solver
First, you should check files named `file` located in `Make` directory, for which the compiled solver's location is described. After checking and modifying the location, type following and you`ll get the solver.  
   ```
   wclean
   wmake
   ```

## Usage
Electrical conductance, electric potential and electric current density fields are added and named sigma, elpot, J respectively. So you'll need additional works for every solid region directory residing in following directories, in order to use the solver properly. **Please refer to example directory for an example case.**

 * **0 directory**  
  Initial / boundary condition for electric conductance and potential, sigma and elpot are required. 
  Electric conductance is calculated by interpolateXY, so **calculated condition should be assigned to the field sigma.**
 * **system directory**    
  `fvSolution`: requires solvers, preconditioners, relative and absolute tolerance of `elpot`, `elpotFinal`  
  `fvSchemes`: requires laplacian scheme for `laplacian(sigma,elpot)`   
 * **constant directory**  
  A file named `sigma` is required. The file matches absolute temperature in Kelvin and corresponding electrical conductance value in S/m, so that you can get interpolated profile of electrical conductance.  
  If you are going to use decomposePar, **you should copy sigma to every processor directories.** This can be done using **copy_sigma.sh** script at case root directory. The script is provided in scripts directory.    
  `sigma` file looks like this:  
   ```
   (  
   293.15 6666666.67  
   373.15 6410256.41  
   473.15 6172839.51  
   573.15 5917159.76  
   673.15 5714285.71  
   )
   ```
## Testing with Example Case
For the given example case, meshing is already done so you'll just need to decompose domain with decomposePar and run the solver(_jouleHeatingMultiRegionSimpleFoam_) and reconstruct. Commands would be:
   ```
   $ decomposePar -allRegions
   $ jouleHeatingMultiRegionSimpleFoam
   $ reconstructPar -allRegions -latestTime
   ```
 
## References
[1] Read temperature dependent thermophysical properties from a file - boundaries false -- CFD Online Discussion Forums. (2012, June 26). CFD Online. Retrieved May 25, 2022, from https://www.cfd-online.com/Forums/openfoam-programming-development/103774-read-temperature-dependent-thermophysical-properties-file-boundaries-false.html  
[2] J??rvstr??t, N. (2009). Adding electric conduction and Joule heating to chtMultiRegionFoam. http://www.tfd.chalmers.se/~hani/kurser/OS_CFD_2009/NiklasJarvstrat/Project0126.pdf
