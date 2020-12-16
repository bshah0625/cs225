#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "intro.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  PNG *original = new PNG;
  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();
  PNG* output = new PNG(width, height);

  for(unsigned x = 0; x < width; x++){
    for(unsigned y = 0; y < height; y++){
      HSLAPixel &previouspic = original->getPixel(width-x-1, height-y-1);
      HSLAPixel &newpic = output->getPixel(x,y);

      newpic.h = previouspic.h;
      newpic.s = previouspic.s;
      newpic.l = previouspic.l;
      newpic.a = previouspic.a;
    }
  }
  output->writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  for(unsigned x = 0; x < width; x++){
    for(unsigned y = 0; y < height; y++){
      HSLAPixel &randompic = png.getPixel(x,y);

      randompic.h = 360*(sqrt(((x-120)*(x-120))+((y-120)*(y-120)))/sqrt((height*height)+(width*width)));
      randompic.s = 1*(sqrt(((x-120)*(x-120))+((y-120)*(y-120)))/sqrt((height*height)+(width*width)));
      randompic.l = 1-(1*(sqrt(((x-120)*(x-120))+((y-120)*(y-120)))/sqrt((height*height)+(width*width))));

    }
  }
  return png;
}
