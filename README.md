# jouleHeatingMultiRegionFoam
Multi-region conjugated heat transfer solver with Joule heating consideration in solid regions and temperature dependent electrical conductance, for OpenFOAM v2.3.1

## solid/interpolateProperties.H
Implements temperature dependent electrical conductance with built-in interpolation library, interpolateXY

## solid/VEqn.H
Defines and solves continuity equation to get electric potential distribution 
