#ifndef SCRIPTOR_H
#define SCRIPTOR_H
#include <fstream>

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
class Scriptor{
private:
  std::map<std::string , int> first;

public:

  Scriptor(std::string _i_fichero);
  short Dame_valor_de(std::string _i_nombre);
  void crear(std::string _i_fichero);

  ~Scriptor();

};

#endif
