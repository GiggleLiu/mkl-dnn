/*******************************************************************************
* Copyright 2016-2017 Intel Corporation
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
*******************************************************************************/

#ifndef CPU_ENGINE_HPP
#define CPU_ENGINE_HPP

#include <assert.h>

#include "mkldnn.h"

#include "c_types_map.hpp"
#include "../common/engine.hpp"

namespace mkldnn {
namespace impl {
namespace cpu {

class cpu_engine_t: public engine_t {
public:
    cpu_engine_t(): engine_t(engine_kind::cpu) {}

    virtual status_t submit(primitive_t *p, event_t *e,
            event_vector &prerequisites);

    /* implementation part */

    virtual status_t memory_primitive_desc_create(memory_pd_t **memory_pd,
            const memory_desc_t *memory_d);
    virtual status_t view_primitive_desc_create(view_pd_t **view_pd,
            const memory_pd_t *memory_pd, const dims_t dims,
            const dims_t offsets);
    virtual status_t concat_primitive_desc_create(concat_pd_t **concat_pd,
            const memory_desc_t *output_d, int n, int concat_dim,
            const memory_pd_t **input_pds);
    virtual status_t sum_primitive_desc_create(sum_pd_t **sum_pd,
            const memory_desc_t *output_d, int n, double* scale,
            const memory_pd_t **input_pds);

    virtual const reorder_primitive_desc_create_f*
        get_reorder_implementation_list() const;
    virtual const primitive_desc_create_f* get_implementation_list() const;
};

class cpu_engine_factory_t: public engine_factory_t {
public:
    virtual size_t count() const { return 1; }
    virtual engine_kind_t kind() const { return engine_kind::cpu; }
    virtual status_t engine_create(engine_t **engine, size_t index) const {
        assert(index == 0);
        *engine = new cpu_engine_t();
        return status::success;
    };
};

extern cpu_engine_factory_t engine_factory;

}
}
}

#endif

// vim: et ts=4 sw=4 cindent cino^=l0,\:0,N-s
