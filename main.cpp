#include "include/config.hpp"
using namespace std;

int main(){
    
    Map my_map = Map("./maps/example.map");
    my_map.claim(5,0, Colors::RED);
    my_map.claim(3,1, Colors::RED);
    my_map.claim(7,2, Colors::RED);
    my_map.addUnit(Infantery(Colors::RED, 5,2));
    my_map.addUnit(Infantery(Colors::RED, 2,1));
    my_map.addUnit(Mechanized(Colors::RED, 6,1));

    my_map.claim(21,2, Colors::GREEN);
    my_map.addUnit(Infantery(Colors::GREEN, 21,1));

    my_map.addUnit(Tank(Colors::BLUE,8,8));
    my_map.addUnit(Infantery(Colors::BLUE, 6,7));
    my_map.claim(6,7, Colors::BLUE);
    my_map.claim(7,6, Colors::BLUE);

    my_map.addUnit(Infantery(Colors::YELLOW, 36,3));
    my_map.claim(36,2, Colors::YELLOW);

    my_map.draw();
    
    return 0;
}
