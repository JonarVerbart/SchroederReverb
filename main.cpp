#include <iostream>
#include <queue>
#include "jack_module.h"
#include "filter.h"

int main(int argc,char **argv) {

  Filter filter;
  JackModule jack;
  //  jack.init(argv[0]);
  //  jack.end();
  //  float samplerate = jack.getSamplerate();
    jack.init(argv[0]);

  jack.onProcess = [&filter](jack_default_audio_sample_t *inBuf,
   jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

  for(unsigned int i = 0; i < nframes; i++) {
    // write input to delay
    //outBuf[i] = inBuf[i];
    outBuf[i] = filter.processChain(inBuf[i]) * 0.25;
    // read delayed output
    // update delay --> next sample
    //delaystack.tickBufs();
  }
  return 0;
};

jack.autoConnect();

bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
    }
  }
  return 0;

/*  while (true) {
    processChain();
  } */
}
