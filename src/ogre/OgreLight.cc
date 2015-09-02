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
#include "ignition/rendering/ogre/OgreLight.hh"

#include "gazebo/common/Exception.hh"
#include "ignition/rendering/ogre/OgreConversions.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/ogre/OgreScene.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
// OgreLight
//////////////////////////////////////////////////
OgreLight::OgreLight() :
  ogreLight(NULL),
  ogreLightType(Ogre::Light::LT_POINT)
{
}

//////////////////////////////////////////////////
OgreLight::~OgreLight()
{
}

//////////////////////////////////////////////////
gazebo::common::Color OgreLight::GetDiffuseColor() const
{
  Ogre::ColourValue color = this->ogreLight->getDiffuseColour();
  return OgreConversions::Convert(color);
}

//////////////////////////////////////////////////
void OgreLight::SetDiffuseColor(const gazebo::common::Color &_color)
{
  this->ogreLight->setDiffuseColour(_color.r, _color.g, _color.b);
}

//////////////////////////////////////////////////
gazebo::common::Color OgreLight::GetSpecularColor() const
{
  Ogre::ColourValue color = this->ogreLight->getSpecularColour();
  return OgreConversions::Convert(color);
}

//////////////////////////////////////////////////
void OgreLight::SetSpecularColor(const gazebo::common::Color &_color)
{
  this->ogreLight->setSpecularColour(_color.r, _color.g, _color.b);
}

//////////////////////////////////////////////////
double OgreLight::GetAttenuationConstant() const
{
  return this->ogreLight->getAttenuationConstant();
}

//////////////////////////////////////////////////
void OgreLight::SetAttenuationConstant(double _value)
{
  this->attenConstant = _value;
  this->UpdateAttenuation();
}

//////////////////////////////////////////////////
double OgreLight::GetAttenuationLinear() const
{
  return this->ogreLight->getAttenuationLinear();
}

//////////////////////////////////////////////////
void OgreLight::SetAttenuationLinear(double _value)
{
  this->attenLinear = _value;
  this->UpdateAttenuation();
}

//////////////////////////////////////////////////
double OgreLight::GetAttenuationQuadratic() const
{
  return this->ogreLight->getAttenuationQuadric();
}

//////////////////////////////////////////////////
void OgreLight::SetAttenuationQuadratic(double _value)
{
  this->attenQuadratic = _value;
  this->UpdateAttenuation();
}

//////////////////////////////////////////////////
double OgreLight::GetAttenuationRange() const
{
  return this->ogreLight->getAttenuationRange();
}

//////////////////////////////////////////////////
void OgreLight::SetAttenuationRange(double _range)
{
  this->attenRange = _range;
  this->UpdateAttenuation();
}

//////////////////////////////////////////////////
bool OgreLight::GetCastShadows() const
{
  return this->ogreLight->getCastShadows();
}

//////////////////////////////////////////////////
void OgreLight::SetCastShadows(bool _castShadows)
{
  this->ogreLight->setCastShadows(_castShadows);
}

//////////////////////////////////////////////////
Ogre::Light *OgreLight::GetOgreLight() const
{
  return this->ogreLight;
}

//////////////////////////////////////////////////
void OgreLight::Destroy()
{
  BaseLight::Destroy();
  Ogre::SceneManager *ogreSceneManager = this->scene->GetOgreSceneManager();
  ogreSceneManager->destroyLight(this->ogreLight);
}

//////////////////////////////////////////////////
void OgreLight::Init()
{
  OgreNode::Init();
  this->CreateLight();
  this->Reset();
}

//////////////////////////////////////////////////
void OgreLight::CreateLight()
{
  try
  {
    Ogre::SceneManager *sceneManager;
    sceneManager = this->scene->GetOgreSceneManager();
    this->ogreLight = sceneManager->createLight(this->name);
    this->ogreLight->setType(this->ogreLightType);
    this->ogreNode->attachObject(this->ogreLight);
    this->ogreLight->setCastShadows(true);
    this->UpdateAttenuation();
  }
  catch (Ogre::Exception &ex)
  {
    gzthrow("Unabled to create light: " << ex.getFullDescription());
  }
}

//////////////////////////////////////////////////
void OgreLight::UpdateAttenuation()
{
  this->ogreLight->setAttenuation(this->attenRange, this->attenConstant,
      this->attenLinear, this->attenQuadratic);
}

//////////////////////////////////////////////////
// OgreDirectionalLight
//////////////////////////////////////////////////
OgreDirectionalLight::OgreDirectionalLight()
{
  this->ogreLightType = Ogre::Light::LT_DIRECTIONAL;
}

//////////////////////////////////////////////////
OgreDirectionalLight::~OgreDirectionalLight()
{
}

//////////////////////////////////////////////////
math::Vector3d OgreDirectionalLight::GetDirection() const
{
  return OgreConversions::Convert(this->ogreLight->getDirection());
}

//////////////////////////////////////////////////
void OgreDirectionalLight::SetDirection(const math::Vector3d &_dir)
{
  this->ogreLight->setDirection(OgreConversions::Convert(_dir));
}

//////////////////////////////////////////////////
// OgrePointLight
//////////////////////////////////////////////////
OgrePointLight::OgrePointLight()
{
  this->ogreLightType = Ogre::Light::LT_POINT;
}

//////////////////////////////////////////////////
OgrePointLight::~OgrePointLight()
{
}

//////////////////////////////////////////////////
// OgreSpotLight
//////////////////////////////////////////////////
OgreSpotLight::OgreSpotLight()
{
  this->ogreLightType = Ogre::Light::LT_SPOTLIGHT;
}

//////////////////////////////////////////////////
OgreSpotLight::~OgreSpotLight()
{
}

//////////////////////////////////////////////////
math::Vector3d OgreSpotLight::GetDirection() const
{
  return OgreConversions::Convert(this->ogreLight->getDirection());
}

//////////////////////////////////////////////////
void OgreSpotLight::SetDirection(const math::Vector3d &_dir)
{
  this->ogreLight->setDirection(OgreConversions::Convert(_dir));
}

//////////////////////////////////////////////////
math::Angle OgreSpotLight::GetInnerAngle() const
{
  return OgreConversions::Convert(this->ogreLight->getSpotlightInnerAngle());
}

//////////////////////////////////////////////////
void OgreSpotLight::SetInnerAngle(const math::Angle &_angle)
{
  this->ogreLight->setSpotlightInnerAngle(OgreConversions::Convert(_angle));
}

//////////////////////////////////////////////////
math::Angle OgreSpotLight::GetOuterAngle() const
{
  return OgreConversions::Convert(this->ogreLight->getSpotlightOuterAngle());
}

//////////////////////////////////////////////////
void OgreSpotLight::SetOuterAngle(const math::Angle &_angle)
{
  this->ogreLight->setSpotlightOuterAngle(OgreConversions::Convert(_angle));
}

//////////////////////////////////////////////////
double OgreSpotLight::GetFalloff() const
{
  return this->ogreLight->getSpotlightFalloff();
}

//////////////////////////////////////////////////
void OgreSpotLight::SetFalloff(double _falloff)
{
  this->ogreLight->setSpotlightFalloff(_falloff);
}

//////////////////////////////////////////////////
