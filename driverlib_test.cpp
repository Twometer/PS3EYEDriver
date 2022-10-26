//
// Created by twome on 26/10/2022.
//

#include "driverlib.cpp"

int main() {
    auto cam = open_camera(0, 1, 75, 1);
    std::vector<uint8_t> vec;
    vec.reserve(unsigned(stride(cam) * height(cam)));

    printf("exp: %d\n", exposure(cam));

    for (;;)
        if (!get_frame(cam, (uint8_t *) vec.data()))
            break;
        else
            printf("frame!");

    printf("exit");
}