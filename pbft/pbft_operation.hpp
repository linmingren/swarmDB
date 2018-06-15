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

#include "include/bluzelle.hpp"
#include "proto/bluzelle.pb.h"
#include "bootstrap/bootstrap_peers_base.hpp"
#include <cstdint>
#include <string>

namespace bzn {

    // View, sequence
    using operation_key_t = std::tuple<uint64_t, uint64_t, pbft_request>;
    // View, sequence
    using log_key_t = std::tuple<uint64_t, uint64_t>;

    struct operation_key_comparator {
        bool operator()(const operation_key_t&, const operation_key_t& b) const;
    };

    enum class pbft_operation_state {
        prepare,
        commit,
        committed
    };

    class pbft_operation {
    public:

        pbft_operation(uint64_t view, uint64_t sequence, pbft_request msg, const peers_list_t& peers);

        operation_key_t get_operation_key();
        pbft_operation_state get_state();

        void record_preprepare();
        bool has_preprepare();

        void record_prepare(const pbft_msg& prepare);
        bool is_prepared();

        void record_commit(const pbft_msg& commit);
        bool is_committed();

        void begin_commit_phase();
        void end_commit_phase();

        const uint64_t view;
        const uint64_t sequence;
        const pbft_request request;

        std::string debug_string();

    private:
        const peers_list_t& peers;

        pbft_operation_state state = pbft_operation_state::prepare;

        bool preprepare_seen = false;
        std::set<bzn::uuid_t> prepares_seen;
        std::set<bzn::uuid_t> commits_seen;


    };
}

