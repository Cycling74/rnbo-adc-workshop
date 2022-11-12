/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2022 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing@cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.

Please see https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ for additional information
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define floor(x) ((long)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_08 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_05 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_08;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_05()
            {
            }
            
            ~RNBOSubpatcher_05()
            {
            }
            
            virtual RNBOSubpatcher_08* getPatcher() const {
                return static_cast<RNBOSubpatcher_08 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number safesqrt(number num) {
                return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
            }
            
            Index vectorsize() {
                return this->vs;
            }
            
            ParameterIndex getParameterIndexForID(ConstCharPointer paramid) const {
                RNBO_UNUSED(paramid);
                return INVALID_INDEX;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                SampleValue ** inputs,
                Index numInputs,
                SampleValue ** outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
            
                this->filtercoeff_01_perform(
                    in2,
                    this->filtercoeff_01_gain,
                    in3,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    n
                );
            
                this->biquad_tilde_01_perform(
                    in1,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 5; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->filtercoeff_01_dspsetup(forceDSPSetup);
                this->biquad_tilde_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    this->setProbingIndex(-1);
                    break;
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    return 0;
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    return "bogus";
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    return "bogus";
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    return value;
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    return value;
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    return value;
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    return nullptr;
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 3;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void filtercoeff_01_perform(
                const Sample * frequency,
                number gain,
                const Sample * q,
                Sample * a0,
                Sample * a1,
                Sample * a2,
                Sample * b1,
                Sample * b2,
                Index n
            ) {
                RNBO_UNUSED(gain);
                auto __filtercoeff_01_activeResamp = this->filtercoeff_01_activeResamp;
                auto __filtercoeff_01_resamp_counter = this->filtercoeff_01_resamp_counter;
                auto __filtercoeff_01_K_EPSILON = this->filtercoeff_01_K_EPSILON;
            
                for (Index i = 0; i < n; i++) {
                    number local_q = q[(Index)i];
                    number local_gain = 1;
            
                    if (local_gain < 0)
                        local_gain = 0;
            
                    number local_frequency = frequency[(Index)i];
            
                    if (local_q < __filtercoeff_01_K_EPSILON)
                        local_q = __filtercoeff_01_K_EPSILON;
            
                    local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                    __filtercoeff_01_resamp_counter--;
            
                    if (__filtercoeff_01_resamp_counter <= 0) {
                        __filtercoeff_01_resamp_counter = __filtercoeff_01_activeResamp;
                        this->filtercoeff_01_updateTerms(local_frequency, local_gain, local_q);
                    }
            
                    a0[(Index)i] = this->filtercoeff_01_la0;
                    a1[(Index)i] = this->filtercoeff_01_la1;
                    a2[(Index)i] = this->filtercoeff_01_la2;
                    b1[(Index)i] = this->filtercoeff_01_lb1;
                    b2[(Index)i] = this->filtercoeff_01_lb2;
                }
            
                this->filtercoeff_01_resamp_counter = __filtercoeff_01_resamp_counter;
            }
            
            void biquad_tilde_01_perform(
                const Sample * x,
                const Sample * a0,
                const Sample * a1,
                const Sample * a2,
                const Sample * b1,
                const Sample * b2,
                Sample * out1,
                Index n
            ) {
                auto __biquad_tilde_01_y2 = this->biquad_tilde_01_y2;
                auto __biquad_tilde_01_y1 = this->biquad_tilde_01_y1;
                auto __biquad_tilde_01_x2 = this->biquad_tilde_01_x2;
                auto __biquad_tilde_01_x1 = this->biquad_tilde_01_x1;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_01_x1 * a1[(Index)i] + __biquad_tilde_01_x2 * a2[(Index)i] - (__biquad_tilde_01_y1 * b1[(Index)i] + __biquad_tilde_01_y2 * b2[(Index)i]);
                    __biquad_tilde_01_x2 = __biquad_tilde_01_x1;
                    __biquad_tilde_01_x1 = x[(Index)i];
                    __biquad_tilde_01_y2 = __biquad_tilde_01_y1;
                    __biquad_tilde_01_y1 = tmp;
                    out1[(Index)i] = tmp;
                }
            
                this->biquad_tilde_01_x1 = __biquad_tilde_01_x1;
                this->biquad_tilde_01_x2 = __biquad_tilde_01_x2;
                this->biquad_tilde_01_y1 = __biquad_tilde_01_y1;
                this->biquad_tilde_01_y2 = __biquad_tilde_01_y2;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void biquad_tilde_01_reset() {
                this->biquad_tilde_01_x1 = 0;
                this->biquad_tilde_01_x2 = 0;
                this->biquad_tilde_01_y1 = 0;
                this->biquad_tilde_01_y2 = 0;
            }
            
            void biquad_tilde_01_dspsetup(bool force) {
                if ((bool)(this->biquad_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->biquad_tilde_01_reset();
                this->biquad_tilde_01_setupDone = true;
            }
            
            array<number, 5> filtercoeff_01_localop_next(number frequency, number q, number gain, number type) {
                number omega = frequency * this->filtercoeff_01_localop_twopi_over_sr;
                this->filtercoeff_01_localop_cs = rnbo_cos(omega);
                this->filtercoeff_01_localop_sn = rnbo_sin(omega);
                this->filtercoeff_01_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                this->filtercoeff_01_localop_one_over_q = (number)1 / q;
                this->filtercoeff_01_localop_alpha = this->filtercoeff_01_localop_sn * 0.5 * this->filtercoeff_01_localop_one_over_q;
            
                switch ((int)type) {
                case 5:
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
            
                    this->filtercoeff_01_localop_beta = this->safesqrt(
                        (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                    );
            
                    this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                    break;
                case 6:
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
            
                    this->filtercoeff_01_localop_beta = this->safesqrt(
                        (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                    );
            
                    this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                    break;
                case 4:
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
                    this->filtercoeff_01_localop_one_over_a = (this->filtercoeff_01_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_01_localop_A);
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a);
                    break;
                case 9:
                case 10:
                case 11:
                case 13:
                case 14:
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    break;
                default:
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                    break;
                }
            
                switch ((int)type) {
                case 0:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 1:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 2:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 7:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 3:
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0;
                    break;
                case 8:
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = 1.0;
                    break;
                case 4:
                    this->filtercoeff_01_localop_la0 = (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a) * this->filtercoeff_01_localop_b0;
                    break;
                case 5:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1 - (this->filtercoeff_01_localop_A + 1) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    break;
                case 6:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = 2. * (this->filtercoeff_01_localop_A - 1. - (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    break;
                case 9:
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 10:
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 11:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 13:
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 12:
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 *= this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 *= this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0g;
                    break;
                case 14:
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la2 = gain;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                case 15:
                    this->filtercoeff_01_localop_la0 = 1;
                    this->filtercoeff_01_localop_la1 = 0;
                    this->filtercoeff_01_localop_la2 = 0;
                    this->filtercoeff_01_localop_lb1 = 0;
                    this->filtercoeff_01_localop_lb2 = 0;
                default:
                    break;
                }
            
                return {
                    this->filtercoeff_01_localop_la0,
                    this->filtercoeff_01_localop_la1,
                    this->filtercoeff_01_localop_la2,
                    this->filtercoeff_01_localop_lb1,
                    this->filtercoeff_01_localop_lb2
                };
            }
            
            void filtercoeff_01_localop_dspsetup() {
                this->filtercoeff_01_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
            }
            
            void filtercoeff_01_localop_reset() {
                this->filtercoeff_01_localop_internal = true;
                this->filtercoeff_01_localop_twopi_over_sr = 0;
                this->filtercoeff_01_localop_cs = 0;
                this->filtercoeff_01_localop_sn = 0;
                this->filtercoeff_01_localop_one_over_gain = 0;
                this->filtercoeff_01_localop_one_over_q = 0;
                this->filtercoeff_01_localop_alpha = 0;
                this->filtercoeff_01_localop_beta = 0;
                this->filtercoeff_01_localop_b0 = 0;
                this->filtercoeff_01_localop_b0g = 0;
                this->filtercoeff_01_localop_A = 0;
                this->filtercoeff_01_localop_one_over_a = 0;
                this->filtercoeff_01_localop_la0 = 0;
                this->filtercoeff_01_localop_la1 = 0;
                this->filtercoeff_01_localop_la2 = 0;
                this->filtercoeff_01_localop_lb1 = 0;
                this->filtercoeff_01_localop_lb2 = 0;
            }
            
            void filtercoeff_01_updateTerms(number local_frequency, number local_gain, number local_q) {
                array<number, 5> tmp = this->filtercoeff_01_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_01_type);
                this->filtercoeff_01_la0 = tmp[0];
                this->filtercoeff_01_la1 = tmp[1];
                this->filtercoeff_01_la2 = tmp[2];
                this->filtercoeff_01_lb1 = tmp[3];
                this->filtercoeff_01_lb2 = tmp[4];
            }
            
            void filtercoeff_01_dspsetup(bool force) {
                if ((bool)(this->filtercoeff_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                {
                    this->filtercoeff_01_activeResamp = this->vectorsize();
                }
            
                this->filtercoeff_01_resamp_counter = 0;
                this->filtercoeff_01_setupDone = true;
                this->filtercoeff_01_localop_dspsetup();
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                biquad_tilde_01_x = 0;
                biquad_tilde_01_a0 = 0;
                biquad_tilde_01_a1 = 0;
                biquad_tilde_01_a2 = 0;
                biquad_tilde_01_b1 = 0;
                biquad_tilde_01_b2 = 0;
                filtercoeff_01_frequency = 1000;
                filtercoeff_01_gain = 1;
                filtercoeff_01_q = 1;
                filtercoeff_01_type = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                biquad_tilde_01_x1 = 0;
                biquad_tilde_01_x2 = 0;
                biquad_tilde_01_y1 = 0;
                biquad_tilde_01_y2 = 0;
                biquad_tilde_01_setupDone = false;
                filtercoeff_01_K_EPSILON = 1e-9;
                filtercoeff_01_localop_internal = true;
                filtercoeff_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number biquad_tilde_01_x;
                number biquad_tilde_01_a0;
                number biquad_tilde_01_a1;
                number biquad_tilde_01_a2;
                number biquad_tilde_01_b1;
                number biquad_tilde_01_b2;
                number filtercoeff_01_frequency;
                number filtercoeff_01_gain;
                number filtercoeff_01_q;
                Int filtercoeff_01_type;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[5];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number biquad_tilde_01_x1;
                number biquad_tilde_01_x2;
                number biquad_tilde_01_y1;
                number biquad_tilde_01_y2;
                bool biquad_tilde_01_setupDone;
                number filtercoeff_01_resamp_counter;
                number filtercoeff_01_activeResamp;
                number filtercoeff_01_K_EPSILON;
                number filtercoeff_01_la0;
                number filtercoeff_01_la1;
                number filtercoeff_01_la2;
                number filtercoeff_01_lb1;
                number filtercoeff_01_lb2;
                bool filtercoeff_01_localop_internal;
                number filtercoeff_01_localop_twopi_over_sr;
                number filtercoeff_01_localop_cs;
                number filtercoeff_01_localop_sn;
                number filtercoeff_01_localop_one_over_gain;
                number filtercoeff_01_localop_one_over_q;
                number filtercoeff_01_localop_alpha;
                number filtercoeff_01_localop_beta;
                number filtercoeff_01_localop_b0;
                number filtercoeff_01_localop_b0g;
                number filtercoeff_01_localop_A;
                number filtercoeff_01_localop_one_over_a;
                number filtercoeff_01_localop_la0;
                number filtercoeff_01_localop_la1;
                number filtercoeff_01_localop_la2;
                number filtercoeff_01_localop_lb1;
                number filtercoeff_01_localop_lb2;
                bool filtercoeff_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_06 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_08;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_06()
            {
            }
            
            ~RNBOSubpatcher_06()
            {
            }
            
            virtual RNBOSubpatcher_08* getPatcher() const {
                return static_cast<RNBOSubpatcher_08 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -1468824490, false);
            }
            
            ParameterIndex getParameterIndexForID(ConstCharPointer paramid) const {
                RNBO_UNUSED(paramid);
                return INVALID_INDEX;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                SampleValue ** inputs,
                Index numInputs,
                SampleValue ** outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
            
                this->adsr_01_perform(
                    this->adsr_01_attack,
                    this->adsr_01_decay,
                    this->adsr_01_sustain,
                    this->adsr_01_release,
                    in2,
                    this->signals[0],
                    n
                );
            
                this->dspexpr_03_perform(this->signals[0], this->signals[0], this->signals[1], n);
                this->dspexpr_02_perform(this->signals[1], this->dspexpr_02_in2, out2, n);
                this->dspexpr_01_perform(in1, this->signals[1], out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 2; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
                    this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->adsr_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    this->setProbingIndex(-1);
                    break;
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    return 0;
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    return "bogus";
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    return "bogus";
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    return value;
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    return value;
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    return value;
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -1468824490:
                    this->adsr_01_mute_bang();
                    break;
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    return nullptr;
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void adsr_01_mute_bang() {}
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 2;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void adsr_01_perform(
                number attack,
                number decay,
                number sustain,
                number release,
                const Sample * trigger_signal,
                Sample * out,
                Index n
            ) {
                RNBO_UNUSED(release);
                RNBO_UNUSED(sustain);
                RNBO_UNUSED(decay);
                RNBO_UNUSED(attack);
                auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
                auto __adsr_01_triggerValueBuf = this->adsr_01_triggerValueBuf;
                auto __adsr_01_time = this->adsr_01_time;
                auto __adsr_01_amplitude = this->adsr_01_amplitude;
                auto __adsr_01_outval = this->adsr_01_outval;
                auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
                auto __adsr_01_phase = this->adsr_01_phase;
                auto __adsr_01_legato = this->adsr_01_legato;
                auto __adsr_01_triggerBuf = this->adsr_01_triggerBuf;
                auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
                auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
                bool bangMute = false;
            
                for (Index i = 0; i < n; i++) {
                    number clampedattack = (5 > __adsr_01_mspersamp ? 5 : __adsr_01_mspersamp);
                    number clampeddecay = (0 > __adsr_01_mspersamp ? 0 : __adsr_01_mspersamp);
                    number clampedrelease = (50 > __adsr_01_mspersamp ? 50 : __adsr_01_mspersamp);
                    number currentTriggerVal = trigger_signal[(Index)i];
            
                    if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || __adsr_01_triggerBuf[(Index)i] == 1) {
                        if ((bool)(__adsr_01_legato)) {
                            if (__adsr_01_phase != 0) {
                                __adsr_01_startingpoint = __adsr_01_outval;
                            } else {
                                __adsr_01_startingpoint = 0;
                            }
                        } else {
                            __adsr_01_startingpoint = 0;
                        }
            
                        __adsr_01_amplitude = currentTriggerVal;
                        __adsr_01_phase = 1;
                        __adsr_01_time = 0.0;
                        bangMute = false;
                    } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                        if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                            __adsr_01_phase = 4;
                            __adsr_01_amplitude = __adsr_01_outval;
                            __adsr_01_time = 0.0;
                        }
                    }
            
                    __adsr_01_time += __adsr_01_mspersamp;
            
                    if (__adsr_01_phase == 0) {
                        __adsr_01_outval = 0;
                    } else if (__adsr_01_phase == 1) {
                        if (__adsr_01_time > clampedattack) {
                            __adsr_01_time -= clampedattack;
                            __adsr_01_phase = 2;
                            __adsr_01_outval = __adsr_01_amplitude;
                        } else {
                            __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                        }
                    } else if (__adsr_01_phase == 2) {
                        if (__adsr_01_time > clampeddecay) {
                            __adsr_01_time -= clampeddecay;
                            __adsr_01_phase = 3;
                            __adsr_01_outval = __adsr_01_amplitude * 1;
                        } else {
                            __adsr_01_outval = __adsr_01_amplitude * 1 + (__adsr_01_amplitude - __adsr_01_amplitude * 1) * (1. - __adsr_01_time / clampeddecay);
                        }
                    } else if (__adsr_01_phase == 3) {
                        __adsr_01_outval = __adsr_01_amplitude * 1;
                    } else if (__adsr_01_phase == 4) {
                        if (__adsr_01_time > clampedrelease) {
                            __adsr_01_time = 0;
                            __adsr_01_phase = 0;
                            __adsr_01_outval = 0;
                            __adsr_01_amplitude = 0;
                            bangMute = true;
                        } else {
                            __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                        }
                    }
            
                    out[(Index)i] = __adsr_01_outval;
                    __adsr_01_triggerBuf[(Index)i] = 0;
                    __adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
                    __adsr_01_lastTriggerVal = currentTriggerVal;
                }
            
                if ((bool)(bangMute)) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1468824490,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;
                }
            
                this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
                this->adsr_01_phase = __adsr_01_phase;
                this->adsr_01_startingpoint = __adsr_01_startingpoint;
                this->adsr_01_outval = __adsr_01_outval;
                this->adsr_01_amplitude = __adsr_01_amplitude;
                this->adsr_01_time = __adsr_01_time;
            }
            
            void dspexpr_03_perform(const Sample * in1, const Sample * in2, Sample * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_02_perform(const Sample * in1, number in2, Sample * out1, Index n) {
                RNBO_UNUSED(in2);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] > 0;//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_01_perform(const Sample * in1, const Sample * in2, Sample * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void adsr_01_dspsetup(bool force) {
                if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->adsr_01_mspersamp = (number)1000 / this->sr;
                this->adsr_01_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_01_in1 = 0;
                dspexpr_01_in2 = 0;
                dspexpr_02_in1 = 0;
                dspexpr_02_in2 = 0;
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0;
                adsr_01_trigger_number = 0;
                adsr_01_attack = 5;
                adsr_01_decay = 0;
                adsr_01_sustain = 1;
                adsr_01_release = 50;
                adsr_01_legato = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                adsr_01_phase = 3;
                adsr_01_mspersamp = 0;
                adsr_01_time = 0;
                adsr_01_lastTriggerVal = 0;
                adsr_01_amplitude = 0;
                adsr_01_outval = 0;
                adsr_01_startingpoint = 0;
                adsr_01_triggerBuf = nullptr;
                adsr_01_triggerValueBuf = nullptr;
                adsr_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_01_in1;
                number dspexpr_01_in2;
                number dspexpr_02_in1;
                number dspexpr_02_in2;
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number adsr_01_trigger_number;
                number adsr_01_attack;
                number adsr_01_decay;
                number adsr_01_sustain;
                number adsr_01_release;
                number adsr_01_legato;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[2];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                Int adsr_01_phase;
                number adsr_01_mspersamp;
                number adsr_01_time;
                number adsr_01_lastTriggerVal;
                number adsr_01_amplitude;
                number adsr_01_outval;
                number adsr_01_startingpoint;
                signal adsr_01_triggerBuf;
                signal adsr_01_triggerValueBuf;
                bool adsr_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_07 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_08;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_07()
            {
            }
            
            ~RNBOSubpatcher_07()
            {
            }
            
            virtual RNBOSubpatcher_08* getPatcher() const {
                return static_cast<RNBOSubpatcher_08 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            inline number cubicinterp(number a, number w, number x, number y, number z) {
                number a2 = a * a;
                number f0 = z - y - w + x;
                number f1 = w - x - f0;
                number f2 = y - w;
                number f3 = x;
                return f0 * a * a2 + f1 * a2 + f2 * a + f3;
            }
            
            inline number splineinterp(number a, number w, number x, number y, number z) {
                number a2 = a * a;
                number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
                number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
                number f2 = -0.5 * w + 0.5 * y;
                return f0 * a * a2 + f1 * a2 + f2 * a + x;
            }
            
            inline number cosT8(number r) {
                number t84 = 56.0;
                number t83 = 1680.0;
                number t82 = 20160.0;
                number t81 = 2.4801587302e-05;
                number t73 = 42.0;
                number t72 = 840.0;
                number t71 = 1.9841269841e-04;
            
                if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
                    number rr = r * r;
                    return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
                } else if (r > 0.0) {
                    r -= 1.57079632679489661923132169163975144;
                    number rr = r * r;
                    return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
                } else {
                    r += 1.57079632679489661923132169163975144;
                    number rr = r * r;
                    return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
                }
            }
            
            inline number cosineinterp(number frac, number x, number y) {
                number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
                return x * (1.0 - a2) + y * a2;
            }
            
            number mstosamps(MillisecondTime ms) {
                return ms * this->sr * 0.001;
            }
            
            number samplerate() {
                return this->sr;
            }
            
            Index vectorsize() {
                return this->vs;
            }
            
            number maximum(number x, number y) {
                return (x < y ? y : x);
            }
            
            ParameterIndex getParameterIndexForID(ConstCharPointer paramid) const {
                if (!stringCompare(paramid, "left_delay")) {
                    return 0;
                }
            
                if (!stringCompare(paramid, "fb")) {
                    return 1;
                }
            
                if (!stringCompare(paramid, "right_delay")) {
                    return 2;
                }
            
                return INVALID_INDEX;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                SampleValue ** inputs,
                Index numInputs,
                SampleValue ** outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->dspexpr_05_perform(in1, this->dspexpr_05_in2, this->signals[0], n);
                this->dspexpr_07_perform(in1, this->dspexpr_07_in2, this->signals[1], n);
                this->feedbackreader_01_perform(this->signals[2], n);
                this->delaytilde_01_perform(this->delaytilde_01_delay, this->signals[2], this->signals[3], n);
                this->dspexpr_04_perform(this->signals[3], this->dspexpr_04_in2, this->signals[4], n);
                this->signaladder_03_perform(this->signals[0], this->signals[4], this->signals[4], n);
                this->feedbackwriter_01_perform(this->signals[4], n);
                this->signalforwarder_01_perform(this->signals[2], out1, n);
                this->feedbackreader_02_perform(this->signals[2], n);
                this->delaytilde_02_perform(this->delaytilde_02_delay, this->signals[2], this->signals[0], n);
                this->dspexpr_06_perform(this->signals[0], this->dspexpr_06_in2, this->signals[3], n);
                this->signaladder_04_perform(this->signals[3], this->signals[1], this->signals[1], n);
                this->feedbackwriter_02_perform(this->signals[1], n);
                this->signalforwarder_02_perform(this->signals[2], out2, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 5; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
                    this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->delaytilde_01_dspsetup(forceDSPSetup);
                this->delaytilde_02_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    this->setProbingIndex(-1);
                    break;
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_01_getPresetValue(getSubState(preset, "left_delay"));
                this->param_02_getPresetValue(getSubState(preset, "fb"));
                this->param_03_getPresetValue(getSubState(preset, "right_delay"));
            }
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    this->param_01_value_set(v);
                    break;
                case 1:
                    this->param_02_value_set(v);
                    break;
                case 2:
                    this->param_03_value_set(v);
                    break;
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    return this->param_01_value;
                case 1:
                    return this->param_02_value;
                case 2:
                    return this->param_03_value;
                default:
                    return 0;
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 3;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    return "left_delay";
                case 1:
                    return "fb";
                case 2:
                    return "right_delay";
                default:
                    return "bogus";
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    return "poly/delay/left_delay";
                case 1:
                    return "poly/delay/fb";
                case 2:
                    return "poly/delay/right_delay";
                default:
                    return "bogus";
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        info->type = ParameterTypeNumber;
                        info->initialValue = 300;
                        info->min = 10;
                        info->max = 10000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                    case 1:
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0.25;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                    case 2:
                        info->type = ParameterTypeNumber;
                        info->initialValue = 400;
                        info->min = 10;
                        info->max = 10000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 1:
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
                        return normalizedValue;
                    }
                case 0:
                case 2:
                    {
                        value = (value < 10 ? 10 : (value > 10000 ? 10000 : value));
                        ParameterValue normalizedValue = (value - 10) / (10000 - 10);
                        return normalizedValue;
                    }
                default:
                    return value;
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 1:
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            return 0 + value * (1 - 0);
                        }
                    }
                case 0:
                case 2:
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            return 10 + value * (10000 - 10);
                        }
                    }
                default:
                    return value;
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    return this->param_01_value_constrain(value);
                case 1:
                    return this->param_02_value_constrain(value);
                case 2:
                    return this->param_03_value_constrain(value);
                default:
                    return value;
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                case 1:
                    return addressOf(this->delaytilde_01_del_bufferobj);
                    break;
                case 2:
                    return addressOf(this->delaytilde_02_del_bufferobj);
                    break;
                default:
                    return nullptr;
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 2;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void zeroDataRef(DataRef& ref) {
                ref->setZero();
            }
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 1) {
                    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
                }
            
                if (index == 2) {
                    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
                }
            }
            
            void initialize() {
                this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr);
                this->delaytilde_02_del_bufferobj = initDataRef("delaytilde_02_del_bufferobj", true, nullptr);
                this->assign_defaults();
                this->setState();
                this->delaytilde_01_del_bufferobj->setIndex(1);
                this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
                this->delaytilde_02_del_bufferobj->setIndex(2);
                this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
            }
            
            protected:
            
            void param_01_value_set(number v) {
                v = this->param_01_value_constrain(v);
                this->param_01_value = v;
                this->sendParameter(0, false);
            
                if (this->param_01_value != this->param_01_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_01_lastValue = this->param_01_value;
                }
            
                this->mstosamps_01_ms_set(v);
            }
            
            void param_02_value_set(number v) {
                v = this->param_02_value_constrain(v);
                this->param_02_value = v;
                this->sendParameter(1, false);
            
                if (this->param_02_value != this->param_02_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_02_lastValue = this->param_02_value;
                }
            
                this->dspexpr_06_in2_set(v);
                this->dspexpr_04_in2_set(v);
            }
            
            void param_03_value_set(number v) {
                v = this->param_03_value_constrain(v);
                this->param_03_value = v;
                this->sendParameter(2, false);
            
                if (this->param_03_value != this->param_03_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_03_lastValue = this->param_03_value;
                }
            
                this->mstosamps_02_ms_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {
                this->delaytilde_01_del_init();
                this->delaytilde_02_del_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            }
            
            void allocateDataRefs() {
                this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();
            
                if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
                    if (this->delaytilde_01_del_bufferobj->wantsFill())
                        this->zeroDataRef(this->delaytilde_01_del_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(1);
                }
            
                this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();
            
                if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
                    if (this->delaytilde_02_del_bufferobj->wantsFill())
                        this->zeroDataRef(this->delaytilde_02_del_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(2);
                }
            }
            
            static number param_01_value_constrain(number v) {
                v = (v > 10000 ? 10000 : (v < 10 ? 10 : v));
                return v;
            }
            
            void delaytilde_01_delay_set(number v) {
                this->delaytilde_01_delay = v;
            }
            
            void mstosamps_01_out1_set(number v) {
                this->delaytilde_01_delay_set(v);
            }
            
            void mstosamps_01_ms_set(number ms) {
                this->mstosamps_01_ms = ms;
            
                {
                    this->mstosamps_01_out1_set(ms * this->sr * 0.001);
                    return;
                }
            }
            
            static number param_02_value_constrain(number v) {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void dspexpr_06_in2_set(number v) {
                this->dspexpr_06_in2 = v;
            }
            
            void dspexpr_04_in2_set(number v) {
                this->dspexpr_04_in2 = v;
            }
            
            static number param_03_value_constrain(number v) {
                v = (v > 10000 ? 10000 : (v < 10 ? 10 : v));
                return v;
            }
            
            void delaytilde_02_delay_set(number v) {
                this->delaytilde_02_delay = v;
            }
            
            void mstosamps_02_out1_set(number v) {
                this->delaytilde_02_delay_set(v);
            }
            
            void mstosamps_02_ms_set(number ms) {
                this->mstosamps_02_ms = ms;
            
                {
                    this->mstosamps_02_out1_set(ms * this->sr * 0.001);
                    return;
                }
            }
            
            void dspexpr_05_perform(const Sample * in1, number in2, Sample * out1, Index n) {
                RNBO_UNUSED(in2);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * 0.3;//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_07_perform(const Sample * in1, number in2, Sample * out1, Index n) {
                RNBO_UNUSED(in2);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * 0.3;//#map:_###_obj_###_:1
                }
            }
            
            void feedbackreader_01_perform(Sample * output, Index n) {
                auto& buffer = this->feedbacktilde_01_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = buffer[(Index)i];
                }
            }
            
            void delaytilde_01_perform(number delay, const Sample * input, Sample * output, Index n) {
                auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
                auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
                auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
                auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;
            
                for (Index i = 0; i < n; i++) {
                    if (__delaytilde_01_lastDelay == -1) {
                        __delaytilde_01_lastDelay = delay;
                    }
            
                    if (__delaytilde_01_ramp > 0) {
                        number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
                        output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
                        __delaytilde_01_ramp--;
                    } else {
                        number effectiveDelay = delay;
            
                        if (effectiveDelay != __delaytilde_01_lastDelay) {
                            __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                            __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                            __delaytilde_01_lastDelay = effectiveDelay;
                            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                            __delaytilde_01_ramp--;
                        } else {
                            output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
                        }
                    }
            
                    this->delaytilde_01_del_write(input[(Index)i]);
                    this->delaytilde_01_del_step();
                }
            
                this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
                this->delaytilde_01_ramp = __delaytilde_01_ramp;
                this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
            }
            
            void dspexpr_04_perform(const Sample * in1, number in2, Sample * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_03_perform(const Sample * in1, const Sample * in2, Sample * out, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out[(Index)i] = in1[(Index)i] + in2[(Index)i];
                }
            }
            
            void feedbackwriter_01_perform(const Sample * input, Index n) {
                auto& buffer = this->feedbacktilde_01_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    buffer[(Index)i] = input[(Index)i];
                }
            }
            
            void signalforwarder_01_perform(const Sample * input, Sample * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void feedbackreader_02_perform(Sample * output, Index n) {
                auto& buffer = this->feedbacktilde_02_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = buffer[(Index)i];
                }
            }
            
            void delaytilde_02_perform(number delay, const Sample * input, Sample * output, Index n) {
                auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
                auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
                auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
                auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;
            
                for (Index i = 0; i < n; i++) {
                    if (__delaytilde_02_lastDelay == -1) {
                        __delaytilde_02_lastDelay = delay;
                    }
            
                    if (__delaytilde_02_ramp > 0) {
                        number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
                        output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
                        __delaytilde_02_ramp--;
                    } else {
                        number effectiveDelay = delay;
            
                        if (effectiveDelay != __delaytilde_02_lastDelay) {
                            __delaytilde_02_ramp = __delaytilde_02_rampInSamples;
                            __delaytilde_02_crossfadeDelay = __delaytilde_02_lastDelay;
                            __delaytilde_02_lastDelay = effectiveDelay;
                            output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0);
                            __delaytilde_02_ramp--;
                        } else {
                            output[(Index)i] = this->delaytilde_02_del_read(effectiveDelay, 0);
                        }
                    }
            
                    this->delaytilde_02_del_write(input[(Index)i]);
                    this->delaytilde_02_del_step();
                }
            
                this->delaytilde_02_lastDelay = __delaytilde_02_lastDelay;
                this->delaytilde_02_ramp = __delaytilde_02_ramp;
                this->delaytilde_02_crossfadeDelay = __delaytilde_02_crossfadeDelay;
            }
            
            void dspexpr_06_perform(const Sample * in1, number in2, Sample * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_04_perform(const Sample * in1, const Sample * in2, Sample * out, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out[(Index)i] = in1[(Index)i] + in2[(Index)i];
                }
            }
            
            void feedbackwriter_02_perform(const Sample * input, Index n) {
                auto& buffer = this->feedbacktilde_02_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    buffer[(Index)i] = input[(Index)i];
                }
            }
            
            void signalforwarder_02_perform(const Sample * input, Sample * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void delaytilde_01_del_step() {
                this->delaytilde_01_del_reader++;
            
                if (this->delaytilde_01_del_reader >= (int)(this->delaytilde_01_del_buffer->getSize()))
                    this->delaytilde_01_del_reader = 0;
            }
            
            number delaytilde_01_del_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index3 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index4 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index3 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index4 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_01_del_wrap))
                    ));
                }
            
                number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->delaytilde_01_del_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_01_del_wrap))
                );
            }
            
            void delaytilde_01_del_write(number v) {
                this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
                this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
            }
            
            number delaytilde_01_del_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
                number val = this->delaytilde_01_del_read(effectiveSize, 0);
                this->delaytilde_01_del_write(v);
                this->delaytilde_01_del_step();
                return val;
            }
            
            array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->delaytilde_01_del_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void delaytilde_01_del_init() {
                auto result = this->delaytilde_01_del_calcSizeInSamples();
                this->delaytilde_01_del__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
                this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
            }
            
            void delaytilde_01_del_clear() {
                this->delaytilde_01_del_buffer->setZero();
            }
            
            void delaytilde_01_del_reset() {
                auto result = this->delaytilde_01_del_calcSizeInSamples();
                this->delaytilde_01_del__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->delaytilde_01_del_buffer);
                this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
                this->delaytilde_01_del_clear();
            
                if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
                    this->delaytilde_01_del_reader = 0;
                    this->delaytilde_01_del_writer = 0;
                }
            }
            
            void delaytilde_01_del_dspsetup() {
                this->delaytilde_01_del_reset();
            }
            
            number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                return samplerate;
            }
            
            number delaytilde_01_del_size() {
                return this->delaytilde_01_del__maxdelay;
            }
            
            void delaytilde_01_dspsetup(bool force) {
                if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->delaytilde_01_rampInSamples = (long)(this->mstosamps(50));
                this->delaytilde_01_lastDelay = -1;
                this->delaytilde_01_setupDone = true;
                this->delaytilde_01_del_dspsetup();
            }
            
            void param_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_01_value;
            }
            
            void param_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_01_value_set(preset["value"]);
            }
            
            void param_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_02_value;
            }
            
            void param_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_02_value_set(preset["value"]);
            }
            
            void param_03_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_03_value;
            }
            
            void param_03_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_03_value_set(preset["value"]);
            }
            
            void delaytilde_02_del_step() {
                this->delaytilde_02_del_reader++;
            
                if (this->delaytilde_02_del_reader >= (int)(this->delaytilde_02_del_buffer->getSize()))
                    this->delaytilde_02_del_reader = 0;
            }
            
            number delaytilde_02_del_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index3 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index4 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index3 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index4 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((UBinOpInt)index2 & (UBinOpInt)this->delaytilde_02_del_wrap))
                    ));
                }
            
                number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->delaytilde_02_del_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((UBinOpInt)index1 & (UBinOpInt)this->delaytilde_02_del_wrap))
                );
            }
            
            void delaytilde_02_del_write(number v) {
                this->delaytilde_02_del_writer = this->delaytilde_02_del_reader;
                this->delaytilde_02_del_buffer[(Index)this->delaytilde_02_del_writer] = v;
            }
            
            number delaytilde_02_del_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->delaytilde_02_del__maxdelay : size);
                number val = this->delaytilde_02_del_read(effectiveSize, 0);
                this->delaytilde_02_del_write(v);
                this->delaytilde_02_del_step();
                return val;
            }
            
            array<Index, 2> delaytilde_02_del_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->delaytilde_02_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->delaytilde_02_del_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void delaytilde_02_del_init() {
                auto result = this->delaytilde_02_del_calcSizeInSamples();
                this->delaytilde_02_del__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->delaytilde_02_del_buffer->requestSize(requestedSizeInSamples, 1);
                this->delaytilde_02_del_wrap = requestedSizeInSamples - 1;
            }
            
            void delaytilde_02_del_clear() {
                this->delaytilde_02_del_buffer->setZero();
            }
            
            void delaytilde_02_del_reset() {
                auto result = this->delaytilde_02_del_calcSizeInSamples();
                this->delaytilde_02_del__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->delaytilde_02_del_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->delaytilde_02_del_buffer);
                this->delaytilde_02_del_wrap = this->delaytilde_02_del_buffer->getSize() - 1;
                this->delaytilde_02_del_clear();
            
                if (this->delaytilde_02_del_reader >= this->delaytilde_02_del__maxdelay || this->delaytilde_02_del_writer >= this->delaytilde_02_del__maxdelay) {
                    this->delaytilde_02_del_reader = 0;
                    this->delaytilde_02_del_writer = 0;
                }
            }
            
            void delaytilde_02_del_dspsetup() {
                this->delaytilde_02_del_reset();
            }
            
            number delaytilde_02_del_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                return samplerate;
            }
            
            number delaytilde_02_del_size() {
                return this->delaytilde_02_del__maxdelay;
            }
            
            void delaytilde_02_dspsetup(bool force) {
                if ((bool)(this->delaytilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->delaytilde_02_rampInSamples = (long)(this->mstosamps(50));
                this->delaytilde_02_lastDelay = -1;
                this->delaytilde_02_setupDone = true;
                this->delaytilde_02_del_dspsetup();
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_04_in1 = 0;
                dspexpr_04_in2 = 0.25;
                delaytilde_01_delay = 0;
                param_01_value = 300;
                mstosamps_01_ms = 0;
                dspexpr_05_in1 = 0;
                dspexpr_05_in2 = 0.3;
                param_02_value = 0.25;
                param_03_value = 400;
                mstosamps_02_ms = 0;
                dspexpr_06_in1 = 0;
                dspexpr_06_in2 = 0.25;
                delaytilde_02_delay = 0;
                dspexpr_07_in1 = 0;
                dspexpr_07_in2 = 0.3;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                delaytilde_01_lastDelay = -1;
                delaytilde_01_crossfadeDelay = 0;
                delaytilde_01_ramp = 0;
                delaytilde_01_rampInSamples = 0;
                delaytilde_01_del__maxdelay = 0;
                delaytilde_01_del_sizemode = 0;
                delaytilde_01_del_wrap = 0;
                delaytilde_01_del_reader = 0;
                delaytilde_01_del_writer = 0;
                delaytilde_01_setupDone = false;
                param_01_lastValue = 0;
                feedbacktilde_01_feedbackbuffer = nullptr;
                param_02_lastValue = 0;
                param_03_lastValue = 0;
                delaytilde_02_lastDelay = -1;
                delaytilde_02_crossfadeDelay = 0;
                delaytilde_02_ramp = 0;
                delaytilde_02_rampInSamples = 0;
                delaytilde_02_del__maxdelay = 0;
                delaytilde_02_del_sizemode = 0;
                delaytilde_02_del_wrap = 0;
                delaytilde_02_del_reader = 0;
                delaytilde_02_del_writer = 0;
                delaytilde_02_setupDone = false;
                feedbacktilde_02_feedbackbuffer = nullptr;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_04_in1;
                number dspexpr_04_in2;
                number delaytilde_01_delay;
                number param_01_value;
                number mstosamps_01_ms;
                number dspexpr_05_in1;
                number dspexpr_05_in2;
                number param_02_value;
                number param_03_value;
                number mstosamps_02_ms;
                number dspexpr_06_in1;
                number dspexpr_06_in2;
                number delaytilde_02_delay;
                number dspexpr_07_in1;
                number dspexpr_07_in2;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[5];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number delaytilde_01_lastDelay;
                number delaytilde_01_crossfadeDelay;
                number delaytilde_01_ramp;
                long delaytilde_01_rampInSamples;
                Float64BufferRef delaytilde_01_del_buffer;
                Index delaytilde_01_del__maxdelay;
                Int delaytilde_01_del_sizemode;
                Index delaytilde_01_del_wrap;
                Int delaytilde_01_del_reader;
                Int delaytilde_01_del_writer;
                bool delaytilde_01_setupDone;
                number param_01_lastValue;
                signal feedbacktilde_01_feedbackbuffer;
                number param_02_lastValue;
                number param_03_lastValue;
                number delaytilde_02_lastDelay;
                number delaytilde_02_crossfadeDelay;
                number delaytilde_02_ramp;
                long delaytilde_02_rampInSamples;
                Float64BufferRef delaytilde_02_del_buffer;
                Index delaytilde_02_del__maxdelay;
                Int delaytilde_02_del_sizemode;
                Index delaytilde_02_del_wrap;
                Int delaytilde_02_del_reader;
                Int delaytilde_02_del_writer;
                bool delaytilde_02_setupDone;
                signal feedbacktilde_02_feedbackbuffer;
                number stackprotect_count;
                DataRef delaytilde_01_del_bufferobj;
                DataRef delaytilde_02_del_bufferobj;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_08()
    {
    }
    
    ~RNBOSubpatcher_08()
    {
        delete this->p_01;
        delete this->p_02;
        delete this->p_03;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, 1646922831, false);
        getEngine()->flushClockEvents(this, -611950441, false);
        getEngine()->flushClockEvents(this, -1584063977, false);
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number samplerate() {
        return this->sr;
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    int notenumber() {
        return this->_noteNumber;
    }
    
    ParameterIndex getParameterIndexForID(ConstCharPointer paramid) const {
        if (!stringCompare(paramid, "cutoff")) {
            return 0;
        }
    
        if (!stringCompare(paramid, "overblow")) {
            return 1;
        }
    
        if (!stringCompare(paramid, "Q")) {
            return 2;
        }
    
        if (!stringCompare(paramid, "harmonics")) {
            return 3;
        }
    
        return INVALID_INDEX;
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time);
        this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        SampleValue ** inputs,
        Index numInputs,
        SampleValue ** outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->mtof_tilde_01_perform(this->mtof_tilde_01_midivalue, this->signals[0], n);
    
        this->slide_tilde_01_perform(
            this->slide_tilde_01_x,
            this->slide_tilde_01_up,
            this->slide_tilde_01_down,
            this->signals[1],
            n
        );
    
        this->slide_tilde_02_perform(
            this->slide_tilde_02_x,
            this->slide_tilde_02_up,
            this->slide_tilde_02_down,
            this->signals[2],
            n
        );
    
        this->slide_tilde_03_perform(
            this->slide_tilde_03_x,
            this->slide_tilde_03_up,
            this->slide_tilde_03_down,
            this->signals[3],
            n
        );
    
        this->ip_01_perform(this->signals[4], n);
    
        this->slide_tilde_04_perform(
            this->slide_tilde_04_x,
            this->slide_tilde_04_up,
            this->slide_tilde_04_down,
            this->signals[5],
            n
        );
    
        this->gen_01_perform(this->signals[0], this->signals[2], this->signals[5], this->signals[6], n);
        this->p_02_perform(this->signals[6], this->signals[4], this->signals[5], this->signals[2], n);
        this->p_01_perform(this->signals[5], this->signals[1], this->signals[3], this->signals[4], n);
        this->dspexpr_08_perform(this->signals[4], this->dspexpr_08_in2, this->signals[3], n);
        this->p_03_perform(this->signals[3], this->signals[4], this->signals[1], n);
        this->signaladder_01_perform(this->signals[4], out1, out1, n);
        this->signaladder_02_perform(this->signals[1], out2, out2, n);
        this->snapshot_01_perform(this->signals[2], n);
        this->delta_tilde_01_perform(this->signals[2], this->signals[1], n);
        this->dspexpr_09_perform(this->signals[1], this->dspexpr_09_in2, this->signals[2], n);
        this->edge_01_perform(this->signals[2], n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 7; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_01_dspsetup(forceDSPSetup);
        this->delta_tilde_01_dspsetup(forceDSPSetup);
        this->edge_01_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            this->setProbingIndex(-1);
            break;
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_01->setVoiceIndex(index);
        this->p_02->setVoiceIndex(index);
        this->p_03->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_01->setNoteNumber(noteNumber);
        this->p_02->setNoteNumber(noteNumber);
        this->p_03->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_05();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
        this->p_02 = new RNBOSubpatcher_06();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_07();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "filter"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "envelope"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "delay"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_01->processTempoEvent(time, tempo);
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_01->processTransportEvent(time, state);
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_01->processBeatTimeEvent(time, beattime);
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            this->param_04_value_set(v);
            break;
        case 1:
            this->param_05_value_set(v);
            break;
        case 2:
            this->param_06_value_set(v);
            break;
        case 3:
            this->param_07_value_set(v);
            break;
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            break;
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            return this->param_04_value;
        case 1:
            return this->param_05_value;
        case 2:
            return this->param_06_value;
        case 3:
            return this->param_07_value;
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            return 0;
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            return voices[0]->getParameterValue(index);
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            for (Index i = 0; i < 8; i++)
                voices[i]->setParameterValue(index, value, time);
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            return "cutoff";
        case 1:
            return "overblow";
        case 2:
            return "Q";
        case 3:
            return "harmonics";
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            return "bogus";
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            return "poly/cutoff";
        case 1:
            return "poly/overblow";
        case 2:
            return "poly/Q";
        case 3:
            return "poly/harmonics";
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            return "bogus";
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                info->type = ParameterTypeNumber;
                info->initialValue = 880;
                info->min = 100;
                info->max = 8000;
                info->exponent = 2;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
            case 1:
                info->type = ParameterTypeNumber;
                info->initialValue = 1.5;
                info->min = 0.1;
                info->max = 5;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
            case 2:
                info->type = ParameterTypeNumber;
                info->initialValue = 3;
                info->min = 0.01;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
            case 3:
                info->type = ParameterTypeNumber;
                info->initialValue = 3;
                info->min = 0.1;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
            default:
                index -= 4;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                index -= this->p_01->getNumParameters();
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                break;
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 4;
    
        if (subpatcher == this->p_02)
            return 4 + this->p_01->getNumParameters();
    
        if (subpatcher == this->p_03)
            return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
                value = (value < 100 ? 100 : (value > 8000 ? 8000 : value));
                ParameterValue normalizedValue = (value - 100) / (8000 - 100);
    
                {
                    normalizedValue = rnbo_exp(rnbo_log(normalizedValue) * 1. / (number)2);
                }
    
                return normalizedValue;
            }
        case 1:
            {
                value = (value < 0.1 ? 0.1 : (value > 5 ? 5 : value));
                ParameterValue normalizedValue = (value - 0.1) / (5 - 0.1);
                return normalizedValue;
            }
        case 3:
            {
                value = (value < 0.1 ? 0.1 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 0.1) / (10 - 0.1);
                return normalizedValue;
            }
        case 2:
            {
                value = (value < 0.01 ? 0.01 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 0.01) / (10 - 0.01);
                return normalizedValue;
            }
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            return value;
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 100 + rnbo_exp(rnbo_log(value) * 2) * (8000 - 100);
                }
            }
        case 1:
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0.1 + value * (5 - 0.1);
                }
            }
        case 3:
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0.1 + value * (10 - 0.1);
                }
            }
        case 2:
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0.01 + value * (10 - 0.01);
                }
            }
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            return value;
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            return this->param_04_value_constrain(value);
        case 1:
            return this->param_05_value_constrain(value);
        case 2:
            return this->param_06_value_constrain(value);
        case 3:
            return this->param_07_value_constrain(value);
        default:
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            return value;
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case 1646922831:
            this->snapshot_01_out_set(value);
            break;
        case -611950441:
            this->edge_01_onout_bang();
            break;
        case -1584063977:
            this->edge_01_offout_bang();
            break;
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processNumMessage(tag, objectId, time, payload);
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("active"):
            return "active";
        case TAG(""):
            return "";
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            return nullptr;
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 0) {
            this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultMtofLookupTable256);
        }
    
        this->p_01->processDataViewUpdate(index, time);
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultMtofLookupTable256);
    }
    
    protected:
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(0, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->slide_tilde_01_x_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(1, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->slide_tilde_02_x_set(v);
    }
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(2, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->slide_tilde_03_x_set(v);
    }
    
    void param_07_value_set(number v) {
        v = this->param_07_value_constrain(v);
        this->param_07_value = v;
        this->sendParameter(3, false);
    
        if (this->param_07_value != this->param_07_lastValue) {
            this->getEngine()->presetTouched();
            this->param_07_lastValue = this->param_07_value;
        }
    
        this->slide_tilde_04_x_set(v);
    }
    
    void snapshot_01_out_set(number v) {
        this->snapshot_01_out = v;
        this->trigger_01_input_number_set(v);
    }
    
    void edge_01_onout_bang() {
        this->snapshot_01_input_bang_bang();
    }
    
    void edge_01_offout_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->gen_01_history_9_init();
        this->gen_01_history_8_init();
        this->gen_01_history_7_init();
        this->gen_01_history_6_init();
        this->gen_01_history_5_init();
        this->gen_01_history_4_init();
        this->gen_01_history_3_init();
        this->gen_01_history_2_init();
        this->gen_01_history_1_init();
        this->mtof_tilde_01_innerScala_init();
        this->mtof_tilde_01_init();
        this->ip_01_init();
        this->p_01->initializeObjects();
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->p_02->startup();
        this->p_03->startup();
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->mtof_tilde_01_innerMtoF_buffer->requestSize(65536, 1);
        this->mtof_tilde_01_innerMtoF_buffer->setSampleRate(this->sr);
        this->mtof_tilde_01_innerMtoF_buffer = this->mtof_tilde_01_innerMtoF_buffer->allocateIfNeeded();
    }
    
    void voice_01_mutestatus_set(number ) {}
    
    void voice_01_mutein_list_set(const list& v) {
        if (v[0] == this->voice() || v[0] == 0) {
            this->voice_01_mutestatus_set(v[1]);
        }
    }
    
    void voice_01_activevoices_set(number ) {}
    
    static number param_04_value_constrain(number v) {
        v = (v > 8000 ? 8000 : (v < 100 ? 100 : v));
        return v;
    }
    
    void slide_tilde_01_x_set(number v) {
        this->slide_tilde_01_x = v;
    }
    
    static number param_05_value_constrain(number v) {
        v = (v > 5 ? 5 : (v < 0.1 ? 0.1 : v));
        return v;
    }
    
    void slide_tilde_02_x_set(number v) {
        this->slide_tilde_02_x = v;
    }
    
    static number param_06_value_constrain(number v) {
        v = (v > 10 ? 10 : (v < 0.01 ? 0.01 : v));
        return v;
    }
    
    void slide_tilde_03_x_set(number v) {
        this->slide_tilde_03_x = v;
    }
    
    static number param_07_value_constrain(number v) {
        v = (v > 10 ? 10 : (v < 0.1 ? 0.1 : v));
        return v;
    }
    
    void slide_tilde_04_x_set(number v) {
        this->slide_tilde_04_x = v;
    }
    
    void pack_01_in2_set(number v) {
        this->pack_01_in2 = v;
    }
    
    void trigger_01_out2_set(number v) {
        this->pack_01_in2_set(v);
    }
    
    void voice_01_noteNumber_set(number ) {}
    
    void outport_01_input_list_set(const list& v) {
        this->getEngine()->sendListMessage(TAG("active"), TAG(""), v, this->_currentTime);
    }
    
    void pack_01_out_set(const list& v) {
        this->outport_01_input_list_set(v);
    }
    
    void pack_01_in1_set(number v) {
        this->pack_01_in1 = v;
        list array = list(0, 0);
        array[0] = rnbo_trunc(this->pack_01_in1);
        array[1] = rnbo_trunc(this->pack_01_in2);
        this->pack_01_out_set(array);
    }
    
    void voice_01_voicenumber_set(number v) {
        this->pack_01_in1_set(v);
    }
    
    void voice_01_voicebang_bang() {
        this->voice_01_noteNumber_set(this->notenumber());
        this->voice_01_voicenumber_set(this->voice());
    }
    
    void trigger_01_out1_bang() {
        this->voice_01_voicebang_bang();
    }
    
    void trigger_01_input_number_set(number v) {
        this->trigger_01_out2_set(rnbo_trunc(v));
        this->trigger_01_out1_bang();
    }
    
    void snapshot_01_input_bang_bang() {
        this->snapshot_01_out_set(this->snapshot_01_lastValue);
    }
    
    void notein_01_outchannel_set(number ) {}
    
    void notein_01_releasevelocity_set(number ) {}
    
    void ip_01_value_set(number v) {
        this->ip_01_value = v;
        this->ip_01_fillSigBuf();
        this->ip_01_lastValue = v;
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->ip_01_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
    
        this->expr_01_out1_set(
            (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
        );//#map:/_obj-2:1
    }
    
    void notein_01_velocity_set(number v) {
        this->expr_01_in1_set(v);
    }
    
    void mtof_tilde_01_midivalue_set(number v) {
        this->mtof_tilde_01_midivalue = v;
    }
    
    void notein_01_notenumber_set(number v) {
        this->mtof_tilde_01_midivalue_set(v);
    }
    
    void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
            if (status == 144 || status == 128) {
                this->notein_01_outchannel_set(channel);
    
                if (status == 128) {
                    this->notein_01_releasevelocity_set(data[2]);
                    this->notein_01_velocity_set(0);
                } else {
                    this->notein_01_releasevelocity_set(0);
                    this->notein_01_velocity_set(data[2]);
                }
    
                this->notein_01_notenumber_set(data[1]);
            }
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void mtof_tilde_01_perform(number midivalue, Sample * out, Index n) {
        auto __mtof_tilde_01_base = this->mtof_tilde_01_base;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->mtof_tilde_01_innerMtoF_next(midivalue, __mtof_tilde_01_base);
        }
    }
    
    void slide_tilde_01_perform(number x, number up, number down, Sample * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_01_prev = this->slide_tilde_01_prev;
        number iup = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        number idown = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_01_prev;
            __slide_tilde_01_prev = __slide_tilde_01_prev + ((x > __slide_tilde_01_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_01_prev;
        }
    
        this->slide_tilde_01_prev = __slide_tilde_01_prev;
    }
    
    void slide_tilde_02_perform(number x, number up, number down, Sample * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_02_prev = this->slide_tilde_02_prev;
        number iup = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        number idown = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_02_prev;
            __slide_tilde_02_prev = __slide_tilde_02_prev + ((x > __slide_tilde_02_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_02_prev;
        }
    
        this->slide_tilde_02_prev = __slide_tilde_02_prev;
    }
    
    void slide_tilde_03_perform(number x, number up, number down, Sample * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_03_prev = this->slide_tilde_03_prev;
        number iup = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        number idown = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_03_prev;
            __slide_tilde_03_prev = __slide_tilde_03_prev + ((x > __slide_tilde_03_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_03_prev;
        }
    
        this->slide_tilde_03_prev = __slide_tilde_03_prev;
    }
    
    void ip_01_perform(Sample * out, Index n) {
        auto __ip_01_sigbuf = this->ip_01_sigbuf;
        auto __ip_01_lastValue = this->ip_01_lastValue;
        auto __ip_01_lastIndex = this->ip_01_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : __ip_01_sigbuf[(Index)i]);
        }
    
        __ip_01_lastIndex = 0;
        this->ip_01_lastIndex = __ip_01_lastIndex;
    }
    
    void slide_tilde_04_perform(number x, number up, number down, Sample * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_04_prev = this->slide_tilde_04_prev;
        number iup = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        number idown = this->safediv(1., this->maximum(1., rnbo_abs(20)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_04_prev;
            __slide_tilde_04_prev = __slide_tilde_04_prev + ((x > __slide_tilde_04_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_04_prev;
        }
    
        this->slide_tilde_04_prev = __slide_tilde_04_prev;
    }
    
    void gen_01_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        Sample * out1,
        Index n
    ) {
        auto __gen_01_history_8_value = this->gen_01_history_8_value;
        auto __gen_01_history_6_value = this->gen_01_history_6_value;
        auto __gen_01_history_5_value = this->gen_01_history_5_value;
        auto __gen_01_history_7_value = this->gen_01_history_7_value;
        auto __gen_01_history_2_value = this->gen_01_history_2_value;
        auto __gen_01_history_4_value = this->gen_01_history_4_value;
        auto __gen_01_history_9_value = this->gen_01_history_9_value;
        auto __gen_01_history_3_value = this->gen_01_history_3_value;
        auto __gen_01_history_1_value = this->gen_01_history_1_value;
        number div_66_66 = this->samplerate() / (number)2;
        Index i;
    
        for (i = 0; i < n; i++) {
            number float_10_0 = float(1.306563);
            number float_11_1 = float(0.541196);
            number mul_12_2 = in1[(Index)i] * in3[(Index)i];
            number min_13_3 = this->maximum(mul_12_2, 0);
            number min_14_4 = this->maximum(float_11_1, 0.000001);
            number omega_5 = (this->samplerate() == 0. ? 0. : min_13_3 * 6.28318530717958647692 / this->samplerate());
            number omega_15_6 = ((bool)(rnbo_isnan(omega_5)) ? 0.1 : omega_5);
            number sn_7 = rnbo_sin(omega_15_6);
            number cs_8 = rnbo_cos(omega_15_6);
            number one_over_Q_9 = (min_14_4 == 0. ? 0. : (number)1 / min_14_4);
            number one_over_Q_16_10 = ((bool)(rnbo_isnan(one_over_Q_9)) ? 2 : one_over_Q_9);
            number alpha_11 = sn_7 * 0.5 * one_over_Q_16_10;
            number b0_12 = (1 + alpha_11 == 0. ? 0. : (number)1 / (1 + alpha_11));
            number a2_13 = (1 - cs_8) * 0.5 * b0_12;
            number a1_14 = (1 - cs_8) * b0_12;
            number b1_15 = -2 * cs_8 * b0_12;
            number b2_16 = (1 - alpha_11) * b0_12;
            number expr_17_17 = a2_13;
            number expr_18_18 = a1_14;
            number expr_19_19 = a2_13;
            number expr_20_20 = b1_15;
            number expr_21_21 = b2_16;
            number mul_22_22 = __gen_01_history_1_value * expr_19_19;
            number mul_23_23 = __gen_01_history_3_value * expr_18_18;
            number mul_24_24 = __gen_01_history_9_value * expr_17_17;
            number mul_25_25 = __gen_01_history_4_value * expr_20_20;
            number mul_26_26 = __gen_01_history_2_value * expr_21_21;
            number sub_27_27 = mul_24_24 + mul_23_23 + mul_22_22 - (mul_26_26 + mul_25_25);
            number gen_28_28 = sub_27_27;
            number history_1_next_29_29 = fixdenorm(__gen_01_history_3_value);
            number history_2_next_30_30 = fixdenorm(__gen_01_history_4_value);
            number history_3_next_31_31 = fixdenorm(__gen_01_history_9_value);
            number history_4_next_32_32 = fixdenorm(sub_27_27);
            number gen_33_33 = gen_28_28;
            number min_34_34 = this->maximum(mul_12_2, 0);
            number min_35_35 = this->maximum(float_10_0, 0.000001);
            number omega_36_36 = (this->samplerate() == 0. ? 0. : min_34_34 * 6.28318530717958647692 / this->samplerate());
            number omega_37_37 = ((bool)(rnbo_isnan(omega_36_36)) ? 0.1 : omega_36_36);
            number sn_38_38 = rnbo_sin(omega_37_37);
            number cs_39_39 = rnbo_cos(omega_37_37);
            number one_over_Q_40_40 = (min_35_35 == 0. ? 0. : (number)1 / min_35_35);
            number one_over_Q_41_41 = ((bool)(rnbo_isnan(one_over_Q_40_40)) ? 2 : one_over_Q_40_40);
            number alpha_42_42 = sn_38_38 * 0.5 * one_over_Q_41_41;
            number b_43_43 = (1 + alpha_42_42 == 0. ? 0. : (number)1 / (1 + alpha_42_42));
            number a_44_44 = (1 - cs_39_39) * 0.5 * b_43_43;
            number a_45_45 = (1 - cs_39_39) * b_43_43;
            number b_46_46 = -2 * cs_39_39 * b_43_43;
            number b_47_47 = (1 - alpha_42_42) * b_43_43;
            number expr_48_48 = a_44_44;
            number expr_49_49 = a_45_45;
            number expr_50_50 = a_44_44;
            number expr_51_51 = b_46_46;
            number expr_52_52 = b_47_47;
            number mul_53_53 = gen_33_33 * expr_48_48;
            number mul_54_54 = __gen_01_history_7_value * expr_49_49;
            number mul_55_55 = __gen_01_history_5_value * expr_50_50;
            number mul_56_56 = __gen_01_history_6_value * expr_52_52;
            number mul_57_57 = __gen_01_history_8_value * expr_51_51;
            number sub_58_58 = mul_55_55 + mul_54_54 + mul_53_53 - (mul_57_57 + mul_56_56);
            number gen_59_59 = sub_58_58;
            number history_5_next_60_60 = fixdenorm(__gen_01_history_7_value);
            number history_6_next_61_61 = fixdenorm(__gen_01_history_8_value);
            number history_7_next_62_62 = fixdenorm(gen_33_33);
            number history_8_next_63_63 = fixdenorm(sub_58_58);
            number gen_64_64 = gen_59_59;
            number mul_65_65 = gen_64_64 * in2[(Index)i];
            number div_67_67 = (div_66_66 == 0. ? 0. : in1[(Index)i] / div_66_66);
            number mul_68_68 = div_67_67 * 3.14159265358979323846;
            number plusequals_69_71 = this->gen_01_plusequals_70_next(mul_68_68, 0);
            number add_70_72 = plusequals_69_71 + mul_65_65;
            number sin_71_73 = rnbo_sin(add_70_72);
            number mul_72_74 = sin_71_73 * 10;
            number tanh_73_75 = rnbo_tanh(mul_72_74);
            out1[(Index)i] = tanh_73_75;
            number history_9_next_74_76 = fixdenorm(sin_71_73);
            __gen_01_history_1_value = history_1_next_29_29;
            __gen_01_history_9_value = history_9_next_74_76;
            __gen_01_history_8_value = history_8_next_63_63;
            __gen_01_history_7_value = history_7_next_62_62;
            __gen_01_history_6_value = history_6_next_61_61;
            __gen_01_history_5_value = history_5_next_60_60;
            __gen_01_history_4_value = history_4_next_32_32;
            __gen_01_history_3_value = history_3_next_31_31;
            __gen_01_history_2_value = history_2_next_30_30;
        }
    
        this->gen_01_history_1_value = __gen_01_history_1_value;
        this->gen_01_history_3_value = __gen_01_history_3_value;
        this->gen_01_history_9_value = __gen_01_history_9_value;
        this->gen_01_history_4_value = __gen_01_history_4_value;
        this->gen_01_history_2_value = __gen_01_history_2_value;
        this->gen_01_history_7_value = __gen_01_history_7_value;
        this->gen_01_history_5_value = __gen_01_history_5_value;
        this->gen_01_history_6_value = __gen_01_history_6_value;
        this->gen_01_history_8_value = __gen_01_history_8_value;
    }
    
    void p_02_perform(Sample * in1, Sample * in2, Sample * out1, Sample * out2, Index n) {
        // subpatcher: envelope
        SampleArray<2> ins = {in1, in2};
    
        SampleArray<2> outs = {out1, out2};
        this->p_02->process(ins, 2, outs, 2, n);
    }
    
    void p_01_perform(Sample * in1, Sample * in2, Sample * in3, Sample * out1, Index n) {
        // subpatcher: filter
        SampleArray<3> ins = {in1, in2, in3};
    
        SampleArray<1> outs = {out1};
        this->p_01->process(ins, 3, outs, 1, n);
    }
    
    void dspexpr_08_perform(const Sample * in1, number in2, Sample * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * 0.5;//#map:_###_obj_###_:1
        }
    }
    
    void p_03_perform(Sample * in1, Sample * out1, Sample * out2, Index n) {
        // subpatcher: delay
        SampleArray<1> ins = {in1};
    
        SampleArray<2> outs = {out1, out2};
        this->p_03->process(ins, 1, outs, 2, n);
    }
    
    void signaladder_01_perform(const Sample * in1, const Sample * in2, Sample * out, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(const Sample * in1, const Sample * in2, Sample * out, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void snapshot_01_perform(const Sample * input_signal, Index n) {
        auto __snapshot_01_lastValue = this->snapshot_01_lastValue;
        auto __snapshot_01_calc = this->snapshot_01_calc;
        auto __snapshot_01_count = this->snapshot_01_count;
        auto __snapshot_01_nextTime = this->snapshot_01_nextTime;
        auto __snapshot_01_interval = this->snapshot_01_interval;
        number timeInSamples = this->msToSamps(__snapshot_01_interval, this->sr);
    
        if (__snapshot_01_interval > 0) {
            for (Index i = 0; i < n; i++) {
                if (__snapshot_01_nextTime <= __snapshot_01_count + (SampleIndex)(i)) {
                    {
                        __snapshot_01_calc = input_signal[(Index)i];
                    }
    
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        1646922831,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        __snapshot_01_calc
                    );;
    
                    __snapshot_01_calc = 0;
                    __snapshot_01_nextTime += timeInSamples;
                }
            }
    
            __snapshot_01_count += this->vs;
        }
    
        __snapshot_01_lastValue = input_signal[(Index)(n - 1)];
        this->snapshot_01_nextTime = __snapshot_01_nextTime;
        this->snapshot_01_count = __snapshot_01_count;
        this->snapshot_01_calc = __snapshot_01_calc;
        this->snapshot_01_lastValue = __snapshot_01_lastValue;
    }
    
    void delta_tilde_01_perform(const Sample * x, Sample * out1, Index n) {
        auto __delta_tilde_01_prev = this->delta_tilde_01_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_01_prev);
            __delta_tilde_01_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_01_prev = __delta_tilde_01_prev;
    }
    
    void dspexpr_09_perform(const Sample * in1, number in2, Sample * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] != 0;//#map:_###_obj_###_:1
        }
    }
    
    void edge_01_perform(const Sample * input, Index n) {
        auto __edge_01_currentState = this->edge_01_currentState;
    
        for (Index i = 0; i < n; i++) {
            if (__edge_01_currentState == 1) {
                if (input[(Index)i] == 0.) {
                    this->getEngine()->scheduleClockEvent(this, -1584063977, this->sampsToMs(i) + this->_currentTime);;
                    __edge_01_currentState = 0;
                }
            } else {
                if (input[(Index)i] != 0.) {
                    this->getEngine()->scheduleClockEvent(this, -611950441, this->sampsToMs(i) + this->_currentTime);;
                    __edge_01_currentState = 1;
                }
            }
        }
    
        this->edge_01_currentState = __edge_01_currentState;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number gen_01_history_9_getvalue() {
        return this->gen_01_history_9_value;
    }
    
    void gen_01_history_9_setvalue(number val) {
        this->gen_01_history_9_value = val;
    }
    
    void gen_01_history_9_reset() {
        this->gen_01_history_9_value = 0;
    }
    
    void gen_01_history_9_init() {
        this->gen_01_history_9_value = 0;
    }
    
    number gen_01_history_8_getvalue() {
        return this->gen_01_history_8_value;
    }
    
    void gen_01_history_8_setvalue(number val) {
        this->gen_01_history_8_value = val;
    }
    
    void gen_01_history_8_reset() {
        this->gen_01_history_8_value = 0;
    }
    
    void gen_01_history_8_init() {
        this->gen_01_history_8_value = 0;
    }
    
    number gen_01_history_7_getvalue() {
        return this->gen_01_history_7_value;
    }
    
    void gen_01_history_7_setvalue(number val) {
        this->gen_01_history_7_value = val;
    }
    
    void gen_01_history_7_reset() {
        this->gen_01_history_7_value = 0;
    }
    
    void gen_01_history_7_init() {
        this->gen_01_history_7_value = 0;
    }
    
    number gen_01_history_6_getvalue() {
        return this->gen_01_history_6_value;
    }
    
    void gen_01_history_6_setvalue(number val) {
        this->gen_01_history_6_value = val;
    }
    
    void gen_01_history_6_reset() {
        this->gen_01_history_6_value = 0;
    }
    
    void gen_01_history_6_init() {
        this->gen_01_history_6_value = 0;
    }
    
    number gen_01_history_5_getvalue() {
        return this->gen_01_history_5_value;
    }
    
    void gen_01_history_5_setvalue(number val) {
        this->gen_01_history_5_value = val;
    }
    
    void gen_01_history_5_reset() {
        this->gen_01_history_5_value = 0;
    }
    
    void gen_01_history_5_init() {
        this->gen_01_history_5_value = 0;
    }
    
    number gen_01_history_4_getvalue() {
        return this->gen_01_history_4_value;
    }
    
    void gen_01_history_4_setvalue(number val) {
        this->gen_01_history_4_value = val;
    }
    
    void gen_01_history_4_reset() {
        this->gen_01_history_4_value = 0;
    }
    
    void gen_01_history_4_init() {
        this->gen_01_history_4_value = 0;
    }
    
    number gen_01_history_3_getvalue() {
        return this->gen_01_history_3_value;
    }
    
    void gen_01_history_3_setvalue(number val) {
        this->gen_01_history_3_value = val;
    }
    
    void gen_01_history_3_reset() {
        this->gen_01_history_3_value = 0;
    }
    
    void gen_01_history_3_init() {
        this->gen_01_history_3_value = 0;
    }
    
    number gen_01_history_2_getvalue() {
        return this->gen_01_history_2_value;
    }
    
    void gen_01_history_2_setvalue(number val) {
        this->gen_01_history_2_value = val;
    }
    
    void gen_01_history_2_reset() {
        this->gen_01_history_2_value = 0;
    }
    
    void gen_01_history_2_init() {
        this->gen_01_history_2_value = 0;
    }
    
    number gen_01_history_1_getvalue() {
        return this->gen_01_history_1_value;
    }
    
    void gen_01_history_1_setvalue(number val) {
        this->gen_01_history_1_value = val;
    }
    
    void gen_01_history_1_reset() {
        this->gen_01_history_1_value = 0;
    }
    
    void gen_01_history_1_init() {
        this->gen_01_history_1_value = 0;
    }
    
    number gen_01_plusequals_70_next(number x, number reset) {
        RNBO_UNUSED(reset);
    
        {
            this->gen_01_plusequals_70_value = this->gen_01_plusequals_70_value + x;
        }
    
        return this->gen_01_plusequals_70_value;
    }
    
    void gen_01_plusequals_70_reset() {
        this->gen_01_plusequals_70_value = 0;
    }
    
    number mtof_tilde_01_innerMtoF_next(number midivalue, number tuning) {
        if (midivalue == this->mtof_tilde_01_innerMtoF_lastInValue && tuning == this->mtof_tilde_01_innerMtoF_lastTuning)
            return this->mtof_tilde_01_innerMtoF_lastOutValue;
    
        this->mtof_tilde_01_innerMtoF_lastInValue = midivalue;
        this->mtof_tilde_01_innerMtoF_lastTuning = tuning;
        number result = 0;
    
        {
            result = rnbo_exp(.057762265 * (midivalue - 69.0));
        }
    
        this->mtof_tilde_01_innerMtoF_lastOutValue = tuning * result;
        return this->mtof_tilde_01_innerMtoF_lastOutValue;
    }
    
    void mtof_tilde_01_innerMtoF_reset() {
        this->mtof_tilde_01_innerMtoF_lastInValue = 0;
        this->mtof_tilde_01_innerMtoF_lastOutValue = 0;
        this->mtof_tilde_01_innerMtoF_lastTuning = 0;
    }
    
    void mtof_tilde_01_innerScala_mid(int v) {
        this->mtof_tilde_01_innerScala_kbmMid = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_ref(int v) {
        this->mtof_tilde_01_innerScala_kbmRefNum = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_base(number v) {
        this->mtof_tilde_01_innerScala_kbmRefFreq = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_init() {
        list sclValid = {
            12,
            100,
            0,
            200,
            0,
            300,
            0,
            400,
            0,
            500,
            0,
            600,
            0,
            700,
            0,
            800,
            0,
            900,
            0,
            1000,
            0,
            1100,
            0,
            2,
            1
        };
    
        this->mtof_tilde_01_innerScala_updateScale(sclValid);
    }
    
    void mtof_tilde_01_innerScala_update(list scale, list map) {
        if (scale->length > 0) {
            this->mtof_tilde_01_innerScala_updateScale(scale);
        }
    
        if (map->length > 0) {
            this->mtof_tilde_01_innerScala_updateMap(map);
        }
    }
    
    number mtof_tilde_01_innerScala_mtof(number note) {
        if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastNote == note) {
            return this->mtof_tilde_01_innerScala_lastFreq;
        }
    
        array<int, 2> degoct = this->mtof_tilde_01_innerScala_applyKBM(note);
        number out = 0;
    
        if (degoct[1] > 0) {
            out = this->mtof_tilde_01_innerScala_applySCL(degoct[0], fract(note), this->mtof_tilde_01_innerScala_refFreq);
        }
    
        this->mtof_tilde_01_innerScala_updateLast(note, out);
        return out;
    }
    
    number mtof_tilde_01_innerScala_ftom(number hz) {
        if (hz <= 0.0) {
            return 0.0;
        }
    
        if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastFreq == hz) {
            return this->mtof_tilde_01_innerScala_lastNote;
        }
    
        array<number, 2> df = this->mtof_tilde_01_innerScala_hztodeg(hz);
        int degree = (int)(df[0]);
        number frac = df[1];
        number out = 0;
    
        if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
            out = this->mtof_tilde_01_innerScala_kbmMid + degree;
        } else {
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmOctaveDegree);
            number oct = (number)(octdeg[0]);
            int index = (int)(octdeg[1]);
            Index entry = 0;
    
            for (Index i = 0; i < this->mtof_tilde_01_innerScala_kbmMapSize; i++) {
                if (index == this->mtof_tilde_01_innerScala_kbmValid[(Index)(i + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]) {
                    entry = i;
                    break;
                }
            }
    
            out = oct * this->mtof_tilde_01_innerScala_kbmSize + entry + this->mtof_tilde_01_innerScala_kbmMid;
        }
    
        out = out + frac;
        this->mtof_tilde_01_innerScala_updateLast(out, hz);
        return this->mtof_tilde_01_innerScala_lastNote;
    }
    
    int mtof_tilde_01_innerScala_updateScale(list scl) {
        if (scl->length > 1 && scl[0] * 2 + 1 == scl->length) {
            this->mtof_tilde_01_innerScala_lastValid = false;
            this->mtof_tilde_01_innerScala_sclExpMul = {};
            number last = 1;
    
            for (Index i = 1; i < scl->length; i += 2) {
                const number c = (const number)(scl[(Index)(i + 0)]);
                const number d = (const number)(scl[(Index)(i + 1)]);
    
                if (d <= 0) {
                    last = c / (number)1200;
                } else {
                    last = rnbo_log2(c / d);
                }
    
                this->mtof_tilde_01_innerScala_sclExpMul->push(last);
            }
    
            this->mtof_tilde_01_innerScala_sclOctaveMul = last;
            this->mtof_tilde_01_innerScala_sclEntryCount = (int)(this->mtof_tilde_01_innerScala_sclExpMul->length);
            this->mtof_tilde_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    int mtof_tilde_01_innerScala_updateMap(list kbm) {
        if (kbm->length == 1 && kbm[0] == 0.0) {
            kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
        }
    
        if (kbm->length >= 6 && kbm[0] >= 0.0) {
            this->mtof_tilde_01_innerScala_lastValid = false;
            Index size = (Index)(kbm[0]);
            int octave = 12;
    
            if (kbm->length > 6) {
                octave = (int)(kbm[6]);
            }
    
            if (size > 0 && kbm->length < this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET) {
                return 0;
            }
    
            this->mtof_tilde_01_innerScala_kbmSize = (int)(size);
            this->mtof_tilde_01_innerScala_kbmMin = (int)(kbm[1]);
            this->mtof_tilde_01_innerScala_kbmMax = (int)(kbm[2]);
            this->mtof_tilde_01_innerScala_kbmMid = (int)(kbm[3]);
            this->mtof_tilde_01_innerScala_kbmRefNum = (int)(kbm[4]);
            this->mtof_tilde_01_innerScala_kbmRefFreq = kbm[5];
            this->mtof_tilde_01_innerScala_kbmOctaveDegree = octave;
            this->mtof_tilde_01_innerScala_kbmValid = kbm;
            this->mtof_tilde_01_innerScala_kbmMapSize = (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET));
            this->mtof_tilde_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    void mtof_tilde_01_innerScala_updateLast(number note, number freq) {
        this->mtof_tilde_01_innerScala_lastValid = true;
        this->mtof_tilde_01_innerScala_lastNote = note;
        this->mtof_tilde_01_innerScala_lastFreq = freq;
    }
    
    array<number, 2> mtof_tilde_01_innerScala_hztodeg(number hz) {
        number hza = rnbo_abs(hz);
    
        number octave = rnbo_floor(
            rnbo_log2(hza / this->mtof_tilde_01_innerScala_refFreq) / this->mtof_tilde_01_innerScala_sclOctaveMul
        );
    
        int i = 0;
        number frac = 0;
        number n = 0;
    
        for (; i < this->mtof_tilde_01_innerScala_sclEntryCount; i++) {
            number c = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
            n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_tilde_01_innerScala_refFreq);
    
            if (c <= hza && hza < n) {
                if (c != hza) {
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
    
                break;
            }
        }
    
        if (i == this->mtof_tilde_01_innerScala_sclEntryCount && n != hza) {
            number c = n;
            n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
        }
    
        number deg = i + octave * this->mtof_tilde_01_innerScala_sclEntryCount;
    
        {
            deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
            frac = 0.0;
        }
    
        return {deg, frac};
    }
    
    array<int, 2> mtof_tilde_01_innerScala_octdegree(int degree, int count) {
        int octave = 0;
        int index = 0;
    
        if (degree < 0) {
            octave = -(1 + (-1 - degree) / count);
            index = -degree % count;
    
            if (index > 0) {
                index = count - index;
            }
        } else {
            octave = degree / count;
            index = degree % count;
        }
    
        return {octave, index};
    }
    
    array<int, 2> mtof_tilde_01_innerScala_applyKBM(number note) {
        if ((this->mtof_tilde_01_innerScala_kbmMin == this->mtof_tilde_01_innerScala_kbmMax && this->mtof_tilde_01_innerScala_kbmMax == 0) || (note >= this->mtof_tilde_01_innerScala_kbmMin && note <= this->mtof_tilde_01_innerScala_kbmMax)) {
            int degree = (int)(rnbo_floor(note - this->mtof_tilde_01_innerScala_kbmMid));
    
            if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
                return {degree, 1};
            }
    
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmSize);
            int octave = (int)(octdeg[0]);
            Index index = (Index)(octdeg[1]);
    
            if (this->mtof_tilde_01_innerScala_kbmMapSize > index) {
                degree = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)(this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET + index)]);
    
                if (degree >= 0) {
                    return {degree + octave * this->mtof_tilde_01_innerScala_kbmOctaveDegree, 1};
                }
            }
        }
    
        return {-1, 0};
    }
    
    number mtof_tilde_01_innerScala_applySCL(int degree, number frac, number refFreq) {
        array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_sclEntryCount);
        return this->mtof_tilde_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
    }
    
    number mtof_tilde_01_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
        number p = 0;
    
        if (index > 0) {
            p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
        }
    
        if (frac > 0) {
            p = this->linearinterp(frac, p, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index]);
        } else if (frac < 0) {
            p = this->linearinterp(-frac, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index], p);
        }
    
        return refFreq * rnbo_pow(2, p + octave * this->mtof_tilde_01_innerScala_sclOctaveMul);
    }
    
    void mtof_tilde_01_innerScala_updateRefFreq() {
        this->mtof_tilde_01_innerScala_lastValid = false;
        int refOffset = (int)(this->mtof_tilde_01_innerScala_kbmRefNum - this->mtof_tilde_01_innerScala_kbmMid);
    
        if (refOffset == 0) {
            this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq;
        } else {
            int base = (int)(this->mtof_tilde_01_innerScala_kbmSize);
    
            if (base < 1) {
                base = this->mtof_tilde_01_innerScala_sclEntryCount;
            }
    
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(refOffset, base);
            number oct = (number)(octdeg[0]);
            int index = (int)(octdeg[1]);
    
            if (base > 0) {
                oct = oct + rnbo_floor(index / base);
                index = index % base;
            }
    
            if (index >= 0 && index < this->mtof_tilde_01_innerScala_kbmSize) {
                if (index < this->mtof_tilde_01_innerScala_kbmMapSize) {
                    index = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]);
                } else {
                    index = -1;
                }
            }
    
            if (index < 0 || index > this->mtof_tilde_01_innerScala_sclExpMul->length)
                {} else {
                number p = 0;
    
                if (index > 0) {
                    p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
                }
    
                this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_tilde_01_innerScala_sclOctaveMul);
            }
        }
    }
    
    void mtof_tilde_01_innerScala_reset() {
        this->mtof_tilde_01_innerScala_internal = true;
        this->mtof_tilde_01_innerScala_lastValid = false;
        this->mtof_tilde_01_innerScala_lastNote = 0;
        this->mtof_tilde_01_innerScala_lastFreq = 0;
        this->mtof_tilde_01_innerScala_sclEntryCount = 0;
        this->mtof_tilde_01_innerScala_sclOctaveMul = 1;
        this->mtof_tilde_01_innerScala_sclExpMul = {};
        this->mtof_tilde_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
        this->mtof_tilde_01_innerScala_kbmMid = 60;
        this->mtof_tilde_01_innerScala_kbmRefNum = 69;
        this->mtof_tilde_01_innerScala_kbmRefFreq = 440;
        this->mtof_tilde_01_innerScala_kbmSize = 0;
        this->mtof_tilde_01_innerScala_kbmMin = 0;
        this->mtof_tilde_01_innerScala_kbmMax = 0;
        this->mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
        this->mtof_tilde_01_innerScala_kbmMapSize = 0;
        this->mtof_tilde_01_innerScala_refFreq = 261.63;
    }
    
    void mtof_tilde_01_init() {
        this->mtof_tilde_01_innerScala_update(this->mtof_tilde_01_scale, this->mtof_tilde_01_map);
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void ip_01_init() {
        this->ip_01_lastValue = this->ip_01_value;
    }
    
    void ip_01_fillSigBuf() {
        if ((bool)(this->ip_01_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_01_lastIndex); i < k; i++) {
                if (this->ip_01_resetCount > 0) {
                    this->ip_01_sigbuf[(Index)i] = 1;
                    this->ip_01_resetCount--;
                } else {
                    this->ip_01_sigbuf[(Index)i] = this->ip_01_lastValue;
                }
            }
    
            this->ip_01_lastIndex = k;
        }
    }
    
    void ip_01_dspsetup(bool force) {
        if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_01_lastIndex = 0;
        this->ip_01_setupDone = true;
    }
    
    void param_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_07_value;
    }
    
    void param_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_07_value_set(preset["value"]);
    }
    
    void edge_01_dspsetup(bool force) {
        if ((bool)(this->edge_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->edge_01_setupDone = true;
    }
    
    void delta_tilde_01_reset() {
        this->delta_tilde_01_prev = 0;
    }
    
    void delta_tilde_01_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_01_reset();
        this->delta_tilde_01_setupDone = true;
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_08_in1 = 0;
        dspexpr_08_in2 = 0.5;
        p_01_target = 0;
        p_02_target = 0;
        gen_01_in1 = 0;
        gen_01_in2 = 0;
        gen_01_in3 = 0;
        p_03_target = 0;
        notein_01_channel = 0;
        mtof_tilde_01_midivalue = 0;
        mtof_tilde_01_base = 440;
        slide_tilde_01_x = 0;
        slide_tilde_01_up = 20;
        slide_tilde_01_down = 20;
        param_04_value = 880;
        slide_tilde_02_x = 0;
        slide_tilde_02_up = 20;
        slide_tilde_02_down = 20;
        param_05_value = 1.5;
        slide_tilde_03_x = 0;
        slide_tilde_03_up = 20;
        slide_tilde_03_down = 20;
        param_06_value = 3;
        ip_01_value = 0;
        ip_01_impulse = 0;
        expr_01_in1 = 0;
        expr_01_in2 = 127;
        expr_01_out1 = 0;
        slide_tilde_04_x = 0;
        slide_tilde_04_up = 20;
        slide_tilde_04_down = 20;
        param_07_value = 3;
        pack_01_in1 = 0;
        pack_01_in2 = 0;
        voice_01_mute_number = 0;
        snapshot_01_interval = 0;
        snapshot_01_out = 0;
        dspexpr_09_in1 = 0;
        dspexpr_09_in2 = 0;
        delta_tilde_01_x = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        gen_01_history_9_value = 0;
        gen_01_history_8_value = 0;
        gen_01_history_7_value = 0;
        gen_01_history_6_value = 0;
        gen_01_history_5_value = 0;
        gen_01_history_4_value = 0;
        gen_01_history_3_value = 0;
        gen_01_history_2_value = 0;
        gen_01_history_1_value = 0;
        gen_01_plusequals_70_value = 0;
        notein_01_status = 0;
        notein_01_byte1 = -1;
        notein_01_inchan = 0;
        mtof_tilde_01_innerMtoF_lastInValue = 0;
        mtof_tilde_01_innerMtoF_lastOutValue = 0;
        mtof_tilde_01_innerMtoF_lastTuning = 0;
        mtof_tilde_01_innerScala_internal = true;
        mtof_tilde_01_innerScala_lastValid = false;
        mtof_tilde_01_innerScala_lastNote = 0;
        mtof_tilde_01_innerScala_lastFreq = 0;
        mtof_tilde_01_innerScala_sclEntryCount = 0;
        mtof_tilde_01_innerScala_sclOctaveMul = 1;
        mtof_tilde_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
        mtof_tilde_01_innerScala_kbmMid = 60;
        mtof_tilde_01_innerScala_kbmRefNum = 69;
        mtof_tilde_01_innerScala_kbmRefFreq = 440;
        mtof_tilde_01_innerScala_kbmSize = 0;
        mtof_tilde_01_innerScala_kbmMin = 0;
        mtof_tilde_01_innerScala_kbmMax = 0;
        mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
        mtof_tilde_01_innerScala_kbmMapSize = 0;
        mtof_tilde_01_innerScala_refFreq = 261.63;
        slide_tilde_01_prev = 0;
        param_04_lastValue = 0;
        slide_tilde_02_prev = 0;
        param_05_lastValue = 0;
        slide_tilde_03_prev = 0;
        param_06_lastValue = 0;
        ip_01_lastIndex = 0;
        ip_01_lastValue = 0;
        ip_01_resetCount = 0;
        ip_01_sigbuf = nullptr;
        ip_01_setupDone = false;
        slide_tilde_04_prev = 0;
        param_07_lastValue = 0;
        snapshot_01_calc = 0;
        snapshot_01_nextTime = 0;
        snapshot_01_count = 0;
        snapshot_01_lastValue = 0;
        edge_01_setupDone = false;
        delta_tilde_01_prev = 0;
        delta_tilde_01_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_08_in1;
        number dspexpr_08_in2;
        number p_01_target;
        number p_02_target;
        number gen_01_in1;
        number gen_01_in2;
        number gen_01_in3;
        number p_03_target;
        number notein_01_channel;
        number mtof_tilde_01_midivalue;
        list mtof_tilde_01_scale;
        list mtof_tilde_01_map;
        number mtof_tilde_01_base;
        number slide_tilde_01_x;
        number slide_tilde_01_up;
        number slide_tilde_01_down;
        number param_04_value;
        number slide_tilde_02_x;
        number slide_tilde_02_up;
        number slide_tilde_02_down;
        number param_05_value;
        number slide_tilde_03_x;
        number slide_tilde_03_up;
        number slide_tilde_03_down;
        number param_06_value;
        number ip_01_value;
        number ip_01_impulse;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number slide_tilde_04_x;
        number slide_tilde_04_up;
        number slide_tilde_04_down;
        number param_07_value;
        number pack_01_in1;
        number pack_01_in2;
        number voice_01_mute_number;
        number snapshot_01_interval;
        number snapshot_01_out;
        number dspexpr_09_in1;
        number dspexpr_09_in2;
        number delta_tilde_01_x;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[7];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number gen_01_history_9_value;
        number gen_01_history_8_value;
        number gen_01_history_7_value;
        number gen_01_history_6_value;
        number gen_01_history_5_value;
        number gen_01_history_4_value;
        number gen_01_history_3_value;
        number gen_01_history_2_value;
        number gen_01_history_1_value;
        number gen_01_plusequals_70_value;
        int notein_01_status;
        int notein_01_byte1;
        int notein_01_inchan;
        number mtof_tilde_01_innerMtoF_lastInValue;
        number mtof_tilde_01_innerMtoF_lastOutValue;
        number mtof_tilde_01_innerMtoF_lastTuning;
        Float64BufferRef mtof_tilde_01_innerMtoF_buffer;
        bool mtof_tilde_01_innerScala_internal;
        const Index mtof_tilde_01_innerScala_KBM_MAP_OFFSET = 7;
        bool mtof_tilde_01_innerScala_lastValid;
        number mtof_tilde_01_innerScala_lastNote;
        number mtof_tilde_01_innerScala_lastFreq;
        int mtof_tilde_01_innerScala_sclEntryCount;
        number mtof_tilde_01_innerScala_sclOctaveMul;
        list mtof_tilde_01_innerScala_sclExpMul;
        list mtof_tilde_01_innerScala_kbmValid;
        int mtof_tilde_01_innerScala_kbmMid;
        int mtof_tilde_01_innerScala_kbmRefNum;
        number mtof_tilde_01_innerScala_kbmRefFreq;
        int mtof_tilde_01_innerScala_kbmSize;
        int mtof_tilde_01_innerScala_kbmMin;
        int mtof_tilde_01_innerScala_kbmMax;
        int mtof_tilde_01_innerScala_kbmOctaveDegree;
        Index mtof_tilde_01_innerScala_kbmMapSize;
        number mtof_tilde_01_innerScala_refFreq;
        number slide_tilde_01_prev;
        number param_04_lastValue;
        number slide_tilde_02_prev;
        number param_05_lastValue;
        number slide_tilde_03_prev;
        number param_06_lastValue;
        SampleIndex ip_01_lastIndex;
        number ip_01_lastValue;
        SampleIndex ip_01_resetCount;
        signal ip_01_sigbuf;
        bool ip_01_setupDone;
        number slide_tilde_04_prev;
        number param_07_lastValue;
        number snapshot_01_calc;
        number snapshot_01_nextTime;
        SampleIndex snapshot_01_count;
        number snapshot_01_lastValue;
        number edge_01_currentState;
        bool edge_01_setupDone;
        number delta_tilde_01_prev;
        bool delta_tilde_01_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_05* p_01;
        RNBOSubpatcher_06* p_02;
        RNBOSubpatcher_07* p_03;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    for (int i = 0; i < 8; i++) {
        delete poly[i];
    }
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo();
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

ParameterIndex getParameterIndexForID(ConstCharPointer paramid) const {
    if (!stringCompare(paramid, "cutoff")) {
        return 0;
    }

    if (!stringCompare(paramid, "overblow")) {
        return 1;
    }

    if (!stringCompare(paramid, "Q")) {
        return 2;
    }

    if (!stringCompare(paramid, "harmonics")) {
        return 3;
    }

    return INVALID_INDEX;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    SampleValue ** inputs,
    Index numInputs,
    SampleValue ** outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        this->setProbingIndex(-1);
        break;
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
    default:
        return nullptr;
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    this->RNBODefaultMtofLookupTable256 = initDataRef("RNBODefaultMtofLookupTable256", true, nullptr);
    this->assign_defaults();
    this->setState();
    this->RNBODefaultMtofLookupTable256->setIndex(0);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    for (Index i = 0; i < 8; i++) {
        this->poly[(Index)i] = new RNBOSubpatcher_08();
        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_08_getPresetValue(getSubState(preset, "cutoff"));
    this->param_09_getPresetValue(getSubState(preset, "overblow"));
    this->param_10_getPresetValue(getSubState(preset, "Q"));
    this->param_11_getPresetValue(getSubState(preset, "harmonics"));

    for (Index i = 0; i < 8; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_08_setPresetValue(getSubState(preset, "cutoff"));
    this->param_09_setPresetValue(getSubState(preset, "overblow"));
    this->param_10_setPresetValue(getSubState(preset, "Q"));
    this->param_11_setPresetValue(getSubState(preset, "harmonics"));

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_03->param_01_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "delay"), "left_delay")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_03->param_02_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "delay"), "fb")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_03->param_03_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "delay"), "right_delay")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(tempo, false)) {
        for (Index i = 0; i < 8; i++) {
            this->poly[i]->processTempoEvent(time, tempo);
        }
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(state, false)) {
        for (Index i = 0; i < 8; i++) {
            this->poly[i]->processTransportEvent(time, state);
        }
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(beattime, false)) {
        for (Index i = 0; i < 8; i++) {
            this->poly[i]->processBeatTimeEvent(time, beattime);
        }
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(numerator, denominator, false)) {
        for (Index i = 0; i < 8; i++) {
            this->poly[i]->processTimeSignatureEvent(time, numerator, denominator);
        }
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        this->param_08_value_set(v);
        break;
    case 1:
        this->param_09_value_set(v);
        break;
    case 2:
        this->param_10_value_set(v);
        break;
    case 3:
        this->param_11_value_set(v);
        break;
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue((PatcherInterface**)this->poly, index, v, time);

        break;
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        return this->param_08_value;
    case 1:
        return this->param_09_value;
    case 2:
        return this->param_10_value;
    case 3:
        return this->param_11_value;
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue((PatcherInterface**)this->poly, index);

        return 0;
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 4 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        return "cutoff";
    case 1:
        return "overblow";
    case 2:
        return "Q";
    case 3:
        return "harmonics";
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        return "cutoff";
    case 1:
        return "overblow";
    case 2:
        return "Q";
    case 3:
        return "harmonics";
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            info->type = ParameterTypeNumber;
            info->initialValue = 880;
            info->min = 100;
            info->max = 8000;
            info->exponent = 2;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
        case 1:
            info->type = ParameterTypeNumber;
            info->initialValue = 1.5;
            info->min = 0.1;
            info->max = 5;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
        case 2:
            info->type = ParameterTypeNumber;
            info->initialValue = 3;
            info->min = 0.01;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
        case 3:
            info->type = ParameterTypeNumber;
            info->initialValue = 3;
            info->min = 0.1;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
        default:
            index -= 4;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 8; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->poly[0])
        return 4;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
            value = (value < 100 ? 100 : (value > 8000 ? 8000 : value));
            ParameterValue normalizedValue = (value - 100) / (8000 - 100);

            {
                normalizedValue = rnbo_exp(rnbo_log(normalizedValue) * 1. / (number)2);
            }

            return normalizedValue;
        }
    case 1:
        {
            value = (value < 0.1 ? 0.1 : (value > 5 ? 5 : value));
            ParameterValue normalizedValue = (value - 0.1) / (5 - 0.1);
            return normalizedValue;
        }
    case 3:
        {
            value = (value < 0.1 ? 0.1 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 0.1) / (10 - 0.1);
            return normalizedValue;
        }
    case 2:
        {
            value = (value < 0.01 ? 0.01 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 0.01) / (10 - 0.01);
            return normalizedValue;
        }
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 100 + rnbo_exp(rnbo_log(value) * 2) * (8000 - 100);
            }
        }
    case 1:
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.1 + value * (5 - 0.1);
            }
        }
    case 3:
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.1 + value * (10 - 0.1);
            }
        }
    case 2:
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.01 + value * (10 - 0.01);
            }
        }
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        return this->param_08_value_constrain(value);
    case 1:
        return this->param_09_value_constrain(value);
    case 2:
        return this->param_10_value_constrain(value);
    case 3:
        return this->param_11_value_constrain(value);
    default:
        index -= 4;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterChange(
            this->paramInitIndices[i],
            this->getParameterValue(this->paramInitIndices[i]),
            0
        );
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 1;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        static const MessageInfo r0 = {
            "active",
            Outport
        };

        return r0;
    }

    return NullMessageInfo;
}

protected:

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(0, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->poly_cutoff_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(1, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->poly_overblow_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(2, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->poly_Q_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(3, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->poly_harmonics_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->initializeObjects();
    }
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->startup();
    }

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    this->processParamInitEvents();
}

static number param_08_value_constrain(number v) {
    v = (v > 8000 ? 8000 : (v < 100 ? 100 : v));
    return v;
}

void poly_cutoff_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(0, v, this->_currentTime);
        }
    }
}

static number param_09_value_constrain(number v) {
    v = (v > 5 ? 5 : (v < 0.1 ? 0.1 : v));
    return v;
}

void poly_overblow_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(1, v, this->_currentTime);
        }
    }
}

static number param_10_value_constrain(number v) {
    v = (v > 10 ? 10 : (v < 0.01 ? 0.01 : v));
    return v;
}

void poly_Q_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(2, v, this->_currentTime);
        }
    }
}

static number param_11_value_constrain(number v) {
    v = (v > 10 ? 10 : (v < 0.1 ? 0.1 : v));
    return v;
}

void poly_harmonics_set(number v) {
    for (number i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(3, v, this->_currentTime);
        }
    }
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 8) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 8; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

void midinotecontroller_01_voicestatus_set(const list& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void poly_voicestatus_set(const list& v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[i]->voice_01_mutein_list_set(v);
        }
    }

    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number v) {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->voice_01_activevoices_set(v);
    }
}

void poly_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 8; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 8) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

void midinotecontroller_01_mute_set(const list& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    int val = (int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
    case MIDI_SecondByteReceived:
        this->midinotecontroller_01_byte1 = val;
        break;
    case MIDI_NoteOn:
        {
            bool sendnoteoff = true;
            number target = 1;
            number oldest = this->midinotecontroller_01_voice_lastontime[0];
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Index i = 0; i < 8; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        number candidate_ontime = this->midinotecontroller_01_voice_lastontime[(Index)i];

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff((int)(target));

            int i = (int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->currenttime();
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend((int)(i));
            this->midinotecontroller_01_sendpressure((int)(i));
            this->midinotecontroller_01_sendtimbre((int)(i));
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((UBinOpInt)MIDI_NoteOnMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
    case MIDI_NoteOff:
        {
            number target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F);

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                int i = (int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
    case MIDI_Aftertouch:
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
    case MIDI_CC:
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 8; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((UBinOpInt)MIDI_NoteOffMask | (UBinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
            case MIDI_CC_TimbreMSB:
                {
                    number channel = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F);
                    int k = (int)(v);
                    number timbre = (BinOpInt)(((UBinOpInt)((UBinOpInt)k & (UBinOpInt)0x7F)) << (UBinOpInt)7);
                    this->midinotecontroller_01_channel_timbre[(Index)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F)] = timbre;

                    for (Index i = 0; i < 8; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
            case MIDI_CC_TimbreLSB:
                {
                    break;
                }
            case MIDI_CC_AllNotesOff:
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
    case MIDI_ProgramChange:
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
    case MIDI_ChannelPressure:
        {
            number channel = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F);

            for (number i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    int k = (int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
    case MIDI_PitchBend:
        {
            number bendamount = (BinOpInt)((UBinOpInt)this->midinotecontroller_01_byte1 | (UBinOpInt)((UBinOpInt)val << (UBinOpInt)7));
            int channel = (int)((BinOpInt)((UBinOpInt)this->midinotecontroller_01_status & (UBinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void poly_perform(Sample * out1, Sample * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 8; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 8; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 8; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(int target) {
    int i = (int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((UBinOpInt)MIDI_NoteOffMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(int v) {
    if (v >= 0 && v < 8) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        int totalbendamount = (int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((UBinOpInt)MIDI_PitchBendMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((UBinOpInt)totalbendamount & (UBinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((UBinOpInt)((UBinOpInt)totalbendamount >> (UBinOpInt)7) & (UBinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((UBinOpInt)MIDI_ChannelPressureMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((UBinOpInt)MIDI_CCMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((UBinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (UBinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((UBinOpInt)MIDI_CCMask | (UBinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((UBinOpInt)((UBinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> (UBinOpInt)7) & (UBinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Index i = 1; i <= 8; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    RNBO_UNUSED(sampleOffset);
    return (this->vs > 0 ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getTempo() {
    return this->globaltransport_getTempoAtSample(this->sampleOffsetIntoNextAudioBuffer);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    RNBO_UNUSED(sampleOffset);
    return (this->vs > 0 ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState() {
    return this->globaltransport_getStateAtSample(this->sampleOffsetIntoNextAudioBuffer);
}

number globaltransport_getBeatTimeAtMsTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState() == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(this->currenttime(), tempo);
        this->globaltransport_notify = true;
    } else if (this->globaltransport_getTempo() != tempo) {
        MillisecondTime ct = this->currenttime();
        this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTimeAtMsTime(ct));
        this->globaltransport_beatTimeChanges->push(ct);

        fillSignal(
            this->globaltransport_tempo,
            this->vs,
            tempo,
            (Index)(this->sampleOffsetIntoNextAudioBuffer)
        );

        this->globaltransport_lastTempo = tempo;
        this->globaltransport_tempoNeedsReset = true;
        return true;
    }

    return false;
}

number globaltransport_getBeatTime() {
    return this->globaltransport_getBeatTimeAtMsTime(this->currenttime());
}

bool globaltransport_setState(number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(this->currenttime(), TransportState(state));
        this->globaltransport_notify = true;
    } else if (this->globaltransport_getState() != state) {
        fillSignal(
            this->globaltransport_state,
            this->vs,
            state,
            (Index)(this->sampleOffsetIntoNextAudioBuffer)
        );

        this->globaltransport_lastState = TransportState(state);
        this->globaltransport_stateNeedsReset = true;

        if (state == 0) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime());
            this->globaltransport_beatTimeChanges->push(this->currenttime());
        }

        return true;
    }

    return false;
}

bool globaltransport_setBeatTime(number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(this->currenttime(), beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime());
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(this->currenttime());
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTimeAtMsTime(this->currenttime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignatureAtMsTime(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignature() {
    return this->globaltransport_getTimeSignatureAtMsTime(this->currenttime());
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignatureAtMsTime(this->currenttime() + msOffset);
}

bool globaltransport_setTimeSignature(number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(this->currenttime(), (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature();

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(this->currenttime());
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    midiin_port = 0;
    param_08_value = 880;
    param_09_value = 1.5;
    param_10_value = 3;
    param_11_value = 3;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number midiin_port;
    number param_08_value;
    number param_09_value;
    number param_10_value;
    number param_11_value;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    int poly_currentStatus;
    uint8_t poly_mididata[3];
    int midinotecontroller_01_currentStatus;
    int midinotecontroller_01_status;
    int midinotecontroller_01_byte1;
    int midinotecontroller_01_zone_masterchannel;
    int midinotecontroller_01_zone_numnotechannels;
    int midinotecontroller_01_zone_masterpitchbendrange;
    int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    number midinotecontroller_01_voice_lastontime[8] = { };
    number midinotecontroller_01_voice_notenumber[8] = { };
    number midinotecontroller_01_voice_channel[8] = { };
    number midinotecontroller_01_voice_state[8] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef RNBODefaultMtofLookupTable256;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_08* poly[8];

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

