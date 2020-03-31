/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#endif

#include "ignition/rendering/Utils.hh"

namespace ignition
{
namespace rendering
{
inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
//
/////////////////////////////////////////////////
float screenScalingFactor()
{
  // todo(anyone) set device pixel ratio for high dpi displays on Windows
  float ratio = 1.0;
#ifdef __linux__
  Display *disp = XOpenDisplay(nullptr);
  char *resourceString = XResourceManagerString(disp);

  if (resourceString)
  {
    char *type = nullptr;
    float dpiDesktop = 0.0;

    // Need to initialize the DB before calling Xrm* functions
    XrmInitialize();

    XrmValue value;
    XrmDatabase db = XrmGetStringDatabase(resourceString);

    // Debug:
    // printf("Entire DB:\n%s\n", resourceString);

    if (XrmGetResource(db, "Xft.dpi", "String", &type, &value) == True)
    {
      if (value.addr)
        dpiDesktop = atof(value.addr);
    }

    // To get the ratio we need the DPI as reported by the Xrmdatabase,
    // which takes into account desktop scaling, and the DPI computed by the
    // actual display resolution.
    //
    // dpiRes = N pixels / (M millimeters / (25.4 millimeters / 1 inch))
    //        = N pixels / (M inch / 25.4)
    //        = (N * 25.4 pixels) / M inch
    //
    // We can use either the width or height in the following line. The zero
    // values in DisplayHeight and DisplayHeightMM is the screen number. A
    // value of zero uses the default screen.
    float yDpiRes = (DisplayHeight(disp, 0) * 25.4) /
      DisplayHeightMM(disp, 0);

    if (!math::equal(dpiDesktop, 0.0f) && !math::equal(yDpiRes, 0.0f))
      ratio = dpiDesktop / yDpiRes;

    // Debug:
    // printf("DPI Desktop: %f, DPI XY: [%f, %f], Ratio XY: [%f, %f]\n",
    // dpiDesktop, xDpiRes, yDpiRes, xRatio, yRatio);
  }
#endif
  return ratio;
}

/////////////////////////////////////////////////
void Transform(const ignition::math::AxisAlignedBox &_bbox,
    const ignition::math::Pose3d &_worldPose,
    std::vector<ignition::math::Vector3d> &_vertices)
{
  auto center = _bbox.Center();

  // Get the 8 corners of the bounding box.
  auto v0 = center + ignition::math::Vector3d(-_bbox.XLength()/2.0,
                                               _bbox.YLength()/2.0,
                                               _bbox.ZLength()/2.0);
  auto v1 = center + ignition::math::Vector3d(_bbox.XLength()/2.0,
                                              _bbox.YLength()/2.0,
                                              _bbox.ZLength()/2.0);
  auto v2 = center + ignition::math::Vector3d(-_bbox.XLength()/2.0,
                                              -_bbox.YLength()/2.0,
                                               _bbox.ZLength()/2.0);
  auto v3 = center + ignition::math::Vector3d(_bbox.XLength()/2.0,
                                             -_bbox.YLength()/2.0,
                                              _bbox.ZLength()/2.0);

  auto v4 = center + ignition::math::Vector3d(-_bbox.XLength()/2.0,
                                               _bbox.YLength()/2.0,
                                              -_bbox.ZLength()/2.0);
  auto v5 = center + ignition::math::Vector3d(_bbox.XLength()/2.0,
                                              _bbox.YLength()/2.0,
                                             -_bbox.ZLength()/2.0);
  auto v6 = center + ignition::math::Vector3d(-_bbox.XLength()/2.0,
                                              -_bbox.YLength()/2.0,
                                              -_bbox.ZLength()/2.0);
  auto v7 = center + ignition::math::Vector3d(_bbox.XLength()/2.0,
                                             -_bbox.YLength()/2.0,
                                             -_bbox.ZLength()/2.0);

  // Transform corners into world spacce.
  v0 = _worldPose.Rot() * v0 + _worldPose.Pos();
  v1 = _worldPose.Rot() * v1 + _worldPose.Pos();
  v2 = _worldPose.Rot() * v2 + _worldPose.Pos();
  v3 = _worldPose.Rot() * v3 + _worldPose.Pos();
  v4 = _worldPose.Rot() * v4 + _worldPose.Pos();
  v5 = _worldPose.Rot() * v5 + _worldPose.Pos();
  v6 = _worldPose.Rot() * v6 + _worldPose.Pos();
  v7 = _worldPose.Rot() * v7 + _worldPose.Pos();

  _vertices.clear();
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _vertices.push_back(v3);
  _vertices.push_back(v4);
  _vertices.push_back(v5);
  _vertices.push_back(v6);
  _vertices.push_back(v7);
}

/////////////////////////////////////////////////
void MinMax(const std::vector<ignition::math::Vector3d> &_vertices,
    ignition::math::Vector3d &_min, ignition::math::Vector3d &_max)
{
  if (_vertices.empty())
    return;

  _min = _vertices[0];
  _max = _vertices[0];

  // find min / max in world space;
  for (unsigned int i = 1; i < _vertices.size(); ++i)
  {
    auto v = _vertices[i];
    if (_min.X() > v.X())
      _min.X() = v.X();
    if (_max.X() < v.X())
      _max.X() = v.X();
    if (_min.Y() > v.Y())
      _min.Y() = v.Y();
    if (_max.Y() < v.Y())
      _max.Y() = v.Y();
    if (_min.Z() > v.Z())
      _min.Z() = v.Z();
    if (_max.Z() < v.Z())
      _max.Z() = v.Z();
  }
}
}
}
}
