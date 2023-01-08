#include <iostream>
#include <ctime>
#include <fstream>

class Image {
	public:
	int r, g, b;
	int itterations = 0;
	Image ( std::string name, int width, int height, std::string seed ) {
		std::ofstream image (name + ".ppm");
		image << "P3" << std::endl;
		image << width << ' ' << height << std::endl;
		image << 255 << std::endl;

		for (int y = 0; y < height; y++) {		// Repeat for all y-values.
			for (int x = 0; x < width; x++) {	// Repeat for all x-values of the given y-value.
				if (y > 6 || x > 6) {		// If the square (x, y) is NOT in the upper left  squares.
					if (seed[itterations] == '1') {		// If the value of the seed corresponding to the
						r = 0; g = 0; b = 0;			// current square is equal to 1, it will be black.
					} else {		// Otherwise it will be white.
						r = 255; g = 255; b = 255;
					}
					itterations += 1;	// Use the next char in the <seed> string.
				} else {	// If the square IS in the upper left 7 squares.
					if (x == 0 || x == 6 || y == 0 || y == 6) {		// If the value of either x or y is equal to either 0 or 6
						r = 0; g = 0; b = 0;						// the square should be black.
					} else if ((y == 2 || y == 4) && 1 < x && x < 5) {	// If y is either 2 or 4, and x is between 2 and 4
						r = 0; g = 0; b = 0;							// the square should be black.
					} else if (y == 3 && (x == 2 || x == 4)) {		// If y is 3, and x is either 2 or 4
						r = 0; g = 0; b = 0;						// the square should be black.
					} else if (y == 3 && x == 1) {			// If the square is in the point (1, 3)
						r = 0; g = 0; b = 0;				// it should be black.
					} else {	// If none of these apply, then the square should be white.
						r = 255; g = 255; b = 255;
					}
				}
				image << r << ' ' << g << ' ' << b << std::endl;	// Write this data to the <name>.ppm file.
			}
		}
	}
};

class QR_CODE {
	std::string randBinary ( int len ) {
		std::string bin;
		for (int i = 0; i < len; i++) {
			bin += std::to_string(rand() % 2);
		}
		return bin;
	};

	public:
	std::string seed;

	QR_CODE () {
		seed = randBinary(526);
		Image* image = new Image("image", 15, 15, seed);
	}
};

int main () {
	srand((unsigned) std::time(NULL));

	QR_CODE qr_code;
	std::cout << qr_code.seed << std::endl;

	return 0;
}