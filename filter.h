#include <queue>
#include "jack_module.h"

class Filter {
public:
  Filter();
  ~Filter();

  jack_default_audio_sample_t allPass1(jack_default_audio_sample_t input);
  jack_default_audio_sample_t allPass2(jack_default_audio_sample_t input);
  jack_default_audio_sample_t allPass3(jack_default_audio_sample_t input);
  jack_default_audio_sample_t FBCF1(jack_default_audio_sample_t input);
  jack_default_audio_sample_t FBCF2(jack_default_audio_sample_t input);
  jack_default_audio_sample_t FBCF3(jack_default_audio_sample_t input);
  jack_default_audio_sample_t FBCF4(jack_default_audio_sample_t input);
  jack_default_audio_sample_t processChain(jack_default_audio_sample_t input);

private:
  jack_default_audio_sample_t yN;
  jack_default_audio_sample_t xN;
  jack_default_audio_sample_t outA;
  jack_default_audio_sample_t outB;
  jack_default_audio_sample_t outC;
  jack_default_audio_sample_t outD;
  jack_default_audio_sample_t allPassOut;
  jack_default_audio_sample_t FBCF1Out;
  jack_default_audio_sample_t FBCF2Out;
  jack_default_audio_sample_t FBCF3Out;
  jack_default_audio_sample_t FBCF4Out;

  std::queue<jack_default_audio_sample_t> inputBuffer1;
  std::queue<jack_default_audio_sample_t> inputBuffer2;
  std::queue<jack_default_audio_sample_t> inputBuffer3;
  std::queue<jack_default_audio_sample_t> allPass1Buffer;
  std::queue<jack_default_audio_sample_t> allPassOut1Buffer;
  std::queue<jack_default_audio_sample_t> allPass2Buffer;
  std::queue<jack_default_audio_sample_t> allPass2OutBuffer;
  std::queue<jack_default_audio_sample_t> allPass3Buffer;
  std::queue<jack_default_audio_sample_t> allPass3OutBuffer;

  std::queue<jack_default_audio_sample_t> FBCF1Buffer;
  std::queue<jack_default_audio_sample_t> FBCF2Buffer;
  std::queue<jack_default_audio_sample_t> FBCF3Buffer;
  std::queue<jack_default_audio_sample_t> FBCF4Buffer;
};
