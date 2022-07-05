# _jouleHeatingMultiRegion\*Foam_
Multi-region conjugated heat transfer solver with time-independent Joule heating consideration in solid regions and temperature dependent electrical conductance, for OpenFOAM v2.3.1.
 
**Both PIMPLE(_jouleHeatingMultiRegionFoam_) and SIMPLE(_jouleHeatingMultiRegionSimpleFoam_) version exists.**

## Changes from _chtMultiRegion\*Foam_
### solid/interpolateProperties.H
Implements temperature dependent electrical conductance $\sigma$ with built-in interpolation library, interpolateXY.
### solid/VEqn.H
Defines and solves continuity equation below to get electric potential distribution.

$\large \qquad \qquad \qquad \qquad \qquad \quad \begin{align*} \nabla\cdot \left( \sigma\nabla V \right) = 0 \end{align*} \longrightarrow$ `fvm::laplacian(sigma,elpot) == 0`
### solid/solveSolid.H
Energy equation in solid regions consider Joule heating per unit volume,
$\mathbf{E} \cdot \mathbf{J} = -\nabla V \cdot \left(-\sigma \nabla V \right) = \sigma |\nabla V|^2$. This heat source term is added on the RHS of the energy equation.

$\large \qquad \qquad \qquad \qquad \qquad \begin{align*} \sigma |\nabla V|^2 \end{align*} \longrightarrow$
`sigma*((fvc::grad(elpot))&(fvc::grad(elpot)))`

## Usage
Electrical conductance $\sigma$, electric potential and electric current density $\mathbf{J}$ fields are added and named sigma, elpot, J respectively. So you'll need additional works for every solid region directory residing in following directories, in order to use the solver properly. 

 * **0 directory**  
  Initial / boundary condition for electric conductance and potential, sigma and elpot are required. 
  Electric conductance is calculated by interpolateXY, so **calculated condition should be assigned to sigma.**
 * **system directory**    
  `fvSolution`: requires `elpot`, `elpotFinal`  
  `fvSchemes`: requires laplacian scheme for `laplacian(sigma,elpot)`  
 * **constant directory**  
  A file named 'sigma' is required. The file matches absolute temperature in Kelvin and corresponding electrical conductance value in S/m, so that you can get interpolated profile of electrical conductance.  
  The file looks like this:  
   ```
   (  
   293.15 6666666.67  
   373.15 6410256.41  
   473.15 6172839.51  
   573.15 5917159.76  
   673.15 5714285.71  
   )
   ```
Please refer to example directory for an example case.

## References
[1] Read temperature dependent thermophysical properties from a file - boundaries false -- CFD Online Discussion Forums. (2012, June 26). CFD Online. Retrieved May 25, 2022, from https://www.cfd-online.com/Forums/openfoam-programming-development/103774-read-temperature-dependent-thermophysical-properties-file-boundaries-false.html  
[2] Järvstråt, N. (2009). Adding electric conduction and Joule heating to chtMultiRegionFoam. http://www.tfd.chalmers.se/~hani/kurser/OS_CFD_2009/NiklasJarvstrat/Project0126.pdf
