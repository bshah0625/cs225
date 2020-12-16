/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>

class StickerSheet {
  
	public:

		const StickerSheet & operator=(const StickerSheet & other);
		void changeMaxStickers(unsigned max);
		StickerSheet(const Image & picture, unsigned max);
		~StickerSheet();
		bool translate(unsigned index, unsigned x, unsigned y);
		StickerSheet(const StickerSheet & other);
		int addSticker(Image & sticker, unsigned x, unsigned y);
		void removeSticker(unsigned index);
		Image * getSticker(unsigned index) const;
		Image render () const;

	private:

		unsigned m;
		unsigned * X;
		unsigned * Y;
		unsigned num_stickers;
		Image * Bottom;
		Image ** Lightning;
		void copy(const StickerSheet & other);
		void clear();
};