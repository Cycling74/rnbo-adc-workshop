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
  // 1. Create the core object
  CoreObject rnboObject;

  // 2. Create some storage
  uint32_t sampleBufferSize = 0;
  float *sampleBuffer = nullptr;
  uint32_t sampleOffset = 0;
  float *outputBuffer = nullptr;

  // 3. Read in the input file
  SF_INFO inputInfo, outputInfo;
  inputInfo.format = 0;
  SNDFILE *sf = sf_open("anton.aif", SFM_READ, &inputInfo);

  // 4. Read the output file, using the saem info
  memcpy((void *) &outputInfo, (void *) &inputInfo, sizeof(SF_INFO));
  SNDFILE *sf_out = sf_open("anton-out.aif", SFM_WRITE, &outputInfo);

  // Might not be the best idea to read the whole sound file into memory, but
  // it's fine for a teaching example
  if (sf && sf_out) {

    // 5. Make space to store the file
    sampleBufferSize = sizeof(float) * inputInfo.frames * inputInfo.channels;
    sampleBuffer = (float *) malloc(sampleBufferSize);
    outputBuffer = (float *) malloc(blocksize * 2 * sizeof(float));

    std::cout << "--- Trying to read " << sampleBufferSize << " bytes" << "\n";
    int readSamples = sf_read_float(sf, (float *) sampleBuffer, sampleBufferSize);
    std::cout << "--- Success: Read " << readSamples << " samples" << "\n";

    sf_close(sf);
  } else {
    std::cout << "--- Failed" << "\n";
  }

  // Get ready to process stereo audio in blocksize-sample chunks
  if (sampleBuffer) {
    rnboObject.prepareToProcess(44100, blocksize);
    RNBO::SampleValue** inputs = new RNBO::SampleValue*[2];
    inputs[0] = new double[blocksize];
    inputs[1] = new double[blocksize];
    RNBO::SampleValue** outputs = new RNBO::SampleValue*[2];
    outputs[0] = new double[blocksize];
    outputs[1] = new double[blocksize];

    int blockcount = 0;

    // Do all of the audio processing
    for (uint32_t i = 0; i < sampleBufferSize / (sizeof(float)); i += (2 * blocksize)) {
      // Read into your input buffers, remembering that the input is interleaved
      for (uint32_t j = 0; j < blocksize; j++) {
        inputs[0][j] = sampleBuffer[i + 2 * j];
        inputs[1][j] = sampleBuffer[i + 2 * j + 1];
      }

      // Process the audio
      rnboObject.process(inputs, 2, outputs, 2, blocksize);

      // Write the output, again mind the interleaving
      for (uint32_t j = 0; j < blocksize; j++) {
        outputBuffer[j * 2] = outputs[0][j];
        outputBuffer[j * 2 + 1] = outputs[1][j];
      }

      // Ship that buffer to the output file
      sf_writef_float(sf_out, outputBuffer, blocksize);
    }

    delete [] inputs[0];
    delete [] inputs[1];
    delete [] inputs;
    delete [] outputs[0];
    delete [] outputs[1];
    delete [] outputs;
    free(sampleBuffer);
    free(outputBuffer);
    sf_close(sf);
    sf_close(sf_out);
  }

  return 0;
}