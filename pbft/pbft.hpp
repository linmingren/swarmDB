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

#include <include/bluzelle.hpp>
#include <pbft/pbft_base.hpp>
#include <pbft/pbft_service_base.hpp>

namespace bzn {

    class pbft final : public bzn::pbft_base, public std::enable_shared_from_this<pbft>{
    public:
        pbft(
                std::shared_ptr<bzn::node_base> node,
                const bzn::peers_list_t& peers,
                const bzn::uuid_t& uuid,
                pbft_service_base& service
        );

        void start() override;

        void handle_message(const pbft_msg& msg) override;

        size_t outstanding_operations_count() const;

        bool is_primary() const override;

        const peer_address_t& get_primary() const override;

        const bzn::uuid_t& get_uuid();


    private:
        // Using 1 as first value here to distinguish from default value of 0 in protobuf
        uint64_t view = 1;
        uint64_t next_issued_sequence_number = 1;

        uint64_t low_water_mark = 1;
        uint64_t high_water_mark = UINT64_MAX;

        std::shared_ptr<bzn::node_base> node;
        const bzn::peers_list_t peers;
        const bzn::uuid_t uuid;
        pbft_service_base& service;

        std::map<bzn::operation_key_t, bzn::pbft_operation, bzn::operation_key_comparator> operations;
        std::map<bzn::log_key_t, bzn::operation_key_t> accepted_preprepares;

        pbft_operation& find_operation(const uint64_t &view, const uint64_t &sequence, const pbft_request &request);
        pbft_operation& find_operation(const pbft_msg& msg);

        bool preliminary_filter_msg(const pbft_msg& msg);

        void handle_request(const pbft_msg& msg);
        void handle_preprepare(const pbft_msg& msg);
        void handle_prepare(const pbft_msg& msg);
        void handle_commit(const pbft_msg& msg);

        void maybe_advance_operation_state(pbft_operation& op);
        void do_preprepare(pbft_operation& op);
        void do_prepare(pbft_operation& op);
        void do_commit(pbft_operation& op);
        void do_committed(pbft_operation& op);

        void unwrap_message(const bzn::message& json, std::shared_ptr<bzn::session_base> session);
        bzn::message wrap_message(const pbft_msg& message);
        pbft_msg common_message_setup(const pbft_operation& op);
        void broadcast(const pbft_msg& message);

    };

} // namespace bzn

