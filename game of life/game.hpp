#include <memory>

constexpr int WIDHT = 680;
constexpr int HEIGHT = 400;

class Game
{
private:
    std::unique_ptr<int[]> state;

public:
    std::unique_ptr<int[]> output;
    int n_cells;
    Game();
    ~Game();
    void update();
    int get_output(int x, int y);
};