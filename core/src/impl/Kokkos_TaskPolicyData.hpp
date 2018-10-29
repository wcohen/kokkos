/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2014) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef KOKKOS_IMPL_TASKPOLICYDATA_HPP
#define KOKKOS_IMPL_TASKPOLICYDATA_HPP

//----------------------------------------------------------------------------

#include <Kokkos_Macros.hpp>
#if defined( KOKKOS_ENABLE_TASKDAG )

#include <Kokkos_Core_fwd.hpp>
#include <Kokkos_TaskScheduler_fwd.hpp>

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

namespace Kokkos {
namespace Impl {

//----------------------------------------------------------------------------

template< int TaskEnum , typename DepFutureType >
struct TaskPolicyData
{
  using execution_space = typename DepFutureType::execution_space ;
  using scheduler_type  = TaskSchedulerBase;

  enum : int { m_task_type = TaskEnum };

  scheduler_type const * m_scheduler ;
  DepFutureType  const   m_dependence ;
  int                    m_priority ;

  TaskPolicyData() = delete ;
  TaskPolicyData( TaskPolicyData && ) = default ;
  TaskPolicyData( TaskPolicyData const & ) = default ;
  TaskPolicyData & operator = ( TaskPolicyData && ) = default ;
  TaskPolicyData & operator = ( TaskPolicyData const & ) = default ;

  KOKKOS_INLINE_FUNCTION
  TaskPolicyData( DepFutureType        const & arg_future
                , Kokkos::TaskPriority const & arg_priority )
    : m_scheduler( nullptr )
    , m_dependence( arg_future )
    , m_priority( static_cast<int>( arg_priority ) )
    {}

  KOKKOS_INLINE_FUNCTION
  TaskPolicyData( scheduler_type const& arg_scheduler
                , Kokkos::TaskPriority const & arg_priority )
    : m_scheduler( & arg_scheduler )
    , m_dependence()
    , m_priority( static_cast<int>( arg_priority ) )
    {}

  KOKKOS_INLINE_FUNCTION
  TaskPolicyData( scheduler_type const& arg_scheduler
                , DepFutureType        const & arg_future
                , Kokkos::TaskPriority const & arg_priority )
    : m_scheduler( & arg_scheduler )
    , m_dependence( arg_future )
    , m_priority( static_cast<int>( arg_priority ) )
    {}
};

} // namespace Impl
} // namespace Kokkos

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#endif /* #if defined( KOKKOS_ENABLE_TASKDAG ) */
#endif /* #ifndef KOKKOS_IMPL_TASKPOLICYDATA_HPP */
