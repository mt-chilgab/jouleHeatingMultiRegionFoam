# _jouleHeatingMultiRegion\*Foam_
Multi-region conjugated heat transfer solver with Joule heating consideration in solid regions and temperature dependent electrical conductance, for OpenFOAM v2.3.1.

**Both PIMPLE(_jouleHeatingMultiRegionFoam_) and SIMPLE(_jouleHeatingMultiRegionSimpleFoam_) version exists.**

## Changes from chtMultiRegion\*Foam
### solid/interpoalateProperties.H
Implements temperature dependent electrical conductance $\sigma$ with built-in interpolation library, interpolateXY.
### solid/VEqn.H
Defines and solves continuity equation below to get electric potential distribution.

$\large	\nabla\cdot \left( \sigma\nabla V \right) \longrightarrow$ `fvm::laplacian(sigma,elpot) == 0`

## References
[1] Read temperature dependent thermophysical properties from a file - boundaries false -- CFD Online Discussion Forums. (2012, June 26). CFD Online. Retrieved May 25, 2022, from https://www.cfd-online.com/Forums/openfoam-programming-development/103774-read-temperature-dependent-thermophysical-properties-file-boundaries-false.html  
[2] Järvstråt, N. (2009). Adding electric conduction and Joule heating to chtMultiRegionFoam. http://www.tfd.chalmers.se/~hani/kurser/OS_CFD_2009/NiklasJarvstrat/Project0126.pdf
