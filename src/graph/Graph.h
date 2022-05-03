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

#ifndef RAGEDB_GRAPH_H
#define RAGEDB_GRAPH_H


#include <string>
#include <iostream>
#include <fstream>
#include <reckless/policy_log.hpp>
#include <reckless/file_writer.hpp>
#include <reckless/crash_handler.hpp>
#include <seastar/core/sleep.hh>
#include <seastar/core/seastar.hh>
#include <seastar/core/coroutine.hh>
#include <seastar/core/future.hh>
#include <seastar/core/sharded.hh>
#include <seastar/core/file.hh>
#include <seastar/core/fstream.hh>
#include <seastar/core/io_intent.hh>

#include "Shard.h"

using log_t = reckless::policy_log<
        reckless::indent<4>,       // 4 spaces of indent
        ' ',                       // Field separator
        reckless::timestamp_field  // Then timestamp field
>;

namespace ragedb {

    class Graph {
    private:
        std::string name;
        char log_path[260] = {0};
        reckless::file_writer writer;
        log_t r_logger;

    public:
        seastar::sharded <Shard> shard;
        explicit Graph(std::string _name) : name (std::move(_name)), writer(strcat(strncat(log_path, name.c_str(), name.size()), ".log")), r_logger(&writer) {};
        std::string GetName() const;
        seastar::future<> Start();
        void StartLogging();
        seastar::future<> Stop();
        void Clear();
        void Log(const seastar::sstring method, const seastar::sstring url);
        void Log(const seastar::sstring method, const seastar::sstring url, const seastar::sstring body);
    };
}

#endif //RAGEDB_GRAPH_H
