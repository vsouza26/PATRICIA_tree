#include "NODES.hpp"
#include <iostream>
#include <fstream>
int main(){
    std::ofstream test("teste");
    char test2[6] = "teste";
    FileNode Node = FileNode('c', test2, test2);
    for (int i = 0; i < 9; i++){
        Node.setPIDestino(test2);
    }
    test.write((char*)&Node, sizeof(Node));
}