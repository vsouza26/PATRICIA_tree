#pragma once
#include "NODES.hpp"
#include <fstream>
#include <iostream>
//EXTENSÃO DO ARQUIVO PRECISA SER .DAT
class PATRICIATREE
{
private:
  INode *raiz;
  int bit(int i, char c);
  std::string nomeArquivo;
  int nBitsChave;
  int writeToFile(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes);
  FileNode readFromFile(int offset);
public:
  PATRICIATREE(std::string nomeArquivo);
  ENode *insertNode(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes);
};