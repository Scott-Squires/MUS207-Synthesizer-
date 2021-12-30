Thanks for checking this out! You are going to have to be pretty savvy to use this, but I'll give you what advice I can. Hopefully in the future I will add more functionality to this and make a front end so it's more useful and accessible. 

I've included the whole solution for Visual Studio 2019, so you may be able to drop that into your repositories folder and get started, otherwise you'll need to make your own build and make sure to disclude every file from the build except main and AudioFile.h

Refer to my class video for a brief overview on how the structure of things work.

Essentailly we've got two classes that you'll be using: RatioWave and ExplicitWave. ExplicitWave objects are waves that hold a fundamental and a bunch of partials. RatioWave objects hold ratios to a fundamental instead of specifc frequencies. Here's how the flow will go for both wave types.

{
ExplicitWave variable_name(fundamentalFrequency, fundamnetalWaveshape{given as either SIN, TRIANGLE, SAW, or SQUARE}, ADSR for the whole wave{attack, sustain, decay, release, and sustain length, in that order, each in seconds, formated like you are intializing a struct, because you are. This is optional}, and ADSR for the fundamental wave, same format)

then you'll use variable_name.addPartial(frequncy, waveshape, loudness<if a value of 1 is standard><optional>, ADSR<optional>)

until you've added all the partials you like

then variable_name.save("file_name.wav") - don't forget the .wav, and then if you run the program, it'll pop out that audio file in your project folder.
}

{
RatioWave variable_name(ADSR for the whole wave{attack, sustain, decay, release, and sustain length, in that order, each in seconds, formated like you are intializing a struct, because you are. This is optional})

then you'll use variable_name.addPartial(frequncy-ratio, waveshape, loudness<if a value of 1 is standard><optional>, ADSR<optional>)

until you've added all the partials you like

then variable_name.save(fundamentalFrequency {this is what all the ratios will be to}, "file_name.wav") - don't forget the .wav, and then if you run the program, it'll pop out that audio file in your project folder.
}

There is also a handy function called explicitToRatioWave(ExplicitWave), and you can give it an ExplicitWave and it will return a RatioWave.


Anyway, hopefully I give this project some more love in the future, but I hope you enjoy it if you decide to play around with it. 