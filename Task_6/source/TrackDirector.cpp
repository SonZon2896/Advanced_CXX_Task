#include "../header/TrackDirector.h"

void TrackDirector::Construct(const std::vector<Checkpoint*>& Checkpoints) {
  if (builder) {
    for (const auto& checkpoint : Checkpoints) {
      builder->AddCheckpoint(checkpoint);
    }
    builder->Build();
  }
}
