# INTRO

[![Build Status](https://travis-ci.com/opokatech/embedded_toolbox.svg?branch=master)](https://travis-ci.com/opokatech/embedded_toolbox)

This repository contains a bunch of c++ classes which might be useful for embedded system.

It was created to demonstrate TDD in action and just published afterwards.
The resulting video was split into 2 parts:

- [introduction](https://vimeo.com/436232709)
- [TDD session](https://vimeo.com/436232138)


## DigitalInput

This class represent an input we can get from a digital source. This can be for example a button.  However due to
mechanical nature of switches it may happen that for a short time around switch time the state is not really clear, it
changes frequently until it settles to some value. Reading all values as they arrive would result in passing all that
noise to other part of the system.

To avoid this we can use so called debouncing.
In its simplest form it is a mechanism that user "feeds" with the raw digital input value and the rest of the system can
read the "final" value out of it. The final value is most of the time the same as the raw value, however a change to a
new value occurs only if a raw value is stable for either some time or some number of samples. In this example we use
samples.

Interface:

    * set raw value - feed the object with a new value,
    * is active - returns already debounced state,
    * get/set debounce samples - how many samples are used for debouncing,

## AnalogInput

This class implements a smoothing of a value taken as some analog input by using moving average.
TODO.
