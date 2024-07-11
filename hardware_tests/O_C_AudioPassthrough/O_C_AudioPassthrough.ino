#include <Audio.h>

AudioInputI2S2       i2s1;
AudioOutputI2S2      i2s2;
AudioAnalyzePeak     peak_L;
AudioAnalyzePeak     peak_R;
AudioConnection      patchCord1(i2s1, 0, i2s2, 0);
AudioConnection      patchCord2(i2s1, 1, i2s2, 1);
AudioConnection      patchCord3(i2s1, 0, peak_L, 0);
AudioConnection      patchCord4(i2s1, 1, peak_R, 0);

void setup() {
  AudioMemory(12);
}

void loop() {
  static elapsedMillis msec;
  uint8_t cnt;

  if (msec > 24) {
    msec = 0;
    uint8_t leftPeak=peak_L.read() * 30.0;
    uint8_t rightPeak=peak_R.read() * 30.0;
    for(cnt=0;cnt<30-leftPeak;cnt++) {
      Serial.print(" ");
    }
    while(cnt++<30) {
      Serial.print("<");
    }
    Serial.print("||");
    for(cnt=0;cnt<rightPeak;cnt++) {
      Serial.print(">");
    }
    while(cnt++<30) {
      Serial.print(" ");
    }
    Serial.println();
  }
}


