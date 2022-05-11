#pragma once

namespace Images {

    const uint8_t PROGMEM PPOT[] = {
#ifndef DEBUG
        65, 32, // 65x31 px image
        /*
        ⡎⠍⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⡇⢸⣏⣹⠆⣿⣉⡷⢸⣏⡉⠁⢾⣉⡓⠰⣏⣙⠂
        ⡇⢸⣿⢩⣫⢹⠭⠭⠭⠭⠭⠭⠭⠀⡇⠸⠇⠀⠀⠿⠙⠦⠸⠧⠤⠄⠲⠤⠟⠐⠦⠼⠃
        ⡇⢸⣿⣾⣾⢊⡭⢭⡉⠉⠉⣉⠉⠀⡇⢸⣏⣹⠆⣿⠀⠀⢠⣞⣳⡄⢿⣀⡿⢸⣷⣄⠀
        ⡇⢸⣿⣿⣿⠸⣌⣢⠇⠉⠁⣿⠀⠀⡇⠸⠇⠀⠀⠿⠤⠤⠸⠇⠸⠇⠀⠿⠀⠸⠟⠁⠀
        ⡇⢸⣿⠛⠛⢳⠶⡶⡶⡶⢶⠶⡶⠀⡇⢰⡏⢹⡆⣿⣦⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⡇⠈⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠀⡇⠘⠧⠼⠃⠿⠈⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⡇⠀⠀⡰⠉⣉⠉⠉⣉⠉⠉⠉⠉⠀⡇⠈⢹⡏⠁⣴⣛⣦⢸⣏⣹⠆⣿⣉⠉⠀⠀⠀⠀
        ⠣⠥⠤⠧⠤⠭⠤⠤⠭⠤⠤⠤⠤⠀⠇⠀⠸⠇⠀⠿⠀⠿⠸⠇⠀⠀⠿⠤⠤⠀⠀⠀⠀
        */
        0xfe, 0x01, 0x05, 0xf1, 0xf1, 0xf1, 0x11, 0xd1, 0xb1, 0xd1, 0x11, 0xf1, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x19, 0x39, 0x6f, 0x46, 0x00, 0x7f, 0x7f, 0x49, 0x49, 0x41, 0x41, 0x00, 0x26, 0x6f, 0x49, 0x49, 0x7b, 0x32, 0x00, 0x26, 0x6f, 0x49, 0x49, 0x7b, 0x32, 
        0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0x02, 0x79, 0xcd, 0x95, 0xa5, 0xcd, 0x79, 0x01, 0x11, 0x11, 0x11, 0x01, 0xf9, 0xf9, 0x01, 0x01, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x00, 0x7c, 0x7e, 0x0b, 0x0b, 0x7e, 0x7c, 0x00, 0x07, 0x0f, 0x78, 0x78, 0x0f, 0x07, 0x00, 0x7F, 0x7F, 0x3E, 0x1C, 0x08, 0x00,
        0xff, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x3e, 0x36, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x00, 0x00, 0xff, 0x00, 0x00, 0x3e, 0x7f, 0x41, 0x41, 0x7f, 0x3e, 0x00, 0x7f, 0x7f, 0x0e, 0x1c, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x3f, 0x40, 0x50, 0x40, 0x40, 0x40, 0x78, 0x46, 0x41, 0x41, 0x59, 0x59, 0x41, 0x41, 0x41, 0x41, 0x59, 0x59, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x01, 0x01, 0x7f, 0x7f, 0x01, 0x01, 0x00, 0x7c, 0x7e, 0x0b, 0x0b, 0x7e, 0x7c, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x49, 0x49, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
#else
        1,1,1
#endif
    };

//  const uint8_t PROGMEM PPOT_Blank[] = {
//      5, 8, // 5x7 px image
//      0x00, 0x00, 0x00, 0x00, 0x00
//  };
//
//  const uint8_t PROGMEM PPOT_Pixel[] = {
//      1, 8,  // 1x8 px images
//      0x11,  // ▓▓▓░▓▓▓░ Frame 0
//      0x31,  // ▓▓░░▓▓▓░ Frame 1
//      0x51,  // ▓░▓░▓▓▓░ Frame 2
//      0x91   // ░▓▓░▓▓▓░ Frame 3
//  };
//
//  const uint8_t PROGMEM PPOT_Spindle[] = {
//      2, 8,  // 2x8 px image
//      0xA5,  // ░▓░▓▓░▓░
//      0x95   // ░▓▓░▓░▓░
//  };

}