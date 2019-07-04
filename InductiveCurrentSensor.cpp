/**
 * @file InductiveCurrentSensor.cpp
 * @author Thomas Novotny
 * @brief Library for reading data from an inductive current sensor
 * @version 0.1
 * 
 */
#include "InductiveCurrentSensor.h"

#define MEASURE_DURATION 	20 		// 20ms = 1 cycle of a 50Hz wave
#define ADC_RANGE 			1024	// ATMega328 ADC 10 bit Range
#define AREF				3.3		// Analog reference voltage [V]

/**
 * @brief Measures the average absolute value of the input signal
 * 
 * @return float 
 */
int m;

float measure_average() {
	unsigned long endtime = millis() + MEASURE_DURATION;
	int val;
	long s = 0;
	long sum = 0;
	int i;

	for (i = 0; millis() < endtime; i++) {
		val = analogRead(A0);
		s += abs(val - m);
		sum += val;
	}

	m = sum/i;
	return ((float) s) / ((float) i) * ((AREF * 1000.0) / (float) ADC_RANGE);
}

/**
 * @brief Measures amplitude
 * Measures the double amplitude of the analog input signal by calculating
 * the difference between the minimum and the maximum
 * 
 * @return Amplitude in mV
 */
float measure_amplitude() {
	unsigned long endtime = millis() + MEASURE_DURATION;
	int val, i;
	int min = ADC_RANGE, max = 0;

	// Measure for 20ms
	for (i = 0; millis() < endtime; i++) {
		val = analogRead(A0);
		if (val > max)
			max = val;
		if (val < min)
			min = val;
	}
	return ((float) max - min) * ((AREF * 1000.0) / (float) ADC_RANGE); // result in mV
}
