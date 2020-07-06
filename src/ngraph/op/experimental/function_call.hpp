//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/op/op.hpp"
#include "ngraph/runtime/backend.hpp"

namespace ngraph
{
    namespace op
    {
        class FunctionCall;
    }
}

class ngraph::op::FunctionCall : public ngraph::op::Op
{
public:
    static constexpr NodeTypeInfo type_info{"FunctionCall", 0};
    const NodeTypeInfo& get_type_info() const override { return type_info; }
    /// \brief Construct a FunctionCall op, which is an op containing a subfunction that is
    /// executed on the passed-in backend.
    /// \param outputs The ordered list of outputs generated by this op. FunctionCall is unique
    /// because it has a variable number of outputs.
    /// \param inputs The input ports used by this node.
    /// \param function The function to be contained within this node.
    /// \param backend The Backend used to execute the function.
    FunctionCall(const std::vector<Output<Node>>& outputs,
                 const std::vector<Output<Node>>& inputs,
                 const Function& function);

    const std::string& description() const override;

    std::shared_ptr<runtime::Backend> get_backend() const;
    std::shared_ptr<runtime::Executable> get_executable() const;
    std::shared_ptr<Function> get_function() const;

private:
    std::shared_ptr<Node> clone_with_new_inputs(const OutputVector& new_args) const override;

    const std::vector<Output<Node>> m_function_outputs;
    std::shared_ptr<Function> m_function;
    std::shared_ptr<runtime::Backend> m_backend;
    std::shared_ptr<runtime::Executable> m_executable;
};
