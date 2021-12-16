Thanks for checking this out! You are going to have to be pretty savvy to use this, but I'll give you what advice I can. Hopefully in the future I will add more functionality to this and make a front end so it's more useful and accessible. 

Firstly, unless you are extremely cool, I don't think you'll be able to get this running without visual studio 2019.

Now that you've either given up or downloaded visual studio, try dragging the entire project, solution and all, into your "repos" folder. Now that we are getting started here, I'd like to say that I am by no means a professional nor is this advice well tested, so if some of these steps don't work, I'm leaving it to your will and ingenuity. So hopefully dragging it into your repos folder worked, but if it didn't, here's what you need to do:

First, make a project in visual studio, and make a file with the same name as each of my files, and copy all the code from each one. Second, disclude every file except main and AudioFile.h from the build by right-clicking on it, selecting "properties", and selecting "yes" from "disclude from build?"

Run the program and hopefully nothing crashes.

Wow, sorry about this.

Well, now you are free to make some sounds. Refer to my class video for a brief overview on how the structure of things work.

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

I'm really sorry about all that. If you actually made this work, give me a call and a date and time to shake your hand.

There is also a handy function called explicitToRatioWave(ExplicitWave), and you can give it an ExplicitWave and it will return a RatioWave.

Anyway, hopefully I give this project some more love in the future, but if you manage to have fun trying a couple things, I'm really glad.