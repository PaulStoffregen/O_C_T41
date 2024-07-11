#include <Audio.h>

// simple sine full scale output
// used to check output is approx 10Vp-p (slightly under is ok)
// and inputs receive it as nearly 100% (approx 95% is good)

AudioSynthWaveform       waveform1;
AudioOutputI2S2          audioOutput;
AudioInputI2S2           audioInput;
AudioAnalyzePeak         peak_L;
AudioAnalyzePeak         peak_R;
AudioConnection          patchCord1(waveform1, 0, audioOutput, 0);
AudioConnection          patchCord2(waveform1, 0, audioOutput, 1);
AudioConnection          patchCord3(audioInput, 0, peak_L, 0);
AudioConnection          patchCord4(audioInput, 1, peak_R, 0);

void setup() {
  AudioMemory(8);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(1.0);
}

void loop() {
  static elapsedMillis msec;

  if (msec > 200 && peak_L.available() && peak_R.available()) {
    msec = 0;
    float left = peak_L.read();
    float right = peak_R.read();
    Serial.printf("%4.1f  %4.1f\n", left * 100.0, right * 100.0);
  }
}
