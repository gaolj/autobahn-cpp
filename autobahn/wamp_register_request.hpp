///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2014 Tavendo GmbH
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AUTOBAHN_WAMP_REGISTER_REQUEST_HPP
#define AUTOBAHN_WAMP_REGISTER_REQUEST_HPP

#include "wamp_procedure.hpp"
#include "wamp_registration.hpp"

// http://stackoverflow.com/questions/22597948/using-boostfuture-with-then-continuations/
#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY
#include <boost/thread/future.hpp>

namespace autobahn {

/// An outstanding wamp call.
class wamp_register_request
{
public:
    wamp_register_request();
    wamp_register_request(const wamp_procedure& procedure);
    wamp_register_request(wamp_register_request&& other);

    const wamp_procedure& procedure() const;
    boost::promise<wamp_registration>& response();
    void set_procedure(wamp_procedure procedure) const;
    void set_response(const wamp_registration& registration);

private:
    wamp_procedure m_procedure;
    boost::promise<wamp_registration> m_response;
};

} // namespace autobahn

#include "wamp_register_request.ipp"

#endif // AUTOBAHN_WAMP_REGISTER_REQUEST_HPP
