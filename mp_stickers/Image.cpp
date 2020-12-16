#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

void Image::lighten()
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      if(this->getPixel(i,j).l+.1>=1.0)
      {
        this->getPixel(i,j).l=1.0;
        continue;
      }
      else
        this->getPixel(i,j).l=this->getPixel(i,j).l+.1;
    }
  }
}
void Image::lighten(double amount)
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      if(this->getPixel(i,j).l+amount>=1.0)
      {
        this->getPixel(i,j).l=1;
        continue;
      }
      else
        this->getPixel(i,j).l=this->getPixel(i,j).l+amount;
    }
  }
}
void Image::darken()
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      if(this->getPixel(i,j).l-.1<=0.0)
      {
        this->getPixel(i,j).l=0;
      }
      else
        this->getPixel(i,j).l=this->getPixel(i,j).l-.1;
    }
  }
}
void Image::darken(double amount)
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      if(this->getPixel(i,j).l-amount<=0.0)
      {
        this->getPixel(i,j).l=0;
      }
      else this->getPixel(i,j).l=this->getPixel(i,j).l-amount;
    }
  }
}
void Image::grayScale()
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      this->getPixel(i,j).s=0;
    }
  }
}

void Image::illinify()
{
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      cs225::HSLAPixel &pixel = this->getPixel(i, j);
      double o, b;
      if(pixel.h>=191)
      {
         o = 371-pixel.h;
      }
      else
      {
        o=sqrt((pixel.h-11)*(pixel.h-11));
      }

      if(pixel.h>=36&&pixel.h<=216)
      {
        b=216-pixel.h;
        b=sqrt(b*b);
      }
      else
      {
        b=pixel.h-216;
        b=sqrt(b*b);
      }

      if(o>=b)
      {
        pixel.h=216;
      }
      else
      {
        pixel.h=11;
      }
    }
  }
}

void Image::desaturate()
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      this->getPixel(i,j).s = this->getPixel(i,j).s-.1;
    }
  }
}
void Image::desaturate(double amount)
{
  int width = this->width();
  int height = this->height();

  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      this->getPixel(i,j).s = this->getPixel(i,j).s-amount;
    }
  }
}
void Image::rotateColor(double degrees)
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      if(this->getPixel(i,j).h+degrees>360)
      {
        this->getPixel(i,j).h=this->getPixel(i,j).h+degrees-360;
      }
      else if(this->getPixel(i,j).h+degrees<0)
      {
        this->getPixel(i,j).h=this->getPixel(i,j).h+degrees+360;
      }
      else
        this->getPixel(i,j).h=this->getPixel(i,j).h+degrees;
    }
  }
}
void Image::saturate()
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      this->getPixel(i,j).s=this->getPixel(i,j).s+.1;
    }
  }
}
void Image::saturate(double amount)
{
  int width = this->width();
  int height = this->height();
  for(int i =0;i<width;i++)
  {
    for(int j=0; j<height; j++)
    {
      this->getPixel(i,j).s=this->getPixel(i,j).s+amount;
    }
  }
}
void Image::scale(double factor)
{
  unsigned int neww = this->width() * factor;
  unsigned int newh = this->height() * factor;
  double xr = this->width()/(double)neww;
  double yr = this->height()/(double)newh;
  if(xr>yr)
  {
    xr=yr;
  }
  else
  {
    yr=xr;
  }
  cs225::PNG si(*this);
    this->resize(ceil(neww),ceil(newh));
    for(unsigned int i = 0; i<neww;i++)
    {
      for(unsigned int j=0; j<newh;j++)
      {
        int ox = i*xr;
        int oy = j*yr;
        this->getPixel(i,j)=si.getPixel(ox,oy);
      }
    }
}
void Image::scale(unsigned w, unsigned h)
{
  unsigned tw = w;
  unsigned th=h;
  double xr=(double)tw/(this->width());

  double yr=(double)th/(this->height());
  if(yr > xr)
  {
    scale(xr);
  }
  else{
    scale(yr);
  }
}