enum waveshapeS //for designating your waveshape in the BasicWave class
{
	SIN,
	TRIANGLE,
	SAW,
	SQUARE
};

struct BasicWaveInfo
{
	ADSR envelope;
	int waveshape;
	double frequency, relativeLoudness;
};


// signum function, for use in the square waveshape function
template <typename T>
int sgn(T x)
{
	if (x == 0)
		return 0;
	else if (x < 0)
		return -1;
	else if (x > 0)
		return 1;
}

//waveshape functions. Calculates what the sample is in a non-decaying waveform given the time of the sample and frequency of the wave
double sine(double time, double frequency)
{
	return sin(time * frequency * 2.f * M_PI);
}

double tri(double time, double frequency)
{
	return 4 * abs(frequency * time - floor(frequency * time + 0.5)) - 1;
}

double square(double time, double frequency)
{
	return sgn(sin(2 * M_PI * frequency * time));
}

double saw(double time, double frequency)
{
	return -2 * (frequency * time - floor(0.5 + frequency * time));
}

class BasicWave
{
private:
	ADSR m_envelope;
	int m_waveshape;
	double m_frequency, m_relativeLoudness; // relative loudness is under the assumption that the fundamental/base wave will have a relative loudness of 1, 
											//so a relative loudness of 0.5 indicates half the loudness
	//add functionality for modulations, probably gonna need std::function

public:
	BasicWave(double hz, int waveshape, ADSR envelope = { 0,0,1,0,2}, double relativeLoudness = 1.0)
		: m_frequency(hz), m_waveshape(waveshape), m_relativeLoudness(relativeLoudness), m_envelope(envelope)
	{
	}

	void setWave(double hz, int waveshape, ADSR envelope = { 0,0,1,0,2 }, double relativeLoudness = 1.0)
	{
		m_frequency = hz;
		m_waveshape = waveshape;
		m_relativeLoudness = relativeLoudness;
		m_envelope = envelope;
	}

	//setFrequency()
	//setwaveshape()
	//setADSR()
	//setLoudness()

	BasicWaveInfo getBasicWaveInfo()
	{
		return { m_envelope, m_waveshape, m_frequency, m_relativeLoudness };
	}

	double getSample(double time) //gets the value of a sample at a given time
	{
		double envelopeFactor = m_envelope.getEnvelopeFactor(time);

		switch (m_waveshape)
		{
		case SIN:
			return sine(time, m_frequency) * m_relativeLoudness * envelopeFactor;
		case TRIANGLE:
			return tri(time, m_frequency) * m_relativeLoudness * envelopeFactor;
		case SQUARE:
			return square(time, m_frequency) * m_relativeLoudness * envelopeFactor;
		case SAW:
			return saw(time, m_frequency) * m_relativeLoudness * envelopeFactor;
		}
	}

	double getLength()
	{
		return m_envelope.calculateTimeFromADSR();
	}
};

