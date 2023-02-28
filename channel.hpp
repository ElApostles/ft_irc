/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#pragma once

#include "irc_constants.hpp"

#include "reply.hpp"

#include <libserv/libserv.hpp>
#include <smart_ptr/smart_ptr.hpp>
#include <thread/readwrite_lock.hpp>

#include <algorithm>
#include <bitset>
#include <string>

namespace ft
{
    namespace irc
    {
        class message;

        class server;

        class user;

        class channel : public ft::enable_shared_from_this<channel>
        {
        public:
            enum channel_mode
            {
                CHANNEL_MODE_PRIVATE,
                CHANNEL_MODE_SECRET,
                CHANNEL_MODE_MODERATED,
                CHANNEL_MODE_TOPIC_LIMIT,
                CHANNEL_MODE_INVITE_ONLY,
                CHANNEL_MODE_NO_PRIVMSG,
                // CHANNEL_MODE_KEY,
                // CHANNEL_MODE_BAN,
                // CHANNEL_MODE_LIMIT,
                NUMBEROF_CHANNEL_MODE
            };

            struct member
            {
                enum member_mode
                {
                    MEMBER_MODE_OWNER,
                    MEMBER_MODE_OPERATOR,
                    MEMBER_MODE_VOICE,
                    NUMBEROF_MEMBER_MODE
                };

                explicit member(const ft::shared_ptr<ft::irc::user>& user);

                ft::shared_ptr<ft::irc::user> user;
                std::bitset<NUMBEROF_MEMBER_MODE> mode;

                bool operator==(ft::shared_ptr<ft::irc::user> that);
            };

            typedef ft::serv::dynamic_array<member>::type member_list;

        private:
            ft::irc::server& server;
            std::string name;
            std::string topic;
            std::bitset<NUMBEROF_CHANNEL_MODE> mode;
            member_list members;
            mutable ft::readwrite_lock lock;
            bool invalidated;

        public:
            channel(ft::irc::server& server, const std::string& pass);
            ~channel();

        public:
            const std::string& get_name() const throw();

            const std::string& get_topic() const throw();
            void set_topic(const std::string& topic);

            bool get_mode(channel_mode index) const throw();
            void set_mode(channel_mode index, bool value) throw();

            const member_list& get_members() const throw();

            ft::irc::reply_numerics enter_user(const ft::shared_ptr<ft::irc::user>& user);
            void leave_user(const ft::shared_ptr<ft::irc::user>& user);

        public:
            void broadcast(const ft::irc::message& message) const;

        private:
            channel(const channel&);
            channel& operator=(const channel&);
        };
    }
}
