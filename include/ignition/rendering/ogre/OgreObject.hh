/*
 * Copyright (C) 2015 Open Source Robotics Foundation
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
#ifndef _IGNITION_RENDERING_OGREOBJECT_HH_
#define _IGNITION_RENDERING_OGREOBJECT_HH_

#include "ignition/rendering/base/BaseObject.hh"
#include "ignition/rendering/ogre/OgreRenderTypes.hh"

namespace ignition
{
  namespace rendering
  {
    class IGNITION_VISIBLE OgreObject :
      public BaseObject
    {
      protected: OgreObject();

      public: virtual ~OgreObject();

      public: virtual ScenePtr GetScene() const;

      protected: OgreScenePtr scene;

      private: friend class OgreScene;
    };
  }
}
#endif
