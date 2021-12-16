class ExplicitWave : public CompoundWave  //this class is basically compound wave, but holds its fundamental wave 
{									//information to be accessed by helper functions that can, say give the
private:							// first x harmonics of that fundamental, or other useful things.
	double m_fundamentalFrequency;
	ADSR m_fundamentalEnvelope;
	int m_fundamentalwaveshape;
	/*
	inheritied:
	std::vector<BasicWave*> m_harmonics;
	ADSR m_masterEnvelope;
	*/
public:
	ExplicitWave(double hz, int waveshape, ADSR masterEnvelope = {0,0,1,0,2}, ADSR fundamentalEnvelope = { 0,0,1,0,2})
		: m_fundamentalFrequency(hz), m_fundamentalwaveshape(waveshape), m_fundamentalEnvelope(fundamentalEnvelope)
	{
		m_harmonics.push_back(new BasicWave(m_fundamentalFrequency, m_fundamentalwaveshape, m_fundamentalEnvelope));
	}

	double getFundamentalFrequency()
	{
		return m_fundamentalFrequency;
	}

	int getFundamentalwaveshape()
	{
		return m_fundamentalwaveshape;
	}

	ADSR getFundamentalEnvelope()
	{
		return m_fundamentalEnvelope;
	}
};