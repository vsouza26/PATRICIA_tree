#pragma once
#include "NODES.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <queue>
// EXTENSÃO DO ARQUIVO PRECISA SER .DAT
class PATRICIATREE
{
private:
  Node *raiz;
  std::string nomeArquivo;
  int nBitsChave;
  FileNode searchTreeRec(Node *Node, char *key);
  INode *insertNodeRec(Node *node, char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes, int index);
  void printTreeRecC(Node *node);
  void printTreeRecC(Node *node, char c);
  void printTreeRecD(Node *node);
  void printTreeRecD(Node *node, char c);
  Node *removeNodeRec(Node *node, char *palavraOriginal);
  void printTreeRec(Node *node, std::queue<char *> *fila);

public:
  static int bit(int i, char c);
  static int diffBit(int i, char *key1, char *key2);
  PATRICIATREE(std::string nomeArquivo);
  void insertNode(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes);
  FileNode searchTree(char *key);
  void removeNode(char *palavraOriginal);
  void printTree(char c);
  void printTreeClasse(char c, char c2);
  void listTranslation(char *k);
  void listClass(char *k);
  void printTree();
};