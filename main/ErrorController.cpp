/*//#include "ErrorCorrection.h" 
#include <stdlib.h>

//TODO: previous value for threshold, compare each data point with prev to decide if it should be disregarded

float _threshold;
float prev_value = 0;

void ErrorCorrection::init(float threshold) {
  _threshold = threshold;
 // nf = new NoiseFiltering();
}

float ErrorCorrection::correctData(float data[]){
  //TODO: call nf to update prev value
}

float ErrorCorrection::getAverage(float data[]){
  int data_count = 0;
  float sum = 0;
  int arraylength = sizeof(data)/sizeof(*data);

  for(int i=0; i<arraylength; i++){
    if(abs(data[i] - prev_value) < _threshold){
      sum += data[i];
      data_count++;
    }
  } 
  return sum/data_count;
}

// float ErrorCorrection::getAverage(float data[]){
//   int data_count = 0;
//   float sum = 0;
//   int arraylength = sizeof(data)/sizeof(*data);

//   int agreementCount[arraylength];

//   for(int i=0; i<arraylength; i++){
//     for(int j=i+1; j < arraylength; j++){
//       if(abs(data[i] - data[j]) < _threshold){
//         agreementCount[i]++;
//         agreementCount[j]++;
//       }
//     }
//     if(agreementCount[i] >= arraylength/2){
//       sum += data[i];
//       data_count ++;
//     }
//   }
//   return sum/data_count;
// }

bool ErrorCorrection::getAverage(bool data[]){
  int true_count = 0;
  int false_count = 0;
  int arraylength = sizeof(data)/sizeof(*data);

  for (int i=0; i<arraylength; i++){
    if (data[i] == true){
      true_count ++;
    }
    else{
      false_count ++;
    }
  }

  if (true_count > false_count){
    return true;
  }
  else{
    return false;
  }
}*/
