#pragma once

#include "Checkpoint.h"
#include "TrackBuilder.h"

class TrackDirector {
 private:
  TrackBuilder* builder;

 public:
  void SetBuilder(TrackBuilder* Builder) { builder = Builder; }

  void Construct(const std::vector<Checkpoint*>& Checkpoints);
};
