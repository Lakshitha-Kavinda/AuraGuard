#include "kalman filter.h"

KalmanFilter::KalmanFilter(float initialEstimate, float errorEstimate, float errorMeasure)
  : estimate(initialEstimate), errorEstimate(errorEstimate), errorMeasure(errorMeasure) {}

float KalmanFilter::update(float measurement) {
  // Compute Kalman Gain
  kalmanGain = errorEstimate / (errorEstimate + errorMeasure);

  // Update estimate with measurement
  estimate = estimate + kalmanGain * (measurement - estimate);

  // Update error estimate
  errorEstimate = (1.0 - kalmanGain) * errorEstimate;

  return estimate;
}