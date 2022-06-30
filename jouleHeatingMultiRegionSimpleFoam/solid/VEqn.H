{

    #include "interpolateProperties.H"

    Info << "Min/max sigma:" << min(sigma) << " "
	 << max(sigma) << endl;

    for(int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
	fvScalarMatrix VEqn
	(
	     fvm::laplacian(sigma, elpot)
	);

	VEqn.relax();
	VEqn.solve();
    }

    J = -(sigma*(fvc::grad(elpot)));

    Info << "Min/max V:" << min(elpot) << " "
	 << max(elpot) << endl;

}


