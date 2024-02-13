#include <iostream>
#include <utility>
#include <vector>
#include "P2PNode.hh"
int main(int argc, char const *argv[]) {
    P2PNode node;
    std::cout << "Init node" << std::endl;
    node.init();
    std::cout << "Start node" << std::endl;
    node.start();
    return 0;
}
