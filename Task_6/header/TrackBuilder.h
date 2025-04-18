#pragma once

#include <iostream>
#include <vector>

#include "Checkpoint.h"

class TrackBuilder {
 protected:
  std::vector<Checkpoint*> checkpoints;

 public:
  void AddCheckpoint(Checkpoint* Checkpoint);
  virtual void Build() = 0;
};

class TextReportBuilder : public TrackBuilder {
  virtual void Build() override;
};

class PenaltyCalculatorBuilder : public TrackBuilder {
  virtual void Build() override;
};
