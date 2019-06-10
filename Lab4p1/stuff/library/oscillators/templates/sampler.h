#pragma once
#ifndef RCH_OSCILLATORS_TEMPLATES_SAMPLER_H_INCLUDED
#define RCH_OSCILLATORS_TEMPLATES_SAMPLER_H_INCLUDED
// ---- MODULE CODE STARTS BELOW ---- //


// SAMPLER WAVE OSCILLATOR
//
// Implemented after Alan Wolfe's AdvanceOscilator_Sampler() function
// https://blog.demofox.org/2012/05/19/diy-synthesizer-chapter-2-common-wave-forms/
//
/** Creates a mono per-sample sampler wave oscillator. */
class Sampler : private Helpers::Skeleton
{
public:
    
    Sampler  () {}
    ~Sampler () {}
    
    //==============================================================================
    using Helpers::Skeleton::reset;
    
    using Helpers::Skeleton::setSampleRate;
    using Helpers::Skeleton::setFrequency;
    using Helpers::Skeleton::setAmplitude;
    using Helpers::Skeleton::setVolume;
    using Helpers::Skeleton::setState;
    using Helpers::Skeleton::setPhaseOffset;
    
    using Helpers::Skeleton::getSampleRate;
    using Helpers::Skeleton::getFrequency;
    using Helpers::Skeleton::getAmplitude;
    using Helpers::Skeleton::getVolume;
    using Helpers::Skeleton::getState;
    using Helpers::Skeleton::getPhaseOffset;
    using Helpers::Skeleton::settheBuffer;
    
    //==============================================================================
    /** Calculates and returns the next sampler wave sample. */
    const double& tick () override
    {
        // Make sure the basic values are correctly set
        if (samplerate <= 0.0) // && "Samplerate not correctly set");
        // "Frequency not correctly set");
            return state;
        
        // Increase phase by +1 step
        phase += fractionFrequency;
        
        // Constrain/wrap phase value to sensible boundaries [0,2PI]
        //
        // if (phase >= M_2PI)
        // {
        //     phase -= M_2PI;
        // }
        // else if (phase < 0.0)
        // {
        //     phase += M_2PI;
        // }
        //
        // IF-branches are slower than simple maths in time critical code, this does the same but faster
        phase += ((phase >= samplSize) * -samplSize) + ((phase < 0.0) * samplSize);  // make this check not both evaluate to true if you want looping.
        //printf("%f\n",phase);
        // Calculate sampler value for current phase step and scale to desired volume. I tried using fast
        // sampler approximations and lookup tables instead, but they added audible harmonic imperfections.
        state = (double) samplBuf[(uintptr_t)phase] * amplitude / -SHRT_MIN;
        //amplitude *= 0.99999;
        
        // Return calculated sampler value
        return state;
    }


    
}; // end class RCH::Oscillators::Templates::Sampler


// ---- MODULE CODE ENDS ABOVE ---- //
#endif // #ifndef RCH_OSCILLATORS_TEMPLATES_SAMPLER_H_INCLUDED
