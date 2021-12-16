struct ADSR
{
	double attack, decay, sustain, release, sustainLength; //attack is the time it takes to reach peak volume after the key is pressed, measured in seconds
											//decay is the time it takes to reach the sustain volume after reaching peak volume, measured in seconds
											//sustain is the volume level that the note will stay at so long as the key stays pressed, measured considering max volume == 1
											//release is the time it takes to go from the sustain volume to zero after the key is released, measured in seconds
											//sustainLength is how long the key is pressed; how long the volume stays at the sustain volume

	double calculateTimeFromADSR()
	{
		return attack + decay + release + sustainLength;
	}

	double getEnvelopeFactor(double time) //calculates how loud the wave should be at a given time. Based on 1 being the highest volume
	{
		if (attack == 0 and decay == 0 and sustain == 1 and release == 0)
			return 1;
		else if (time <= attack) //attacking
			return time / attack;
		else if (time < attack + decay) //decaying
			return 1 - ((1 - sustain) / decay) * (time - attack);
		else if (time < attack + decay + sustainLength) //sustaining
			return sustain;
		else if (time < attack + decay + sustainLength + release) //releasing
			return sustain - sustain / release * (time - (attack + decay + sustainLength));
		else return 0;
	}
};
