#pragma once
#include "Vector3D.h"

struct ProcessedData {
  float altitude;
  Vector3D orientation;
  Vector3D angularVelocity;
  Vector3D linearAcceleration;
  Vector3D netAcceleration;
};

struct RawData {
  float temperature[BMPS];
  float pressure[BMPS];
  float altitude[BMPS];
  Vector3D orientation;
  Vector3D angularVelocity;
  Vector3D linearAcceleration;
  Vector3D netAcceleration;
};

class DataInterface {
  public:
    static DataInterface* getInstance() {
      static DataInterface* instance = nullptr;
      if (!instance) {
        instance = new DataInterface();
        instance->processedData = new ProcessedData();
        instance->rawData = new RawData();
      }
      return instance;
    }
    ProcessedData& getProcessedData() {
      return *processedData;
    }
    RawData& getRawData() {
      return *rawData;
    }
  private:
    ProcessedData* processedData;
    RawData* rawData;
};
