#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
int main() {

  Image alma; 
  alma.readFromFile("alma.png");
  Image i;    
  i.readFromFile("i.png");
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, alma.width()-5, 50);
  sheet.addSticker(i, 50, 50);
  sheet.addSticker(i, alma.width()/2, 100);
  Image expected = sheet.render();
  expected.writeToFile("myImage.png");
  return 0;
}