// Copyright (C) 2018 Bluzelle
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License, version 3,
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <string>

#include <node/node_base.hpp>
#include <bootstrap/bootstrap_peers.hpp>
#include <bootstrap/peer_address.hpp>

namespace bzn {
    using client_t = std::string; //placeholder

    class pbft_base {
    public:
        virtual void start() = 0;

        virtual void handle_message(const bzn::message &msg, std::shared_ptr<bzn::session_base> session) = 0;

        virtual bool is_primary() = 0;

        virtual const peer_address_t &get_primary() = 0;

    };
}
