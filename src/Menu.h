#ifndef _MENU_H_
#define _MENU_H_
#include <vector>   // std::vector
#include <sstream>  // std::istringstream
#include <fstream>  // std::ifstream
struct Meal
{
    int _prepTime;
    std::string _name;
};

enum OrderType {
    takeOut,
    sitDown,
    thatsAllFolks
};

struct MealOrder
{
    Meal _meal;
    int _orderNumber;
    OrderType _orderType;
};

class Menu
{
    private:
        std::string _fileName;
        std::vector<Meal> _menu;
        void _readMenuFromFile();

    public:
        Menu(std::string file):_fileName(file){}
        std::vector<Meal> && getMenu()
        {
            _readMenuFromFile();
            return std::move(_menu);
        };
};
#endif