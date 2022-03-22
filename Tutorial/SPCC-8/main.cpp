#include "Shapes.h"
#include <sstream>
namespace E1 {

}

int main(int argc, char** argv) {
    Circle* c1 = new Circle();
    c1->SetColour("Red");
    c1->SetRadius(5.3);
    c1->Print();

    std::stringstream ss;
    c1->Serialise(ss);
    std::cout << std::endl << ss.str() << std::endl;

    Circle* c2 = new Circle();
    c2->UnSerialise(ss);
    c2->Print();

    delete c1;
    delete c2;

    return 0;
}