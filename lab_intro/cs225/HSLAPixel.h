/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel{
        public:
            double h;   //double for the hue of the pixel, in degrees [0,360]
            double s;   //double for the saturation of the pixel [0,1]
            double l;   //double for the luminance of the pixel [0, 1]
            double a;   //double for the alpha channel of the pixel [0,1]

            //construct default HSLAPixel. Default pixel will be completely opaque and white
            HSLAPixel();
            
            //construct opaque HSLAPixel with given hue, saturation, and luminance values. Alpha will be 1.0
            HSLAPixel(double hue, double saturation, double luminance);

            //construct HSLAPixel with given hue, saturation, luminance, and alpha values
            HSLAPixel(double hue, double saturation, double luminance, double alpha);

    };
}