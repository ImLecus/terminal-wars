#include "include/config.hpp"
int main(){

    struct termios t;
    struct termios t_saved;
    tcgetattr(fileno(stdin), &t);
    t_saved = t;
    t.c_lflag &= (~ICANON & ~ECHO);
    t.c_cc[VTIME] = 0;
    t.c_cc[VMIN] = 1;
    if (tcsetattr(fileno(stdin), TCSANOW, &t) < 0) {
        perror("Unable to set terminal to single character mode");
        return -1;
    }

    Map my_map = Map("./maps/example.map");
    Game game = Game(&my_map);

    my_map.claim(5,0, Colors::RED);
    my_map.claim(3,1, Colors::RED);
    my_map.claim(7,2, Colors::RED);
    my_map.addUnit( Infantery(Colors::RED, 5,2));
    my_map.addUnit( Infantery(Colors::RED, 2,1));
    my_map.addUnit( Mechanized(Colors::RED, 6,1));

    my_map.claim(21,2, Colors::GREEN);
    my_map.addUnit( Infantery(Colors::GREEN, 21,1));

    my_map.addUnit( Tank(Colors::BLUE,8,8));
    my_map.addUnit( Infantery(Colors::BLUE, 6,7));
    my_map.claim(6,7, Colors::BLUE);
    my_map.claim(7,6, Colors::BLUE);

    my_map.addUnit( Infantery(Colors::YELLOW, 36,3));
    my_map.claim(36,2, Colors::YELLOW);
  
    game.start();
    
    
    
    if (tcsetattr(fileno(stdin), TCSANOW, &t_saved) < 0) {
        perror("Unable to restore terminal mode");
        return -1;
    }
    return 0;
}
