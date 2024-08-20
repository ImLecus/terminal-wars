#include "include/config.hpp"
using namespace std;

int main(){
    cout << "Hello world!" << endl;
    Infantery u = Infantery(Colors::RED);
    u.print();

    for(int i = 0; i < 10; ++i){
        for(int i = 0; i < 20; ++i){
            GrassTile g = GrassTile();
            g.print();
        }
        std::cout << std::endl;
    }

    return 0;
}
