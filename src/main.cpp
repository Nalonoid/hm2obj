#include <iostream>
#include "formats.hpp"

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        std::cout << "usage: " << argv[0]
                  << " src.ppm dst.obj [is_src_rgb={0,1}]" << std::endl;
        return 1;
    }

    bool is_rgb = argc == 4 ? static_cast<bool>(std::stoi(argv[3])) : true;

    std::cout << "Hello hm2obj! :-)\n" << std::endl;

    PPM ppm_img(argv[1], is_rgb);
    OBJ obj(ppm_img);

    obj.save(argv[2]);

    std::cout << "\nBye hm2obj... :-(" << std::endl;

    return 0;
}
