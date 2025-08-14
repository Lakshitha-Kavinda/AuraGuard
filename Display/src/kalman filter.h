#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

class KalmanFilter {
  float estimate;
  float errorEstimate;
  float errorMeasure;
  float kalmanGain;

public:
  KalmanFilter(float initialEstimate = 0.0, float errorEstimate = 1.0, float errorMeasure = 1.0);

  float update(float measurement);
};

#endif