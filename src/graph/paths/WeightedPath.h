/*
 * Copyright Max De Marzi. All Rights Reserved.
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

#ifndef RAGEDB_WEIGHTEDPATH_H
#define RAGEDB_WEIGHTEDPATH_H


#include "../Node.h"
#include "../Relationship.h"
namespace ragedb {
    class WeightedPath {
        private:
            std::vector<Node> nodes;
            std::vector<Relationship> relationships;
            double path_weight;

        public:
            WeightedPath(Node start_node);
            WeightedPath(std::vector<Node> nodes);
            WeightedPath(std::vector<Node> nodes, std::vector<Relationship> relationships, double weight);

            Node GetEndNode();
            Node GetStartNode();
            std::vector<Node> GetNodes();
            Relationship GetLastRelationship();
            std::vector<Relationship> GetRelationships();
            int length();
            double weight();
    };
}


#endif// RAGEDB_WEIGHTEDPATH_H
