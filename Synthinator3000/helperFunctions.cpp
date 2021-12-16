RatioWave explicitToRatioWave(ExplicitWave& explicitWave)
{
	double fundamentalHz{ explicitWave.getFundamentalFrequency() };
	
	RatioWave ratioWave(explicitWave.getMasterEnvelope());

	//add the fundamental as a wave component
	ratioWave.addPartial(1, explicitWave.getFundamentalwaveshape(), 1.0, explicitWave.getFundamentalEnvelope());

	//add all the partials
	for (int i{ 0 }; i < explicitWave.getNumberOfHarmonics(); i++)
	{
		BasicWaveInfo partialInfo = explicitWave.getPartialInfo(i);
		ratioWave.addPartial(partialInfo.frequency / fundamentalHz, partialInfo.waveshape, partialInfo.relativeLoudness, partialInfo.envelope);
	}

	return ratioWave;
}