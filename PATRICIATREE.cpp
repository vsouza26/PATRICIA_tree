#include <iostream>
#include "PATRICIATREE.hpp"

int PATRICIATREE::bit(int i, char c){ //retorna o bit da posição i no caracter C.
  if (i == 0) return 0;
  int k = (int)c;
  for(int j = 1; j <= this->nBitsChave - i; i++) k = k/2;
  return k%2;
}

PATRICIATREE::PATRICIATREE(std::string nomeArquivo)
{
  this->nomeArquivo = nomeArquivo;
  this->nBitsChave = 30;
}

int PATRICIATREE::writeToFile(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char * traducoes){
  std::ofstream fd(this->nomeArquivo, std::ios::binary | std::ios::app);//File Descriptor que abre o arquivo em binário e em modo de adiciona ao final
  FileNode fn = FileNode(classeMorfologica, palavraOriginal, numTraducoes, traducoes);
  int pointer = fd.tellp();
  fd.write((char*)&fn, sizeof(FileNode));
  fd.close();
  return pointer;
}

ENode *PATRICIATREE::insertNode(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes){
  //se já houver palavra inserida
  //se procuraArvore(palavraOriginal) 
  
  //se precisar escrever um novo arquivo
  int pointer = this->writeToFile(palavraOriginal, classeMorfologica, numTraducoes, traducoes);
  ENode *en = new ENode(pointer);
  return en;
}

FileNode PATRICIATREE::readFromFile(int offset){
  std::ifstream fd(this->nomeArquivo, std::ios::binary | std::ios::in); //File descriptor que lê o arquivo nomeArquivo no offset e retorna o FileNode
  fd.seekg(offset);
  FileNode fn; //FileNode a ser populado
  fd.read((char *)&fn, sizeof(FileNode));
  fd.close();
  return fn;
}