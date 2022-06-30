const wordList solidRegionNames(rp["solid"]);

forAll(sigmaSolid, i){

	IFstream fileSigma(runTime.path()/runTime.constant()/solidRegionNames[i]/"sigma");
	
	graph sigmaGraph
	(
   		"sigmaDataFile",
    	"T",
    	"sigma",
    	fileSigma
	);

	sigmaSolid[i].field() = interpolateXY
    (
        thermos[i].T().field(),
        sigmaGraph.x(),
        sigmaGraph.y()
    );

    forAll(sigmaSolid[i].boundaryField(), patchi){
        sigmaSolid[i].boundaryField()[patchi] = interpolateXY
        (
            thermos[i].T().boundaryField()[patchi],
            sigmaGraph.x(),
    	    sigmaGraph.y()
        );
    }
}


