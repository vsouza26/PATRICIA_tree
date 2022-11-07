#include "main.hpp"
int main(){
  PATRICIATREE ptree = PATRICIATREE("saida.dat");
  char palavraOriginal[30] = {'d','o','r','m','i','r'};
  char traducoes[500] = {'s','l','e', 'e','p'};
  char c[1] = {'c'};
  ptree.insertNode(palavraOriginal, c, 1, traducoes);
}