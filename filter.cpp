#include "filter.h"
#include <iostream>

Filter::Filter() {
  for(int  i = 0; i < 347; i++){
    inputBuffer1.push(0);
    //allPassOut1Buffer.push(0);
  }
  for(int  i = 0; i < 347; i++){
    allPass1Buffer.push(0);
    //allPassOut1Buffer.push(0);
  }
  for(int  i = 0; i < 113; i++){
    inputBuffer2.push(0);
    //allPassOut1Buffer.push(0);
  }
  for(int  i = 0; i < 113; i++){
    allPass2Buffer.push(0);
    //allPassOut2Buffer.push(0);
  }
  for(int  i = 0; i < 37; i++){
    inputBuffer3.push(0);
    //allPassOut1Buffer.push(0);
  }
  for(int  i = 0; i < 37; i++){
    allPass3Buffer.push(0);
    //allPassOut2Buffer.push(0);
  }
  for(int  i = 0; i < 1687; i++){
    FBCF1Buffer.push(0);
  }
  for(int  i = 0; i < 1601; i++){
    FBCF2Buffer.push(0);
  }
  for(int  i = 0; i < 2053; i++){
    FBCF3Buffer.push(0);
  }
  for(int  i = 0; i < 2251; i++){
    FBCF4Buffer.push(0);
  }
}

Filter::~ Filter() {

}

jack_default_audio_sample_t Filter::allPass1(jack_default_audio_sample_t input) {
    float yN = 0.7 * (input + allPass1Buffer.front()) - inputBuffer1.front();
    //input = 0;
    allPass1Buffer.push(yN);

    //inputBuffer.pop();
    //std::cout << "SampleValue: " << yN << '\n';
    return yN;
}

jack_default_audio_sample_t Filter::allPass2(jack_default_audio_sample_t input) {
    float yN = 0.7 * (input + allPass2Buffer.front()) - inputBuffer2.front();
    //input = 0;
    allPass2Buffer.push(yN);

    //inputBuffer.pop();
    //std::cout << "SampleValue: " << yN << '\n';
    return yN;
}

jack_default_audio_sample_t Filter::allPass3(jack_default_audio_sample_t input) {
    //inputBuffer.push(input);
    float yN = 0.7 * (input + allPass3Buffer.front()) - inputBuffer3.front();
    //input = 0;
    allPass3Buffer.push(yN);

    //inputBuffer.pop();
    //std::cout << "SampleValue: " << yN << '\n';
    return yN;
}

jack_default_audio_sample_t Filter::FBCF1(jack_default_audio_sample_t input) {
  FBCF1Buffer.push(input * 0.773);

  return FBCF1Buffer.front();
}
jack_default_audio_sample_t Filter::FBCF2(jack_default_audio_sample_t input) {
  FBCF2Buffer.push(input * 0.802);

  return FBCF2Buffer.front();
}
jack_default_audio_sample_t Filter::FBCF3(jack_default_audio_sample_t input) {
  FBCF3Buffer.push(input * 0.753);

  return FBCF3Buffer.front();
}
jack_default_audio_sample_t Filter::FBCF4(jack_default_audio_sample_t input) {
  FBCF4Buffer.push(input * 0.733);

  return FBCF4Buffer.front();
}

 jack_default_audio_sample_t Filter::processChain(jack_default_audio_sample_t input) {
  allPassOut = allPass3(allPass2(allPass1(input)));
  FBCF1Out = FBCF1(allPassOut);
  FBCF2Out = FBCF2(allPassOut);
  FBCF3Out = FBCF3(allPassOut);
  FBCF4Out = FBCF4(allPassOut);

  allPass1Buffer.pop();
  allPass2Buffer.pop();
  allPass3Buffer.pop();
  FBCF1Buffer.pop();
  FBCF2Buffer.pop();
  FBCF3Buffer.pop();
  FBCF4Buffer.pop();

  outA = FBCF1Out + FBCF2Out + FBCF3Out + FBCF4Out;
  outB = -outA;
  outD = (FBCF1Out + FBCF3Out) - (FBCF2Out + FBCF4Out);
  outC = -outD;

  jack_default_audio_sample_t speakerOutput = outA / 4;
  std::cout << "SampleValue: " << speakerOutput << '\n';
  return speakerOutput;
}
