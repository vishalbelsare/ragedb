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

    std::map<uint16_t, std::vector<Link>> Shard::PartitionLinksByNodeShardId(std::vector<Link> &links) const {
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

    std::map<uint16_t, std::map<Link, std::vector<Link>>> Shard::PartitionMapOfLinksByNodeShardId(const std::map<Link, std::vector<Link>> &map_of_links) const {
      std::map<uint16_t, std::map<Link, std::vector<Link>>> sharded_links;
      for (int i = 0; i < cpus; i++) {
        sharded_links.insert({i, std::map<Link, std::vector<Link>>() });
      }
      for (auto const& [key, links] :  map_of_links) {
        for (Link link : links) {
          uint16_t node_shard_id = CalculateShardId(link.node_id);
          sharded_links.at(node_shard_id)[key].push_back(link);
        }
      }

      for (int i = 0; i < cpus; i++) {
        if (sharded_links.at(i).empty()) {
          sharded_links.erase(i);
        }
      }
      return sharded_links;
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, Direction direction) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, direction](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, direction);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, Direction direction, const std::string &rel_type) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, direction, rel_type](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, direction, rel_type);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, Direction direction, uint16_t type_id) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, direction, type_id](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, direction, type_id);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, Direction direction, const std::vector<std::string> &rel_types) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, direction, rel_types](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, direction, rel_types);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, const std::string &rel_type) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::BOTH);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, uint16_t type_id) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, type_id](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::BOTH, type_id);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Link>>> Shard::LinksGetRelationshipsIDsPeered(std::vector<Link> links, const std::vector<std::string> &rel_types) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<Link, std::vector<Link>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, rel_types](Shard &local_shard) {
          return local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::BOTH, rel_types);
        });
        futures.push_back(std::move(future));
      }

      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p] (const std::vector<std::map<Link, std::vector<Link>>> &results) {
        std::map<Link, std::vector<Link>> combined;

        for (const std::map<Link, std::vector<Link>> &sharded : results) {
          combined.insert(std::begin(sharded), std::end(sharded));
        }
        return combined;
      });
    }

    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links) {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<uint16_t, std::map<Link, std::vector<Link>>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
          return local_shard.LinksGetShardedIncomingLinks(grouped_links);
        });
        futures.push_back(std::move(future));
      }

      // I now have the incoming links of each Link and which shard they belong to, need to combine them by shard, and for each shard go get them.
      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p, cpus = cpus, sharded_links, this] (const std::vector<std::map<uint16_t, std::map<Link, std::vector<Link>>>> &maps_of_links) {
        std::map<uint16_t, std::map<Link, std::vector<Link>>> incoming_sharded_links;
        for (int i = 0; i < cpus; i++) {
          incoming_sharded_links.insert({ i, std::map<Link, std::vector<Link>>() });
        }
        for (auto map_of_links : maps_of_links) {
          for (auto const &[their_shard_id, map_of_incoming_links] : map_of_links) {
            incoming_sharded_links.at(their_shard_id).insert(std::begin(map_of_incoming_links), std::end(map_of_incoming_links));
          }
        }

        std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;

        for (auto const &[their_shard, grouped_links] : incoming_sharded_links) {
          auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
            return local_shard.LinksGetRelationships(grouped_links);
          });
          futures.push_back(std::move(future));
        }

        // I now have the incoming Relationship of each Link, need to get the outgoing Relationships
        auto p2 = make_shared(std::move(futures));
        return seastar::when_all_succeed(p2->begin(), p2->end()).then([p2, sharded_links, this](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_incoming_relationships) {
          std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;
          for (auto const &[their_shard, grouped_links] : sharded_links) {
            auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
              return local_shard.LinksGetRelationships(local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::OUT));
            });
            futures.push_back(std::move(future));
          }

          auto p3 = make_shared(std::move(futures));
          return seastar::when_all_succeed(p3->begin(), p3->end()).then([p3, maps_of_incoming_relationships](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_outgoing_relationships) {
            std::map<Link, std::vector<Relationship>> combined;

            for (auto map_of_relationships : maps_of_incoming_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }

            for (auto map_of_relationships : maps_of_outgoing_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }
            return combined;
          });

        });
      });
    }


//    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, Direction direction)
//    {
//      return seastar::future<std::map<Link, std::vector<Relationship>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, Direction direction, const std::string &rel_type)
//    {
//      return seastar::future<std::map<Link, std::vector<Relationship>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, Direction direction, uint16_t type_id)
//    {
//      return seastar::future<std::map<Link, std::vector<Relationship>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, Direction direction, const std::vector<std::string> &rel_types)
//    {
//      return seastar::future<std::map<Link, std::vector<Relationship>>>(seastar::future());
//    }
    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, const std::string &rel_type)
    {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<uint16_t, std::map<Link, std::vector<Link>>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
          return local_shard.LinksGetShardedIncomingLinks(grouped_links);
        });
        futures.push_back(std::move(future));
      }

      // I now have the incoming links of each Link and which shard they belong to, need to combine them by shard, and for each shard go get them.
      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p, cpus = cpus, sharded_links, this] (const std::vector<std::map<uint16_t, std::map<Link, std::vector<Link>>>> &maps_of_links) {
        std::map<uint16_t, std::map<Link, std::vector<Link>>> incoming_sharded_links;
        for (int i = 0; i < cpus; i++) {
          incoming_sharded_links.insert({ i, std::map<Link, std::vector<Link>>() });
        }
        for (auto map_of_links : maps_of_links) {
          for (auto const &[their_shard_id, map_of_incoming_links] : map_of_links) {
            incoming_sharded_links.at(their_shard_id).insert(std::begin(map_of_incoming_links), std::end(map_of_incoming_links));
          }
        }

        std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;

        for (auto const &[their_shard, grouped_links] : incoming_sharded_links) {
          auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
            return local_shard.LinksGetRelationships(grouped_links);
          });
          futures.push_back(std::move(future));
        }

        // I now have the incoming Relationship of each Link, need to get the outgoing Relationships
        auto p2 = make_shared(std::move(futures));
        return seastar::when_all_succeed(p2->begin(), p2->end()).then([p2, sharded_links, this](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_incoming_relationships) {
          std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;
          for (auto const &[their_shard, grouped_links] : sharded_links) {
            auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
              return local_shard.LinksGetRelationships(local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::OUT));
            });
            futures.push_back(std::move(future));
          }

          auto p3 = make_shared(std::move(futures));
          return seastar::when_all_succeed(p3->begin(), p3->end()).then([p3, maps_of_incoming_relationships](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_outgoing_relationships) {
            std::map<Link, std::vector<Relationship>> combined;

            for (auto map_of_relationships : maps_of_incoming_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }

            for (auto map_of_relationships : maps_of_outgoing_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }
            return combined;
          });

        });
      });
    }
    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, uint16_t type_id)
    {
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<uint16_t, std::map<Link, std::vector<Link>>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
          return local_shard.LinksGetShardedIncomingLinks(grouped_links);
        });
        futures.push_back(std::move(future));
      }

      // I now have the incoming links of each Link and which shard they belong to, need to combine them by shard, and for each shard go get them.
      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p, cpus = cpus, sharded_links, this] (const std::vector<std::map<uint16_t, std::map<Link, std::vector<Link>>>> &maps_of_links) {
        std::map<uint16_t, std::map<Link, std::vector<Link>>> incoming_sharded_links;
        for (int i = 0; i < cpus; i++) {
          incoming_sharded_links.insert({ i, std::map<Link, std::vector<Link>>() });
        }
        for (auto map_of_links : maps_of_links) {
          for (auto const &[their_shard_id, map_of_incoming_links] : map_of_links) {
            incoming_sharded_links.at(their_shard_id).insert(std::begin(map_of_incoming_links), std::end(map_of_incoming_links));
          }
        }

        std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;

        for (auto const &[their_shard, grouped_links] : incoming_sharded_links) {
          auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
            return local_shard.LinksGetRelationships(grouped_links);
          });
          futures.push_back(std::move(future));
        }

        // I now have the incoming Relationship of each Link, need to get the outgoing Relationships
        auto p2 = make_shared(std::move(futures));
        return seastar::when_all_succeed(p2->begin(), p2->end()).then([p2, sharded_links, this](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_incoming_relationships) {
          std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;
          for (auto const &[their_shard, grouped_links] : sharded_links) {
            auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
              return local_shard.LinksGetRelationships(local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::OUT));
            });
            futures.push_back(std::move(future));
          }

          auto p3 = make_shared(std::move(futures));
          return seastar::when_all_succeed(p3->begin(), p3->end()).then([p3, maps_of_incoming_relationships](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_outgoing_relationships) {
            std::map<Link, std::vector<Relationship>> combined;

            for (auto map_of_relationships : maps_of_incoming_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }

            for (auto map_of_relationships : maps_of_outgoing_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }
            return combined;
          });

        });
      });
    }
    seastar::future<std::map<Link, std::vector<Relationship>>> Shard::LinksGetRelationshipsPeered(std::vector<Link> links, const std::vector<std::string> &rel_types){
      std::map<uint16_t, std::vector<Link>> sharded_links = PartitionLinksByNodeShardId(links);

      std::vector<seastar::future<std::map<uint16_t, std::map<Link, std::vector<Link>>>>> futures;
      for (auto const &[their_shard, grouped_links] : sharded_links) {
        auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, rel_types](Shard &local_shard) {
          return local_shard.LinksGetShardedIncomingLinks(grouped_links, rel_types);
        });
        futures.push_back(std::move(future));
      }

      // I now have the incoming links of each Link and which shard they belong to, need to combine them by shard, and for each shard go get them.
      auto p = make_shared(std::move(futures));
      return seastar::when_all_succeed(p->begin(), p->end()).then([p, cpus = cpus, sharded_links, rel_types, this] (const std::vector<std::map<uint16_t, std::map<Link, std::vector<Link>>>> &maps_of_links) {
        std::map<uint16_t, std::map<Link, std::vector<Link>>> incoming_sharded_links;
        for (int i = 0; i < cpus; i++) {
          incoming_sharded_links.insert({ i, std::map<Link, std::vector<Link>>() });
        }
        for (auto map_of_links : maps_of_links) {
          for (auto const &[their_shard_id, map_of_incoming_links] : map_of_links) {
            incoming_sharded_links.at(their_shard_id).insert(std::begin(map_of_incoming_links), std::end(map_of_incoming_links));
          }
        }

        std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;

        for (auto const &[their_shard, grouped_links] : incoming_sharded_links) {
          auto future = container().invoke_on(their_shard, [grouped_links = grouped_links](Shard &local_shard) {
            return local_shard.LinksGetRelationships(grouped_links);
          });
          futures.push_back(std::move(future));
        }

        // I now have the incoming Relationship of each Link, need to get the outgoing Relationships
        auto p2 = make_shared(std::move(futures));
        return seastar::when_all_succeed(p2->begin(), p2->end()).then([p2, sharded_links, rel_types, this](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_incoming_relationships) {
          std::vector<seastar::future<std::map<Link, std::vector<Relationship>>>> futures;
          for (auto const &[their_shard, grouped_links] : sharded_links) {
            auto future = container().invoke_on(their_shard, [grouped_links = grouped_links, rel_types](Shard &local_shard) {
              return local_shard.LinksGetRelationships(local_shard.LinksGetRelationshipsIDs(grouped_links, Direction::OUT, rel_types));
            });
            futures.push_back(std::move(future));
          }

          auto p3 = make_shared(std::move(futures));
          return seastar::when_all_succeed(p3->begin(), p3->end()).then([p3, maps_of_incoming_relationships](const std::vector<std::map<Link, std::vector<Relationship>>> &maps_of_outgoing_relationships) {
            std::map<Link, std::vector<Relationship>> combined;

            for (auto map_of_relationships : maps_of_incoming_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }

            for (auto map_of_relationships : maps_of_outgoing_relationships) {
              for (auto const [link, rels] : map_of_relationships) {
                combined[link].insert(std::end(combined[link]), std::begin(rels), std::end(rels));
              }
            }
            return combined;
          });

        });
      });
    }
//
//
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, Direction direction)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, Direction direction, const std::string &rel_type)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, Direction direction, uint16_t type_id)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, Direction direction, const std::vector<std::string> &rel_types)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, const std::string &rel_type)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, uint16_t type_id)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
//    seastar::future<std::map<Link, std::vector<Node>>> Shard::LinksGetNeighborsPeered(std::vector<Link> links, const std::vector<std::string> &rel_types)
//    {
//      return seastar::future<std::map<Link, std::vector<Node>>>(seastar::future());
//    }
}