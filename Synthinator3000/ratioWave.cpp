struct RatioedWaveInfo
{
	double ratio, relativeLoudness;
	int waveshape;
	ADSR envelope;
};


class RatioWave : public CompoundWave
{
private:
	/*
	inheritied:
	std::vector<BasicWave*> m_harmonics;
	ADSR m_masterEnvelope;
	*/
	std::vector<RatioedWaveInfo> m_harmonicsInfo;

public:
	RatioWave(ADSR envelope = { 0,0,1,0,2 })
		: CompoundWave(envelope)
	{}

	void addPartial(double ratio, int waveshape, double relativeLoudness = 1.0, ADSR envelope = { 0,0,1,0,2 })
	{
		m_harmonicsInfo.push_back(RatioedWaveInfo{ratio, relativeLoudness, waveshape, envelope});
	}

	void setUpHarmonicsFromRatios(double fundamentalFrequency)
	{
		//make all the harmonics with thier ratio from their fundamental
		for (auto& element : m_harmonicsInfo)
		{
			m_harmonics.push_back(new BasicWave(element.ratio * fundamentalFrequency, element.waveshape, element.envelope, element.relativeLoudness));
		}
	}

	void save(double fundamentalFrequency, std::string filename = "no_name.wav")
	{

		setUpHarmonicsFromRatios(fundamentalFrequency);

		AudioFile<double> audio;
		audio.setNumChannels(numChannels);
		double length = getLength();

		double numSamplesPerChannel = floor(samplingRate * length);
		audio.setNumSamplesPerChannel(numSamplesPerChannel);



		for (int i{ 0 }; i < numSamplesPerChannel; i++)
		{
			double time = static_cast<double>(i) / samplingRate;
			double masterEnvelopeFactor = m_masterEnvelope.getEnvelopeFactor(time);

			for (int channel = 0; channel < audio.getNumChannels(); channel++)
			{
				audio.samples[channel][i] = getSample(time) * masterEnvelopeFactor;
			}
		}

		audio.save(filename, AudioFileFormat::Wave);
	}
};