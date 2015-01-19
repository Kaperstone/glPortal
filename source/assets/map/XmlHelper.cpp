#include "XmlHelper.hpp"

#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include <engine/Entity.hpp>

using namespace std;

namespace glPortal {

  std::string XmlHelper::mandatoryAttributeMessage("Mandatory attribute has not been defined.");
  std::string XmlHelper::invalidElementMessage("pushAttributeToVector received an invalid XML-Element.");
  /**
   * Pushes vector coordinates from an XML-element to a Vector3f.
   * Trying to pull attributes from a non-existing element is considered an exception.
   */
  void XmlHelper::pushAttributeVertexToVector(XMLElement* xmlElement, Vector3f &targetVector) {
    if(xmlElement) {
      int xQueryResult = xmlElement->QueryFloatAttribute("x", &targetVector.x);
      int yQueryResult = xmlElement->QueryFloatAttribute("y", &targetVector.y);
      int zQueryResult = xmlElement->QueryFloatAttribute("z", &targetVector.z);
      if(xQueryResult == XML_NO_ATTRIBUTE){
        throwMandatoryAttributeException("<x>");
      }
      if(yQueryResult == XML_NO_ATTRIBUTE){
        throwMandatoryAttributeException("<y>");
      }
      if(zQueryResult == XML_NO_ATTRIBUTE){
        throwMandatoryAttributeException("<z>");
      }
    } else {
      throw runtime_error(invalidElementMessage);
    }
  }
  
  void XmlHelper::throwMandatoryAttributeException(std::string message){
    throw runtime_error(mandatoryAttributeMessage + message);
  }

  void XmlHelper::extractPositionAndRotation(XMLElement* element, Entity &entity){
    Vector3f pos;
    Vector3f rot;
    XMLElement* positionElement = element->FirstChildElement("position");
    pushAttributeVertexToVector(positionElement, pos);
    
    XMLElement* rotationElement = element->FirstChildElement("rotation");
    pushAttributeVertexToVector(rotationElement, rot);

    entity.position.set(pos);
    entity.rotation.set(rot);
  }  
} /* namespace glPortal */
