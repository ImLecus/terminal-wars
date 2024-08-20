#include "include/config.hpp"
using namespace std;

int main(){
    
    Map my_map = Map("./maps/example.map");
    my_map.claim(5,0, Colors::RED);
    my_map.claim(3,1, Colors::RED);
    my_map.claim(7,2, Colors::RED);
    Infantery i = Infantery(Colors::RED, 5,2);
    Infantery j = Infantery(Colors::RED, 7,1);
    my_map.addUnit(i);
    my_map.addUnit(j);
    my_map.draw();
    
    return 0;
}
