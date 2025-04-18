#include "../header/TrackBuilder.h"

void TrackBuilder::AddCheckpoint(Checkpoint* Checkpoint) {
  checkpoints.push_back(Checkpoint);
}

void TextReportBuilder::Build() {
  std::cout << "=== Checkpoints List ===" << std::endl;
  int index = 1;
  for (const auto& checkpoint : checkpoints) {
    std::cout << index++ << ". " << checkpoint->GetName() << " ("
              << checkpoint->GetX() << ", " << checkpoint->GetY() << ") - ";

    if (checkpoint->GetType() == Checkpoint::Type::Optional) {
      std::cout << "penalty: " << checkpoint->GetPenalty();
    } else {
      std::cout << "fail";
    }

    std::cout << std::endl;
  }
}

void PenaltyCalculatorBuilder::Build() {
  double totalPenalty = 0;
  for (const auto& checkpoint : checkpoints) {
    totalPenalty += checkpoint->GetPenalty();
  }
  std::cout << "=== Summary Penalty ===" << std::endl;
  std::cout << "TotalPenalty: " << totalPenalty << std::endl;
}
