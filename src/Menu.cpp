#include "Menu.h"
/**
 * @brief Reads the menu file and fills in the structure. It is assumed that
 * the menu file is present. The menu file is expected to have data arranged in
 * a specific format. For more on how the data needs to arranged, please refer
 * to ../data/Menu.txt. It then populates the vector of structures in the same
 * class object.
 *
 */
void Menu::_readMenuFromFile()
{
    // load file with answer graph elements
    std::ifstream file(this->_fileName);
    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            std::istringstream sline(lineStr);
            Meal _mealObj;
            sline >> _mealObj._name >> _mealObj._prepTime;
            // We are using emplace_back to avoid the additional memory copy.
            this->_menu.emplace_back(_mealObj);
        }
    }
}