/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_68 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_68()
    {
    }
    
    ~RNBOSubpatcher_68()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        this->linetilde_01_perform(this->signals[0], n);
        this->xfade_tilde_01_perform(this->signals[0], in1, in3, out1, n);
        this->xfade_tilde_02_perform(this->signals[0], in2, in4, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 1; i++) {
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
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
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
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
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
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
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
        case -62043057:
            {
            this->linetilde_01_target_bang();
            break;
            }
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
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("Mix~/number_obj-5") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("Mix~/number_obj-8") == objectId)
                this->numberobj_02_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("Mix~/number_obj-5") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("Mix~/number_obj-8") == objectId)
                this->numberobj_02_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("Mix~/number_obj-5"):
            {
            return "Mix~/number_obj-5";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("Mix~/number_obj-8"):
            {
            return "Mix~/number_obj-8";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
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
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_01_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void linetilde_01_target_bang() {}
    
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
        return 4;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_01_time_set(number v) {
        this->linetilde_01_time = v;
    }
    
    void linetilde_01_segments_set(const list& v) {
        this->linetilde_01_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_01_time == 0) {
                this->linetilde_01_activeRamps->length = 0;
                this->linetilde_01_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_01_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_01_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_01_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_01_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_01_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_01_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_01_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_01_activeRamps->push(lastRampValue);
                    this->linetilde_01_activeRamps->push(0);
                    this->linetilde_01_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_01_keepramp)) {
                            this->linetilde_01_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_01_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_01_activeRamps->push(destinationValue);
                    this->linetilde_01_activeRamps->push(inc);
                    this->linetilde_01_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_01_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_01_segments_set(converted);
        }
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-5"), localvalue, this->_currentTime);
        this->numberobj_01_output_set(localvalue);
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->numberobj_01_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
    
        this->expr_01_out1_set(
            (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
        );//#map:Mix~//_obj-7:1
    }
    
    void numberobj_02_output_set(number v) {
        this->expr_01_in1_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-8"), localvalue, this->_currentTime);
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-8"), localvalue, this->_currentTime);
        this->numberobj_02_output_set(localvalue);
    }
    
    void linetilde_01_perform(SampleValue * out, Index n) {
        auto __linetilde_01_time = this->linetilde_01_time;
        auto __linetilde_01_keepramp = this->linetilde_01_keepramp;
        auto __linetilde_01_currentValue = this->linetilde_01_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_01_activeRamps->length)) {
            while ((bool)(this->linetilde_01_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_01_activeRamps[0];
                number inc = this->linetilde_01_activeRamps[1];
                number rampTimeInSamples = this->linetilde_01_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_01_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_01_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_01_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_01_keepramp))) {
                            __linetilde_01_time = 0;
                        }
                    }
                }
    
                __linetilde_01_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_01_currentValue;
            i++;
        }
    
        this->linetilde_01_currentValue = __linetilde_01_currentValue;
        this->linetilde_01_time = __linetilde_01_time;
    }
    
    void xfade_tilde_01_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 1);
        }
    }
    
    void xfade_tilde_02_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 1);
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    number xfade_tilde_01_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_01_func_reset() {}
    
    number xfade_tilde_02_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_02_func_reset() {}
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Mix~/number_obj-5"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Mix~/number_obj-8"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
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
        xfade_tilde_01_pos = 0;
        xfade_tilde_02_pos = 0;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        expr_01_in1 = 0;
        expr_01_in2 = 100;
        expr_01_out1 = 0;
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        linetilde_01_time = 10;
        linetilde_01_keepramp = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        linetilde_01_currentValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number xfade_tilde_01_pos;
        number xfade_tilde_02_pos;
        number numberobj_01_value;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number numberobj_02_value;
        list linetilde_01_segments;
        number linetilde_01_time;
        number linetilde_01_keepramp;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[1];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        list linetilde_01_activeRamps;
        number linetilde_01_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_69 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_69()
    {
    }
    
    ~RNBOSubpatcher_69()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -871642103, false);
        getEngine()->flushClockEvents(this, -1494586265, false);
        getEngine()->flushClockEvents(this, 2098551528, false);
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        const SampleValue * in5 = (numInputs >= 5 && inputs[4] ? inputs[4] : this->zeroBuffer);
        this->dspexpr_03_perform(in5, this->dspexpr_03_in2, this->signals[0], n);
    
        this->rampsmooth_tilde_01_perform(
            this->signals[0],
            this->rampsmooth_tilde_01_up,
            this->rampsmooth_tilde_01_down,
            this->signals[1],
            n
        );
    
        this->dspexpr_01_perform(in1, in3, this->signals[1], out1, n);
        this->dspexpr_02_perform(in2, in4, this->signals[1], out2, n);
        this->numbertilde_01_perform(this->signals[0], this->dummyBuffer, n);
        this->numbertilde_02_perform(in5, this->dummyBuffer, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
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
    
        this->rampsmooth_tilde_01_dspsetup(forceDSPSetup);
        this->numbertilde_01_dspsetup(forceDSPSetup);
        this->numbertilde_02_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double samplerate) {
        this->translate_01_onSampleRateChanged(samplerate);
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->translate_01_onTempoChanged(tempo);
    }
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
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
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
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
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -871642103:
            {
            this->loadbang_01_startupbang_bang();
            break;
            }
        case -1494586265:
            {
            this->numbertilde_01_value_set(value);
            break;
            }
        case 2098551528:
            {
            this->numbertilde_02_value_set(value);
            break;
            }
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
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("Switch~/number~_obj-6") == objectId)
                this->numbertilde_01_sig_number_set(payload);
    
            if (TAG("Switch~/number~_obj-5") == objectId)
                this->numbertilde_02_sig_number_set(payload);
    
            break;
            }
        case TAG("mode"):
            {
            if (TAG("Switch~/number~_obj-6") == objectId)
                this->numbertilde_01_mode_set(payload);
    
            if (TAG("Switch~/number~_obj-5") == objectId)
                this->numbertilde_02_mode_set(payload);
    
            break;
            }
        case TAG("valin"):
            {
            if (TAG("Switch~/number_obj-112") == objectId)
                this->numberobj_03_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("Switch~/number_obj-112") == objectId)
                this->numberobj_03_format_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("Switch~/message_obj-110") == objectId)
                this->message_01_listin_number_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("Switch~/number~_obj-6") == objectId)
                this->numbertilde_01_sig_list_set(payload);
    
            if (TAG("Switch~/number~_obj-5") == objectId)
                this->numbertilde_02_sig_list_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("Switch~/message_obj-110") == objectId)
                this->message_01_listin_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("startupbang"):
            {
            if (TAG("Switch~/loadbang_obj-115") == objectId)
                this->loadbang_01_startupbang_bang();
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("Switch~/message_obj-110") == objectId)
                this->message_01_listin_bang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("monitor"):
            {
            return "monitor";
            }
        case TAG("Switch~/number~_obj-6"):
            {
            return "Switch~/number~_obj-6";
            }
        case TAG("assign"):
            {
            return "assign";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("Switch~/number~_obj-5"):
            {
            return "Switch~/number~_obj-5";
            }
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("Switch~/number_obj-112"):
            {
            return "Switch~/number_obj-112";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("Switch~/message_obj-110"):
            {
            return "Switch~/message_obj-110";
            }
        case TAG("sig"):
            {
            return "sig";
            }
        case TAG("mode"):
            {
            return "mode";
            }
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("Switch~/loadbang_obj-115"):
            {
            return "Switch~/loadbang_obj-115";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
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
    
    void numbertilde_01_sig_number_set(number v) {
        this->numbertilde_01_outValue = v;
    }
    
    void numbertilde_01_sig_list_set(const list& v) {
        this->numbertilde_01_outValue = v[0];
    }
    
    void numbertilde_01_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_01_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_01_currentMode = 1;
        }
    }
    
    void numbertilde_02_sig_number_set(number v) {
        this->numbertilde_02_outValue = v;
    }
    
    void numbertilde_02_sig_list_set(const list& v) {
        this->numbertilde_02_outValue = v[0];
    }
    
    void numbertilde_02_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_02_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_02_currentMode = 1;
        }
    }
    
    void loadbang_01_startupbang_bang() {
        this->loadbang_01_output_bang();
    }
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void message_01_listin_list_set(const list& v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_number_set(number v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_bang_bang() {
        this->message_01_trigger_bang();
    }
    
    void numbertilde_01_value_set(number ) {}
    
    void numbertilde_02_value_set(number ) {}
    
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
        return 5;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numbertilde_01_init();
        this->numbertilde_02_init();
        this->numberobj_03_init();
        this->message_01_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    }
    
    void allocateDataRefs() {}
    
    void rampsmooth_tilde_01_down_set(number v) {
        this->rampsmooth_tilde_01_down = v;
    }
    
    void rampsmooth_tilde_01_up_set(number v) {
        this->rampsmooth_tilde_01_up = v;
    }
    
    void numberobj_03_output_set(number v) {
        this->rampsmooth_tilde_01_down_set(v);
        this->rampsmooth_tilde_01_up_set(v);
    }
    
    void numberobj_03_value_set(number v) {
        this->numberobj_03_value_setter(v);
        v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("Switch~/number_obj-112"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void translate_01_out_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void translate_01_value_set(number v) {
        this->translate_01_value = v;
    
        {
            {
                {
                    {
                        {
                            this->translate_01_out_set(this->mstosamps(v));
                        }
                    }
                }
            }
        }
    }
    
    void message_01_out_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->translate_01_value_set(converted);
        }
    }
    
    void message_01_trigger_bang() {
        this->message_01_out_set(this->message_01_set);
    }
    
    void loadbang_01_output_bang() {
        this->message_01_trigger_bang();
    }
    
    void message_01_set_set(const list& v) {
        this->message_01_set = jsCreateListCopy(v);
        this->getEngine()->sendListMessage(TAG("listout"), TAG("Switch~/message_obj-110"), v, this->_currentTime);
    }
    
    void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] != 0;//#map:_###_obj_###_:1
        }
    }
    
    void rampsmooth_tilde_01_perform(const Sample * x, number up, number down, SampleValue * out1, Index n) {
        auto __rampsmooth_tilde_01_increment = this->rampsmooth_tilde_01_increment;
        auto __rampsmooth_tilde_01_index = this->rampsmooth_tilde_01_index;
        auto __rampsmooth_tilde_01_prev = this->rampsmooth_tilde_01_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (this->rampsmooth_tilde_01_d_next(x[(Index)i]) != 0.) {
                if (x[(Index)i] > __rampsmooth_tilde_01_prev) {
                    number _up = up;
    
                    if (_up < 1)
                        _up = 1;
    
                    __rampsmooth_tilde_01_index = _up;
                    __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _up;
                } else if (x[(Index)i] < __rampsmooth_tilde_01_prev) {
                    number _down = down;
    
                    if (_down < 1)
                        _down = 1;
    
                    __rampsmooth_tilde_01_index = _down;
                    __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _down;
                }
            }
    
            if (__rampsmooth_tilde_01_index > 0) {
                __rampsmooth_tilde_01_prev += __rampsmooth_tilde_01_increment;
                __rampsmooth_tilde_01_index -= 1;
            } else {
                __rampsmooth_tilde_01_prev = x[(Index)i];
            }
    
            out1[(Index)i] = __rampsmooth_tilde_01_prev;
        }
    
        this->rampsmooth_tilde_01_prev = __rampsmooth_tilde_01_prev;
        this->rampsmooth_tilde_01_index = __rampsmooth_tilde_01_index;
        this->rampsmooth_tilde_01_increment = __rampsmooth_tilde_01_increment;
    }
    
    void dspexpr_01_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        SampleValue * out1,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + in3[(Index)i] * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_02_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        SampleValue * out1,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + in3[(Index)i] * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
        auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
        auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
        auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
        auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
        auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_01_currentMode == 0) {
                output[(Index)i] = this->numbertilde_01_smooth_next(
                    __numbertilde_01_outValue,
                    __numbertilde_01_rampInSamples,
                    __numbertilde_01_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_01_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
            __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1494586265,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_01_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("Switch~/number~_obj-6"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
        this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
    }
    
    void numbertilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_02_currentIntervalInSamples = this->numbertilde_02_currentIntervalInSamples;
        auto __numbertilde_02_lastValue = this->numbertilde_02_lastValue;
        auto __numbertilde_02_currentInterval = this->numbertilde_02_currentInterval;
        auto __numbertilde_02_rampInSamples = this->numbertilde_02_rampInSamples;
        auto __numbertilde_02_outValue = this->numbertilde_02_outValue;
        auto __numbertilde_02_currentMode = this->numbertilde_02_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_02_currentMode == 0) {
                output[(Index)i] = this->numbertilde_02_smooth_next(
                    __numbertilde_02_outValue,
                    __numbertilde_02_rampInSamples,
                    __numbertilde_02_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_02_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_02_lastValue && __numbertilde_02_currentInterval <= 0) {
            __numbertilde_02_currentInterval = __numbertilde_02_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                2098551528,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_02_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("Switch~/number~_obj-5"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_02_currentInterval = __numbertilde_02_currentInterval;
        this->numbertilde_02_lastValue = __numbertilde_02_lastValue;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_03_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_03_value = localvalue;
    }
    
    number rampsmooth_tilde_01_d_next(number x) {
        number temp = (number)(x - this->rampsmooth_tilde_01_d_prev);
        this->rampsmooth_tilde_01_d_prev = x;
        return temp;
    }
    
    void rampsmooth_tilde_01_d_dspsetup() {
        this->rampsmooth_tilde_01_d_reset();
    }
    
    void rampsmooth_tilde_01_d_reset() {
        this->rampsmooth_tilde_01_d_prev = 0;
    }
    
    void rampsmooth_tilde_01_dspsetup(bool force) {
        if ((bool)(this->rampsmooth_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rampsmooth_tilde_01_setupDone = true;
        this->rampsmooth_tilde_01_d_dspsetup();
    }
    
    number numbertilde_01_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
        this->numbertilde_01_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_01_smooth_d_dspsetup() {
        this->numbertilde_01_smooth_d_reset();
    }
    
    void numbertilde_01_smooth_d_reset() {
        this->numbertilde_01_smooth_d_prev = 0;
    }
    
    number numbertilde_01_smooth_next(number x, number up, number down) {
        if (this->numbertilde_01_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_01_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_01_smooth_index = _up;
                this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
            } else if (x < this->numbertilde_01_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_01_smooth_index = _down;
                this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_01_smooth_index > 0) {
            this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
            this->numbertilde_01_smooth_index -= 1;
        } else {
            this->numbertilde_01_smooth_prev = x;
        }
    
        return this->numbertilde_01_smooth_prev;
    }
    
    void numbertilde_01_smooth_reset() {
        this->numbertilde_01_smooth_prev = 0;
        this->numbertilde_01_smooth_index = 0;
        this->numbertilde_01_smooth_increment = 0;
        this->numbertilde_01_smooth_d_reset();
    }
    
    void numbertilde_01_init() {
        this->numbertilde_01_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Switch~/number~_obj-6"), 1, this->_currentTime);
    }
    
    void numbertilde_01_dspsetup(bool force) {
        if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
        this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
        this->numbertilde_01_setupDone = true;
        this->numbertilde_01_smooth_d_dspsetup();
    }
    
    number numbertilde_02_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_02_smooth_d_prev);
        this->numbertilde_02_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_02_smooth_d_dspsetup() {
        this->numbertilde_02_smooth_d_reset();
    }
    
    void numbertilde_02_smooth_d_reset() {
        this->numbertilde_02_smooth_d_prev = 0;
    }
    
    number numbertilde_02_smooth_next(number x, number up, number down) {
        if (this->numbertilde_02_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_02_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_02_smooth_index = _up;
                this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _up;
            } else if (x < this->numbertilde_02_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_02_smooth_index = _down;
                this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_02_smooth_index > 0) {
            this->numbertilde_02_smooth_prev += this->numbertilde_02_smooth_increment;
            this->numbertilde_02_smooth_index -= 1;
        } else {
            this->numbertilde_02_smooth_prev = x;
        }
    
        return this->numbertilde_02_smooth_prev;
    }
    
    void numbertilde_02_smooth_reset() {
        this->numbertilde_02_smooth_prev = 0;
        this->numbertilde_02_smooth_index = 0;
        this->numbertilde_02_smooth_increment = 0;
        this->numbertilde_02_smooth_d_reset();
    }
    
    void numbertilde_02_init() {
        this->numbertilde_02_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Switch~/number~_obj-5"), 1, this->_currentTime);
    }
    
    void numbertilde_02_dspsetup(bool force) {
        if ((bool)(this->numbertilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_02_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_02_currentInterval = this->numbertilde_02_currentIntervalInSamples;
        this->numbertilde_02_rampInSamples = this->mstosamps(this->numbertilde_02_ramp);
        this->numbertilde_02_setupDone = true;
        this->numbertilde_02_smooth_d_dspsetup();
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Switch~/number_obj-112"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    void message_01_init() {
        this->message_01_set_set({50});
    }
    
    void translate_01_onTempoChanged(number ) {}
    
    void translate_01_onSampleRateChanged(number samplerate) {
        RNBO_UNUSED(samplerate);
    
        {
            this->translate_01_value_set(this->translate_01_value);
        }
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
        dspexpr_01_in3 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        dspexpr_02_in3 = 0;
        rampsmooth_tilde_01_x = 0;
        rampsmooth_tilde_01_up = 0;
        rampsmooth_tilde_01_down = 0;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0;
        numbertilde_01_input_number = 0;
        numbertilde_01_ramp = 0;
        numbertilde_02_input_number = 0;
        numbertilde_02_ramp = 0;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        translate_01_value = 0;
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
        rampsmooth_tilde_01_prev = 0;
        rampsmooth_tilde_01_index = 0;
        rampsmooth_tilde_01_increment = 0;
        rampsmooth_tilde_01_d_prev = 0;
        rampsmooth_tilde_01_setupDone = false;
        numbertilde_01_currentInterval = 0;
        numbertilde_01_currentIntervalInSamples = 0;
        numbertilde_01_lastValue = 0;
        numbertilde_01_outValue = 0;
        numbertilde_01_rampInSamples = 0;
        numbertilde_01_currentMode = 0;
        numbertilde_01_smooth_d_prev = 0;
        numbertilde_01_smooth_prev = 0;
        numbertilde_01_smooth_index = 0;
        numbertilde_01_smooth_increment = 0;
        numbertilde_01_setupDone = false;
        numbertilde_02_currentInterval = 0;
        numbertilde_02_currentIntervalInSamples = 0;
        numbertilde_02_lastValue = 0;
        numbertilde_02_outValue = 0;
        numbertilde_02_rampInSamples = 0;
        numbertilde_02_currentMode = 0;
        numbertilde_02_smooth_d_prev = 0;
        numbertilde_02_smooth_prev = 0;
        numbertilde_02_smooth_index = 0;
        numbertilde_02_smooth_increment = 0;
        numbertilde_02_setupDone = false;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_01_in3;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number dspexpr_02_in3;
        number rampsmooth_tilde_01_x;
        number rampsmooth_tilde_01_up;
        number rampsmooth_tilde_01_down;
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number numbertilde_01_input_number;
        number numbertilde_01_ramp;
        number numbertilde_02_input_number;
        number numbertilde_02_ramp;
        number numberobj_03_value;
        list message_01_set;
        number translate_01_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number rampsmooth_tilde_01_prev;
        number rampsmooth_tilde_01_index;
        number rampsmooth_tilde_01_increment;
        number rampsmooth_tilde_01_d_prev;
        bool rampsmooth_tilde_01_setupDone;
        SampleIndex numbertilde_01_currentInterval;
        SampleIndex numbertilde_01_currentIntervalInSamples;
        number numbertilde_01_lastValue;
        number numbertilde_01_outValue;
        number numbertilde_01_rampInSamples;
        Int numbertilde_01_currentMode;
        number numbertilde_01_smooth_d_prev;
        number numbertilde_01_smooth_prev;
        number numbertilde_01_smooth_index;
        number numbertilde_01_smooth_increment;
        bool numbertilde_01_setupDone;
        SampleIndex numbertilde_02_currentInterval;
        SampleIndex numbertilde_02_currentIntervalInSamples;
        number numbertilde_02_lastValue;
        number numbertilde_02_outValue;
        number numbertilde_02_rampInSamples;
        Int numbertilde_02_currentMode;
        number numbertilde_02_smooth_d_prev;
        number numbertilde_02_smooth_prev;
        number numbertilde_02_smooth_index;
        number numbertilde_02_smooth_increment;
        bool numbertilde_02_setupDone;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_70 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_70()
    {
    }
    
    ~RNBOSubpatcher_70()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numOutputs);
        RNBO_UNUSED(outputs);
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
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
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
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
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("FreqCalc/number_obj-118") == objectId)
                this->numberobj_04_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-107") == objectId)
                this->numberobj_05_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-90") == objectId)
                this->numberobj_06_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-81") == objectId)
                this->numberobj_07_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-78") == objectId)
                this->numberobj_08_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-71") == objectId)
                this->numberobj_09_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-92") == objectId)
                this->numberobj_10_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-119") == objectId)
                this->numberobj_11_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-87") == objectId)
                this->numberobj_12_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-77") == objectId)
                this->numberobj_13_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-84") == objectId)
                this->numberobj_14_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-70") == objectId)
                this->numberobj_15_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-98") == objectId)
                this->numberobj_16_valin_set(payload);
    
            if (TAG("FreqCalc/number_obj-100") == objectId)
                this->numberobj_17_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("FreqCalc/number_obj-118") == objectId)
                this->numberobj_04_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-107") == objectId)
                this->numberobj_05_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-90") == objectId)
                this->numberobj_06_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-81") == objectId)
                this->numberobj_07_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-78") == objectId)
                this->numberobj_08_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-71") == objectId)
                this->numberobj_09_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-92") == objectId)
                this->numberobj_10_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-119") == objectId)
                this->numberobj_11_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-87") == objectId)
                this->numberobj_12_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-77") == objectId)
                this->numberobj_13_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-84") == objectId)
                this->numberobj_14_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-70") == objectId)
                this->numberobj_15_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-98") == objectId)
                this->numberobj_16_format_set(payload);
    
            if (TAG("FreqCalc/number_obj-100") == objectId)
                this->numberobj_17_format_set(payload);
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("FreqCalc/message_obj-3") == objectId)
                this->message_02_listin_number_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("FreqCalc/message_obj-3") == objectId)
                this->message_02_listin_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("FreqCalc/message_obj-3") == objectId)
                this->message_02_listin_bang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("FreqCalc/number_obj-118"):
            {
            return "FreqCalc/number_obj-118";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("FreqCalc/number_obj-107"):
            {
            return "FreqCalc/number_obj-107";
            }
        case TAG("FreqCalc/number_obj-90"):
            {
            return "FreqCalc/number_obj-90";
            }
        case TAG("FreqCalc/number_obj-81"):
            {
            return "FreqCalc/number_obj-81";
            }
        case TAG("FreqCalc/number_obj-78"):
            {
            return "FreqCalc/number_obj-78";
            }
        case TAG("FreqCalc/number_obj-71"):
            {
            return "FreqCalc/number_obj-71";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("FreqCalc/message_obj-3"):
            {
            return "FreqCalc/message_obj-3";
            }
        case TAG("FreqCalc/number_obj-92"):
            {
            return "FreqCalc/number_obj-92";
            }
        case TAG("FreqCalc/number_obj-119"):
            {
            return "FreqCalc/number_obj-119";
            }
        case TAG("FreqCalc/number_obj-87"):
            {
            return "FreqCalc/number_obj-87";
            }
        case TAG("FreqCalc/number_obj-77"):
            {
            return "FreqCalc/number_obj-77";
            }
        case TAG("FreqCalc/number_obj-84"):
            {
            return "FreqCalc/number_obj-84";
            }
        case TAG("FreqCalc/number_obj-70"):
            {
            return "FreqCalc/number_obj-70";
            }
        case TAG("FreqCalc/number_obj-98"):
            {
            return "FreqCalc/number_obj-98";
            }
        case TAG("FreqCalc/number_obj-100"):
            {
            return "FreqCalc/number_obj-100";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
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
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_07_valin_set(number v) {
        this->numberobj_07_value_set(v);
    }
    
    void numberobj_07_format_set(number v) {
        this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_08_valin_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void numberobj_08_format_set(number v) {
        this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_09_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_09_value_set(converted);
        }
    }
    
    void numberobj_09_valin_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void numberobj_09_format_set(number v) {
        this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void message_02_listin_list_set(const list& v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_number_set(number v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_bang_bang() {
        this->message_02_trigger_bang();
    }
    
    void numberobj_10_valin_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void numberobj_10_format_set(number v) {
        this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_11_valin_set(number v) {
        this->numberobj_11_value_set(v);
    }
    
    void numberobj_11_format_set(number v) {
        this->numberobj_11_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_12_valin_set(number v) {
        this->numberobj_12_value_set(v);
    }
    
    void numberobj_12_format_set(number v) {
        this->numberobj_12_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_13_valin_set(number v) {
        this->numberobj_13_value_set(v);
    }
    
    void numberobj_13_format_set(number v) {
        this->numberobj_13_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_14_valin_set(number v) {
        this->numberobj_14_value_set(v);
    }
    
    void numberobj_14_format_set(number v) {
        this->numberobj_14_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->numberobj_15_value_bang();
    }
    
    void eventinlet_03_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_15_value_set(converted);
        }
    }
    
    void numberobj_15_valin_set(number v) {
        this->numberobj_15_value_set(v);
    }
    
    void numberobj_15_format_set(number v) {
        this->numberobj_15_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_16_valin_set(number v) {
        this->numberobj_16_value_set(v);
    }
    
    void numberobj_16_format_set(number v) {
        this->numberobj_16_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_17_valin_set(number v) {
        this->numberobj_17_value_set(v);
    }
    
    void numberobj_17_format_set(number v) {
        this->numberobj_17_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->numberobj_17_value_bang();
    }
    
    void eventinlet_04_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_17_value_set(converted);
        }
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
        return 0;
    }
    
    void initializeObjects() {
        this->numberobj_04_init();
        this->numberobj_05_init();
        this->numberobj_06_init();
        this->numberobj_07_init();
        this->numberobj_08_init();
        this->numberobj_09_init();
        this->message_02_init();
        this->numberobj_10_init();
        this->numberobj_11_init();
        this->numberobj_12_init();
        this->numberobj_13_init();
        this->numberobj_14_init();
        this->numberobj_15_init();
        this->numberobj_16_init();
        this->numberobj_17_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void eventoutlet_02_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_03_out2_number_set(v);
    }
    
    void numberobj_10_output_set(number v) {
        this->eventoutlet_02_in1_number_set(v);
    }
    
    void numberobj_10_value_set(number v) {
        this->numberobj_10_value_setter(v);
        v = this->numberobj_10_value;
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-92"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_10_output_set(localvalue);
    }
    
    void message_02_out_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_10_value_set(converted);
        }
    }
    
    void message_02_trigger_bang() {
        this->message_02_out_set(this->message_02_set);
    }
    
    void select_01_match1_bang() {
        this->message_02_trigger_bang();
    }
    
    void select_01_nomatch_number_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void select_01_input_number_set(number v) {
        if (v == this->select_01_test1)
            this->select_01_match1_bang();
        else
            this->select_01_nomatch_number_set(v);
    }
    
    void expr_07_out1_set(number v) {
        this->expr_07_out1 = v;
        this->select_01_input_number_set(this->expr_07_out1);
    }
    
    void expr_07_in1_set(number in1) {
        this->expr_07_in1 = in1;
    
        this->expr_07_out1_set(
            (this->expr_07_in2 == 0 ? 0 : (this->expr_07_in2 == 0. ? 0. : this->expr_07_in1 / this->expr_07_in2))
        );//#map:FreqCalc//_obj-93:1
    }
    
    void expr_07_in2_set(number v) {
        this->expr_07_in2 = v;
        this->expr_07_in1_set(this->expr_07_in1);
    }
    
    void numberobj_11_output_set(number v) {
        this->expr_07_in2_set(v);
    }
    
    void numberobj_11_value_set(number v) {
        this->numberobj_11_value_setter(v);
        v = this->numberobj_11_value;
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-119"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_11_output_set(localvalue);
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->numberobj_11_value_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
        this->expr_08_out1_set(this->expr_08_in2 - this->expr_08_in1);//#map:FreqCalc/!-_obj-117:1
    }
    
    void numberobj_12_output_set(number v) {
        this->expr_08_in1_set(v);
    }
    
    void numberobj_12_value_set(number v) {
        this->numberobj_12_value_setter(v);
        v = this->numberobj_12_value;
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-87"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_12_output_set(localvalue);
    }
    
    void expr_09_out1_set(number v) {
        this->expr_09_out1 = v;
        this->numberobj_12_value_set(this->expr_09_out1);
    }
    
    void expr_09_in1_set(number in1) {
        this->expr_09_in1 = in1;
        this->expr_09_out1_set(fixnan(rnbo_pow(2, this->expr_09_in1 / (number)1200)));//#map:FreqCalc/expr_obj-86:1
    }
    
    void numberobj_13_output_set(number v) {
        this->expr_09_in1_set(v);
    }
    
    void numberobj_13_value_set(number v) {
        this->numberobj_13_value_setter(v);
        v = this->numberobj_13_value;
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-77"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_13_output_set(localvalue);
    }
    
    void expr_10_out1_set(number v) {
        this->expr_10_out1 = v;
        this->numberobj_13_value_set(this->expr_10_out1);
    }
    
    void expr_10_in1_set(number in1) {
        this->expr_10_in1 = in1;
        this->expr_10_out1_set(this->expr_10_in1 + this->expr_10_in2);//#map:FreqCalc/+_obj-79:1
    }
    
    void eventoutlet_01_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_03_out1_number_set(v);
    }
    
    void numberobj_05_output_set(number v) {
        this->eventoutlet_01_in1_number_set(v);
    }
    
    void numberobj_05_value_set(number v) {
        this->numberobj_05_value_setter(v);
        v = this->numberobj_05_value;
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-107"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->numberobj_05_value_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
    
        this->expr_03_out1_set(
            (this->expr_03_in2 == 0 ? 0 : (this->expr_03_in2 == 0. ? 0. : this->expr_03_in1 / this->expr_03_in2))
        );//#map:FreqCalc//_obj-108:1
    }
    
    void numberobj_04_output_set(number v) {
        this->expr_07_in1_set(v);
        this->expr_03_in1_set(v);
    }
    
    void numberobj_04_value_set(number v) {
        this->numberobj_04_value_setter(v);
        v = this->numberobj_04_value;
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-118"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_04_output_set(localvalue);
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->numberobj_04_value_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(this->expr_02_in2 - this->expr_02_in1);//#map:FreqCalc/!-_obj-115:1
    }
    
    void numberobj_06_output_set(number v) {
        this->expr_02_in1_set(v);
    }
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-90"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->numberobj_06_value_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
        this->expr_04_out1_set(fixnan(rnbo_pow(2, this->expr_04_in1 / (number)1200)));//#map:FreqCalc/expr_obj-89:1
    }
    
    void numberobj_08_output_set(number v) {
        this->expr_04_in1_set(v);
    }
    
    void numberobj_08_value_set(number v) {
        this->numberobj_08_value_setter(v);
        v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-78"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_08_output_set(localvalue);
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->numberobj_08_value_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
        this->expr_05_out1_set(this->expr_05_in1 - this->expr_05_in2);//#map:FreqCalc/-_obj-80:1
    }
    
    void numberobj_07_output_set(number v) {
        this->expr_10_in1_set(v);
        this->expr_05_in1_set(v);
    }
    
    void numberobj_07_value_set(number v) {
        this->numberobj_07_value_setter(v);
        v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-81"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_07_output_set(localvalue);
    }
    
    void expr_06_out1_set(number v) {
        this->expr_06_out1 = v;
        this->numberobj_07_value_set(this->expr_06_out1);
    }
    
    void expr_06_in1_set(number in1) {
        this->expr_06_in1 = in1;
        this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:FreqCalc/*_obj-76:1
    }
    
    void numberobj_09_output_set(number v) {
        this->expr_06_in1_set(v);
    }
    
    void numberobj_09_value_set(number v) {
        this->numberobj_09_value_setter(v);
        v = this->numberobj_09_value;
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-71"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_09_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void expr_10_in2_set(number v) {
        this->expr_10_in2 = v;
        this->expr_10_in1_set(this->expr_10_in1);
    }
    
    void expr_05_in2_set(number v) {
        this->expr_05_in2 = v;
        this->expr_05_in1_set(this->expr_05_in1);
    }
    
    void numberobj_14_output_set(number v) {
        this->expr_10_in2_set(v);
        this->expr_05_in2_set(v);
    }
    
    void numberobj_14_value_set(number v) {
        this->numberobj_14_value_setter(v);
        v = this->numberobj_14_value;
        number localvalue = v;
    
        if (this->numberobj_14_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-84"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_14_output_set(localvalue);
    }
    
    void expr_11_out1_set(number v) {
        this->expr_11_out1 = v;
        this->numberobj_14_value_set(this->expr_11_out1);
    }
    
    void expr_11_in1_set(number in1) {
        this->expr_11_in1 = in1;
    
        this->expr_11_out1_set(
            (this->expr_11_in2 == 0 ? 0 : (this->expr_11_in2 == 0. ? 0. : this->expr_11_in1 / this->expr_11_in2))
        );//#map:FreqCalc//_obj-83:1
    }
    
    void numberobj_15_output_set(number v) {
        this->expr_11_in1_set(v);
    }
    
    void numberobj_15_value_set(number v) {
        this->numberobj_15_value_setter(v);
        v = this->numberobj_15_value;
        number localvalue = v;
    
        if (this->numberobj_15_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-70"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_15_output_set(localvalue);
    }
    
    void eventinlet_03_out1_number_set(number v) {
        this->numberobj_15_value_set(v);
    }
    
    void expr_03_in2_set(number v) {
        this->expr_03_in2 = v;
        this->expr_03_in1_set(this->expr_03_in1);
    }
    
    void numberobj_16_output_set(number v) {
        this->expr_03_in2_set(v);
    }
    
    void numberobj_16_value_set(number v) {
        this->numberobj_16_value_setter(v);
        v = this->numberobj_16_value;
        number localvalue = v;
    
        if (this->numberobj_16_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-98"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_16_output_set(localvalue);
    }
    
    void expr_12_out1_set(number v) {
        this->expr_12_out1 = v;
        this->numberobj_16_value_set(this->expr_12_out1);
    }
    
    void expr_12_in1_set(number in1) {
        this->expr_12_in1 = in1;
    
        this->expr_12_out1_set(
            (this->expr_12_in2 == 0 ? 0 : (this->expr_12_in2 == 0. ? 0. : this->expr_12_in1 / this->expr_12_in2))
        );//#map:FreqCalc//_obj-99:1
    }
    
    void numberobj_17_output_set(number v) {
        this->expr_12_in1_set(v);
    }
    
    void numberobj_17_value_set(number v) {
        this->numberobj_17_value_setter(v);
        v = this->numberobj_17_value;
        number localvalue = v;
    
        if (this->numberobj_17_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-100"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_17_output_set(localvalue);
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->numberobj_17_value_set(v);
    }
    
    void numberobj_09_value_bang() {
        number v = this->numberobj_09_value;
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-71"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_09_output_set(localvalue);
    }
    
    void message_02_set_set(const list& v) {
        this->message_02_set = jsCreateListCopy(v);
        this->getEngine()->sendListMessage(TAG("listout"), TAG("FreqCalc/message_obj-3"), v, this->_currentTime);
    }
    
    void numberobj_15_value_bang() {
        number v = this->numberobj_15_value;
        number localvalue = v;
    
        if (this->numberobj_15_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-70"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_15_output_set(localvalue);
    }
    
    void numberobj_17_value_bang() {
        number v = this->numberobj_17_value;
        number localvalue = v;
    
        if (this->numberobj_17_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("FreqCalc/number_obj-100"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_17_output_set(localvalue);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_04_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_04_value = localvalue;
    }
    
    void numberobj_05_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_05_value = localvalue;
    }
    
    void numberobj_06_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_value = localvalue;
    }
    
    void numberobj_07_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_07_value = localvalue;
    }
    
    void numberobj_08_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_value = localvalue;
    }
    
    void numberobj_09_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_09_value = localvalue;
    }
    
    void numberobj_10_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_value = localvalue;
    }
    
    void numberobj_11_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_11_value = localvalue;
    }
    
    void numberobj_12_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_12_value = localvalue;
    }
    
    void numberobj_13_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_13_value = localvalue;
    }
    
    void numberobj_14_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_14_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_14_value = localvalue;
    }
    
    void numberobj_15_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_15_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_15_value = localvalue;
    }
    
    void numberobj_16_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_16_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_16_value = localvalue;
    }
    
    void numberobj_17_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_17_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_17_value = localvalue;
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-118"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void numberobj_05_init() {
        this->numberobj_05_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-107"), 1, this->_currentTime);
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
    }
    
    void numberobj_06_init() {
        this->numberobj_06_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-90"), 1, this->_currentTime);
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
    }
    
    void numberobj_07_init() {
        this->numberobj_07_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-81"), 1, this->_currentTime);
    }
    
    void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_07_value;
    }
    
    void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_07_value_set(preset["value"]);
    }
    
    void numberobj_08_init() {
        this->numberobj_08_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-78"), 1, this->_currentTime);
    }
    
    void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_08_value;
    }
    
    void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_08_value_set(preset["value"]);
    }
    
    void numberobj_09_init() {
        this->numberobj_09_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-71"), 1, this->_currentTime);
    }
    
    void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_09_value;
    }
    
    void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_09_value_set(preset["value"]);
    }
    
    void message_02_init() {
        this->message_02_set_set({1});
    }
    
    void numberobj_10_init() {
        this->numberobj_10_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-92"), 1, this->_currentTime);
    }
    
    void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_10_value;
    }
    
    void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_10_value_set(preset["value"]);
    }
    
    void numberobj_11_init() {
        this->numberobj_11_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-119"), 1, this->_currentTime);
    }
    
    void numberobj_11_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_11_value;
    }
    
    void numberobj_11_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_11_value_set(preset["value"]);
    }
    
    void numberobj_12_init() {
        this->numberobj_12_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-87"), 1, this->_currentTime);
    }
    
    void numberobj_12_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_12_value;
    }
    
    void numberobj_12_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_12_value_set(preset["value"]);
    }
    
    void numberobj_13_init() {
        this->numberobj_13_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-77"), 1, this->_currentTime);
    }
    
    void numberobj_13_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_13_value;
    }
    
    void numberobj_13_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_13_value_set(preset["value"]);
    }
    
    void numberobj_14_init() {
        this->numberobj_14_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-84"), 1, this->_currentTime);
    }
    
    void numberobj_14_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_14_value;
    }
    
    void numberobj_14_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_14_value_set(preset["value"]);
    }
    
    void numberobj_15_init() {
        this->numberobj_15_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-70"), 1, this->_currentTime);
    }
    
    void numberobj_15_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_15_value;
    }
    
    void numberobj_15_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_15_value_set(preset["value"]);
    }
    
    void numberobj_16_init() {
        this->numberobj_16_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-98"), 1, this->_currentTime);
    }
    
    void numberobj_16_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_16_value;
    }
    
    void numberobj_16_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_16_value_set(preset["value"]);
    }
    
    void numberobj_17_init() {
        this->numberobj_17_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("FreqCalc/number_obj-100"), 1, this->_currentTime);
    }
    
    void numberobj_17_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_17_value;
    }
    
    void numberobj_17_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_17_value_set(preset["value"]);
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
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        expr_02_in1 = 0;
        expr_02_in2 = 1;
        expr_02_out1 = 0;
        numberobj_05_value = 0;
        numberobj_05_value_setter(numberobj_05_value);
        expr_03_in1 = 0;
        expr_03_in2 = 1;
        expr_03_out1 = 0;
        expr_04_in1 = 0;
        expr_04_out1 = 0;
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        numberobj_07_value = 0;
        numberobj_07_value_setter(numberobj_07_value);
        numberobj_08_value = 0;
        numberobj_08_value_setter(numberobj_08_value);
        expr_05_in1 = 0;
        expr_05_in2 = 0;
        expr_05_out1 = 0;
        expr_06_in1 = 0;
        expr_06_in2 = 100;
        expr_06_out1 = 0;
        numberobj_09_value = 0;
        numberobj_09_value_setter(numberobj_09_value);
        select_01_test1 = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 1;
        expr_07_out1 = 0;
        numberobj_10_value = 0;
        numberobj_10_value_setter(numberobj_10_value);
        numberobj_11_value = 0;
        numberobj_11_value_setter(numberobj_11_value);
        expr_08_in1 = 0;
        expr_08_in2 = 1;
        expr_08_out1 = 0;
        expr_09_in1 = 0;
        expr_09_out1 = 0;
        numberobj_12_value = 0;
        numberobj_12_value_setter(numberobj_12_value);
        numberobj_13_value = 0;
        numberobj_13_value_setter(numberobj_13_value);
        expr_10_in1 = 0;
        expr_10_in2 = 0;
        expr_10_out1 = 0;
        numberobj_14_value = 0;
        numberobj_14_value_setter(numberobj_14_value);
        expr_11_in1 = 0;
        expr_11_in2 = 2;
        expr_11_out1 = 0;
        numberobj_15_value = 0;
        numberobj_15_value_setter(numberobj_15_value);
        numberobj_16_value = 0;
        numberobj_16_value_setter(numberobj_16_value);
        expr_12_in1 = 0;
        expr_12_in2 = 1000;
        expr_12_out1 = 0;
        numberobj_17_value = 0;
        numberobj_17_value_setter(numberobj_17_value);
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
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        numberobj_05_currentFormat = 6;
        numberobj_05_lastValue = 0;
        numberobj_06_currentFormat = 6;
        numberobj_06_lastValue = 0;
        numberobj_07_currentFormat = 6;
        numberobj_07_lastValue = 0;
        numberobj_08_currentFormat = 6;
        numberobj_08_lastValue = 0;
        numberobj_09_currentFormat = 6;
        numberobj_09_lastValue = 0;
        numberobj_10_currentFormat = 6;
        numberobj_10_lastValue = 0;
        numberobj_11_currentFormat = 6;
        numberobj_11_lastValue = 0;
        numberobj_12_currentFormat = 6;
        numberobj_12_lastValue = 0;
        numberobj_13_currentFormat = 6;
        numberobj_13_lastValue = 0;
        numberobj_14_currentFormat = 6;
        numberobj_14_lastValue = 0;
        numberobj_15_currentFormat = 6;
        numberobj_15_lastValue = 0;
        numberobj_16_currentFormat = 6;
        numberobj_16_lastValue = 0;
        numberobj_17_currentFormat = 6;
        numberobj_17_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number numberobj_04_value;
        number expr_02_in1;
        number expr_02_in2;
        number expr_02_out1;
        number numberobj_05_value;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number expr_04_in1;
        number expr_04_out1;
        number numberobj_06_value;
        number numberobj_07_value;
        number numberobj_08_value;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        number expr_06_in1;
        number expr_06_in2;
        number expr_06_out1;
        number numberobj_09_value;
        list message_02_set;
        number select_01_test1;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number numberobj_10_value;
        number numberobj_11_value;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number expr_09_in1;
        number expr_09_out1;
        number numberobj_12_value;
        number numberobj_13_value;
        number expr_10_in1;
        number expr_10_in2;
        number expr_10_out1;
        number numberobj_14_value;
        number expr_11_in1;
        number expr_11_in2;
        number expr_11_out1;
        number numberobj_15_value;
        number numberobj_16_value;
        number expr_12_in1;
        number expr_12_in2;
        number expr_12_out1;
        number numberobj_17_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        Int numberobj_05_currentFormat;
        number numberobj_05_lastValue;
        Int numberobj_06_currentFormat;
        number numberobj_06_lastValue;
        Int numberobj_07_currentFormat;
        number numberobj_07_lastValue;
        Int numberobj_08_currentFormat;
        number numberobj_08_lastValue;
        Int numberobj_09_currentFormat;
        number numberobj_09_lastValue;
        Int numberobj_10_currentFormat;
        number numberobj_10_lastValue;
        Int numberobj_11_currentFormat;
        number numberobj_11_lastValue;
        Int numberobj_12_currentFormat;
        number numberobj_12_lastValue;
        Int numberobj_13_currentFormat;
        number numberobj_13_lastValue;
        Int numberobj_14_currentFormat;
        number numberobj_14_lastValue;
        Int numberobj_15_currentFormat;
        number numberobj_15_lastValue;
        Int numberobj_16_currentFormat;
        number numberobj_16_lastValue;
        Int numberobj_17_currentFormat;
        number numberobj_17_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_71 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_71()
    {
    }
    
    ~RNBOSubpatcher_71()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1494586265, false);
        getEngine()->flushClockEvents(this, 2098551528, false);
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number cubicinterp(number a, number w, number x, number y, number z) {
        number a1 = 1. + a;
        number aa = a * a1;
        number b = 1. - a;
        number b1 = 2. - a;
        number bb = b * b1;
        number fw = -.1666667 * bb * a;
        number fx = .5 * bb * a1;
        number fy = .5 * aa * b1;
        number fz = -.1666667 * aa * b;
        return w * fw + x * fx + y * fy + z * fz;
    }
    
    inline number fastcubicinterp(number a, number w, number x, number y, number z) {
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
    
    inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
        number ym2py2 = y0 + y4;
        number ym1py1 = y1 + y3;
        number y2mym2 = y4 - y0;
        number y1mym1 = y3 - y1;
        number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
        number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
        number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
        number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
        number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
        number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
        number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
        return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
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
    
    number samplerate() const {
        return this->sr;
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        this->scopetilde_01_perform(in2, this->zeroBuffer, n);
        this->welch_tilde_01_perform(in2, this->signals[0], n);
        this->scopetilde_03_perform(this->signals[0], this->zeroBuffer, n);
        this->dspexpr_09_perform(in2, this->dspexpr_09_in2, this->signals[1], n);
    
        this->wrap_tilde_01_perform(
            this->signals[1],
            this->wrap_tilde_01_low,
            this->wrap_tilde_01_high,
            this->signals[2],
            n
        );
    
        this->welch_tilde_02_perform(this->signals[2], this->signals[1], n);
        this->scopetilde_02_perform(this->signals[1], this->zeroBuffer, n);
        this->dspexpr_08_perform(this->signals[2], in3, this->signals[3], n);
        this->numbertilde_04_perform(this->signals[3], this->dummyBuffer, n);
        this->delaytilde_02_perform(this->signals[3], in1, this->signals[2], n);
        this->dspexpr_07_perform(this->signals[2], this->signals[1], this->signals[3], n);
        this->dspexpr_06_perform(in2, in3, this->signals[1], n);
        this->numbertilde_03_perform(this->signals[1], this->dummyBuffer, n);
        this->delaytilde_01_perform(this->signals[1], in1, this->signals[2], n);
        this->dspexpr_05_perform(this->signals[2], this->signals[0], this->signals[1], n);
        this->dspexpr_04_perform(this->signals[1], this->signals[3], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
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
    
        this->scopetilde_01_dspsetup(forceDSPSetup);
        this->scopetilde_03_dspsetup(forceDSPSetup);
        this->scopetilde_02_dspsetup(forceDSPSetup);
        this->numbertilde_04_dspsetup(forceDSPSetup);
        this->delaytilde_02_dspsetup(forceDSPSetup);
        this->numbertilde_03_dspsetup(forceDSPSetup);
        this->delaytilde_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
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
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
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
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1494586265:
            {
            this->numbertilde_04_value_set(value);
            break;
            }
        case 2098551528:
            {
            this->numbertilde_03_value_set(value);
            break;
            }
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
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("PitchShift~[1]/number~_obj-64") == objectId)
                this->numbertilde_03_sig_number_set(payload);
    
            if (TAG("PitchShift~[1]/number~_obj-65") == objectId)
                this->numbertilde_04_sig_number_set(payload);
    
            break;
            }
        case TAG("mode"):
            {
            if (TAG("PitchShift~[1]/number~_obj-64") == objectId)
                this->numbertilde_03_mode_set(payload);
    
            if (TAG("PitchShift~[1]/number~_obj-65") == objectId)
                this->numbertilde_04_mode_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("PitchShift~[1]/number~_obj-64") == objectId)
                this->numbertilde_03_sig_list_set(payload);
    
            if (TAG("PitchShift~[1]/number~_obj-65") == objectId)
                this->numbertilde_04_sig_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("monitor"):
            {
            return "monitor";
            }
        case TAG("PitchShift~[1]/number~_obj-64"):
            {
            return "PitchShift~[1]/number~_obj-64";
            }
        case TAG("assign"):
            {
            return "assign";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("PitchShift~[1]/scope~_obj-62"):
            {
            return "PitchShift~[1]/scope~_obj-62";
            }
        case TAG("PitchShift~[1]/number~_obj-65"):
            {
            return "PitchShift~[1]/number~_obj-65";
            }
        case TAG("PitchShift~[1]/scope~_obj-60"):
            {
            return "PitchShift~[1]/scope~_obj-60";
            }
        case TAG("PitchShift~[1]/scope~_obj-61"):
            {
            return "PitchShift~[1]/scope~_obj-61";
            }
        case TAG("sig"):
            {
            return "sig";
            }
        case TAG("mode"):
            {
            return "mode";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 0:
            {
            return addressOf(this->delaytilde_01_del_bufferobj);
            break;
            }
        case 1:
            {
            return addressOf(this->delaytilde_02_del_bufferobj);
            break;
            }
        default:
            {
            return nullptr;
            }
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
    
        if (index == 0) {
            this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
        }
    
        if (index == 1) {
            this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
        }
    }
    
    void initialize() {
        this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr, "buffer~");
        this->delaytilde_02_del_bufferobj = initDataRef("delaytilde_02_del_bufferobj", true, nullptr, "buffer~");
        this->assign_defaults();
        this->setState();
        this->delaytilde_01_del_bufferobj->setIndex(0);
        this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
        this->delaytilde_02_del_bufferobj->setIndex(1);
        this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
    }
    
    protected:
    
    void numbertilde_03_sig_number_set(number v) {
        this->numbertilde_03_outValue = v;
    }
    
    void numbertilde_03_sig_list_set(const list& v) {
        this->numbertilde_03_outValue = v[0];
    }
    
    void numbertilde_03_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_03_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_03_currentMode = 1;
        }
    }
    
    void numbertilde_04_sig_number_set(number v) {
        this->numbertilde_04_outValue = v;
    }
    
    void numbertilde_04_sig_list_set(const list& v) {
        this->numbertilde_04_outValue = v[0];
    }
    
    void numbertilde_04_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_04_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_04_currentMode = 1;
        }
    }
    
    void numbertilde_04_value_set(number ) {}
    
    void numbertilde_03_value_set(number ) {}
    
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
    
    void initializeObjects() {
        this->delaytilde_01_del_init();
        this->numbertilde_03_init();
        this->delaytilde_02_del_init();
        this->numbertilde_04_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();
    
        if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
            if (this->delaytilde_01_del_bufferobj->wantsFill())
                this->zeroDataRef(this->delaytilde_01_del_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(0);
        }
    
        this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();
    
        if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
            if (this->delaytilde_02_del_bufferobj->wantsFill())
                this->zeroDataRef(this->delaytilde_02_del_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(1);
        }
    }
    
    void scopetilde_01_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_01_ysign = this->scopetilde_01_ysign;
        auto __scopetilde_01_ymonitorvalue = this->scopetilde_01_ymonitorvalue;
        auto __scopetilde_01_xsign = this->scopetilde_01_xsign;
        auto __scopetilde_01_xmonitorvalue = this->scopetilde_01_xmonitorvalue;
        auto __scopetilde_01_mode = this->scopetilde_01_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_01_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_01_xmonitorvalue) {
                    __scopetilde_01_xmonitorvalue = xabsval;
                    __scopetilde_01_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_01_ymonitorvalue) {
                    __scopetilde_01_ymonitorvalue = yabsval;
                    __scopetilde_01_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_01_xmonitorvalue = xval;
                __scopetilde_01_xsign = 1;
                __scopetilde_01_ymonitorvalue = yval;
                __scopetilde_01_ysign = 1;
            }
    
            this->scopetilde_01_effectiveCount--;
    
            if (this->scopetilde_01_effectiveCount <= 0) {
                this->scopetilde_01_updateEffectiveCount();
                this->scopetilde_01_monitorbuffer->push(__scopetilde_01_xmonitorvalue * __scopetilde_01_xsign);
    
                if (__scopetilde_01_mode == 1)
                    __scopetilde_01_xmonitorvalue = 0;
    
                if (this->scopetilde_01_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~[1]/scope~_obj-62"),
                        this->scopetilde_01_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_01_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_01_xmonitorvalue = __scopetilde_01_xmonitorvalue;
        this->scopetilde_01_xsign = __scopetilde_01_xsign;
        this->scopetilde_01_ymonitorvalue = __scopetilde_01_ymonitorvalue;
        this->scopetilde_01_ysign = __scopetilde_01_ysign;
    }
    
    void welch_tilde_01_perform(const Sample * x, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number __x = x[(Index)i];
            __x = (__x > 1 ? 1 : (__x < 0 ? 0 : __x));
            number w = (__x - 0.5) * 2;
            out1[(Index)i] = 1 - w * w;
        }
    }
    
    void scopetilde_03_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_03_ysign = this->scopetilde_03_ysign;
        auto __scopetilde_03_ymonitorvalue = this->scopetilde_03_ymonitorvalue;
        auto __scopetilde_03_xsign = this->scopetilde_03_xsign;
        auto __scopetilde_03_xmonitorvalue = this->scopetilde_03_xmonitorvalue;
        auto __scopetilde_03_mode = this->scopetilde_03_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_03_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_03_xmonitorvalue) {
                    __scopetilde_03_xmonitorvalue = xabsval;
                    __scopetilde_03_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_03_ymonitorvalue) {
                    __scopetilde_03_ymonitorvalue = yabsval;
                    __scopetilde_03_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_03_xmonitorvalue = xval;
                __scopetilde_03_xsign = 1;
                __scopetilde_03_ymonitorvalue = yval;
                __scopetilde_03_ysign = 1;
            }
    
            this->scopetilde_03_effectiveCount--;
    
            if (this->scopetilde_03_effectiveCount <= 0) {
                this->scopetilde_03_updateEffectiveCount();
                this->scopetilde_03_monitorbuffer->push(__scopetilde_03_xmonitorvalue * __scopetilde_03_xsign);
    
                if (__scopetilde_03_mode == 1)
                    __scopetilde_03_xmonitorvalue = 0;
    
                if (this->scopetilde_03_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~[1]/scope~_obj-61"),
                        this->scopetilde_03_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_03_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_03_xmonitorvalue = __scopetilde_03_xmonitorvalue;
        this->scopetilde_03_xsign = __scopetilde_03_xsign;
        this->scopetilde_03_ymonitorvalue = __scopetilde_03_ymonitorvalue;
        this->scopetilde_03_ysign = __scopetilde_03_ysign;
    }
    
    void dspexpr_09_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + -0.5;//#map:_###_obj_###_:1
        }
    }
    
    void wrap_tilde_01_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void welch_tilde_02_perform(const Sample * x, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number __x = x[(Index)i];
            __x = (__x > 1 ? 1 : (__x < 0 ? 0 : __x));
            number w = (__x - 0.5) * 2;
            out1[(Index)i] = 1 - w * w;
        }
    }
    
    void scopetilde_02_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_02_ysign = this->scopetilde_02_ysign;
        auto __scopetilde_02_ymonitorvalue = this->scopetilde_02_ymonitorvalue;
        auto __scopetilde_02_xsign = this->scopetilde_02_xsign;
        auto __scopetilde_02_xmonitorvalue = this->scopetilde_02_xmonitorvalue;
        auto __scopetilde_02_mode = this->scopetilde_02_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_02_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_02_xmonitorvalue) {
                    __scopetilde_02_xmonitorvalue = xabsval;
                    __scopetilde_02_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_02_ymonitorvalue) {
                    __scopetilde_02_ymonitorvalue = yabsval;
                    __scopetilde_02_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_02_xmonitorvalue = xval;
                __scopetilde_02_xsign = 1;
                __scopetilde_02_ymonitorvalue = yval;
                __scopetilde_02_ysign = 1;
            }
    
            this->scopetilde_02_effectiveCount--;
    
            if (this->scopetilde_02_effectiveCount <= 0) {
                this->scopetilde_02_updateEffectiveCount();
                this->scopetilde_02_monitorbuffer->push(__scopetilde_02_xmonitorvalue * __scopetilde_02_xsign);
    
                if (__scopetilde_02_mode == 1)
                    __scopetilde_02_xmonitorvalue = 0;
    
                if (this->scopetilde_02_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~[1]/scope~_obj-60"),
                        this->scopetilde_02_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_02_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_02_xmonitorvalue = __scopetilde_02_xmonitorvalue;
        this->scopetilde_02_xsign = __scopetilde_02_xsign;
        this->scopetilde_02_ymonitorvalue = __scopetilde_02_ymonitorvalue;
        this->scopetilde_02_ysign = __scopetilde_02_ysign;
    }
    
    void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numbertilde_04_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_04_currentIntervalInSamples = this->numbertilde_04_currentIntervalInSamples;
        auto __numbertilde_04_lastValue = this->numbertilde_04_lastValue;
        auto __numbertilde_04_currentInterval = this->numbertilde_04_currentInterval;
        auto __numbertilde_04_rampInSamples = this->numbertilde_04_rampInSamples;
        auto __numbertilde_04_outValue = this->numbertilde_04_outValue;
        auto __numbertilde_04_currentMode = this->numbertilde_04_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_04_currentMode == 0) {
                output[(Index)i] = this->numbertilde_04_smooth_next(
                    __numbertilde_04_outValue,
                    __numbertilde_04_rampInSamples,
                    __numbertilde_04_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_04_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_04_lastValue && __numbertilde_04_currentInterval <= 0) {
            __numbertilde_04_currentInterval = __numbertilde_04_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1494586265,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_04_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("PitchShift~[1]/number~_obj-65"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_04_currentInterval = __numbertilde_04_currentInterval;
        this->numbertilde_04_lastValue = __numbertilde_04_lastValue;
    }
    
    void delaytilde_02_perform(
        const Sample * delay,
        const SampleValue * input,
        SampleValue * output,
        Index n
    ) {
        auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
        auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
        auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
        auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;
    
        for (Index i = 0; i < n; i++) {
            if (__delaytilde_02_lastDelay == -1) {
                __delaytilde_02_lastDelay = delay[(Index)i];
            }
    
            if (__delaytilde_02_ramp > 0) {
                number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
                output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
                __delaytilde_02_ramp--;
            } else {
                number effectiveDelay = delay[(Index)i];
    
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
    
    void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numbertilde_03_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_03_currentIntervalInSamples = this->numbertilde_03_currentIntervalInSamples;
        auto __numbertilde_03_lastValue = this->numbertilde_03_lastValue;
        auto __numbertilde_03_currentInterval = this->numbertilde_03_currentInterval;
        auto __numbertilde_03_rampInSamples = this->numbertilde_03_rampInSamples;
        auto __numbertilde_03_outValue = this->numbertilde_03_outValue;
        auto __numbertilde_03_currentMode = this->numbertilde_03_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_03_currentMode == 0) {
                output[(Index)i] = this->numbertilde_03_smooth_next(
                    __numbertilde_03_outValue,
                    __numbertilde_03_rampInSamples,
                    __numbertilde_03_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_03_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_03_lastValue && __numbertilde_03_currentInterval <= 0) {
            __numbertilde_03_currentInterval = __numbertilde_03_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                2098551528,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_03_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("PitchShift~[1]/number~_obj-64"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_03_currentInterval = __numbertilde_03_currentInterval;
        this->numbertilde_03_lastValue = __numbertilde_03_lastValue;
    }
    
    void delaytilde_01_perform(
        const Sample * delay,
        const SampleValue * input,
        SampleValue * output,
        Index n
    ) {
        auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
        auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
        auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
        auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;
    
        for (Index i = 0; i < n; i++) {
            if (__delaytilde_01_lastDelay == -1) {
                __delaytilde_01_lastDelay = delay[(Index)i];
            }
    
            if (__delaytilde_01_ramp > 0) {
                number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
                __delaytilde_01_ramp--;
            } else {
                number effectiveDelay = delay[(Index)i];
    
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
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
            ));
        } else if (interp == 6) {
            number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->fastcubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
            ));
        } else if (interp == 7) {
            number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
            Index index5 = (Index)(index4 + 1);
            Index index6 = (Index)(index5 + 1);
    
            return this->spline6interp(frac, this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_01_del_wrap))
            ));
        } else if (interp == 3) {
            number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
    
            return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
            ), this->delaytilde_01_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
            ));
        }
    
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
    
        return this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
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
    
        this->delaytilde_01_rampInSamples = (long)(this->mstosamps(0));
        this->delaytilde_01_lastDelay = -1;
        this->delaytilde_01_setupDone = true;
        this->delaytilde_01_del_dspsetup();
    }
    
    number numbertilde_03_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_03_smooth_d_prev);
        this->numbertilde_03_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_03_smooth_d_dspsetup() {
        this->numbertilde_03_smooth_d_reset();
    }
    
    void numbertilde_03_smooth_d_reset() {
        this->numbertilde_03_smooth_d_prev = 0;
    }
    
    number numbertilde_03_smooth_next(number x, number up, number down) {
        if (this->numbertilde_03_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_03_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_03_smooth_index = _up;
                this->numbertilde_03_smooth_increment = (x - this->numbertilde_03_smooth_prev) / _up;
            } else if (x < this->numbertilde_03_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_03_smooth_index = _down;
                this->numbertilde_03_smooth_increment = (x - this->numbertilde_03_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_03_smooth_index > 0) {
            this->numbertilde_03_smooth_prev += this->numbertilde_03_smooth_increment;
            this->numbertilde_03_smooth_index -= 1;
        } else {
            this->numbertilde_03_smooth_prev = x;
        }
    
        return this->numbertilde_03_smooth_prev;
    }
    
    void numbertilde_03_smooth_reset() {
        this->numbertilde_03_smooth_prev = 0;
        this->numbertilde_03_smooth_index = 0;
        this->numbertilde_03_smooth_increment = 0;
        this->numbertilde_03_smooth_d_reset();
    }
    
    void numbertilde_03_init() {
        this->numbertilde_03_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("PitchShift~[1]/number~_obj-64"), 1, this->_currentTime);
    }
    
    void numbertilde_03_dspsetup(bool force) {
        if ((bool)(this->numbertilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_03_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_03_currentInterval = this->numbertilde_03_currentIntervalInSamples;
        this->numbertilde_03_rampInSamples = this->mstosamps(this->numbertilde_03_ramp);
        this->numbertilde_03_setupDone = true;
        this->numbertilde_03_smooth_d_dspsetup();
    }
    
    void scopetilde_01_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_01_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_01_dspsetup(bool force) {
        if ((bool)(this->scopetilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_01_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~[1]/scope~_obj-62"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_01_mode},
            this->_currentTime
        );;
    
        this->scopetilde_01_updateEffectiveCount();
        this->scopetilde_01_setupDone = true;
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
            ));
        } else if (interp == 6) {
            number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->fastcubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
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
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
            ));
        } else if (interp == 7) {
            number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
            Index index5 = (Index)(index4 + 1);
            Index index6 = (Index)(index5 + 1);
    
            return this->spline6interp(frac, this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_02_del_wrap))
            ));
        } else if (interp == 3) {
            number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
    
            return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
            ), this->delaytilde_02_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
            ));
        }
    
        number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
    
        return this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
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
    
        this->delaytilde_02_rampInSamples = (long)(this->mstosamps(0));
        this->delaytilde_02_lastDelay = -1;
        this->delaytilde_02_setupDone = true;
        this->delaytilde_02_del_dspsetup();
    }
    
    number numbertilde_04_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_04_smooth_d_prev);
        this->numbertilde_04_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_04_smooth_d_dspsetup() {
        this->numbertilde_04_smooth_d_reset();
    }
    
    void numbertilde_04_smooth_d_reset() {
        this->numbertilde_04_smooth_d_prev = 0;
    }
    
    number numbertilde_04_smooth_next(number x, number up, number down) {
        if (this->numbertilde_04_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_04_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_04_smooth_index = _up;
                this->numbertilde_04_smooth_increment = (x - this->numbertilde_04_smooth_prev) / _up;
            } else if (x < this->numbertilde_04_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_04_smooth_index = _down;
                this->numbertilde_04_smooth_increment = (x - this->numbertilde_04_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_04_smooth_index > 0) {
            this->numbertilde_04_smooth_prev += this->numbertilde_04_smooth_increment;
            this->numbertilde_04_smooth_index -= 1;
        } else {
            this->numbertilde_04_smooth_prev = x;
        }
    
        return this->numbertilde_04_smooth_prev;
    }
    
    void numbertilde_04_smooth_reset() {
        this->numbertilde_04_smooth_prev = 0;
        this->numbertilde_04_smooth_index = 0;
        this->numbertilde_04_smooth_increment = 0;
        this->numbertilde_04_smooth_d_reset();
    }
    
    void numbertilde_04_init() {
        this->numbertilde_04_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("PitchShift~[1]/number~_obj-65"), 1, this->_currentTime);
    }
    
    void numbertilde_04_dspsetup(bool force) {
        if ((bool)(this->numbertilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_04_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_04_currentInterval = this->numbertilde_04_currentIntervalInSamples;
        this->numbertilde_04_rampInSamples = this->mstosamps(this->numbertilde_04_ramp);
        this->numbertilde_04_setupDone = true;
        this->numbertilde_04_smooth_d_dspsetup();
    }
    
    void scopetilde_02_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_02_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_02_dspsetup(bool force) {
        if ((bool)(this->scopetilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_02_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~[1]/scope~_obj-60"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_02_mode},
            this->_currentTime
        );;
    
        this->scopetilde_02_updateEffectiveCount();
        this->scopetilde_02_setupDone = true;
    }
    
    void scopetilde_03_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_03_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_03_dspsetup(bool force) {
        if ((bool)(this->scopetilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_03_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~[1]/scope~_obj-61"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_03_mode},
            this->_currentTime
        );;
    
        this->scopetilde_03_updateEffectiveCount();
        this->scopetilde_03_setupDone = true;
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
        dspexpr_04_in2 = 0;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        delaytilde_01_delay = 0;
        numbertilde_03_input_number = 0;
        numbertilde_03_ramp = 0;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        welch_tilde_01_x = 0;
        dspexpr_07_in1 = 0;
        dspexpr_07_in2 = 0;
        delaytilde_02_delay = 0;
        numbertilde_04_input_number = 0;
        numbertilde_04_ramp = 0;
        dspexpr_08_in1 = 0;
        dspexpr_08_in2 = 0;
        welch_tilde_02_x = 0;
        wrap_tilde_01_x = 0;
        wrap_tilde_01_low = 0;
        wrap_tilde_01_high = 1;
        dspexpr_09_in1 = 0;
        dspexpr_09_in2 = -0.5;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
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
        numbertilde_03_currentInterval = 0;
        numbertilde_03_currentIntervalInSamples = 0;
        numbertilde_03_lastValue = 0;
        numbertilde_03_outValue = 0;
        numbertilde_03_rampInSamples = 0;
        numbertilde_03_currentMode = 0;
        numbertilde_03_smooth_d_prev = 0;
        numbertilde_03_smooth_prev = 0;
        numbertilde_03_smooth_index = 0;
        numbertilde_03_smooth_increment = 0;
        numbertilde_03_setupDone = false;
        scopetilde_01_lastValue = 0;
        scopetilde_01_effectiveCount = 256;
        scopetilde_01_xsign = 1;
        scopetilde_01_ysign = 1;
        scopetilde_01_mode = 0;
        scopetilde_01_setupDone = false;
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
        numbertilde_04_currentInterval = 0;
        numbertilde_04_currentIntervalInSamples = 0;
        numbertilde_04_lastValue = 0;
        numbertilde_04_outValue = 0;
        numbertilde_04_rampInSamples = 0;
        numbertilde_04_currentMode = 0;
        numbertilde_04_smooth_d_prev = 0;
        numbertilde_04_smooth_prev = 0;
        numbertilde_04_smooth_index = 0;
        numbertilde_04_smooth_increment = 0;
        numbertilde_04_setupDone = false;
        scopetilde_02_lastValue = 0;
        scopetilde_02_effectiveCount = 256;
        scopetilde_02_xsign = 1;
        scopetilde_02_ysign = 1;
        scopetilde_02_mode = 0;
        scopetilde_02_setupDone = false;
        scopetilde_03_lastValue = 0;
        scopetilde_03_effectiveCount = 256;
        scopetilde_03_xsign = 1;
        scopetilde_03_ysign = 1;
        scopetilde_03_mode = 0;
        scopetilde_03_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number delaytilde_01_delay;
        number numbertilde_03_input_number;
        number numbertilde_03_ramp;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number welch_tilde_01_x;
        number dspexpr_07_in1;
        number dspexpr_07_in2;
        number delaytilde_02_delay;
        number numbertilde_04_input_number;
        number numbertilde_04_ramp;
        number dspexpr_08_in1;
        number dspexpr_08_in2;
        number welch_tilde_02_x;
        number wrap_tilde_01_x;
        number wrap_tilde_01_low;
        number wrap_tilde_01_high;
        number dspexpr_09_in1;
        number dspexpr_09_in2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
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
        SampleIndex numbertilde_03_currentInterval;
        SampleIndex numbertilde_03_currentIntervalInSamples;
        number numbertilde_03_lastValue;
        number numbertilde_03_outValue;
        number numbertilde_03_rampInSamples;
        Int numbertilde_03_currentMode;
        number numbertilde_03_smooth_d_prev;
        number numbertilde_03_smooth_prev;
        number numbertilde_03_smooth_index;
        number numbertilde_03_smooth_increment;
        bool numbertilde_03_setupDone;
        number scopetilde_01_lastValue;
        number scopetilde_01_effectiveCount;
        number scopetilde_01_xmonitorvalue;
        number scopetilde_01_ymonitorvalue;
        list scopetilde_01_monitorbuffer;
        number scopetilde_01_xsign;
        number scopetilde_01_ysign;
        Int scopetilde_01_mode;
        bool scopetilde_01_setupDone;
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
        SampleIndex numbertilde_04_currentInterval;
        SampleIndex numbertilde_04_currentIntervalInSamples;
        number numbertilde_04_lastValue;
        number numbertilde_04_outValue;
        number numbertilde_04_rampInSamples;
        Int numbertilde_04_currentMode;
        number numbertilde_04_smooth_d_prev;
        number numbertilde_04_smooth_prev;
        number numbertilde_04_smooth_index;
        number numbertilde_04_smooth_increment;
        bool numbertilde_04_setupDone;
        number scopetilde_02_lastValue;
        number scopetilde_02_effectiveCount;
        number scopetilde_02_xmonitorvalue;
        number scopetilde_02_ymonitorvalue;
        list scopetilde_02_monitorbuffer;
        number scopetilde_02_xsign;
        number scopetilde_02_ysign;
        Int scopetilde_02_mode;
        bool scopetilde_02_setupDone;
        number scopetilde_03_lastValue;
        number scopetilde_03_effectiveCount;
        number scopetilde_03_xmonitorvalue;
        number scopetilde_03_ymonitorvalue;
        list scopetilde_03_monitorbuffer;
        number scopetilde_03_xsign;
        number scopetilde_03_ysign;
        Int scopetilde_03_mode;
        bool scopetilde_03_setupDone;
        number stackprotect_count;
        DataRef delaytilde_01_del_bufferobj;
        DataRef delaytilde_02_del_bufferobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_72 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_72()
    {
    }
    
    ~RNBOSubpatcher_72()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1494586265, false);
        getEngine()->flushClockEvents(this, 2098551528, false);
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number cubicinterp(number a, number w, number x, number y, number z) {
        number a1 = 1. + a;
        number aa = a * a1;
        number b = 1. - a;
        number b1 = 2. - a;
        number bb = b * b1;
        number fw = -.1666667 * bb * a;
        number fx = .5 * bb * a1;
        number fy = .5 * aa * b1;
        number fz = -.1666667 * aa * b;
        return w * fw + x * fx + y * fy + z * fz;
    }
    
    inline number fastcubicinterp(number a, number w, number x, number y, number z) {
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
    
    inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
        number ym2py2 = y0 + y4;
        number ym1py1 = y1 + y3;
        number y2mym2 = y4 - y0;
        number y1mym1 = y3 - y1;
        number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
        number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
        number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
        number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
        number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
        number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
        number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
        return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
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
    
    number samplerate() const {
        return this->sr;
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        this->scopetilde_04_perform(in2, this->zeroBuffer, n);
        this->welch_tilde_03_perform(in2, this->signals[0], n);
        this->scopetilde_06_perform(this->signals[0], this->zeroBuffer, n);
        this->dspexpr_15_perform(in2, this->dspexpr_15_in2, this->signals[1], n);
    
        this->wrap_tilde_02_perform(
            this->signals[1],
            this->wrap_tilde_02_low,
            this->wrap_tilde_02_high,
            this->signals[2],
            n
        );
    
        this->welch_tilde_04_perform(this->signals[2], this->signals[1], n);
        this->scopetilde_05_perform(this->signals[1], this->zeroBuffer, n);
        this->dspexpr_14_perform(this->signals[2], in3, this->signals[3], n);
        this->numbertilde_06_perform(this->signals[3], this->dummyBuffer, n);
        this->delaytilde_04_perform(this->signals[3], in1, this->signals[2], n);
        this->dspexpr_13_perform(this->signals[2], this->signals[1], this->signals[3], n);
        this->dspexpr_12_perform(in2, in3, this->signals[1], n);
        this->numbertilde_05_perform(this->signals[1], this->dummyBuffer, n);
        this->delaytilde_03_perform(this->signals[1], in1, this->signals[2], n);
        this->dspexpr_11_perform(this->signals[2], this->signals[0], this->signals[1], n);
        this->dspexpr_10_perform(this->signals[1], this->signals[3], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
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
    
        this->scopetilde_04_dspsetup(forceDSPSetup);
        this->scopetilde_06_dspsetup(forceDSPSetup);
        this->scopetilde_05_dspsetup(forceDSPSetup);
        this->numbertilde_06_dspsetup(forceDSPSetup);
        this->delaytilde_04_dspsetup(forceDSPSetup);
        this->numbertilde_05_dspsetup(forceDSPSetup);
        this->delaytilde_03_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
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
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
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
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1494586265:
            {
            this->numbertilde_06_value_set(value);
            break;
            }
        case 2098551528:
            {
            this->numbertilde_05_value_set(value);
            break;
            }
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
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("PitchShift~/number~_obj-64") == objectId)
                this->numbertilde_05_sig_number_set(payload);
    
            if (TAG("PitchShift~/number~_obj-65") == objectId)
                this->numbertilde_06_sig_number_set(payload);
    
            break;
            }
        case TAG("mode"):
            {
            if (TAG("PitchShift~/number~_obj-64") == objectId)
                this->numbertilde_05_mode_set(payload);
    
            if (TAG("PitchShift~/number~_obj-65") == objectId)
                this->numbertilde_06_mode_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("sig"):
            {
            if (TAG("PitchShift~/number~_obj-64") == objectId)
                this->numbertilde_05_sig_list_set(payload);
    
            if (TAG("PitchShift~/number~_obj-65") == objectId)
                this->numbertilde_06_sig_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("monitor"):
            {
            return "monitor";
            }
        case TAG("PitchShift~/number~_obj-64"):
            {
            return "PitchShift~/number~_obj-64";
            }
        case TAG("assign"):
            {
            return "assign";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("PitchShift~/scope~_obj-62"):
            {
            return "PitchShift~/scope~_obj-62";
            }
        case TAG("PitchShift~/number~_obj-65"):
            {
            return "PitchShift~/number~_obj-65";
            }
        case TAG("PitchShift~/scope~_obj-60"):
            {
            return "PitchShift~/scope~_obj-60";
            }
        case TAG("PitchShift~/scope~_obj-61"):
            {
            return "PitchShift~/scope~_obj-61";
            }
        case TAG("sig"):
            {
            return "sig";
            }
        case TAG("mode"):
            {
            return "mode";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 0:
            {
            return addressOf(this->delaytilde_03_del_bufferobj);
            break;
            }
        case 1:
            {
            return addressOf(this->delaytilde_04_del_bufferobj);
            break;
            }
        default:
            {
            return nullptr;
            }
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
    
        if (index == 0) {
            this->delaytilde_03_del_buffer = new Float64Buffer(this->delaytilde_03_del_bufferobj);
        }
    
        if (index == 1) {
            this->delaytilde_04_del_buffer = new Float64Buffer(this->delaytilde_04_del_bufferobj);
        }
    }
    
    void initialize() {
        this->delaytilde_03_del_bufferobj = initDataRef("delaytilde_03_del_bufferobj", true, nullptr, "buffer~");
        this->delaytilde_04_del_bufferobj = initDataRef("delaytilde_04_del_bufferobj", true, nullptr, "buffer~");
        this->assign_defaults();
        this->setState();
        this->delaytilde_03_del_bufferobj->setIndex(0);
        this->delaytilde_03_del_buffer = new Float64Buffer(this->delaytilde_03_del_bufferobj);
        this->delaytilde_04_del_bufferobj->setIndex(1);
        this->delaytilde_04_del_buffer = new Float64Buffer(this->delaytilde_04_del_bufferobj);
    }
    
    protected:
    
    void numbertilde_05_sig_number_set(number v) {
        this->numbertilde_05_outValue = v;
    }
    
    void numbertilde_05_sig_list_set(const list& v) {
        this->numbertilde_05_outValue = v[0];
    }
    
    void numbertilde_05_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_05_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_05_currentMode = 1;
        }
    }
    
    void numbertilde_06_sig_number_set(number v) {
        this->numbertilde_06_outValue = v;
    }
    
    void numbertilde_06_sig_list_set(const list& v) {
        this->numbertilde_06_outValue = v[0];
    }
    
    void numbertilde_06_mode_set(number v) {
        if (v == 1) {
            this->numbertilde_06_currentMode = 0;
        } else if (v == 2) {
            this->numbertilde_06_currentMode = 1;
        }
    }
    
    void numbertilde_06_value_set(number ) {}
    
    void numbertilde_05_value_set(number ) {}
    
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
    
    void initializeObjects() {
        this->delaytilde_03_del_init();
        this->numbertilde_05_init();
        this->delaytilde_04_del_init();
        this->numbertilde_06_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->delaytilde_03_del_buffer = this->delaytilde_03_del_buffer->allocateIfNeeded();
    
        if (this->delaytilde_03_del_bufferobj->hasRequestedSize()) {
            if (this->delaytilde_03_del_bufferobj->wantsFill())
                this->zeroDataRef(this->delaytilde_03_del_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(0);
        }
    
        this->delaytilde_04_del_buffer = this->delaytilde_04_del_buffer->allocateIfNeeded();
    
        if (this->delaytilde_04_del_bufferobj->hasRequestedSize()) {
            if (this->delaytilde_04_del_bufferobj->wantsFill())
                this->zeroDataRef(this->delaytilde_04_del_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(1);
        }
    }
    
    void scopetilde_04_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_04_ysign = this->scopetilde_04_ysign;
        auto __scopetilde_04_ymonitorvalue = this->scopetilde_04_ymonitorvalue;
        auto __scopetilde_04_xsign = this->scopetilde_04_xsign;
        auto __scopetilde_04_xmonitorvalue = this->scopetilde_04_xmonitorvalue;
        auto __scopetilde_04_mode = this->scopetilde_04_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_04_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_04_xmonitorvalue) {
                    __scopetilde_04_xmonitorvalue = xabsval;
                    __scopetilde_04_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_04_ymonitorvalue) {
                    __scopetilde_04_ymonitorvalue = yabsval;
                    __scopetilde_04_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_04_xmonitorvalue = xval;
                __scopetilde_04_xsign = 1;
                __scopetilde_04_ymonitorvalue = yval;
                __scopetilde_04_ysign = 1;
            }
    
            this->scopetilde_04_effectiveCount--;
    
            if (this->scopetilde_04_effectiveCount <= 0) {
                this->scopetilde_04_updateEffectiveCount();
                this->scopetilde_04_monitorbuffer->push(__scopetilde_04_xmonitorvalue * __scopetilde_04_xsign);
    
                if (__scopetilde_04_mode == 1)
                    __scopetilde_04_xmonitorvalue = 0;
    
                if (this->scopetilde_04_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~/scope~_obj-62"),
                        this->scopetilde_04_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_04_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_04_xmonitorvalue = __scopetilde_04_xmonitorvalue;
        this->scopetilde_04_xsign = __scopetilde_04_xsign;
        this->scopetilde_04_ymonitorvalue = __scopetilde_04_ymonitorvalue;
        this->scopetilde_04_ysign = __scopetilde_04_ysign;
    }
    
    void welch_tilde_03_perform(const Sample * x, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number __x = x[(Index)i];
            __x = (__x > 1 ? 1 : (__x < 0 ? 0 : __x));
            number w = (__x - 0.5) * 2;
            out1[(Index)i] = 1 - w * w;
        }
    }
    
    void scopetilde_06_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_06_ysign = this->scopetilde_06_ysign;
        auto __scopetilde_06_ymonitorvalue = this->scopetilde_06_ymonitorvalue;
        auto __scopetilde_06_xsign = this->scopetilde_06_xsign;
        auto __scopetilde_06_xmonitorvalue = this->scopetilde_06_xmonitorvalue;
        auto __scopetilde_06_mode = this->scopetilde_06_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_06_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_06_xmonitorvalue) {
                    __scopetilde_06_xmonitorvalue = xabsval;
                    __scopetilde_06_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_06_ymonitorvalue) {
                    __scopetilde_06_ymonitorvalue = yabsval;
                    __scopetilde_06_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_06_xmonitorvalue = xval;
                __scopetilde_06_xsign = 1;
                __scopetilde_06_ymonitorvalue = yval;
                __scopetilde_06_ysign = 1;
            }
    
            this->scopetilde_06_effectiveCount--;
    
            if (this->scopetilde_06_effectiveCount <= 0) {
                this->scopetilde_06_updateEffectiveCount();
                this->scopetilde_06_monitorbuffer->push(__scopetilde_06_xmonitorvalue * __scopetilde_06_xsign);
    
                if (__scopetilde_06_mode == 1)
                    __scopetilde_06_xmonitorvalue = 0;
    
                if (this->scopetilde_06_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~/scope~_obj-61"),
                        this->scopetilde_06_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_06_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_06_xmonitorvalue = __scopetilde_06_xmonitorvalue;
        this->scopetilde_06_xsign = __scopetilde_06_xsign;
        this->scopetilde_06_ymonitorvalue = __scopetilde_06_ymonitorvalue;
        this->scopetilde_06_ysign = __scopetilde_06_ysign;
    }
    
    void dspexpr_15_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + -0.5;//#map:_###_obj_###_:1
        }
    }
    
    void wrap_tilde_02_perform(const Sample * x, number low, number high, SampleValue * out1, Index n) {
        RNBO_UNUSED(high);
        RNBO_UNUSED(low);
        Index i;
    
        for (i = 0; i < n; i++) {
            number lo;
            number hi;
            lo = 0;
            hi = 1;
            number range = hi - lo;
    
            if (x[(Index)i] >= lo && x[(Index)i] < hi) {
                out1[(Index)i] = x[(Index)i];
                continue;
            }
    
            if (range <= 0.000000001) {
                out1[(Index)i] = lo;
                continue;
            }
    
            long numWraps = (long)(trunc((x[(Index)i] - lo) / range));
            numWraps = numWraps - ((x[(Index)i] < lo ? 1 : 0));
            number result = x[(Index)i] - range * numWraps;
    
            if (result >= hi) {
                out1[(Index)i] = result - range;
                continue;
            } else {
                out1[(Index)i] = result;
                continue;
            }
        }
    }
    
    void welch_tilde_04_perform(const Sample * x, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number __x = x[(Index)i];
            __x = (__x > 1 ? 1 : (__x < 0 ? 0 : __x));
            number w = (__x - 0.5) * 2;
            out1[(Index)i] = 1 - w * w;
        }
    }
    
    void scopetilde_05_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_05_ysign = this->scopetilde_05_ysign;
        auto __scopetilde_05_ymonitorvalue = this->scopetilde_05_ymonitorvalue;
        auto __scopetilde_05_xsign = this->scopetilde_05_xsign;
        auto __scopetilde_05_xmonitorvalue = this->scopetilde_05_xmonitorvalue;
        auto __scopetilde_05_mode = this->scopetilde_05_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_05_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_05_xmonitorvalue) {
                    __scopetilde_05_xmonitorvalue = xabsval;
                    __scopetilde_05_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_05_ymonitorvalue) {
                    __scopetilde_05_ymonitorvalue = yabsval;
                    __scopetilde_05_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_05_xmonitorvalue = xval;
                __scopetilde_05_xsign = 1;
                __scopetilde_05_ymonitorvalue = yval;
                __scopetilde_05_ysign = 1;
            }
    
            this->scopetilde_05_effectiveCount--;
    
            if (this->scopetilde_05_effectiveCount <= 0) {
                this->scopetilde_05_updateEffectiveCount();
                this->scopetilde_05_monitorbuffer->push(__scopetilde_05_xmonitorvalue * __scopetilde_05_xsign);
    
                if (__scopetilde_05_mode == 1)
                    __scopetilde_05_xmonitorvalue = 0;
    
                if (this->scopetilde_05_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("PitchShift~/scope~_obj-60"),
                        this->scopetilde_05_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_05_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_05_xmonitorvalue = __scopetilde_05_xmonitorvalue;
        this->scopetilde_05_xsign = __scopetilde_05_xsign;
        this->scopetilde_05_ymonitorvalue = __scopetilde_05_ymonitorvalue;
        this->scopetilde_05_ysign = __scopetilde_05_ysign;
    }
    
    void dspexpr_14_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numbertilde_06_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_06_currentIntervalInSamples = this->numbertilde_06_currentIntervalInSamples;
        auto __numbertilde_06_lastValue = this->numbertilde_06_lastValue;
        auto __numbertilde_06_currentInterval = this->numbertilde_06_currentInterval;
        auto __numbertilde_06_rampInSamples = this->numbertilde_06_rampInSamples;
        auto __numbertilde_06_outValue = this->numbertilde_06_outValue;
        auto __numbertilde_06_currentMode = this->numbertilde_06_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_06_currentMode == 0) {
                output[(Index)i] = this->numbertilde_06_smooth_next(
                    __numbertilde_06_outValue,
                    __numbertilde_06_rampInSamples,
                    __numbertilde_06_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_06_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_06_lastValue && __numbertilde_06_currentInterval <= 0) {
            __numbertilde_06_currentInterval = __numbertilde_06_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1494586265,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_06_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("PitchShift~/number~_obj-65"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_06_currentInterval = __numbertilde_06_currentInterval;
        this->numbertilde_06_lastValue = __numbertilde_06_lastValue;
    }
    
    void delaytilde_04_perform(
        const Sample * delay,
        const SampleValue * input,
        SampleValue * output,
        Index n
    ) {
        auto __delaytilde_04_crossfadeDelay = this->delaytilde_04_crossfadeDelay;
        auto __delaytilde_04_rampInSamples = this->delaytilde_04_rampInSamples;
        auto __delaytilde_04_ramp = this->delaytilde_04_ramp;
        auto __delaytilde_04_lastDelay = this->delaytilde_04_lastDelay;
    
        for (Index i = 0; i < n; i++) {
            if (__delaytilde_04_lastDelay == -1) {
                __delaytilde_04_lastDelay = delay[(Index)i];
            }
    
            if (__delaytilde_04_ramp > 0) {
                number factor = __delaytilde_04_ramp / __delaytilde_04_rampInSamples;
                output[(Index)i] = this->delaytilde_04_del_read(__delaytilde_04_crossfadeDelay, 0) * factor + this->delaytilde_04_del_read(__delaytilde_04_lastDelay, 0) * (1. - factor);
                __delaytilde_04_ramp--;
            } else {
                number effectiveDelay = delay[(Index)i];
    
                if (effectiveDelay != __delaytilde_04_lastDelay) {
                    __delaytilde_04_ramp = __delaytilde_04_rampInSamples;
                    __delaytilde_04_crossfadeDelay = __delaytilde_04_lastDelay;
                    __delaytilde_04_lastDelay = effectiveDelay;
                    output[(Index)i] = this->delaytilde_04_del_read(__delaytilde_04_crossfadeDelay, 0);
                    __delaytilde_04_ramp--;
                } else {
                    output[(Index)i] = this->delaytilde_04_del_read(effectiveDelay, 0);
                }
            }
    
            this->delaytilde_04_del_write(input[(Index)i]);
            this->delaytilde_04_del_step();
        }
    
        this->delaytilde_04_lastDelay = __delaytilde_04_lastDelay;
        this->delaytilde_04_ramp = __delaytilde_04_ramp;
        this->delaytilde_04_crossfadeDelay = __delaytilde_04_crossfadeDelay;
    }
    
    void dspexpr_13_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_12_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void numbertilde_05_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
        auto __numbertilde_05_currentIntervalInSamples = this->numbertilde_05_currentIntervalInSamples;
        auto __numbertilde_05_lastValue = this->numbertilde_05_lastValue;
        auto __numbertilde_05_currentInterval = this->numbertilde_05_currentInterval;
        auto __numbertilde_05_rampInSamples = this->numbertilde_05_rampInSamples;
        auto __numbertilde_05_outValue = this->numbertilde_05_outValue;
        auto __numbertilde_05_currentMode = this->numbertilde_05_currentMode;
        number monitorvalue = input_signal[0];
    
        for (Index i = 0; i < n; i++) {
            if (__numbertilde_05_currentMode == 0) {
                output[(Index)i] = this->numbertilde_05_smooth_next(
                    __numbertilde_05_outValue,
                    __numbertilde_05_rampInSamples,
                    __numbertilde_05_rampInSamples
                );
            } else {
                output[(Index)i] = input_signal[(Index)i];
            }
        }
    
        __numbertilde_05_currentInterval -= n;
    
        if (monitorvalue != __numbertilde_05_lastValue && __numbertilde_05_currentInterval <= 0) {
            __numbertilde_05_currentInterval = __numbertilde_05_currentIntervalInSamples;
    
            this->getEngine()->scheduleClockEventWithValue(
                this,
                2098551528,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                monitorvalue
            );;
    
            __numbertilde_05_lastValue = monitorvalue;
    
            this->getEngine()->sendListMessage(
                TAG("monitor"),
                TAG("PitchShift~/number~_obj-64"),
                {monitorvalue},
                this->_currentTime
            );;
        }
    
        this->numbertilde_05_currentInterval = __numbertilde_05_currentInterval;
        this->numbertilde_05_lastValue = __numbertilde_05_lastValue;
    }
    
    void delaytilde_03_perform(
        const Sample * delay,
        const SampleValue * input,
        SampleValue * output,
        Index n
    ) {
        auto __delaytilde_03_crossfadeDelay = this->delaytilde_03_crossfadeDelay;
        auto __delaytilde_03_rampInSamples = this->delaytilde_03_rampInSamples;
        auto __delaytilde_03_ramp = this->delaytilde_03_ramp;
        auto __delaytilde_03_lastDelay = this->delaytilde_03_lastDelay;
    
        for (Index i = 0; i < n; i++) {
            if (__delaytilde_03_lastDelay == -1) {
                __delaytilde_03_lastDelay = delay[(Index)i];
            }
    
            if (__delaytilde_03_ramp > 0) {
                number factor = __delaytilde_03_ramp / __delaytilde_03_rampInSamples;
                output[(Index)i] = this->delaytilde_03_del_read(__delaytilde_03_crossfadeDelay, 0) * factor + this->delaytilde_03_del_read(__delaytilde_03_lastDelay, 0) * (1. - factor);
                __delaytilde_03_ramp--;
            } else {
                number effectiveDelay = delay[(Index)i];
    
                if (effectiveDelay != __delaytilde_03_lastDelay) {
                    __delaytilde_03_ramp = __delaytilde_03_rampInSamples;
                    __delaytilde_03_crossfadeDelay = __delaytilde_03_lastDelay;
                    __delaytilde_03_lastDelay = effectiveDelay;
                    output[(Index)i] = this->delaytilde_03_del_read(__delaytilde_03_crossfadeDelay, 0);
                    __delaytilde_03_ramp--;
                } else {
                    output[(Index)i] = this->delaytilde_03_del_read(effectiveDelay, 0);
                }
            }
    
            this->delaytilde_03_del_write(input[(Index)i]);
            this->delaytilde_03_del_step();
        }
    
        this->delaytilde_03_lastDelay = __delaytilde_03_lastDelay;
        this->delaytilde_03_ramp = __delaytilde_03_ramp;
        this->delaytilde_03_crossfadeDelay = __delaytilde_03_crossfadeDelay;
    }
    
    void dspexpr_11_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_10_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void delaytilde_03_del_step() {
        this->delaytilde_03_del_reader++;
    
        if (this->delaytilde_03_del_reader >= (int)(this->delaytilde_03_del_buffer->getSize()))
            this->delaytilde_03_del_reader = 0;
    }
    
    number delaytilde_03_del_read(number size, Int interp) {
        if (interp == 0) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            long index2 = (long)(index1 + 1);
    
            return this->linearinterp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        } else if (interp == 1) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? 1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->cubicinterp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        } else if (interp == 6) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? 1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->fastcubicinterp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        } else if (interp == 2) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? 1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->splineinterp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        } else if (interp == 7) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? 1 + this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
            Index index5 = (Index)(index4 + 1);
            Index index6 = (Index)(index5 + 1);
    
            return this->spline6interp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        } else if (interp == 3) {
            number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
    
            return this->cosineinterp(frac, this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
            ), this->delaytilde_03_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_03_del_wrap))
            ));
        }
    
        number r = (int)(this->delaytilde_03_del_buffer->getSize()) + this->delaytilde_03_del_reader - ((size > this->delaytilde_03_del__maxdelay ? this->delaytilde_03_del__maxdelay : (size < (this->delaytilde_03_del_reader != this->delaytilde_03_del_writer) ? this->delaytilde_03_del_reader != this->delaytilde_03_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
    
        return this->delaytilde_03_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_03_del_wrap))
        );
    }
    
    void delaytilde_03_del_write(number v) {
        this->delaytilde_03_del_writer = this->delaytilde_03_del_reader;
        this->delaytilde_03_del_buffer[(Index)this->delaytilde_03_del_writer] = v;
    }
    
    number delaytilde_03_del_next(number v, int size) {
        number effectiveSize = (size == -1 ? this->delaytilde_03_del__maxdelay : size);
        number val = this->delaytilde_03_del_read(effectiveSize, 0);
        this->delaytilde_03_del_write(v);
        this->delaytilde_03_del_step();
        return val;
    }
    
    array<Index, 2> delaytilde_03_del_calcSizeInSamples() {
        number sizeInSamples = 0;
        Index allocatedSizeInSamples = 0;
    
        {
            sizeInSamples = this->delaytilde_03_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
            this->delaytilde_03_del_sizemode = 0;
        }
    
        sizeInSamples = rnbo_floor(sizeInSamples);
        sizeInSamples = this->maximum(sizeInSamples, 2);
        allocatedSizeInSamples = (Index)(sizeInSamples);
        allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
        return {sizeInSamples, allocatedSizeInSamples};
    }
    
    void delaytilde_03_del_init() {
        auto result = this->delaytilde_03_del_calcSizeInSamples();
        this->delaytilde_03_del__maxdelay = result[0];
        Index requestedSizeInSamples = (Index)(result[1]);
        this->delaytilde_03_del_buffer->requestSize(requestedSizeInSamples, 1);
        this->delaytilde_03_del_wrap = requestedSizeInSamples - 1;
    }
    
    void delaytilde_03_del_clear() {
        this->delaytilde_03_del_buffer->setZero();
    }
    
    void delaytilde_03_del_reset() {
        auto result = this->delaytilde_03_del_calcSizeInSamples();
        this->delaytilde_03_del__maxdelay = result[0];
        Index allocatedSizeInSamples = (Index)(result[1]);
        this->delaytilde_03_del_buffer->setSize(allocatedSizeInSamples);
        updateDataRef(this, this->delaytilde_03_del_buffer);
        this->delaytilde_03_del_wrap = this->delaytilde_03_del_buffer->getSize() - 1;
        this->delaytilde_03_del_clear();
    
        if (this->delaytilde_03_del_reader >= this->delaytilde_03_del__maxdelay || this->delaytilde_03_del_writer >= this->delaytilde_03_del__maxdelay) {
            this->delaytilde_03_del_reader = 0;
            this->delaytilde_03_del_writer = 0;
        }
    }
    
    void delaytilde_03_del_dspsetup() {
        this->delaytilde_03_del_reset();
    }
    
    number delaytilde_03_del_evaluateSizeExpr(number samplerate, number vectorsize) {
        RNBO_UNUSED(vectorsize);
        return samplerate;
    }
    
    number delaytilde_03_del_size() {
        return this->delaytilde_03_del__maxdelay;
    }
    
    void delaytilde_03_dspsetup(bool force) {
        if ((bool)(this->delaytilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delaytilde_03_rampInSamples = (long)(this->mstosamps(0));
        this->delaytilde_03_lastDelay = -1;
        this->delaytilde_03_setupDone = true;
        this->delaytilde_03_del_dspsetup();
    }
    
    number numbertilde_05_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_05_smooth_d_prev);
        this->numbertilde_05_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_05_smooth_d_dspsetup() {
        this->numbertilde_05_smooth_d_reset();
    }
    
    void numbertilde_05_smooth_d_reset() {
        this->numbertilde_05_smooth_d_prev = 0;
    }
    
    number numbertilde_05_smooth_next(number x, number up, number down) {
        if (this->numbertilde_05_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_05_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_05_smooth_index = _up;
                this->numbertilde_05_smooth_increment = (x - this->numbertilde_05_smooth_prev) / _up;
            } else if (x < this->numbertilde_05_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_05_smooth_index = _down;
                this->numbertilde_05_smooth_increment = (x - this->numbertilde_05_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_05_smooth_index > 0) {
            this->numbertilde_05_smooth_prev += this->numbertilde_05_smooth_increment;
            this->numbertilde_05_smooth_index -= 1;
        } else {
            this->numbertilde_05_smooth_prev = x;
        }
    
        return this->numbertilde_05_smooth_prev;
    }
    
    void numbertilde_05_smooth_reset() {
        this->numbertilde_05_smooth_prev = 0;
        this->numbertilde_05_smooth_index = 0;
        this->numbertilde_05_smooth_increment = 0;
        this->numbertilde_05_smooth_d_reset();
    }
    
    void numbertilde_05_init() {
        this->numbertilde_05_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("PitchShift~/number~_obj-64"), 1, this->_currentTime);
    }
    
    void numbertilde_05_dspsetup(bool force) {
        if ((bool)(this->numbertilde_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_05_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_05_currentInterval = this->numbertilde_05_currentIntervalInSamples;
        this->numbertilde_05_rampInSamples = this->mstosamps(this->numbertilde_05_ramp);
        this->numbertilde_05_setupDone = true;
        this->numbertilde_05_smooth_d_dspsetup();
    }
    
    void scopetilde_04_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_04_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_04_dspsetup(bool force) {
        if ((bool)(this->scopetilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_04_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~/scope~_obj-62"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_04_mode},
            this->_currentTime
        );;
    
        this->scopetilde_04_updateEffectiveCount();
        this->scopetilde_04_setupDone = true;
    }
    
    void delaytilde_04_del_step() {
        this->delaytilde_04_del_reader++;
    
        if (this->delaytilde_04_del_reader >= (int)(this->delaytilde_04_del_buffer->getSize()))
            this->delaytilde_04_del_reader = 0;
    }
    
    number delaytilde_04_del_read(number size, Int interp) {
        if (interp == 0) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            long index2 = (long)(index1 + 1);
    
            return this->linearinterp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        } else if (interp == 1) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? 1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->cubicinterp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        } else if (interp == 6) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? 1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->fastcubicinterp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        } else if (interp == 2) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? 1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
    
            return this->splineinterp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        } else if (interp == 7) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? 1 + this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);
            Index index5 = (Index)(index4 + 1);
            Index index6 = (Index)(index5 + 1);
    
            return this->spline6interp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        } else if (interp == 3) {
            number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
    
            return this->cosineinterp(frac, this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
            ), this->delaytilde_04_del_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_04_del_wrap))
            ));
        }
    
        number r = (int)(this->delaytilde_04_del_buffer->getSize()) + this->delaytilde_04_del_reader - ((size > this->delaytilde_04_del__maxdelay ? this->delaytilde_04_del__maxdelay : (size < (this->delaytilde_04_del_reader != this->delaytilde_04_del_writer) ? this->delaytilde_04_del_reader != this->delaytilde_04_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
    
        return this->delaytilde_04_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_04_del_wrap))
        );
    }
    
    void delaytilde_04_del_write(number v) {
        this->delaytilde_04_del_writer = this->delaytilde_04_del_reader;
        this->delaytilde_04_del_buffer[(Index)this->delaytilde_04_del_writer] = v;
    }
    
    number delaytilde_04_del_next(number v, int size) {
        number effectiveSize = (size == -1 ? this->delaytilde_04_del__maxdelay : size);
        number val = this->delaytilde_04_del_read(effectiveSize, 0);
        this->delaytilde_04_del_write(v);
        this->delaytilde_04_del_step();
        return val;
    }
    
    array<Index, 2> delaytilde_04_del_calcSizeInSamples() {
        number sizeInSamples = 0;
        Index allocatedSizeInSamples = 0;
    
        {
            sizeInSamples = this->delaytilde_04_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
            this->delaytilde_04_del_sizemode = 0;
        }
    
        sizeInSamples = rnbo_floor(sizeInSamples);
        sizeInSamples = this->maximum(sizeInSamples, 2);
        allocatedSizeInSamples = (Index)(sizeInSamples);
        allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
        return {sizeInSamples, allocatedSizeInSamples};
    }
    
    void delaytilde_04_del_init() {
        auto result = this->delaytilde_04_del_calcSizeInSamples();
        this->delaytilde_04_del__maxdelay = result[0];
        Index requestedSizeInSamples = (Index)(result[1]);
        this->delaytilde_04_del_buffer->requestSize(requestedSizeInSamples, 1);
        this->delaytilde_04_del_wrap = requestedSizeInSamples - 1;
    }
    
    void delaytilde_04_del_clear() {
        this->delaytilde_04_del_buffer->setZero();
    }
    
    void delaytilde_04_del_reset() {
        auto result = this->delaytilde_04_del_calcSizeInSamples();
        this->delaytilde_04_del__maxdelay = result[0];
        Index allocatedSizeInSamples = (Index)(result[1]);
        this->delaytilde_04_del_buffer->setSize(allocatedSizeInSamples);
        updateDataRef(this, this->delaytilde_04_del_buffer);
        this->delaytilde_04_del_wrap = this->delaytilde_04_del_buffer->getSize() - 1;
        this->delaytilde_04_del_clear();
    
        if (this->delaytilde_04_del_reader >= this->delaytilde_04_del__maxdelay || this->delaytilde_04_del_writer >= this->delaytilde_04_del__maxdelay) {
            this->delaytilde_04_del_reader = 0;
            this->delaytilde_04_del_writer = 0;
        }
    }
    
    void delaytilde_04_del_dspsetup() {
        this->delaytilde_04_del_reset();
    }
    
    number delaytilde_04_del_evaluateSizeExpr(number samplerate, number vectorsize) {
        RNBO_UNUSED(vectorsize);
        return samplerate;
    }
    
    number delaytilde_04_del_size() {
        return this->delaytilde_04_del__maxdelay;
    }
    
    void delaytilde_04_dspsetup(bool force) {
        if ((bool)(this->delaytilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delaytilde_04_rampInSamples = (long)(this->mstosamps(0));
        this->delaytilde_04_lastDelay = -1;
        this->delaytilde_04_setupDone = true;
        this->delaytilde_04_del_dspsetup();
    }
    
    number numbertilde_06_smooth_d_next(number x) {
        number temp = (number)(x - this->numbertilde_06_smooth_d_prev);
        this->numbertilde_06_smooth_d_prev = x;
        return temp;
    }
    
    void numbertilde_06_smooth_d_dspsetup() {
        this->numbertilde_06_smooth_d_reset();
    }
    
    void numbertilde_06_smooth_d_reset() {
        this->numbertilde_06_smooth_d_prev = 0;
    }
    
    number numbertilde_06_smooth_next(number x, number up, number down) {
        if (this->numbertilde_06_smooth_d_next(x) != 0.) {
            if (x > this->numbertilde_06_smooth_prev) {
                number _up = up;
    
                if (_up < 1)
                    _up = 1;
    
                this->numbertilde_06_smooth_index = _up;
                this->numbertilde_06_smooth_increment = (x - this->numbertilde_06_smooth_prev) / _up;
            } else if (x < this->numbertilde_06_smooth_prev) {
                number _down = down;
    
                if (_down < 1)
                    _down = 1;
    
                this->numbertilde_06_smooth_index = _down;
                this->numbertilde_06_smooth_increment = (x - this->numbertilde_06_smooth_prev) / _down;
            }
        }
    
        if (this->numbertilde_06_smooth_index > 0) {
            this->numbertilde_06_smooth_prev += this->numbertilde_06_smooth_increment;
            this->numbertilde_06_smooth_index -= 1;
        } else {
            this->numbertilde_06_smooth_prev = x;
        }
    
        return this->numbertilde_06_smooth_prev;
    }
    
    void numbertilde_06_smooth_reset() {
        this->numbertilde_06_smooth_prev = 0;
        this->numbertilde_06_smooth_index = 0;
        this->numbertilde_06_smooth_increment = 0;
        this->numbertilde_06_smooth_d_reset();
    }
    
    void numbertilde_06_init() {
        this->numbertilde_06_currentMode = 1;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("PitchShift~/number~_obj-65"), 1, this->_currentTime);
    }
    
    void numbertilde_06_dspsetup(bool force) {
        if ((bool)(this->numbertilde_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->numbertilde_06_currentIntervalInSamples = this->mstosamps(100);
        this->numbertilde_06_currentInterval = this->numbertilde_06_currentIntervalInSamples;
        this->numbertilde_06_rampInSamples = this->mstosamps(this->numbertilde_06_ramp);
        this->numbertilde_06_setupDone = true;
        this->numbertilde_06_smooth_d_dspsetup();
    }
    
    void scopetilde_05_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_05_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_05_dspsetup(bool force) {
        if ((bool)(this->scopetilde_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_05_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~/scope~_obj-60"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_05_mode},
            this->_currentTime
        );;
    
        this->scopetilde_05_updateEffectiveCount();
        this->scopetilde_05_setupDone = true;
    }
    
    void scopetilde_06_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_06_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_06_dspsetup(bool force) {
        if ((bool)(this->scopetilde_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_06_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("PitchShift~/scope~_obj-61"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_06_mode},
            this->_currentTime
        );;
    
        this->scopetilde_06_updateEffectiveCount();
        this->scopetilde_06_setupDone = true;
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
        dspexpr_10_in1 = 0;
        dspexpr_10_in2 = 0;
        dspexpr_11_in1 = 0;
        dspexpr_11_in2 = 0;
        delaytilde_03_delay = 0;
        numbertilde_05_input_number = 0;
        numbertilde_05_ramp = 0;
        dspexpr_12_in1 = 0;
        dspexpr_12_in2 = 0;
        welch_tilde_03_x = 0;
        dspexpr_13_in1 = 0;
        dspexpr_13_in2 = 0;
        delaytilde_04_delay = 0;
        numbertilde_06_input_number = 0;
        numbertilde_06_ramp = 0;
        dspexpr_14_in1 = 0;
        dspexpr_14_in2 = 0;
        welch_tilde_04_x = 0;
        wrap_tilde_02_x = 0;
        wrap_tilde_02_low = 0;
        wrap_tilde_02_high = 1;
        dspexpr_15_in1 = 0;
        dspexpr_15_in2 = -0.5;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        delaytilde_03_lastDelay = -1;
        delaytilde_03_crossfadeDelay = 0;
        delaytilde_03_ramp = 0;
        delaytilde_03_rampInSamples = 0;
        delaytilde_03_del__maxdelay = 0;
        delaytilde_03_del_sizemode = 0;
        delaytilde_03_del_wrap = 0;
        delaytilde_03_del_reader = 0;
        delaytilde_03_del_writer = 0;
        delaytilde_03_setupDone = false;
        numbertilde_05_currentInterval = 0;
        numbertilde_05_currentIntervalInSamples = 0;
        numbertilde_05_lastValue = 0;
        numbertilde_05_outValue = 0;
        numbertilde_05_rampInSamples = 0;
        numbertilde_05_currentMode = 0;
        numbertilde_05_smooth_d_prev = 0;
        numbertilde_05_smooth_prev = 0;
        numbertilde_05_smooth_index = 0;
        numbertilde_05_smooth_increment = 0;
        numbertilde_05_setupDone = false;
        scopetilde_04_lastValue = 0;
        scopetilde_04_effectiveCount = 256;
        scopetilde_04_xsign = 1;
        scopetilde_04_ysign = 1;
        scopetilde_04_mode = 0;
        scopetilde_04_setupDone = false;
        delaytilde_04_lastDelay = -1;
        delaytilde_04_crossfadeDelay = 0;
        delaytilde_04_ramp = 0;
        delaytilde_04_rampInSamples = 0;
        delaytilde_04_del__maxdelay = 0;
        delaytilde_04_del_sizemode = 0;
        delaytilde_04_del_wrap = 0;
        delaytilde_04_del_reader = 0;
        delaytilde_04_del_writer = 0;
        delaytilde_04_setupDone = false;
        numbertilde_06_currentInterval = 0;
        numbertilde_06_currentIntervalInSamples = 0;
        numbertilde_06_lastValue = 0;
        numbertilde_06_outValue = 0;
        numbertilde_06_rampInSamples = 0;
        numbertilde_06_currentMode = 0;
        numbertilde_06_smooth_d_prev = 0;
        numbertilde_06_smooth_prev = 0;
        numbertilde_06_smooth_index = 0;
        numbertilde_06_smooth_increment = 0;
        numbertilde_06_setupDone = false;
        scopetilde_05_lastValue = 0;
        scopetilde_05_effectiveCount = 256;
        scopetilde_05_xsign = 1;
        scopetilde_05_ysign = 1;
        scopetilde_05_mode = 0;
        scopetilde_05_setupDone = false;
        scopetilde_06_lastValue = 0;
        scopetilde_06_effectiveCount = 256;
        scopetilde_06_xsign = 1;
        scopetilde_06_ysign = 1;
        scopetilde_06_mode = 0;
        scopetilde_06_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_10_in1;
        number dspexpr_10_in2;
        number dspexpr_11_in1;
        number dspexpr_11_in2;
        number delaytilde_03_delay;
        number numbertilde_05_input_number;
        number numbertilde_05_ramp;
        number dspexpr_12_in1;
        number dspexpr_12_in2;
        number welch_tilde_03_x;
        number dspexpr_13_in1;
        number dspexpr_13_in2;
        number delaytilde_04_delay;
        number numbertilde_06_input_number;
        number numbertilde_06_ramp;
        number dspexpr_14_in1;
        number dspexpr_14_in2;
        number welch_tilde_04_x;
        number wrap_tilde_02_x;
        number wrap_tilde_02_low;
        number wrap_tilde_02_high;
        number dspexpr_15_in1;
        number dspexpr_15_in2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number delaytilde_03_lastDelay;
        number delaytilde_03_crossfadeDelay;
        number delaytilde_03_ramp;
        long delaytilde_03_rampInSamples;
        Float64BufferRef delaytilde_03_del_buffer;
        Index delaytilde_03_del__maxdelay;
        Int delaytilde_03_del_sizemode;
        Index delaytilde_03_del_wrap;
        Int delaytilde_03_del_reader;
        Int delaytilde_03_del_writer;
        bool delaytilde_03_setupDone;
        SampleIndex numbertilde_05_currentInterval;
        SampleIndex numbertilde_05_currentIntervalInSamples;
        number numbertilde_05_lastValue;
        number numbertilde_05_outValue;
        number numbertilde_05_rampInSamples;
        Int numbertilde_05_currentMode;
        number numbertilde_05_smooth_d_prev;
        number numbertilde_05_smooth_prev;
        number numbertilde_05_smooth_index;
        number numbertilde_05_smooth_increment;
        bool numbertilde_05_setupDone;
        number scopetilde_04_lastValue;
        number scopetilde_04_effectiveCount;
        number scopetilde_04_xmonitorvalue;
        number scopetilde_04_ymonitorvalue;
        list scopetilde_04_monitorbuffer;
        number scopetilde_04_xsign;
        number scopetilde_04_ysign;
        Int scopetilde_04_mode;
        bool scopetilde_04_setupDone;
        number delaytilde_04_lastDelay;
        number delaytilde_04_crossfadeDelay;
        number delaytilde_04_ramp;
        long delaytilde_04_rampInSamples;
        Float64BufferRef delaytilde_04_del_buffer;
        Index delaytilde_04_del__maxdelay;
        Int delaytilde_04_del_sizemode;
        Index delaytilde_04_del_wrap;
        Int delaytilde_04_del_reader;
        Int delaytilde_04_del_writer;
        bool delaytilde_04_setupDone;
        SampleIndex numbertilde_06_currentInterval;
        SampleIndex numbertilde_06_currentIntervalInSamples;
        number numbertilde_06_lastValue;
        number numbertilde_06_outValue;
        number numbertilde_06_rampInSamples;
        Int numbertilde_06_currentMode;
        number numbertilde_06_smooth_d_prev;
        number numbertilde_06_smooth_prev;
        number numbertilde_06_smooth_index;
        number numbertilde_06_smooth_increment;
        bool numbertilde_06_setupDone;
        number scopetilde_05_lastValue;
        number scopetilde_05_effectiveCount;
        number scopetilde_05_xmonitorvalue;
        number scopetilde_05_ymonitorvalue;
        list scopetilde_05_monitorbuffer;
        number scopetilde_05_xsign;
        number scopetilde_05_ysign;
        Int scopetilde_05_mode;
        bool scopetilde_05_setupDone;
        number scopetilde_06_lastValue;
        number scopetilde_06_effectiveCount;
        number scopetilde_06_xmonitorvalue;
        number scopetilde_06_ymonitorvalue;
        list scopetilde_06_monitorbuffer;
        number scopetilde_06_xsign;
        number scopetilde_06_ysign;
        Int scopetilde_06_mode;
        bool scopetilde_06_setupDone;
        number stackprotect_count;
        DataRef delaytilde_03_del_bufferobj;
        DataRef delaytilde_04_del_bufferobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_01;
    delete this->p_02;
    delete this->p_03;
    delete this->p_04;
    delete this->p_05;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -1621164530, false);
    getEngine()->flushClockEvents(this, -62043057, false);
    getEngine()->flushClockEvents(this, 1114681293, false);
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

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number samplerate() const {
    return this->sr;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

ParameterValue fromnormalized(ParameterIndex index, ParameterValue normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->p_03_perform(n);
    this->linetilde_02_perform(this->signals[0], n);
    this->phasor_01_perform(this->signals[0], this->signals[1], n);
    this->linetilde_03_perform(this->signals[2], n);
    this->rate_tilde_01_perform(this->signals[1], this->signals[2], this->signals[3], n);
    this->linetilde_04_perform(this->signals[2], n);
    this->p_05_perform(in2, this->signals[3], this->signals[2], this->signals[4], n);
    this->p_04_perform(in1, this->signals[1], this->signals[2], this->signals[3], n);

    this->p_02_perform(
        in1,
        in2,
        this->signals[3],
        this->signals[4],
        this->signals[0],
        this->signals[2],
        this->signals[1],
        n
    );

    this->p_01_perform(in1, in2, this->signals[2], this->signals[1], out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 5; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
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

    this->phasor_01_dspsetup(forceDSPSetup);
    this->rate_tilde_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_01->processDataViewUpdate(index, time);
    this->p_02->processDataViewUpdate(index, time);
    this->p_03->processDataViewUpdate(index, time);
    this->p_04->processDataViewUpdate(index, time);
    this->p_05->processDataViewUpdate(index, time);
}

void initialize() {
    this->assign_defaults();
    this->setState();
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

void onSampleRateChanged(double ) {}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_01->processTempoEvent(time, tempo);
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
        this->p_04->processTempoEvent(time, tempo);
        this->p_05->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_01->processTransportEvent(time, state);
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
        this->p_04->processTransportEvent(time, state);
        this->p_05->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_01->processBeatTimeEvent(time, beattime);
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
        this->p_04->processBeatTimeEvent(time, beattime);
        this->p_05->processBeatTimeEvent(time, beattime);
    }
}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
        this->p_04->processTimeSignatureEvent(time, numerator, denominator);
        this->p_05->processTimeSignatureEvent(time, numerator, denominator);
    }
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_01 = new RNBOSubpatcher_68();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    this->p_02 = new RNBOSubpatcher_69();
    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
    this->p_03 = new RNBOSubpatcher_70();
    this->p_03->setEngineAndPatcher(this->getEngine(), this);
    this->p_03->initialize();
    this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    this->p_04 = new RNBOSubpatcher_71();
    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    this->p_05 = new RNBOSubpatcher_72();
    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "transp"));
    this->param_02_getPresetValue(getSubState(preset, "mix"));
    this->param_03_getPresetValue(getSubState(preset, "spread"));
    this->param_04_getPresetValue(getSubState(preset, "window"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "Mix~"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "Switch~"));
    this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "FreqCalc"));
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "PitchShift~[1]"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "PitchShift~"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_04_setPresetValue(getSubState(preset, "window"));
    this->param_01_setPresetValue(getSubState(preset, "transp"));
    this->param_03_setPresetValue(getSubState(preset, "spread"));
    this->param_02_setPresetValue(getSubState(preset, "mix"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            this->p_02->setParameterValue(index, v, time);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            this->p_03->setParameterValue(index, v, time);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            this->p_04->setParameterValue(index, v, time);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            this->p_05->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterValue(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterValue(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterValue(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "transp";
        }
    case 1:
        {
        return "mix";
        }
    case 2:
        {
        return "spread";
        }
    case 3:
        {
        return "window";
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterName(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterName(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterName(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "transp";
        }
    case 1:
        {
        return "mix";
        }
    case 2:
        {
        return "spread";
        }
    case 3:
        {
        return "window";
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterId(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterId(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterId(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -24;
            info->max = 24;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Transp";
            info->unit = "st";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Mix";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Spread";
            info->unit = "ct";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 80;
            info->min = 2;
            info->max = 200;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Window";
            info->unit = "ms";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 4;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            index -= this->p_01->getNumParameters();

            if (index < this->p_02->getNumParameters())
                this->p_02->getParameterInfo(index, info);

            index -= this->p_02->getNumParameters();

            if (index < this->p_03->getNumParameters())
                this->p_03->getParameterInfo(index, info);

            index -= this->p_03->getNumParameters();

            if (index < this->p_04->getNumParameters())
                this->p_04->getParameterInfo(index, info);

            index -= this->p_04->getNumParameters();

            if (index < this->p_05->getNumParameters())
                this->p_05->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_01)
        return 4;

    if (subpatcher == this->p_02)
        return 4 + this->p_01->getNumParameters();

    if (subpatcher == this->p_03)
        return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters();

    if (subpatcher == this->p_04)
        return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();

    if (subpatcher == this->p_05)
        return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();

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
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 2 ? 2 : (value > 200 ? 200 : value));
            ParameterValue normalizedValue = (value - 2) / (200 - 2);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < -24 ? -24 : (value > 24 ? 24 : value));
            ParameterValue normalizedValue = (value - -24) / (24 - -24);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < -100 ? -100 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - -100) / (100 - -100);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertToNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertToNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertToNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 1:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return 2 + value * (200 - 2);
            }
        }
        }
    case 0:
        {
        {
            {
                return -24 + value * (24 - -24);
            }
        }
        }
    case 2:
        {
        {
            {
                return -100 + value * (100 - -100);
            }
        }
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertFromNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertFromNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertFromNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    default:
        {
        index -= 4;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->constrainParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->constrainParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->constrainParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->constrainParameterValue(index, value);

        return value;
        }
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
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -1621164530:
        {
        this->linetilde_02_target_bang();
        break;
        }
    case -62043057:
        {
        this->linetilde_03_target_bang();
        break;
        }
    case 1114681293:
        {
        this->linetilde_04_target_bang();
        break;
        }
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
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("number_obj-63") == objectId)
            this->numberobj_18_valin_set(payload);

        if (TAG("number_obj-82") == objectId)
            this->numberobj_19_valin_set(payload);

        if (TAG("number_obj-51") == objectId)
            this->numberobj_20_valin_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_21_valin_set(payload);

        if (TAG("number_obj-31") == objectId)
            this->numberobj_22_valin_set(payload);

        if (TAG("number_obj-4") == objectId)
            this->numberobj_23_valin_set(payload);

        if (TAG("number_obj-70") == objectId)
            this->numberobj_24_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-63") == objectId)
            this->numberobj_18_format_set(payload);

        if (TAG("number_obj-82") == objectId)
            this->numberobj_19_format_set(payload);

        if (TAG("number_obj-51") == objectId)
            this->numberobj_20_format_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_21_format_set(payload);

        if (TAG("number_obj-31") == objectId)
            this->numberobj_22_format_set(payload);

        if (TAG("number_obj-4") == objectId)
            this->numberobj_23_format_set(payload);

        if (TAG("number_obj-70") == objectId)
            this->numberobj_24_format_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
    this->p_02->processNumMessage(tag, objectId, time, payload);
    this->p_03->processNumMessage(tag, objectId, time, payload);
    this->p_04->processNumMessage(tag, objectId, time, payload);
    this->p_05->processNumMessage(tag, objectId, time, payload);
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
    this->p_04->processListMessage(tag, objectId, time, payload);
    this->p_05->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processBangMessage(tag, objectId, time);
    this->p_02->processBangMessage(tag, objectId, time);
    this->p_03->processBangMessage(tag, objectId, time);
    this->p_04->processBangMessage(tag, objectId, time);
    this->p_05->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-63"):
        {
        return "number_obj-63";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("number_obj-82"):
        {
        return "number_obj-82";
        }
    case TAG("number_obj-51"):
        {
        return "number_obj-51";
        }
    case TAG("number_obj-24"):
        {
        return "number_obj-24";
        }
    case TAG("number_obj-31"):
        {
        return "number_obj-31";
        }
    case TAG("number_obj-4"):
        {
        return "number_obj-4";
        }
    case TAG("number_obj-70"):
        {
        return "number_obj-70";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
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

    auto subpatchResult_3 = this->p_04->resolveTag(tag);

    if (subpatchResult_3)
        return subpatchResult_3;

    auto subpatchResult_4 = this->p_05->resolveTag(tag);

    if (subpatchResult_4)
        return subpatchResult_4;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
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

    this->numberobj_18_value_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->numberobj_20_value_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->numberobj_21_value_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->numberobj_24_value_set(v);
}

void numberobj_18_valin_set(number v) {
    this->numberobj_18_value_set(v);
}

void numberobj_18_format_set(number v) {
    this->numberobj_18_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_19_valin_set(number v) {
    this->numberobj_19_value_set(v);
}

void numberobj_19_format_set(number v) {
    this->numberobj_19_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_20_valin_set(number v) {
    this->numberobj_20_value_set(v);
}

void numberobj_20_format_set(number v) {
    this->numberobj_20_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_21_valin_set(number v) {
    this->numberobj_21_value_set(v);
}

void numberobj_21_format_set(number v) {
    this->numberobj_21_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_22_valin_set(number v) {
    this->numberobj_22_value_set(v);
}

void numberobj_22_format_set(number v) {
    this->numberobj_22_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_23_valin_set(number v) {
    this->numberobj_23_value_set(v);
}

void numberobj_23_format_set(number v) {
    this->numberobj_23_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_24_valin_set(number v) {
    this->numberobj_24_value_set(v);
}

void numberobj_24_format_set(number v) {
    this->numberobj_24_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void linetilde_02_target_bang() {}

void linetilde_03_target_bang() {}

void linetilde_04_target_bang() {}

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

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
    this->p_02->allocateDataRefs();
    this->p_03->allocateDataRefs();
    this->p_04->allocateDataRefs();
    this->p_05->allocateDataRefs();
}

void initializeObjects() {
    this->numberobj_18_init();
    this->numberobj_19_init();
    this->numberobj_20_init();
    this->numberobj_21_init();
    this->numberobj_22_init();
    this->numberobj_23_init();
    this->numberobj_24_init();
    this->p_01->initializeObjects();
    this->p_02->initializeObjects();
    this->p_03->initializeObjects();
    this->p_04->initializeObjects();
    this->p_05->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();
    this->p_02->startup();
    this->p_03->startup();
    this->p_04->startup();
    this->p_05->startup();

    {
        this->scheduleParamInit(0, 2);
    }

    {
        this->scheduleParamInit(1, 4);
    }

    {
        this->scheduleParamInit(2, 3);
    }

    {
        this->scheduleParamInit(3, 1);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 24 ? 24 : (v < -24 ? -24 : v));
    return v;
}

void linetilde_03_time_set(number v) {
    this->linetilde_03_time = v;
}

void linetilde_03_segments_set(const list& v) {
    this->linetilde_03_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_03_time == 0) {
            this->linetilde_03_activeRamps->length = 0;
            this->linetilde_03_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_03_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_03_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_03_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_03_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_03_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_03_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_03_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_03_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_03_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_03_activeRamps->push(lastRampValue);
                this->linetilde_03_activeRamps->push(0);
                this->linetilde_03_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_03_keepramp)) {
                        this->linetilde_03_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_03_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_03_activeRamps->push(destinationValue);
                this->linetilde_03_activeRamps->push(inc);
                this->linetilde_03_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_22_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_03_segments_set(converted);
    }
}

void numberobj_22_value_set(number v) {
    this->numberobj_22_value_setter(v);
    v = this->numberobj_22_value;
    number localvalue = v;

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-31"), localvalue, this->_currentTime);
    this->numberobj_22_output_set(localvalue);
}

void p_03_out2_number_set(number v) {
    this->numberobj_22_value_set(v);
}

void linetilde_02_time_set(number v) {
    this->linetilde_02_time = v;
}

void linetilde_02_segments_set(const list& v) {
    this->linetilde_02_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_02_time == 0) {
            this->linetilde_02_activeRamps->length = 0;
            this->linetilde_02_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_02_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_02_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_02_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_02_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_02_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_02_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_02_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_02_activeRamps->push(lastRampValue);
                this->linetilde_02_activeRamps->push(0);
                this->linetilde_02_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_02_keepramp)) {
                        this->linetilde_02_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_02_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_02_activeRamps->push(destinationValue);
                this->linetilde_02_activeRamps->push(inc);
                this->linetilde_02_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_19_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_02_segments_set(converted);
    }
}

void numberobj_19_value_set(number v) {
    this->numberobj_19_value_setter(v);
    v = this->numberobj_19_value;
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-82"), localvalue, this->_currentTime);
    this->numberobj_19_output_set(localvalue);
}

void p_03_out1_number_set(number v) {
    this->numberobj_19_value_set(v);
}

void p_03_in1_number_set(number v) {
    this->p_03->updateTime(this->_currentTime);
    this->p_03->eventinlet_02_out1_number_set(v);
}

void numberobj_18_output_set(number v) {
    this->p_03_in1_number_set(v);
}

void numberobj_18_value_set(number v) {
    this->numberobj_18_value_setter(v);
    v = this->numberobj_18_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -24) {
        localvalue = -24;
    }

    if ((bool)(true) && localvalue > 24) {
        localvalue = 24;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-63"), localvalue, this->_currentTime);
    this->numberobj_18_output_set(localvalue);
}

number param_02_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in5_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_01_out1_number_set(v);
}

void numberobj_20_output_set(number v) {
    this->p_01_in5_number_set(v);
}

void numberobj_20_value_set(number v) {
    this->numberobj_20_value_setter(v);
    v = this->numberobj_20_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-51"), localvalue, this->_currentTime);
    this->numberobj_20_output_set(localvalue);
}

number param_03_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_03_in2_number_set(number v) {
    this->p_03->updateTime(this->_currentTime);
    this->p_03->eventinlet_03_out1_number_set(v);
}

void numberobj_21_output_set(number v) {
    this->p_03_in2_number_set(v);
}

void numberobj_21_value_set(number v) {
    this->numberobj_21_value_setter(v);
    v = this->numberobj_21_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-24"), localvalue, this->_currentTime);
    this->numberobj_21_output_set(localvalue);
}

number param_04_value_constrain(number v) const {
    v = (v > 200 ? 200 : (v < 2 ? 2 : v));
    return v;
}

void linetilde_04_time_set(number v) {
    this->linetilde_04_time = v;
}

void linetilde_04_segments_set(const list& v) {
    this->linetilde_04_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_04_time == 0) {
            this->linetilde_04_activeRamps->length = 0;
            this->linetilde_04_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_04_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_04_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_04_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_04_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_04_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_04_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_04_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_04_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_04_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_04_activeRamps->push(lastRampValue);
                this->linetilde_04_activeRamps->push(0);
                this->linetilde_04_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_04_keepramp)) {
                        this->linetilde_04_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_04_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_04_activeRamps->push(destinationValue);
                this->linetilde_04_activeRamps->push(inc);
                this->linetilde_04_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_23_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_04_segments_set(converted);
    }
}

void numberobj_23_value_set(number v) {
    this->numberobj_23_value_setter(v);
    v = this->numberobj_23_value;
    number localvalue = v;

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-4"), localvalue, this->_currentTime);
    this->numberobj_23_output_set(localvalue);
}

void mstosamps_01_out1_set(number v) {
    this->numberobj_23_value_set(v);
}

void mstosamps_01_ms_set(number ms) {
    this->mstosamps_01_ms = ms;

    {
        this->mstosamps_01_out1_set(ms * this->sr * 0.001);
        return;
    }
}

void p_03_in3_number_set(number v) {
    this->p_03->updateTime(this->_currentTime);
    this->p_03->eventinlet_04_out1_number_set(v);
}

void numberobj_24_output_set(number v) {
    this->mstosamps_01_ms_set(v);
    this->p_03_in3_number_set(v);
}

void numberobj_24_value_set(number v) {
    this->numberobj_24_value_setter(v);
    v = this->numberobj_24_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 2) {
        localvalue = 2;
    }

    if ((bool)(true) && localvalue > 200) {
        localvalue = 200;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-70"), localvalue, this->_currentTime);
    this->numberobj_24_output_set(localvalue);
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_01_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(0, v));
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->fromnormalized_01_input_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:expr_13:1
}

void ctlin_01_value_set(number v) {
    this->expr_13_in1_set(v);
}

void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
        this->ctlin_01_outchannel_set(channel);
        this->ctlin_01_outcontroller_set(data[1]);
        this->ctlin_01_value_set(data[2]);
        this->ctlin_01_status = 0;
    }
}

void ctlin_02_outchannel_set(number ) {}

void ctlin_02_outcontroller_set(number ) {}

void fromnormalized_02_output_set(number v) {
    this->param_02_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(1, v));
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->fromnormalized_02_input_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:expr_14:1
}

void ctlin_02_value_set(number v) {
    this->expr_14_in1_set(v);
}

void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
        this->ctlin_02_outchannel_set(channel);
        this->ctlin_02_outcontroller_set(data[1]);
        this->ctlin_02_value_set(data[2]);
        this->ctlin_02_status = 0;
    }
}

void ctlin_03_outchannel_set(number ) {}

void ctlin_03_outcontroller_set(number ) {}

void fromnormalized_03_output_set(number v) {
    this->param_03_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(2, v));
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->fromnormalized_03_input_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 * this->expr_15_in2);//#map:expr_15:1
}

void ctlin_03_value_set(number v) {
    this->expr_15_in1_set(v);
}

void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
        this->ctlin_03_outchannel_set(channel);
        this->ctlin_03_outcontroller_set(data[1]);
        this->ctlin_03_value_set(data[2]);
        this->ctlin_03_status = 0;
    }
}

void ctlin_04_outchannel_set(number ) {}

void ctlin_04_outcontroller_set(number ) {}

void fromnormalized_04_output_set(number v) {
    this->param_04_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(3, v));
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->fromnormalized_04_input_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 * this->expr_16_in2);//#map:expr_16:1
}

void ctlin_04_value_set(number v) {
    this->expr_16_in1_set(v);
}

void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
        this->ctlin_04_outchannel_set(channel);
        this->ctlin_04_outcontroller_set(data[1]);
        this->ctlin_04_value_set(data[2]);
        this->ctlin_04_status = 0;
    }
}

void p_03_perform(Index n) {
    // subpatcher: FreqCalc
    this->p_03->process(nullptr, 0, nullptr, 0, n);
}

void linetilde_02_perform(SampleValue * out, Index n) {
    auto __linetilde_02_time = this->linetilde_02_time;
    auto __linetilde_02_keepramp = this->linetilde_02_keepramp;
    auto __linetilde_02_currentValue = this->linetilde_02_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_02_activeRamps->length)) {
        while ((bool)(this->linetilde_02_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_02_activeRamps[0];
            number inc = this->linetilde_02_activeRamps[1];
            number rampTimeInSamples = this->linetilde_02_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_02_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_02_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_02_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1621164530,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_02_keepramp))) {
                        __linetilde_02_time = 0;
                    }
                }
            }

            __linetilde_02_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_02_currentValue;
        i++;
    }

    this->linetilde_02_currentValue = __linetilde_02_currentValue;
    this->linetilde_02_time = __linetilde_02_time;
}

void phasor_01_perform(const Sample * freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_01_ph_next(freq[(Index)i], -1);
        this->phasor_01_sigbuf[(Index)i] = -1;
    }
}

void linetilde_03_perform(SampleValue * out, Index n) {
    auto __linetilde_03_time = this->linetilde_03_time;
    auto __linetilde_03_keepramp = this->linetilde_03_keepramp;
    auto __linetilde_03_currentValue = this->linetilde_03_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_03_activeRamps->length)) {
        while ((bool)(this->linetilde_03_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_03_activeRamps[0];
            number inc = this->linetilde_03_activeRamps[1];
            number rampTimeInSamples = this->linetilde_03_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_03_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_03_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_03_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -62043057,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_03_keepramp))) {
                        __linetilde_03_time = 0;
                    }
                }
            }

            __linetilde_03_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_03_currentValue;
        i++;
    }

    this->linetilde_03_currentValue = __linetilde_03_currentValue;
    this->linetilde_03_time = __linetilde_03_time;
}

void rate_tilde_01_perform(
    const Sample * phase,
    const Sample * multiplier,
    SampleValue * out1,
    Index n
) {
    auto __rate_tilde_01_currentPhase = this->rate_tilde_01_currentPhase;
    auto __rate_tilde_01_prev = this->rate_tilde_01_prev;
    auto __rate_tilde_01_diff = this->rate_tilde_01_diff;
    auto __rate_tilde_01_wantlock = this->rate_tilde_01_wantlock;
    auto __rate_tilde_01_invmult = this->rate_tilde_01_invmult;
    auto __rate_tilde_01_mult = this->rate_tilde_01_mult;
    Index i;

    for (i = 0; i < n; i++) {
        if (multiplier[(Index)i] != __rate_tilde_01_mult && (bool)(!(bool)(rnbo_isnan(multiplier[(Index)i])))) {
            __rate_tilde_01_mult = multiplier[(Index)i];
            __rate_tilde_01_invmult = this->safediv(1.0, __rate_tilde_01_mult);
            __rate_tilde_01_wantlock = 1;
        }

        __rate_tilde_01_diff = phase[(Index)i] - __rate_tilde_01_prev;

        if (__rate_tilde_01_diff < -0.5) {
            __rate_tilde_01_diff += 1;
        } else if (__rate_tilde_01_diff > 0.5) {
            __rate_tilde_01_diff -= 1;
        }

        __rate_tilde_01_currentPhase += __rate_tilde_01_diff * __rate_tilde_01_invmult;

        if (__rate_tilde_01_currentPhase > 1.0 || __rate_tilde_01_currentPhase < -0.0) {
            __rate_tilde_01_currentPhase = __rate_tilde_01_currentPhase - rnbo_floor(__rate_tilde_01_currentPhase);
        }

        __rate_tilde_01_prev = phase[(Index)i];
        out1[(Index)i] = __rate_tilde_01_currentPhase;
        continue;
    }

    this->rate_tilde_01_mult = __rate_tilde_01_mult;
    this->rate_tilde_01_invmult = __rate_tilde_01_invmult;
    this->rate_tilde_01_wantlock = __rate_tilde_01_wantlock;
    this->rate_tilde_01_diff = __rate_tilde_01_diff;
    this->rate_tilde_01_prev = __rate_tilde_01_prev;
    this->rate_tilde_01_currentPhase = __rate_tilde_01_currentPhase;
}

void linetilde_04_perform(SampleValue * out, Index n) {
    auto __linetilde_04_time = this->linetilde_04_time;
    auto __linetilde_04_keepramp = this->linetilde_04_keepramp;
    auto __linetilde_04_currentValue = this->linetilde_04_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_04_activeRamps->length)) {
        while ((bool)(this->linetilde_04_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_04_activeRamps[0];
            number inc = this->linetilde_04_activeRamps[1];
            number rampTimeInSamples = this->linetilde_04_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_04_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_04_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_04_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        1114681293,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_04_keepramp))) {
                        __linetilde_04_time = 0;
                    }
                }
            }

            __linetilde_04_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_04_currentValue;
        i++;
    }

    this->linetilde_04_currentValue = __linetilde_04_currentValue;
    this->linetilde_04_time = __linetilde_04_time;
}

void p_05_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out1,
    Index n
) {
    // subpatcher: PitchShift~
    ConstSampleArray<3> ins = {in1, in2, in3};

    SampleArray<1> outs = {out1};
    this->p_05->process(ins, 3, outs, 1, n);
}

void p_04_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out1,
    Index n
) {
    // subpatcher: PitchShift~
    ConstSampleArray<3> ins = {in1, in2, in3};

    SampleArray<1> outs = {out1};
    this->p_04->process(ins, 3, outs, 1, n);
}

void p_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: Switch~
    ConstSampleArray<5> ins = {in1, in2, in3, in4, in5};

    SampleArray<2> outs = {out1, out2};
    this->p_02->process(ins, 5, outs, 2, n);
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: Mix~
    ConstSampleArray<4> ins = {in1, in2, in3, in4};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 4, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_18_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -24) {
        localvalue = -24;
    }

    if ((bool)(true) && localvalue > 24) {
        localvalue = 24;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_18_value = localvalue;
}

void numberobj_19_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_19_value = localvalue;
}

void numberobj_20_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_20_value = localvalue;
}

void numberobj_21_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_21_value = localvalue;
}

void numberobj_22_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_22_value = localvalue;
}

void numberobj_23_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_23_value = localvalue;
}

void numberobj_24_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 2) {
        localvalue = 2;
    }

    if ((bool)(true) && localvalue > 200) {
        localvalue = 200;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_24_value = localvalue;
}

void numberobj_18_init() {
    this->numberobj_18_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-63"), 1, this->_currentTime);
}

void numberobj_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_18_value;
}

void numberobj_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_18_value_set(preset["value"]);
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void numberobj_19_init() {
    this->numberobj_19_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-82"), 1, this->_currentTime);
}

void numberobj_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_19_value;
}

void numberobj_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_19_value_set(preset["value"]);
}

number phasor_01_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_01_ph_conv;

    if (this->phasor_01_ph_currentPhase < 0.)
        this->phasor_01_ph_currentPhase = 1. + this->phasor_01_ph_currentPhase;

    if (this->phasor_01_ph_currentPhase > 1.)
        this->phasor_01_ph_currentPhase = this->phasor_01_ph_currentPhase - 1.;

    number tmp = this->phasor_01_ph_currentPhase;
    this->phasor_01_ph_currentPhase += pincr;
    return tmp;
}

void phasor_01_ph_reset() {
    this->phasor_01_ph_currentPhase = 0;
}

void phasor_01_ph_dspsetup() {
    this->phasor_01_ph_conv = (number)1 / this->sr;
}

void phasor_01_dspsetup(bool force) {
    if ((bool)(this->phasor_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_01_conv = (number)1 / this->samplerate();
    this->phasor_01_setupDone = true;
    this->phasor_01_ph_dspsetup();
}

void numberobj_20_init() {
    this->numberobj_20_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-51"), 1, this->_currentTime);
}

void numberobj_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_20_value;
}

void numberobj_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_20_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void numberobj_21_init() {
    this->numberobj_21_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-24"), 1, this->_currentTime);
}

void numberobj_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_21_value;
}

void numberobj_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_21_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void rate_tilde_01_reset() {
    this->rate_tilde_01_currentPhase = 0;
    this->rate_tilde_01_diff = 0;
    this->rate_tilde_01_prev = 0;
    this->rate_tilde_01_mult = 1;
    this->rate_tilde_01_invmult = 1;
    this->rate_tilde_01_wantlock = 1;
    this->rate_tilde_01_quant = 1;
}

void rate_tilde_01_dspsetup(bool force) {
    if ((bool)(this->rate_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->rate_tilde_01_reset();
    this->rate_tilde_01_setupDone = true;
}

void numberobj_22_init() {
    this->numberobj_22_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-31"), 1, this->_currentTime);
}

void numberobj_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_22_value;
}

void numberobj_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_22_value_set(preset["value"]);
}

void numberobj_23_init() {
    this->numberobj_23_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-4"), 1, this->_currentTime);
}

void numberobj_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_23_value;
}

void numberobj_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_23_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void numberobj_24_init() {
    this->numberobj_24_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-70"), 1, this->_currentTime);
}

void numberobj_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_24_value;
}

void numberobj_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_24_value_set(preset["value"]);
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    number diffInBeats = diff * this->globaltransport_getTempo(time) * 0.008 / (number)480;
    return beatTimeBase + diffInBeats;
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample((SampleIndex)(offset)) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
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

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = (MillisecondTime)(this->sampstoms(sampleOffset));
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
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
    p_01_target = 0;
    p_02_target = 0;
    p_03_target = 0;
    numberobj_18_value = 0;
    numberobj_18_value_setter(numberobj_18_value);
    param_01_value = 0;
    numberobj_19_value = 0;
    numberobj_19_value_setter(numberobj_19_value);
    linetilde_02_time = 50;
    linetilde_02_keepramp = 1;
    p_04_target = 0;
    phasor_01_freq = 0;
    numberobj_20_value = 0;
    numberobj_20_value_setter(numberobj_20_value);
    param_02_value = 50;
    numberobj_21_value = 0;
    numberobj_21_value_setter(numberobj_21_value);
    param_03_value = 0;
    p_05_target = 0;
    rate_tilde_01_phase = 0;
    rate_tilde_01_multiplier = 1;
    numberobj_22_value = 0;
    numberobj_22_value_setter(numberobj_22_value);
    linetilde_03_time = 50;
    linetilde_03_keepramp = 1;
    numberobj_23_value = 0;
    numberobj_23_value_setter(numberobj_23_value);
    mstosamps_01_ms = 0;
    param_04_value = 80;
    linetilde_04_time = 50;
    linetilde_04_keepramp = 1;
    numberobj_24_value = 0;
    numberobj_24_value_setter(numberobj_24_value);
    ctlin_01_input = 0;
    ctlin_01_controller = 2;
    ctlin_01_channel = -1;
    expr_13_in1 = 0;
    expr_13_in2 = 0.007874015748;
    expr_13_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 4;
    ctlin_02_channel = -1;
    expr_14_in1 = 0;
    expr_14_in2 = 0.007874015748;
    expr_14_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 3;
    ctlin_03_channel = -1;
    expr_15_in1 = 0;
    expr_15_in2 = 0.007874015748;
    expr_15_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 1;
    ctlin_04_channel = -1;
    expr_16_in1 = 0;
    expr_16_in2 = 0.007874015748;
    expr_16_out1 = 0;
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
    numberobj_18_currentFormat = 6;
    numberobj_18_lastValue = 0;
    param_01_lastValue = 0;
    numberobj_19_currentFormat = 6;
    numberobj_19_lastValue = 0;
    linetilde_02_currentValue = 0;
    phasor_01_sigbuf = nullptr;
    phasor_01_lastLockedPhase = 0;
    phasor_01_conv = 0;
    phasor_01_ph_currentPhase = 0;
    phasor_01_ph_conv = 0;
    phasor_01_setupDone = false;
    numberobj_20_currentFormat = 6;
    numberobj_20_lastValue = 0;
    param_02_lastValue = 0;
    numberobj_21_currentFormat = 6;
    numberobj_21_lastValue = 0;
    param_03_lastValue = 0;
    rate_tilde_01_currentPhase = 0;
    rate_tilde_01_diff = 0;
    rate_tilde_01_prev = 0;
    rate_tilde_01_mult = 1;
    rate_tilde_01_invmult = 1;
    rate_tilde_01_wantlock = 1;
    rate_tilde_01_quant = 1;
    rate_tilde_01_setupDone = false;
    numberobj_22_currentFormat = 6;
    numberobj_22_lastValue = 0;
    linetilde_03_currentValue = 0;
    numberobj_23_currentFormat = 6;
    numberobj_23_lastValue = 0;
    param_04_lastValue = 0;
    linetilde_04_currentValue = 100;
    numberobj_24_currentFormat = 6;
    numberobj_24_lastValue = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
    ctlin_02_status = 0;
    ctlin_02_byte1 = -1;
    ctlin_02_inchan = 0;
    ctlin_03_status = 0;
    ctlin_03_byte1 = -1;
    ctlin_03_inchan = 0;
    ctlin_04_status = 0;
    ctlin_04_byte1 = -1;
    ctlin_04_inchan = 0;
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

    number p_01_target;
    number p_02_target;
    number p_03_target;
    number numberobj_18_value;
    number param_01_value;
    number numberobj_19_value;
    list linetilde_02_segments;
    number linetilde_02_time;
    number linetilde_02_keepramp;
    number p_04_target;
    number phasor_01_freq;
    number numberobj_20_value;
    number param_02_value;
    number numberobj_21_value;
    number param_03_value;
    number p_05_target;
    number rate_tilde_01_phase;
    number rate_tilde_01_multiplier;
    number numberobj_22_value;
    list linetilde_03_segments;
    number linetilde_03_time;
    number linetilde_03_keepramp;
    number numberobj_23_value;
    number mstosamps_01_ms;
    number param_04_value;
    list linetilde_04_segments;
    number linetilde_04_time;
    number linetilde_04_keepramp;
    number numberobj_24_value;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[5];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    Int numberobj_18_currentFormat;
    number numberobj_18_lastValue;
    number param_01_lastValue;
    Int numberobj_19_currentFormat;
    number numberobj_19_lastValue;
    list linetilde_02_activeRamps;
    number linetilde_02_currentValue;
    signal phasor_01_sigbuf;
    number phasor_01_lastLockedPhase;
    number phasor_01_conv;
    number phasor_01_ph_currentPhase;
    number phasor_01_ph_conv;
    bool phasor_01_setupDone;
    Int numberobj_20_currentFormat;
    number numberobj_20_lastValue;
    number param_02_lastValue;
    Int numberobj_21_currentFormat;
    number numberobj_21_lastValue;
    number param_03_lastValue;
    SampleValue rate_tilde_01_currentPhase;
    SampleValue rate_tilde_01_diff;
    SampleValue rate_tilde_01_prev;
    SampleValue rate_tilde_01_mult;
    SampleValue rate_tilde_01_invmult;
    int rate_tilde_01_wantlock;
    int rate_tilde_01_quant;
    bool rate_tilde_01_setupDone;
    Int numberobj_22_currentFormat;
    number numberobj_22_lastValue;
    list linetilde_03_activeRamps;
    number linetilde_03_currentValue;
    Int numberobj_23_currentFormat;
    number numberobj_23_lastValue;
    number param_04_lastValue;
    list linetilde_04_activeRamps;
    number linetilde_04_currentValue;
    Int numberobj_24_currentFormat;
    number numberobj_24_lastValue;
    int ctlin_01_status;
    int ctlin_01_byte1;
    int ctlin_01_inchan;
    int ctlin_02_status;
    int ctlin_02_byte1;
    int ctlin_02_inchan;
    int ctlin_03_status;
    int ctlin_03_byte1;
    int ctlin_03_inchan;
    int ctlin_04_status;
    int ctlin_04_byte1;
    int ctlin_04_inchan;
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
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_68* p_01;
    RNBOSubpatcher_69* p_02;
    RNBOSubpatcher_70* p_03;
    RNBOSubpatcher_71* p_04;
    RNBOSubpatcher_72* p_05;

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

