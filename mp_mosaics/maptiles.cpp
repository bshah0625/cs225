/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     if (theTiles.empty()) return NULL;

     int rows = theSource.getRows();
     int columns = theSource.getColumns();

     MosaicCanvas* mosaic = new MosaicCanvas(rows, columns);
     map<Point<3>, int> tile_avg_map;
     vector<Point<3>> points;
     points.reserve(theTiles.size());
     for(unsigned i = 0; i < theTiles.size(); ++i){
       LUVAPixel avg = theTiles[i].getAverageColor();
       Point<3> ppp = convertToXYZ(avg);
       tile_avg_map[ppp] = i;
       points.push_back(ppp);
     }
     KDTree<3> tree(points);

     // Finally, fill tiles
     for (int row = 0; row < rows; row++) {
         for (int col = 0; col < columns; col++) {
             TileImage* matchTile = get_match_at_idx(
                 tree, tile_avg_map, theTiles, theSource, row, col);
             mosaic->setTile(row, col, matchTile);
         }
     }

     return mosaic;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    LUVAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToXYZ(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}




