// __BEGIN_LICENSE__
// Copyright (C) 2006-2011 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


/// \file Reflectance.h

#ifndef __VW_PHOTOMETRY_REFLECTANCE_H__
#define __VW_PHOTOMETRY_REFLECTANCE_H__

#ifdef _MSC_VER
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4996)
#endif

#include <string>
#include <vw/Math/Vector.h>

#include <vw/Photometry/Reconstruct.h>

namespace vw {
namespace photometry {

  Vector3 computeNormalFrom3DPointsGeneral(Vector3 p1, Vector3 p2, Vector3 p3);
  Vector3 computeNormalFrom3DPoints(Vector3 p1, Vector3 p2, Vector3 p3);

  std::vector<Vector3> ReadSunPosition(std::string const& filename,
                                       int const& numEntries);
  std::vector<Vector3> ReadSpacecraftPosition(std::string const& filename,
                                              int const& numEntries);

  float computeReflectanceFromNormal(Vector3 sunPos, Vector3 xyz,  Vector3 normal);
  float computeLambertianReflectanceFromNormal(Vector3 sunPos,
                                               Vector3 xyz, Vector3 normal);
  float computeLunarLambertianReflectanceFromNormal(Vector3 sunPos,
                                                    Vector3 viewerPos,
                                                    Vector3 xyz,
                                                    Vector3 normal,
                                                    float B_0, float L);
  float computeLunarLambertianReflectanceFromNormal(Vector3 sunPos,
                                                    Vector3 viewPos,
                                                    Vector3 xyz,
                                                    Vector3 normal);
  float computeImageReflectance(ModelParams input_img_params,
                                GlobalParams globalParams);
  float ComputeReflectance(Vector3 normal, Vector3 xyz,
                           ModelParams input_img_params,
                           GlobalParams globalParams);
  float computeImageReflectance(ModelParams input_img_params,
                                ModelParams overlap_img_params,
                                GlobalParams globalParams);

  void computeXYZandSurfaceNormal(ImageView<PixelGray<float> > const& DEMTile,
                                  cartography::GeoReference const& DEMGeo,
                                  GlobalParams globalParams,
                                  ImageView<Vector3> & dem_xyz,
                                  ImageView<Vector3> & surface_normal
                                  );

  void computeReflectanceAux(ImageView<Vector3> const& dem_xyz,
                             ImageView<Vector3> const& surface_normal,
                             ModelParams input_img_params,
                             GlobalParams globalParams,
                             ImageView<PixelMask<PixelGray<float> > >& outputReflectance);

  
  float computeAvgReflectanceOverTilesOrUpdateExposure(bool compAvgRefl,
                                                       bool useReflectance,
                                                       int pixelPadding, double tileSize,
                                                       std::vector<ImageRecord> & DEMTiles,
                                                       std::vector<ImageRecord> & albedoTiles,
                                                       std::vector<int> & overlap,
                                                       ModelParams input_img_params,
                                                       GlobalParams globalParams);
  
  float computeImageReflectanceNoWrite(ModelParams input_img_params,
                                       GlobalParams globalParams,
                                       ImageView<PixelMask<PixelGray<float> > >& output_img);
  
}}

#endif//__VW_PHOTOMETRY_REFLECTANCE_H__
