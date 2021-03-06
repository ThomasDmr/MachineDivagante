#pragma once

#include <Audio.h>
#include <synth_simple_drum.h>

#ifdef AUDIO_ENABLED
namespace AudioController
{
    // variable chorus
    const int   CHORUS_DELAY_LENGTH = 16 * AUDIO_BLOCK_SAMPLES;
    short       l_delayline[CHORUS_DELAY_LENGTH];

    // number of "voices" in the chorus which INCLUDES the original voice
    int n_chorus = 6;

    AudioSynthKarplusStrong string1;
    AudioSynthKarplusStrong string2;
    AudioSynthKarplusStrong string3;
    AudioSynthKarplusStrong string4;
    AudioSynthKarplusStrong string5;
    AudioSynthKarplusStrong string6;

    AudioSynthSimpleDrum drum1;
    AudioSynthToneSweep myEffect;

    AudioSynthWaveformSine sine1;
    AudioSynthWaveformSine sine2;
    AudioSynthWaveformSine sine3;
    AudioSynthWaveformSine sine4;
    AudioSynthWaveformSine sine5;
    AudioSynthWaveformSine sine6;

    AudioEffectChorus l_myEffect;

    AudioMixer4 mix1; //  4-channel mixers
    AudioMixer4 mix2; //
    AudioMixer4 mix3; //
    AudioMixer4 mix4; //
    AudioMixer4 mix5; //

    AudioOutputAnalogStereo dacs1;

    AudioConnection patchCord28(drum1, 0, l_myEffect, 0);

    AudioConnection patchCord1(string1, 0, mix1, 0);
    AudioConnection patchCord2(string2, 0, mix1, 1);
    AudioConnection patchCord3(string3, 0, mix1, 2);
    AudioConnection patchCord4(string4, 0, mix1, 3);
    AudioConnection patchCord5(mix1, 0, mix2, 0); // output of mix1 into 1st input on mix2
    AudioConnection patchCord6(string5, 0, mix2, 1);
    AudioConnection patchCord7(string6, 0, mix2, 2);
    AudioConnection patchCord8(l_myEffect, 0, mix2, 3);
    AudioConnection patchCord9(mix2, 0, mix3, 0); // output of mix2 into 1st input on mix3
    AudioConnection patchCord10(myEffect, 0, mix3, 1);
    AudioConnection patchCord11(sine1, 0, mix3, 2);
    AudioConnection patchCord12(sine2, 0, mix3, 3);
    AudioConnection patchCord13(mix3, 0, mix4, 0); // output of mix3 into 1st input on mix4
    AudioConnection patchCord14(sine3, 0, mix4, 1);
    AudioConnection patchCord15(sine4, 0, mix4, 2);
    AudioConnection patchCord16(sine5, 0, mix4, 3);
    AudioConnection patchCord17(mix4, 0, mix5, 0); // output of mix4 into 1st input on mix5
    AudioConnection patchCord18(sine6, 0, mix5, 1);

    AudioConnection patchCord19(mix5, 0, dacs1, 0); // patch on OUTPUT DAC0
    AudioConnection patchCord20(mix5, 0, dacs1, 1); // patch on OUTPUT DAC0

    ///////////////////////////// SETUP AUDIO ////////////////////////////////////
    void initAudioControllers()
    {
        // Audio connections require memory to work.  For more
        // detailed information, see the MemoryAndCpuUsage example
        AudioMemory(10);

        drum1.frequency(60);
        drum1.length(1500);
        drum1.secondMix(0.0);
        drum1.pitchMod(1.0);

        // reduce the gain on mixer channels, so more than 1
        // sound can play simultaneously without clipping
        mix1.gain(0, 0.8);
        mix1.gain(1, 0.8);
        mix1.gain(2, 0.8);
        mix1.gain(3, 0.8);

        mix2.gain(0, 0.8);
        mix2.gain(1, 0.8);
        mix2.gain(2, 0.8);
        mix2.gain(3, 0.8);

        mix3.gain(0, 0.8);
        mix3.gain(1, 0.8);
        mix3.gain(2, 0.05);
        mix3.gain(3, 0.05);

        mix4.gain(0, 0.8);
        mix4.gain(1, 0.05);
        mix4.gain(2, 0.05);
        mix4.gain(3, 0.05);

        mix5.gain(0, 0.8);
        mix5.gain(1, 0.05);
        mix5.gain(2, 0.8);
        mix5.gain(3, 0.8);

        l_myEffect.begin(l_delayline, CHORUS_DELAY_LENGTH, n_chorus);
    }

    
    // trigger a sound
    void triggerSound(int myFreq, int myLengthSound)
    {
        drum1.noteOn();
        drum1.frequency(myFreq);
        drum1.length(myLengthSound);
    }
}// namespace AudioController

#endif //AUDIO_ENABLED
