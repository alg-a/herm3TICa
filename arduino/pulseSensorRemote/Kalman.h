
#ifndef _Kalman_h
#define _Kalman_h

class Kalman {
  public:
    double q; // process noise covariance
    double r; // measurement noise covariance
    double x; // value
    double p; // estimation error covariance
    double k; // kalman gain
    
    Kalman(){
      // Custom factors, depends from the hardware we are using
      q = 0.150;
      r = 3.425;
      p = 0.3;
    }
    
    void init(double _intial_value){
      x = _intial_value;
    }
    
    double update(double measurement){
      //prediction update
      p = p + q;

      //measurement update
      k = p / (p + r);
      x = x + k * (measurement - x);
      p = (1 - k) * p;
      
      return x;
    }
  
};

#endif
