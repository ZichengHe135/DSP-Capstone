#pragma once
#ifndef RCH_OSCILLATORS_Sampler_H_INCLUDED
#define RCH_OSCILLATORS_Sampler_H_INCLUDED
// ---- MODULE CODE STARTS BELOW ---- //


// Convenience definitions for this oscillator
#define OSCILLATOR_TYPE     Oscillators::Templates::Sampler
#define OSCILLATOR_WRAPPER  Helpers::Wrapper


/** Creates a multi-channel capable Sampler wave generator.
    This will generate a MONO oscillator wave and duplicate
    it to all channels of a passed sample buffer. */
class Sampler : private OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>
{
public:
    
    Sampler  () {}
    ~Sampler () {}
    
    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::reset;
    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::setup;
    
    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::tick;
    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::noteOff;

    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::fill;
    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::add;

    using OSCILLATOR_WRAPPER<OSCILLATOR_TYPE>::settheBuffer;


}; // end class RCH::Oscillators::Sampler


// Just cleaning up
#undef OSCILLATOR_WRAPPER
#undef OSCILLATOR_TYPE


// ---- MODULE CODE ENDS ABOVE ---- //
#endif // #ifndef RCH_OSCILLATORS_Sampler_H_INCLUDED
