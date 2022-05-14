/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
 */

#include "../RelationshipTypes.h"
#include "../Shard.h"

namespace ragedb {

  void RelationshipTypes::removeDeletedIds(uint16_t type_id, std::vector<uint64_t> &list) {
      std::erase_if(list, [deleted = deleted_ids[type_id] ](auto id) {
          return deleted.contains(Shard::externalToInternal(id));
      });
  }
  
  void RelationshipTypes::removeDeletedProperties(uint16_t type_id, std::vector<uint64_t> &list, const std::string &property) {
      std::erase_if(list, [deleted = properties[type_id].getDeletedMap(property) ](auto id) {
          return deleted.contains(Shard::externalToInternal(id));
      });
  }
  
  uint64_t RelationshipTypes::filterCountBooleans(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isBooleanProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const bool typedValue = get<bool>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::Evaluate<bool>(operation, properties[type_id].getBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountIntegers(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isIntegerProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const int64_t typedValue = get<int64_t>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::Evaluate<int64_t>(operation, properties[type_id].getIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountDoubles(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isDoubleProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const double typedValue = get<double>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::Evaluate<double>(operation, properties[type_id].getDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountStrings(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isStringProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const std::string typedValue = get<std::string>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::EvaluateString(operation, properties[type_id].getStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountBooleanLists(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isBooleanListProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const std::vector<bool> typedValue = get<std::vector<bool>>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::EvaluateVector<bool>(operation, properties[type_id].getListOfBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountIntegerLists(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isIntegerListProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const std::vector<int64_t> typedValue = get<std::vector<int64_t>>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::EvaluateVector<int64_t>(operation, properties[type_id].getListOfIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountDoubleLists(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isDoubleListProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const std::vector<double> typedValue = get<std::vector<double>>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::EvaluateVector<double>(operation, properties[type_id].getListOfDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCountStringLists(const std::vector<uint64_t>& ids, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    uint64_t count = 0;
    if (Properties::isStringListProperty(value)) {
      const roaring::Roaring64Map blank = getBlanks(type_id, property);
      const std::vector<std::string> typedValue = get<std::vector<std::string>>(value);
      for(auto id : ids) {
        // If the relationship or property has been deleted, ignore it
        if (blank.contains( Shard::externalToInternal(id))) {
          continue;
        }
        if (!Expression::EvaluateVector<std::string>(operation, properties[type_id].getListOfStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        count++;
      }
    }
    return count;
  }
  
  uint64_t RelationshipTypes::filterCount(std::vector<uint64_t> unfiltered, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value) {
    // If the type is invalid, we can't filter any so return zero
    if (!ValidTypeId(type_id)) return 0;
  
    if(operation == Operation::IS_NULL) {
      uint64_t count = 0;
      for (auto id : unfiltered) {
        count += static_cast<uint8_t>(properties[type_id].isDeleted(property, id));
      }
      return count;
    }
  
    if(operation == Operation::NOT_IS_NULL) {
      uint64_t count = 0;
      for (auto id : unfiltered) {
        count += (1 - static_cast<uint8_t>(properties[type_id].isDeleted(property, id)));
      }
      return count;
    }
  
    const uint16_t property_type_id = properties[type_id].getPropertyTypeId(property);
  
    switch (property_type_id) {
    case Properties::boolean_type: 
      return filterCountBooleans(unfiltered, type_id, property, operation, value);
     case Properties::integer_type: 
      return filterCountIntegers(unfiltered, type_id, property, operation, value);
     case Properties::double_type: 
      return filterCountDoubles(unfiltered, type_id, property, operation, value);
     case Properties::date_type: 
      return filterCountDoubles(unfiltered, type_id, property, operation, value);
     case Properties::string_type: 
      return filterCountStrings(unfiltered, type_id, property, operation, value);
     case Properties::boolean_list_type: 
      return filterCountBooleanLists(unfiltered, type_id, property, operation, value);
     case Properties::integer_list_type: 
      return filterCountIntegerLists(unfiltered, type_id, property, operation, value);
     case Properties::double_list_type: 
      return filterCountDoubleLists(unfiltered, type_id, property, operation, value);
     case Properties::date_list_type: 
      return filterCountDoubleLists(unfiltered, type_id, property, operation, value);
     case Properties::string_list_type: 
      return filterCountStringLists(unfiltered, type_id, property, operation, value);
    default: 
      return 0;
    }
  }
  
  std::vector<uint64_t> RelationshipTypes::filterNullIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    uint64_t current = 1;
    for (auto id : list) {
      if (current > (skip + limit)) {
        break;
      }
  
      if (properties[type_id].isDeleted(property, Shard::externalToInternal(id))) {
        if (current++ > skip ) {
          ids.emplace_back(id);
        }
      }
    }
    return ids;
  }
  
  std::vector<uint64_t> RelationshipTypes::filterNotNullIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    uint64_t current = 1;
    for (auto id : list) {
      if (current > (skip + limit)) {
        break;
      }
  
      if (!properties[type_id].isDeleted(property, Shard::externalToInternal(id))) {
        if (current++ > skip ) {
          ids.emplace_back(id);
        }
      }
    }
    return ids;
  }
  
  std::vector<uint64_t> RelationshipTypes::filterBooleanIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isBooleanProperty(value)) {
      const bool typedValue = get<bool>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
        if (!Expression::Evaluate<bool>(operation, properties[type_id].getBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterIntegerIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isIntegerProperty(value)) {
      const int64_t typedValue = get<int64_t>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
  
        if (!Expression::Evaluate<int64_t>(operation, properties[type_id].getIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterDoubleIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isDoubleProperty(value)) {
      const double typedValue = get<double>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
  
        if (!Expression::Evaluate<double>(operation, properties[type_id].getDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterStringIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isStringProperty(value)) {
      const std::string typedValue = get<std::string>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
  
        if (!Expression::Evaluate<std::string>(operation, properties[type_id].getStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterBooleanListIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<bool> typedValue = get<std::vector<bool>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
        if (!Expression::Evaluate<std::vector<bool>>(operation, properties[type_id].getListOfBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterIntegerListIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<int64_t> typedValue = get<std::vector<int64_t>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
        if (!Expression::Evaluate<std::vector<int64_t>>(operation, properties[type_id].getListOfIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterDoubleListIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<double> typedValue = get<std::vector<double>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
        if (!Expression::Evaluate<std::vector<double>>(operation, properties[type_id].getListOfDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
    
  std::vector<uint64_t> RelationshipTypes::filterStringListIds(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<uint64_t> ids;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<std::string> typedValue = get<std::vector<std::string>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return ids;
        }
        if (!Expression::Evaluate<std::vector<std::string>>(operation, properties[type_id].getListOfStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          ids.emplace_back(id);
        }
        current++;
      }
    }
    return ids;
  }
  
  std::vector<uint64_t> RelationshipTypes::filterIds(std::vector<uint64_t> unfiltered, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    // If the type is invalid, we can't filter any so return an empty array
    if (!ValidTypeId(type_id)) return std::vector<uint64_t>();
  
    // Deleted Nodes will never return from a filter
    removeDeletedIds(type_id, unfiltered);
  
    if(operation == Operation::IS_NULL) {
      return filterNullIds(unfiltered, type_id, property, skip, limit);
    }
  
    if(operation == Operation::NOT_IS_NULL) {
      return filterNotNullIds(unfiltered, type_id, property, skip, limit);
    }
  
    // From here on out we don't want deleted properties
    removeDeletedProperties(type_id, unfiltered, property);
  
    const uint16_t property_type_id = properties[type_id].getPropertyTypeId(property);
    switch (property_type_id) {
    case Properties::boolean_type: 
      return filterBooleanIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::integer_type: 
      return filterIntegerIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::double_type: 
      return filterDoubleIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::date_type: 
      return filterDoubleIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::string_type: 
      return filterStringIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::boolean_list_type: 
      return filterBooleanListIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::integer_list_type: 
      return filterIntegerListIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::double_list_type: 
      return filterDoubleListIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::date_list_type: 
      return filterDoubleListIds(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::string_list_type: 
      return filterStringListIds(unfiltered, type_id, property, operation, value, skip, limit);
    default: 
      return std::vector<uint64_t>();
    }
  }
  
  std::vector<Relationship> RelationshipTypes::filterNullRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    uint64_t current = 1;
    for (auto id : list) {
      if (current > (skip + limit)) {
        break;
      }
  
      if (properties[type_id].isDeleted(property, Shard::externalToInternal(id))) {
        if (current++ > skip ) {
          relationships.emplace_back(getRelationship(id));
        }
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterNotNullRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    uint64_t current = 1;
    for (auto id : list) {
      if (current > (skip + limit)) {
        break;
      }
  
      if (!properties[type_id].isDeleted(property, Shard::externalToInternal(id))) {
        if (current++ > skip ) {
          relationships.emplace_back(getRelationship(id));
        }
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterBooleanRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isBooleanProperty(value)) {
      const bool typedValue = get<bool>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
        if (!Expression::Evaluate<bool>(operation, properties[type_id].getBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterIntegerRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isIntegerProperty(value)) {
      const int64_t typedValue = get<int64_t>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
  
        if (!Expression::Evaluate<int64_t>(operation, properties[type_id].getIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterDoubleRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isDoubleProperty(value)) {
      const double typedValue = get<double>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
  
        if (!Expression::Evaluate<double>(operation, properties[type_id].getDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterStringRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isStringProperty(value)) {
      const std::string typedValue = get<std::string>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
  
        if (!Expression::Evaluate<std::string>(operation, properties[type_id].getStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterBooleanListRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<bool> typedValue = get<std::vector<bool>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
        if (!Expression::Evaluate<std::vector<bool>>(operation, properties[type_id].getListOfBooleanProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterIntegerListRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<int64_t> typedValue = get<std::vector<int64_t>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
        if (!Expression::Evaluate<std::vector<int64_t>>(operation, properties[type_id].getListOfIntegerProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterDoubleListRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<double> typedValue = get<std::vector<double>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
        if (!Expression::Evaluate<std::vector<double>>(operation, properties[type_id].getListOfDoubleProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterStringListRelationships(const std::vector<uint64_t>& list, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    std::vector<Relationship> relationships;
    int current = 1;
    if (Properties::isBooleanListProperty(value)) {
      const std::vector<std::string> typedValue = get<std::vector<std::string>>(value);
      for (auto id : list) {
        // If we reached our limit, return
        if (current > (skip + limit)) {
          return relationships;
        }
        if (!Expression::Evaluate<std::vector<std::string>>(operation, properties[type_id].getListOfStringProperty(property,  Shard::externalToInternal(id)), typedValue)) {
          continue;
        }
        // If it is true add it if we are over the skip, otherwise ignore it
        if (current > skip) {
          relationships.emplace_back(getRelationship(id));
        }
        current++;
      }
    }
    return relationships;
  }
  
  std::vector<Relationship> RelationshipTypes::filterRelationships(std::vector<uint64_t> unfiltered, uint16_t type_id, const std::string &property, Operation operation, const property_type_t& value, uint64_t skip, uint64_t limit) {
    // If the type is invalid, we can't filter any so return an empty array
    if (!ValidTypeId(type_id)) return std::vector<Relationship>();
  
    // Deleted Nodes will never return from a filter
    removeDeletedIds(type_id, unfiltered);
  
    if(operation == Operation::IS_NULL) {
      return filterNullRelationships(unfiltered, type_id, property, skip, limit);
    }
  
    if(operation == Operation::NOT_IS_NULL) {
      return filterNotNullRelationships(unfiltered, type_id, property, skip, limit);
    }
  
    const uint16_t property_type_id = properties[type_id].getPropertyTypeId(property);
    switch (property_type_id) {
    case Properties::boolean_type: 
      return filterBooleanRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::integer_type: 
      return filterIntegerRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::double_type: 
      return filterDoubleRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::date_type: 
      return filterDoubleRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::string_type: 
      return filterStringRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::boolean_list_type: 
      return filterBooleanListRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::integer_list_type: 
      return filterIntegerListRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::double_list_type: 
      return filterDoubleListRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::date_list_type: 
      return filterDoubleListRelationships(unfiltered, type_id, property, operation, value, skip, limit);
     case Properties::string_list_type: 
      return filterStringListRelationships(unfiltered, type_id, property, operation, value, skip, limit);
    default: 
      return std::vector<Relationship>();
    }
  }

}