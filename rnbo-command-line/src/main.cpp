#include <iostream>
#include <memory>
#include <atomic>
#include <RNBO.h>

#include <unistd.h>
#include <fstream>
#include <sstream>
#include <sndfile.h>

using namespace RNBO;

const uint32_t blocksize = 64;

int main(int argc, const char * argv[]) {
  // ==> TODO: 1. Create the RNBO Core object.

  // 2. Make a couple of buffers.
  uint32_t sampleBufferSize = 0;
  double *sampleBuffer = nullptr;
  uint32_t sampleOffset = 0;
  double *outputBuffer = nullptr;

  // 3. Read in the input file.
  SF_INFO inputInfo, outputInfo;
  inputInfo.format = 0;
  SNDFILE *sf = sf_open("cherokee.aif", SFM_READ, &inputInfo);

  // 4. Use the same format to open the output for writing
  memcpy((void *) &outputInfo, (void *) &inputInfo, sizeof(SF_INFO));
  SNDFILE *sf_out = sf_open("cherokee-out.aif", SFM_WRITE, &outputInfo);

  // 5. Might not be the best idea to read the whole sound file into memory, but
  // it's fine for a teaching example
  // Make space to store the file
  if (sf && sf_out) {
    sampleBufferSize = sizeof(double) * inputInfo.frames * inputInfo.channels;
    sampleBuffer = (double *) malloc(sampleBufferSize);
    outputBuffer = (double *) malloc(blocksize * sizeof(double));

    std::cout << "--- Trying to read " << sampleBufferSize << " bytes" << "\n";
    int readSamples = sf_read_double(sf, (double *) sampleBuffer, sampleBufferSize);
    std::cout << "--- Success: Read " << readSamples << " samples" << "\n";

    sf_close(sf);
  } else {
    std::cout << "--- Failed" << "\n";
  }

  // 6. Get ready to process stereo audio in blocksize-sample chunks
  if (sampleBuffer) {

    // ==> TODO: 7. Get RNBO ready to process
    RNBO::SampleValue** inputs = new RNBO::SampleValue*[1];
    inputs[0] = new RNBO::SampleValue[blocksize];
    RNBO::SampleValue** outputs = new RNBO::SampleValue*[1];
    outputs[0] = new RNBO::SampleValue[blocksize];

    // 8. Do all of the audio processing
    for (uint32_t i = 0; i < sampleBufferSize / (sizeof(double)); i += (blocksize)) {

      // 9. Read into your input buffers, remembering that the input is interleaved
      for (uint32_t j = 0; j < blocksize; j++) {
        inputs[0][j] = sampleBuffer[i + j];
      }

      // ==> TODO: 10. Process the audio
      memcpy(outputs[0], inputs[0], blocksize * sizeof(double)); // fake processing

      // 11. Ship that buffer to the output file
      sf_writef_double(sf_out, outputs[0], blocksize);
    }

    // 12. Cleanup
    delete [] inputs[0];
    delete [] inputs;
    delete [] outputs[0];
    delete [] outputs;
    free(sampleBuffer);
    free(outputBuffer);
    sf_close(sf);
    sf_close(sf_out);
  }

  return 0;
}