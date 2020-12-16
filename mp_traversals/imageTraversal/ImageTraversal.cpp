#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  t = NULL;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int w = base_.width();
  unsigned int h = base_.height();
  pointsV.resize(w, std::vector<bool>(h));
  while(width < w){
    while(height < h){
      pointsV[width][height] = false;
      height++;
    }
    width++;
  }
}

bool ImageTraversal::Iterator::isAllowed(Point p)
{
  Point temp  = p;
  if(temp.y>=base_.height() || temp.x>=base_.width()) 
    return false;
  if(temp.y<base_.height() && temp.x<base_.width())
  {
    HSLAPixel & begin = base_.getPixel(start_.x,start_.y);
    HSLAPixel & position = base_.getPixel(temp.x,temp.y);
    if(calculateDelta(begin,position)<tol_)
    {
      if(pointsV[temp.x][temp.y]==false)
      {
        return true;
      }
    }
  }
  return false;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* imaget,PNG png, Point p, double d)
{
  t = imaget;
  base_ = png;
  start_=p;
  pos_= p;
  tol_ = d;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int w= base_.width();
  unsigned int h = base_.height();
  pointsV.resize(w,std::vector<bool>(h));
  while(width<w)
  {
    height = 0;
    while(height<h)
    {
      pointsV[width][height]=false;
      height++;
    }
    width++;
  }


  if(!isAllowed(pos_)==false)
  {
    pointsV[pos_.x][pos_.y]=true;
  }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  pointsV[pos_.x][pos_.y]=true;
  Point right, left, above, below;
  right = Point(pos_.x+1,pos_.y);
  left = Point(pos_.x-1,pos_.y);
  above = Point(pos_.x,pos_.y-1);
  below = Point(pos_.x,pos_.y+1);
  if(isAllowed(right)){ t->add(right);}
  if(isAllowed(below)){ t->add(below);}
  if(isAllowed(left)) {t->add(left);}
  if(isAllowed(above)) {t->add(above);}
  while(t->empty() != true && isAllowed(t->peek()) != true)
  {
    t->pop();
    if(t->empty() == true)
    {
      return *this;
    }
  }
  if(t->empty() == false)
  {
    pos_ = t->peek();
    return *this;
  }
  else
  {
    t = NULL;
    return *this;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return pos_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool tEmpty = false;
  bool oEmpty = false;

  if (t == NULL) { tEmpty = true; }
  if (other.t == NULL) { oEmpty = true; }

  if (!tEmpty)  { tEmpty = t->empty(); }
  if (!oEmpty) { oEmpty = other.t->empty(); }

  if (tEmpty && oEmpty)
    return false; 
  else if ((!tEmpty)&&(!oEmpty))
    return (t != other.t); 
  else 
    return true; 
}

