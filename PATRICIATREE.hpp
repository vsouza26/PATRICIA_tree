#pragma once
#include "NODES.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>
// EXTENSÃO DO ARQUIVO PRECISA SER .DAT
class PATRICIATREE
{
private:
  Node *raiz;
  std::string nomeArquivo;
  int nBitsChave;
  int writeToFile(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes);
  FileNode readFromFile(int offset);
  FileNode searchTreeRec(Node *Node, char *key);
  void insertNodeRec(Node *node, char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes, int index);
  void printTreeRec(Node *node);
public:
  static int bit(int i, char c);
  static int diffBit(int i, char *key1, char *key2);
  PATRICIATREE(std::string nomeArquivo);
  void insertNode(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes);
  FileNode searchTree(char *key);
  void printTree();
};