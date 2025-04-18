#include "header/Checkpoint.h"
#include "header/TrackBuilder.h"
#include "header/TrackDirector.h"

int main() {
  // Создаем список контрольных пунктов
  std::vector<Checkpoint*> checkpoints = {
      new RequiredCheckpoint("Start", 55.7558, 37.6176),
      new OptionalCheckpoint("CP1", 55.7600, 37.6200, 1.5),
      new RequiredCheckpoint("CP2", 55.7650, 37.6250),
      new OptionalCheckpoint("CP3", 55.7700, 37.6300, 2.0),
      new RequiredCheckpoint("Finish", 55.7750, 37.6350)};

  // Создаем директора и строителей
  TrackDirector director;
  TextReportBuilder textBuilder;
  PenaltyCalculatorBuilder penaltyBuilder;

  // Строим текстовый отчет
  std::cout << "=== Text countdown ===" << std::endl;
  director.SetBuilder(&textBuilder);
  director.Construct(checkpoints);

  // Считаем суммарный штраф
  std::cout << "\n=== Calculate penalty ===" << std::endl;
  director.SetBuilder(&penaltyBuilder);
  director.Construct(checkpoints);

  return 0;
}
