#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;


StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	m = max;
	num_stickers = 0;
	Lightning = new Image * [m];
	X = new unsigned[m];
	Y = new unsigned[m];
	Bottom = new Image(picture);
	X[0] = 0;
	Y[0] = 0;
}

StickerSheet::~StickerSheet() {
	clear();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	Image ** tLightning = new Image * [num_stickers];
	unsigned * tX = new unsigned [num_stickers];
	unsigned * tY = new unsigned [num_stickers];
	for (unsigned i = 0; i < num_stickers; i++) {
		tLightning[i] = Lightning[i];
		tX[i] = X[i];
		tY[i] = Y[i];
	}
	delete[] Lightning;
	delete[] X;
	delete[] Y;
	Lightning = new Image * [max];
	X = new unsigned[max];
	Y = new unsigned[max];

	if (max < num_stickers) {
		for (unsigned i = max; i < num_stickers; i++) {
			tLightning[i] = NULL;
		}

		num_stickers = max;

		for (unsigned i = 0; i < num_stickers; i++) {
			Lightning[i] = tLightning[i];
			X[i] = tX[i];
			Y[i] = tY[i];
		}
	}

	else {
		for (unsigned i = 0; i < num_stickers; i++) {
			Lightning[i] = tLightning[i];
			X[i] = tX[i];
			Y[i] = tY[i];
		}
	}
	delete[] tLightning;
	delete[] tX;
	delete[] tY;
	m = max;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < m; i++) {
		if (i == num_stickers) {
			Lightning[i] = new Image(sticker);
			X[i] = x;
			Y[i] = y;
			num_stickers = num_stickers + 1;
			return int(i);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_stickers) {
		X[index] = x;
		Y[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Lightning[index];
	for (unsigned i = index; i < m - 1; i++) {
		Lightning[i] = Lightning[i + 1];
		X[i] = X[i + 1];
		Y[i] = Y[i + 1];
	}

  	Lightning[m - 1] = NULL;
	X[m - 1] = 0; 
	Y[m - 1] = 0; 
	num_stickers = num_stickers - 1;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_stickers) {
    	return NULL;
  }

	return Lightning[index];
}

Image StickerSheet::render() const {
	Image result(*Bottom);
	for (unsigned i = 0; i < num_stickers; i++) {
		unsigned currentw = Lightning[i]->width();
		unsigned currenth = Lightning[i]->height();

		if ((currentw + X[i]) > result.width()) {
			result.resize(currentw + X[i], result.height());
		}
		if ((currenth + Y[i]) > result.height()) {
			result.resize(result.width(), currenth + Y[i]);
		}

		for (unsigned x = 0; x < currentw; x++) {
			for (unsigned y = 0; y < currenth; y++) {
				HSLAPixel &cur_result_pixel = result.getPixel(x + X[i], y + Y[i]);
				HSLAPixel &cur_image_pixel = Lightning[i]->getPixel(x, y);
				if (cur_image_pixel.a != 0) {
					cur_result_pixel = cur_image_pixel;
				}
			}
		}

	}
	return result;
}

void StickerSheet::copy(const StickerSheet & other) {
	m = other.m;
	num_stickers = other.num_stickers;
	Bottom = new Image(*(other.Bottom));
	Lightning = new Image * [m];
	X = new unsigned[m];
	Y = new unsigned[m];
	for (unsigned i = 0; i < num_stickers; i++) {
		Lightning[i] = new Image();
		*(Lightning[i]) = *(other.Lightning[i]);
		X[i] = other.X[i];
		Y[i] = other.Y[i];
	}
}

void StickerSheet::clear() {
	for (unsigned i = 0; i < num_stickers; i++) {
		delete Lightning[i];
		Lightning[i] = NULL;
	}
  	delete[] X;
  	delete[] Y;
  	delete[] Lightning;
	delete Bottom;

}