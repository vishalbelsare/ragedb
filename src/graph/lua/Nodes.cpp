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

#include "../Shard.h"

namespace ragedb {

    sol::as_table_t<std::vector<Node>> Shard::NodesGetViaLua(std::vector<uint64_t> ids) {
      std::vector<Node> nodes = NodesGetPeered(ids).get0();

      sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.getId() < b.getId();
      });

       return sol::as_table(nodes);
    }

    sol::as_table_t<std::vector<Node>> Shard::NodesGetByLinksViaLua(std::vector<Link> links) {
      return sol::as_table(NodesGetPeered(links).get0());
    }

    sol::table Shard::NodesGetKeyViaLua(std::vector<uint64_t> ids) {
        sol::table properties = lua.create_table(0, ids.size());
        for (const auto& [id, value] : NodesGetKeyPeered(ids).get0()) {
            properties.set(id, value);
        }
        return properties;
    }

    sol::as_table_t<std::map<Link, std::string>> Shard::NodesGetKeyByLinksViaLua(std::vector<Link> links) {
      return sol::as_table(NodesGetKeyPeered(links).get0());
    }

    sol::table Shard::NodesGetTypeViaLua(std::vector<uint64_t> ids) {
        sol::table properties = lua.create_table(0, ids.size());
        for (const auto& [id, value] : NodesGetTypePeered(ids).get0()) {
            properties.set(id, value);
        }
        return properties;
    }

    sol::as_table_t<std::map<Link, std::string>> Shard::NodesGetTypeByLinksViaLua(std::vector<Link> links) {
      return sol::as_table(NodesGetTypePeered(links).get0());
    }

    sol::table Shard::NodesGetPropertyViaLua(std::vector<uint64_t> ids, const std::string& property) {
        sol::table properties = lua.create_table(0, ids.size());
        for (const auto& [id, value] : NodesGetPropertyPeered(ids, property).get0()) {
            properties.set(id, value);
        }
        return properties;
    }

    sol::as_table_t<std::map<Link, sol::object>> Shard::NodesGetPropertyByLinksViaLua(std::vector<Link> links, const std::string& property) {
      std::map<Link, sol::object> properties;

      for(const auto& [link, value] : NodesGetPropertyPeered(links, property).get0()) {
        properties[link] = PropertyToSolObject(value);
      }
      return sol::as_table(properties);
    }

    sol::table Shard::NodesGetPropertiesViaLua(std::vector<uint64_t> ids) {
        sol::table properties = lua.create_table(0, ids.size());
        for (const auto& [id, node_properties] : NodesGetPropertiesPeered(ids).get0()) {
            sol::table property_map = lua.create_table();
            for (const auto& [_key, property] : node_properties) {
                property_map.set(_key, property);
            }
            properties.set(id, property_map);
        }
        return properties;
    }

    sol::as_table_t<std::map<Link, sol::table>> Shard::NodesGetPropertiesByLinksViaLua(std::vector<Link> links) {
      std::map<Link, sol::table> properties;

      for(const auto& [link, value] : NodesGetPropertiesPeered(links).get0()) {
        properties[link] = PropertiesToSolObject(value);
      }
      return sol::as_table(properties);
    }
}