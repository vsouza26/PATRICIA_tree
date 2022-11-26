#include <iostream>
#include <cstdio>
#include <cstring>
#include "PATRICIATREE.hpp"
class FHandler{
  PATRICIATREE *arvore;
  public:
  FHandler();
  void handleInput(char c);
  void insereTraducao();
  void listaPalavrasOrigem();
  void listaTraducoes();
  void consultaClasse();
  void removePalavra();
  void imprimeArvore();
  void listaClasse();
};