/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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
#ifndef IGNITION_RENDERING_OGRE2_OGRE2RENDERTYPES_HH_
#define IGNITION_RENDERING_OGRE2_OGRE2RENDERTYPES_HH_

#include <memory>

#include "ignition/rendering/config.hh"
#include "ignition/rendering/base/BaseRenderTypes.hh"

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    //
    class Ogre2Camera;
    class Ogre2Node;
    class Ogre2Object;
    class Ogre2RenderEngine;
    class Ogre2RenderTarget;
    class Ogre2RenderTexture;
    class Ogre2RenderWindow;
    class Ogre2Scene;
    class Ogre2Sensor;
    class Ogre2DirectionalLight;
    class Ogre2Light;
    class Ogre2PointLight;
    class Ogre2SpotLight;

    typedef BaseSceneStore<Ogre2Scene>            Ogre2SceneStore;
    typedef BaseNodeStore<Ogre2Node>              Ogre2NodeStore;
    typedef BaseSensorStore<Ogre2Sensor>          Ogre2SensorStore;
    typedef BaseLightStore<Ogre2Light>            Ogre2LightStore;

    typedef shared_ptr<Ogre2Camera>               Ogre2CameraPtr;
    typedef shared_ptr<Ogre2Node>                 Ogre2NodePtr;
    typedef shared_ptr<Ogre2Object>               Ogre2ObjectPtr;
    typedef shared_ptr<Ogre2RenderEngine>         Ogre2RenderEnginePtr;
    typedef shared_ptr<Ogre2RenderTarget>         Ogre2RenderTargetPtr;
    typedef shared_ptr<Ogre2RenderTexture>        Ogre2RenderTexturePtr;
    typedef shared_ptr<Ogre2RenderWindow>         Ogre2RenderWindowPtr;
    typedef shared_ptr<Ogre2Scene>                Ogre2ScenePtr;
    typedef shared_ptr<Ogre2Sensor>               Ogre2SensorPtr;
    typedef shared_ptr<Ogre2DirectionalLight>     Ogre2DirectionalLightPtr;
    typedef shared_ptr<Ogre2Light>                Ogre2LightPtr;
    typedef shared_ptr<Ogre2PointLight>           Ogre2PointLightPtr;
    typedef shared_ptr<Ogre2SpotLight>            Ogre2SpotLightPtr;

    typedef shared_ptr<Ogre2NodeStore>            Ogre2NodeStorePtr;
    typedef shared_ptr<Ogre2SceneStore>           Ogre2SceneStorePtr;
    typedef shared_ptr<Ogre2SensorStore>          Ogre2SensorStorePtr;
    typedef shared_ptr<Ogre2LightStore>           Ogre2LightStorePtr;
    }
  }
}
#endif