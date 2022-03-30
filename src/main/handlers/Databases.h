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

#ifndef RAGEDB_DATABASES_H
#define RAGEDB_DATABASES_H


#include <string>
#include "../Database.h"
#include "../Management.h"
class Databases {

  class GetDatabasesHandler : public httpd::handler_base {
  public:
    explicit GetDatabasesHandler(Databases & databases) : parent(databases) {};
  private:
    Databases & parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

  class GetDatabaseHandler : public httpd::handler_base {
  public:
    explicit GetDatabaseHandler(Databases & databases) : parent(databases) {};
  private:
    Databases & parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

  class PostDatabaseHandler : public httpd::handler_base {
  public:
    explicit PostDatabaseHandler(Databases & databases) : parent(databases) {};
  private:
    Databases & parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

  class PutDatabaseHandler : public httpd::handler_base {
  public:
    explicit PutDatabaseHandler(Databases & databases) : parent(databases) {};
  private:
    Databases & parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

  class DeleteDatabaseHandler : public httpd::handler_base {
  public:
    explicit DeleteDatabaseHandler(Databases & databases) : parent(databases) {};
  private:
    Databases & parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

private:
  Management &databases;
  GetDatabasesHandler getDatabasesHandler;
  GetDatabaseHandler getDatabaseHandler;
  PostDatabaseHandler postDatabaseHandler;
  PutDatabaseHandler putDatabaseHandler;
  DeleteDatabaseHandler deleteDatabaseHandler;

public:
  Databases(Management &_databases) : databases(_databases), getDatabasesHandler(*this), getDatabaseHandler(*this),
                                      postDatabaseHandler(*this), putDatabaseHandler(*this), deleteDatabaseHandler(*this) {}
  void set_routes(routes& routes);
};


#endif// RAGEDB_DATABASES_H
