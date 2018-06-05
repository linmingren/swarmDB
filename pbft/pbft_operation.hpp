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
#include <cstdint>

namespace bzn {

    using operation_key_t = std::tuple<uint64_t, uint64_t, bzn::message>;

    class pbft_operation {
    public:

        pbft_operation(uint64_t view, uint64_t sequence, bzn::message msg);

        operation_key_t get_operation_key();

        bool has_preprepare();
        void record_preprepare();


    private:

        const uint64_t view;
        const uint64_t sequence;
        const bzn::message request;

        bool preprepare_seen = false;
    };
}
