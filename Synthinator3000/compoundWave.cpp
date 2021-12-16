#include <vector>

class CompoundWave   //a wave made from multiple basic waves, meant to be inherited by more sophisticated complex wave classes, ExplicitWave and RatioWave
{
protected:
	std::vector<BasicWave*> m_harmonics;
	ADSR m_masterEnvelope;

	double getSample(double time)
	{
		double total = 0;

		for (auto& i : m_harmonics)
		{
			total += i->getSample(time);
		}
		total *= m_masterEnvelope.getEnvelopeFactor(time);
		return total / double(m_harmonics.size());					// does this need to be quanitized? not really sure. current answer: yes
	}

public:
	CompoundWave(ADSR envelope = {0,0,1,0,2})
		: m_masterEnvelope(envelope)
	{}

	~CompoundWave()
	{
		for (auto& x : m_harmonics)
		{
			delete x;
		}
	}

	void addPartial(double hz, int waveshape, double relativeLoudness = 1.0, ADSR envelope = { 0,0,1,0,2})
	{
		m_harmonics.push_back(new BasicWave(hz, waveshape, envelope, relativeLoudness));
	}

	/**************************************************************/

	double getLength()
	{
		return m_masterEnvelope.calculateTimeFromADSR();
	}

	ADSR getMasterEnvelope()
	{
		return m_masterEnvelope;
	}

	int getNumberOfHarmonics()
	{
		return m_harmonics.size();
	}

	BasicWaveInfo getPartialInfo(int partial)
	{
		if (partial < getNumberOfHarmonics())
			return m_harmonics[partial]->getBasicWaveInfo();
		else
			return {};
	}

	/**************************************************************/

	void setMasterEnvelope(ADSR newEnvelope)
	{
		m_masterEnvelope = newEnvelope;
	}
	/**************************************************************/

	void save(std::string filename = "no_name.wav")
	{
		AudioFile<double> audio;
		audio.setNumChannels(numChannels);
		double length = getLength();

		double numSamplesPerChannel = floor(samplingRate * length);
		audio.setNumSamplesPerChannel(numSamplesPerChannel);

		

		for (int i{0}; i < numSamplesPerChannel; i++)
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