#pragma once

#include <string>

class Checkpoint {
 private:
  std::string name;
  double x, y;

 public:
  enum Type { Optional, Required };

  Checkpoint(const std::string& Name, double X, double Y)
      : name(Name), x(X), y(Y) {}

  const std::string& GetName() { return name; }
  double GetX() { return x; }
  double GetY() { return y; }
  virtual Type GetType() const = 0;
  virtual double GetPenalty() const = 0;
};

class OptionalCheckpoint : public Checkpoint {
 private:
  double penalty;

 public:
  OptionalCheckpoint(const std::string& Name, double X, double Y,
                     double Penalty)
      : Checkpoint(Name, X, Y), penalty(Penalty) {}

  virtual Type GetType() const override { return Optional; }
  virtual double GetPenalty() const override { return penalty; }
};

class RequiredCheckpoint : public Checkpoint {
 private:
 public:
  RequiredCheckpoint(const std::string& Name, double X, double Y)
      : Checkpoint(Name, X, Y) {}

  virtual Type GetType() const override { return Required; }
  virtual double GetPenalty() const override { return Optional; }
};
