#include "Interface.h"

int main(){

    try {
        Interface &inter = Interface::interface();
        inter.aircraft_conveyor();
    }
    catch(Validator){
        std::cin.clear();
        std::cerr << "Error input data!" << std::endl;
    }
    catch (const boost::property_tree::ptree_bad_data& error){
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
