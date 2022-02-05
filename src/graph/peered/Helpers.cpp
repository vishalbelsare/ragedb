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

    std::map<uint16_t, std::vector<uint64_t>> Shard::PartitionNodeIdsByNodeShardId(const std::vector<uint64_t> &ids) const {
      std::map<uint16_t, std::vector<uint64_t>> sharded_nodes_ids;
      for (int i = 0; i < cpus; i++) {
        sharded_nodes_ids.insert({i, std::vector<uint64_t>() });
      }
      for (auto id : ids) {
        sharded_nodes_ids[CalculateShardId(id)].emplace_back(id);
      }

      for (int i = 0; i < cpus; i++) {
        if (sharded_nodes_ids.at(i).empty()) {
          sharded_nodes_ids.erase(i);
        }
      }
      return sharded_nodes_ids;
    }

    std::map<uint16_t, std::vector<uint64_t>> Shard::PartitionNodeIdsByNodeShardId(const std::vector<Link>& links) const {
      std::map<uint16_t, std::vector<uint64_t>> sharded_nodes_ids;
      for (int i = 0; i < cpus; i++) {
        sharded_nodes_ids.insert({i, std::vector<uint64_t>() });
      }
      for (auto link : links) {
        sharded_nodes_ids[CalculateShardId(link.node_id)].emplace_back(link.node_id);
      }

      for (int i = 0; i < cpus; i++) {
        if (sharded_nodes_ids.at(i).empty()) {
          sharded_nodes_ids.erase(i);
        }
      }
      return sharded_nodes_ids;
    }

    std::map<uint16_t, std::vector<Link>> Shard::PartitionLinksByNodeShardId(const std::vector<Link> &links) const {
      std::map<uint16_t, std::vector<Link>> sharded_links;
      for (int i = 0; i < cpus; i++) {
        sharded_links.insert({i, std::vector<Link>() });
      }

      for (Link link : links) {
        uint16_t node_shard_id = CalculateShardId(link.node_id);
        sharded_links.at(node_shard_id).push_back(link);
      }

      for (int i = 0; i < cpus; i++) {
        if (sharded_links.at(i).empty()) {
          sharded_links.erase(i);
        }
      }
      return sharded_links;
    }

}