/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#pragma once

#include "irc_constants.hpp"

#include "message.hpp"

#include <libserv/libserv.hpp>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#define IRC_REP_MAP(_MACRO)           \
                                      \
    /* Error Replies */               \
    _MACRO(401, ERR_NOSUCHNICK)       \
    _MACRO(402, ERR_NOSUCHSERVER)     \
    _MACRO(403, ERR_NOSUCHCHANNEL)    \
    _MACRO(404, ERR_CANNOTSENDTOCHAN) \
    _MACRO(405, ERR_TOOMANYCHANNELS)  \
    _MACRO(406, ERR_WASNOSUCHNICK)    \
    _MACRO(407, ERR_TOOMANYTARGETS)   \
    _MACRO(409, ERR_NOORIGIN)         \
    _MACRO(411, ERR_NORECIPIENT)      \
    _MACRO(412, ERR_NOTEXTTOSEND)     \
    _MACRO(413, ERR_NOTOPLEVEL)       \
    _MACRO(414, ERR_WILDTOPLEVEL)     \
    _MACRO(421, ERR_UNKNOWNCOMMAND)   \
    _MACRO(422, ERR_NOMOTD)           \
    _MACRO(423, ERR_NOADMININFO)      \
    _MACRO(424, ERR_FILEERROR)        \
    _MACRO(431, ERR_NONICKNAMEGIVEN)  \
    _MACRO(432, ERR_ERRONEUSNICKNAME) \
    _MACRO(433, ERR_NICKNAMEINUSE)    \
    _MACRO(436, ERR_NICKCOLLISION)    \
    _MACRO(441, ERR_USERNOTINCHANNEL) \
    _MACRO(442, ERR_NOTONCHANNEL)     \
    _MACRO(443, ERR_USERONCHANNEL)    \
    _MACRO(444, ERR_NOLOGIN)          \
    _MACRO(445, ERR_SUMMONDISABLED)   \
    _MACRO(446, ERR_USERSDISABLED)    \
    _MACRO(451, ERR_NOTREGISTERED)    \
    _MACRO(461, ERR_NEEDMOREPARAMS)   \
    _MACRO(462, ERR_ALREADYREGISTRED) \
    _MACRO(463, ERR_NOPERMFORHOST)    \
    _MACRO(464, ERR_PASSWDMISMATCH)   \
    _MACRO(465, ERR_YOUREBANNEDCREEP) \
    _MACRO(467, ERR_KEYSET)           \
    _MACRO(471, ERR_CHANNELISFULL)    \
    _MACRO(472, ERR_UNKNOWNMODE)      \
    _MACRO(473, ERR_INVITEONLYCHAN)   \
    _MACRO(474, ERR_BANNEDFROMCHAN)   \
    _MACRO(475, ERR_BADCHANNELKEY)    \
    _MACRO(481, ERR_NOPRIVILEGES)     \
    _MACRO(482, ERR_CHANOPRIVSNEEDED) \
    _MACRO(483, ERR_CANTKILLSERVER)   \
    _MACRO(491, ERR_NOOPERHOST)       \
    _MACRO(501, ERR_UMODEUNKNOWNFLAG) \
    _MACRO(502, ERR_USERSDONTMATCH)   \
                                      \
    /* Command responses */           \
    _MACRO(300, RPL_NONE)             \
    _MACRO(302, RPL_USERHOST)         \
    _MACRO(303, RPL_ISON)             \
    _MACRO(301, RPL_AWAY)             \
    _MACRO(305, RPL_UNAWAY)           \
    _MACRO(306, RPL_NOWAWAY)          \
    _MACRO(311, RPL_WHOISUSER)        \
    _MACRO(312, RPL_WHOISSERVER)      \
    _MACRO(313, RPL_WHOISOPERATOR)    \
    _MACRO(317, RPL_WHOISIDLE)        \
    _MACRO(318, RPL_ENDOFWHOIS)       \
    _MACRO(319, RPL_WHOISCHANNELS)    \
    _MACRO(314, RPL_WHOWASUSER)       \
    _MACRO(369, RPL_ENDOFWHOWAS)      \
    _MACRO(321, RPL_LISTSTART)        \
    _MACRO(322, RPL_LIST)             \
    _MACRO(323, RPL_LISTEND)          \
    _MACRO(324, RPL_CHANNELMODEIS)    \
    _MACRO(331, RPL_NOTOPIC)          \
    _MACRO(332, RPL_TOPIC)            \
    _MACRO(341, RPL_INVITING)         \
    _MACRO(342, RPL_SUMMONING)        \
    _MACRO(351, RPL_VERSION)          \
    _MACRO(352, RPL_WHOREPLY)         \
    _MACRO(315, RPL_ENDOFWHO)         \
    _MACRO(353, RPL_NAMREPLY)         \
    _MACRO(366, RPL_ENDOFNAMES)       \
    _MACRO(364, RPL_LINKS)            \
    _MACRO(365, RPL_ENDOFLINKS)       \
    _MACRO(367, RPL_BANLIST)          \
    _MACRO(368, RPL_ENDOFBANLIST)     \
    _MACRO(371, RPL_INFO)             \
    _MACRO(374, RPL_ENDOFINFO)        \
    _MACRO(375, RPL_MOTDSTART)        \
    _MACRO(372, RPL_MOTD)             \
    _MACRO(376, RPL_ENDOFMOTD)        \
    _MACRO(381, RPL_YOUREOPER)        \
    _MACRO(382, RPL_REHASHING)        \
    _MACRO(391, RPL_TIME)             \
    _MACRO(392, RPL_USERSSTART)       \
    _MACRO(393, RPL_USERS)            \
    _MACRO(394, RPL_ENDOFUSERS)       \
    _MACRO(395, RPL_NOUSERS)          \
    _MACRO(200, RPL_TRACELINK)        \
    _MACRO(201, RPL_TRACECONNECTING)  \
    _MACRO(202, RPL_TRACEHANDSHAKE)   \
    _MACRO(203, RPL_TRACEUNKNOWN)     \
    _MACRO(204, RPL_TRACEOPERATOR)    \
    _MACRO(205, RPL_TRACEUSER)        \
    _MACRO(206, RPL_TRACESERVER)      \
    _MACRO(208, RPL_TRACENEWTYPE)     \
    _MACRO(261, RPL_TRACELOG)         \
    _MACRO(211, RPL_STATSLINKINFO)    \
    _MACRO(212, RPL_STATSCOMMANDS)    \
    _MACRO(213, RPL_STATSCLINE)       \
    _MACRO(214, RPL_STATSNLINE)       \
    _MACRO(215, RPL_STATSILINE)       \
    _MACRO(216, RPL_STATSKLINE)       \
    _MACRO(218, RPL_STATSYLINE)       \
    _MACRO(219, RPL_ENDOFSTATS)       \
    _MACRO(241, RPL_STATSLLINE)       \
    _MACRO(242, RPL_STATSUPTIME)      \
    _MACRO(243, RPL_STATSOLINE)       \
    _MACRO(244, RPL_STATSHLINE)       \
    _MACRO(221, RPL_UMODEIS)          \
    _MACRO(251, RPL_LUSERCLIENT)      \
    _MACRO(252, RPL_LUSEROP)          \
    _MACRO(253, RPL_LUSERUNKNOWN)     \
    _MACRO(254, RPL_LUSERCHANNELS)    \
    _MACRO(255, RPL_LUSERME)          \
    _MACRO(256, RPL_ADMINME)          \
    _MACRO(257, RPL_ADMINLOC1)        \
    _MACRO(258, RPL_ADMINLOC2)        \
    _MACRO(259, RPL_ADMINEMAIL)       \
                                      \
    /* Reserved numerics */           \
    _MACRO(209, RPL_TRACECLASS)       \
    _MACRO(217, RPL_STATSQLINE)       \
    _MACRO(231, RPL_SERVICEINFO)      \
    _MACRO(232, RPL_ENDOFSERVICES)    \
    _MACRO(233, RPL_SERVICE)          \
    _MACRO(234, RPL_SERVLIST)         \
    _MACRO(235, RPL_SERVLISTEND)      \
    _MACRO(316, RPL_WHOISCHANOP)      \
    _MACRO(361, RPL_KILLDONE)         \
    _MACRO(362, RPL_CLOSING)          \
    _MACRO(363, RPL_CLOSEEND)         \
    _MACRO(373, RPL_INFOSTART)        \
    _MACRO(384, RPL_MYPORTIS)         \
    _MACRO(466, ERR_YOUWILLBEBANNED)  \
    _MACRO(476, ERR_BADCHANMASK)      \
    _MACRO(492, ERR_NOSERVICEHOST)    \
    /* END */

namespace ft
{
    namespace irc
    {
        enum reply_numerics
        {
#define _MAKE_ENUM(numeric, name) name = numeric,
            IRC_REP_MAP(_MAKE_ENUM)
#undef _MAKE_ENUM
        };

        struct make_reply_base
        {
            typedef const std::string& param_t;

            std::string prefix;
        };

        struct make_error : make_reply_base
        {
            static inline ft::irc::message no_such_nickname(param_t nickname)
            {
                return ft::irc::message(ERR_NOSUCHNICK) << nickname << "No such nick/channel";
            }

            static inline ft::irc::message no_such_server(param_t server_name)
            {
                return ft::irc::message(ERR_NOSUCHSERVER) << server_name << "No such server";
            }

            static inline ft::irc::message no_such_channel(param_t channel_name)
            {
                return ft::irc::message(ERR_NOSUCHCHANNEL) << channel_name << "No such channel";
            }

            static inline ft::irc::message cannot_send_to_channel(param_t channel_name)
            {
                return ft::irc::message(ERR_CANNOTSENDTOCHAN) << channel_name << "Cannot send to channel";
            }

            static inline ft::irc::message too_many_channels(param_t channel_name)
            {
                return ft::irc::message(ERR_TOOMANYCHANNELS) << channel_name << "You have joined too many channels";
            }

            static inline ft::irc::message was_no_such_nickname(param_t nickname)
            {
                return ft::irc::message(ERR_WASNOSUCHNICK) << nickname << "There was no such nickname";
            }

            static inline ft::irc::message too_many_targets(param_t target)
            {
                return ft::irc::message(ERR_TOOMANYTARGETS) << target << "Duplicate recipients. No ft::irc::message delivered";
            }

            static inline ft::irc::message no_origin()
            {
                return ft::irc::message(ERR_NOORIGIN) << "No origin specified";
            }

            static inline ft::irc::message no_recipient(param_t command)
            {
                return ft::irc::message(ERR_NORECIPIENT) << "No recipient given (" + command + ")";
            }

            static inline ft::irc::message no_text_to_send()
            {
                return ft::irc::message(ERR_NOTEXTTOSEND) << "No text to send";
            }

            static inline ft::irc::message no_toplevel(param_t mask)
            {
                return ft::irc::message(ERR_NOTOPLEVEL) << mask << "No toplevel domain specified";
            }

            static inline ft::irc::message wildcard_toplevel(param_t mask)
            {
                return ft::irc::message(ERR_WILDTOPLEVEL) << mask << "Wildcard in toplevel domain";
            }

            static inline ft::irc::message unknown_command(param_t command)
            {
                return ft::irc::message(ERR_UNKNOWNCOMMAND) << command << "Unknown command";
            }

            static inline ft::irc::message no_motd()
            {
                return ft::irc::message(ERR_NOMOTD) << "MOTD File is missing";
            }

            static inline ft::irc::message no_admin_info(param_t server_name)
            {
                return ft::irc::message(ERR_NOADMININFO) << server_name << "No administrative info available";
            }

            static inline ft::irc::message file_error(param_t file_operation, param_t filename)
            {
                return ft::irc::message(ERR_FILEERROR) << "File error doing " + file_operation + " on " + filename;
            }

            static inline ft::irc::message no_nickname_given()
            {
                return ft::irc::message(ERR_NONICKNAMEGIVEN) << "No nickname given";
            }

            static inline ft::irc::message erroneous_nickname(param_t nickname)
            {
                return ft::irc::message(ERR_ERRONEUSNICKNAME) << nickname << "Erroneous nickname";
            }

            static inline ft::irc::message nickname_in_use(param_t nickname)
            {
                return ft::irc::message(ERR_NICKNAMEINUSE) << nickname << "Nickname is already in use";
            }

            static inline ft::irc::message nickname_collision(param_t nickname)
            {
                return ft::irc::message(ERR_NICKCOLLISION) << nickname << "Nickname collision KILL";
            }

            static inline ft::irc::message user_not_in_channel(param_t nickname, param_t channel_name)
            {
                return ft::irc::message(ERR_USERNOTINCHANNEL) << nickname << channel_name << "They aren't on that channel";
            }

            static inline ft::irc::message not_on_channel(param_t channel_name)
            {
                return ft::irc::message(ERR_NOTONCHANNEL) << channel_name << "You're not on that channel";
            }

            static inline ft::irc::message user_on_channel(param_t username, param_t channel_name)
            {
                return ft::irc::message(ERR_USERONCHANNEL) << username << channel_name << "is already on channel";
            }

            static inline ft::irc::message no_login(param_t username)
            {
                return ft::irc::message(ERR_NOLOGIN) << username << "User not logged in";
            }

            static inline ft::irc::message summon_disabled()
            {
                return ft::irc::message(ERR_SUMMONDISABLED) << "SUMMON has been disabled";
            }

            static inline ft::irc::message users_disabled()
            {
                return ft::irc::message(ERR_USERSDISABLED) << "USERS has been disabled";
            }

            static inline ft::irc::message not_registered()
            {
                return ft::irc::message(ERR_NOTREGISTERED) << "You have not registered";
            }

            static inline ft::irc::message need_more_parameters(param_t command)
            {
                return ft::irc::message(ERR_NEEDMOREPARAMS) << command << "Not enough parameters";
            }

            static inline ft::irc::message already_registered()
            {
                return ft::irc::message(ERR_ALREADYREGISTRED) << "You may not reregister";
            }

            static inline ft::irc::message no_permission_for_host()
            {
                return ft::irc::message(ERR_NOPERMFORHOST) << "Your host isn't among the privileged";
            }

            static inline ft::irc::message password_mismatch()
            {
                return ft::irc::message(ERR_PASSWDMISMATCH) << "Password incorrect";
            }

            static inline ft::irc::message banned_from_server()
            {
                return ft::irc::message(ERR_YOUREBANNEDCREEP) << "You are banned from this server";
            }

            static inline ft::irc::message channel_key_already_set(param_t channel_name)
            {
                return ft::irc::message(ERR_KEYSET) << channel_name << "Channel key already set";
            }

            static inline ft::irc::message channel_is_full(param_t channel_name)
            {
                return ft::irc::message(ERR_CHANNELISFULL) << channel_name << "Cannot join channel (+l)";
            }

            static inline ft::irc::message unknown_mode(char mode_char)
            {
                return ft::irc::message(ERR_UNKNOWNMODE) << mode_char << "is unknown mode char to me";
            }

            static inline ft::irc::message invite_only_channel(param_t channel_name)
            {
                return ft::irc::message(ERR_INVITEONLYCHAN) << channel_name << "Cannot join channel (+i)";
            }

            static inline ft::irc::message banned_from_channel(param_t channel_name)
            {
                return ft::irc::message(ERR_BANNEDFROMCHAN) << channel_name << "Cannot join channel (+b)";
            }

            static inline ft::irc::message bad_channel_key(param_t channel_name)
            {
                return ft::irc::message(ERR_BADCHANNELKEY) << channel_name << "Cannot join channel (+k)";
            }

            static inline ft::irc::message no_privileges()
            {
                return ft::irc::message(ERR_NOPRIVILEGES) << "Permission Denied- You're not an IRC operator";
            }

            static inline ft::irc::message channel_operator_privileges_needed(param_t channel_name)
            {
                return ft::irc::message(ERR_CHANOPRIVSNEEDED) << channel_name << "You're not channel operator";
            }

            static inline ft::irc::message cannot_kill_server()
            {
                return ft::irc::message(ERR_CANTKILLSERVER) << "You cant kill a server!";
            }

            static inline ft::irc::message no_operator_host()
            {
                return ft::irc::message(ERR_NOOPERHOST) << "No O-lines for your host";
            }

            static inline ft::irc::message user_mode_unknown_flag()
            {
                return ft::irc::message(ERR_UMODEUNKNOWNFLAG) << "Unknown MODE flag";
            }

            static inline ft::irc::message users_donot_match()
            {
                return ft::irc::message(ERR_USERSDONTMATCH) << "Cant change mode for other users";
            }
        };

        struct person_info
        {
            std::string nickname;
            std::string username;
            std::string host;
            bool is_operator;
            bool is_away;
        };

        struct channel_info
        {
            std::string channel_name;
            bool is_chanop;
            bool is_chanspk;
        };

        struct member_info
        {
            std::string nickname;
            bool is_chanop;
            bool is_chanspk;
        };

        struct make_reply : make_reply_base
        {
            static inline ft::irc::message none()
            {
                return ft::irc::message(RPL_NONE);
            }

            static inline ft::irc::message user_host(const std::vector<person_info>& found_person_list)
            {
                std::ostringstream oss;
                foreach (std::vector<person_info>::const_iterator, it, found_person_list)
                {
                    oss << it->nickname << (it->is_operator ? "*" : "") << '=' << (it->is_away ? '-' : '+') << it->username << '@' << it->host << ' ';
                }
                return ft::irc::message(RPL_USERHOST) << oss.str();
            }

            static inline ft::irc::message ison(const std::vector<std::string>& nickname_list)
            {
                std::ostringstream oss;
                foreach (std::vector<std::string>::const_iterator, it, nickname_list)
                {
                    oss << *it << ' ';
                }
                return ft::irc::message(RPL_ISON);
            }

            static inline ft::irc::message away(param_t nickname, param_t msg)
            {
                return ft::irc::message(RPL_AWAY) << nickname << msg;
            }

            static inline ft::irc::message unaway()
            {
                return ft::irc::message(RPL_UNAWAY) << "You are no longer marked as being away";
            }

            static inline ft::irc::message now_away()
            {
                return ft::irc::message(RPL_NOWAWAY) << "You have been marked as being away";
            }

            static inline ft::irc::message whois_user(param_t nickname, param_t username, param_t host, param_t info)
            {
                const char* const pass = "*";
                return ft::irc::message(RPL_WHOISUSER) << nickname << username << host << pass << info;
            }

            static inline ft::irc::message whois_server(param_t nickname, param_t server_name, param_t info)
            {
                return ft::irc::message(RPL_WHOISSERVER) << nickname << server_name << info;
            }

            static inline ft::irc::message whois_operator(param_t nickname)
            {
                return ft::irc::message(RPL_WHOISOPERATOR) << nickname << "is an IRC operator";
            }

            static inline ft::irc::message whois_idle(param_t nickname, long idle_time_second)
            {
                return ft::irc::message(RPL_WHOISIDLE) << nickname << idle_time_second << "seconds idle";
            }

            static inline ft::irc::message end_of_whois(param_t nickname)
            {
                return ft::irc::message(RPL_ENDOFWHOIS) << nickname << "End of /WHOIS list";
            }

            static inline ft::irc::message whois_channels(param_t nickname, const std::vector<channel_info>& channel_list)
            {
                std::ostringstream oss;
                foreach (std::vector<channel_info>::const_iterator, it, channel_list)
                {
                    oss << (it->is_chanop ? "@" : (it->is_chanspk ? "+" : "")) << it->channel_name << ' ';
                }
                return ft::irc::message(RPL_WHOISCHANNELS) << nickname << oss.str();
            }

            static inline ft::irc::message whowas_user(param_t nickname, param_t username, param_t host, param_t info)
            {
                const char* const pass = "*";
                return ft::irc::message(RPL_WHOWASUSER) << nickname << username << host << pass << info;
            }

            static inline ft::irc::message end_of_whowas(param_t nickname)
            {
                return ft::irc::message(RPL_ENDOFWHOWAS) << nickname << "End of WHOWAS";
            }

            static inline ft::irc::message list_start()
            {
                return ft::irc::message(RPL_LISTSTART) << "Channel"
                                                       << "Users  Name";
            }

            static inline ft::irc::message list(param_t channel_name, int visible_count, param_t channel_topic)
            {
                return ft::irc::message(RPL_LIST) << channel_name << visible_count << channel_topic;
            }

            static inline ft::irc::message list_end()
            {
                return ft::irc::message(RPL_LISTEND) << "End of /LIST";
            }

            static inline ft::irc::message channel_mode_is(param_t channel_name, param_t channel_mode, param_t member_mode_param)
            {
                return ft::irc::message(RPL_CHANNELMODEIS) << channel_name << channel_mode << member_mode_param;
            }

            static inline ft::irc::message no_topic(param_t channel_name)
            {
                return ft::irc::message(RPL_NOTOPIC) << channel_name << "No topic is set";
            }

            static inline ft::irc::message topic(param_t channel_name, param_t channel_topic)
            {
                return ft::irc::message(RPL_TOPIC) << channel_name << channel_topic;
            }

            static inline ft::irc::message inviting(param_t channel_name, param_t nickname)
            {
                return ft::irc::message(RPL_INVITING) << channel_name << nickname;
            }

            static inline ft::irc::message summoning(param_t username)
            {
                return ft::irc::message(RPL_SUMMONING) << username << "Summoning user to IRC";
            }

            static inline ft::irc::message version(param_t version, int debug_level, param_t server_name, param_t comments)
            {
                std::ostringstream oss;
                oss << version << "." << debug_level;
                return ft::irc::message(RPL_VERSION) << oss.str() << server_name << comments;
            }

            static inline ft::irc::message who_reply(param_t channel_name, param_t username, param_t host, param_t server_name, param_t nickname, bool is_away, bool is_operator, bool is_chanop, bool is_chanspk, int hop_count, param_t info)
            {
                std::ostringstream status, oss;
                status << (is_away ? "G" : "H") << (is_operator ? "*" : "") << (is_chanop ? "@" : (is_chanspk ? "+" : ""));
                oss << hop_count << " " << info;
                return ft::irc::message(RPL_WHOREPLY) << channel_name << username << host << server_name << nickname << status.str() << oss.str();
            }

            static inline ft::irc::message end_of_who(param_t name)
            {
                return ft::irc::message(RPL_ENDOFWHO) << name << "End of /WHO list";
            }

            static inline ft::irc::message name_reply(param_t channel_name, const std::vector<member_info>& user_list)
            {
                std::ostringstream oss;
                foreach (std::vector<member_info>::const_iterator, it, user_list)
                {
                    oss << it->nickname << (it->is_chanop ? "@" : (it->is_chanspk ? "+" : "")) << ' ';
                }
                return ft::irc::message(RPL_NAMREPLY) << channel_name << oss.str();
            }

            static inline ft::irc::message end_of_names(param_t channel_name)
            {
                return ft::irc::message(RPL_ENDOFNAMES) << channel_name << "End of /NAMES list";
            }

            static inline ft::irc::message links(param_t mask, param_t server_name, int hop_count, param_t info)
            {
                std::ostringstream oss;
                oss << hop_count << " " << info;
                return ft::irc::message(RPL_LINKS) << mask << server_name << oss.str();
            }

            static inline ft::irc::message end_of_links(param_t mask)
            {
                return ft::irc::message(RPL_ENDOFLINKS) << mask << "End of /LINKS list";
            }

            static inline ft::irc::message ban_list(param_t channel_name, int ban_id)
            {
                return ft::irc::message(RPL_BANLIST) << channel_name << ban_id;
            }

            static inline ft::irc::message end_of_ban_list(param_t channel_name)
            {
                return ft::irc::message(RPL_ENDOFBANLIST) << channel_name << "End of channel ban list";
            }

            static inline ft::irc::message info(param_t info)
            {
                return ft::irc::message(RPL_INFO) << info;
            }

            static inline ft::irc::message end_of_info()
            {
                return ft::irc::message(RPL_ENDOFINFO) << "End of /INFO list";
            }

            static inline ft::irc::message motd_start(param_t server_name)
            {
                return ft::irc::message(RPL_MOTDSTART) << "- " + server_name + " Message of the day - ";
            }

            static inline ft::irc::message motd(param_t text)
            {
                return ft::irc::message(RPL_MOTD) << "- " + text;
            }

            static inline ft::irc::message end_of_motd()
            {
                return ft::irc::message(RPL_ENDOFMOTD) << "End of /MOTD command";
            }

            static inline ft::irc::message now_operator()
            {
                return ft::irc::message(RPL_YOUREOPER) << "You are now an IRC operator";
            }

            static inline ft::irc::message rehashing(param_t config_filename)
            {
                return ft::irc::message(RPL_REHASHING) << config_filename << "Rehashing";
            }

            static inline ft::irc::message time(param_t server_name, param_t local_time_str)
            {
                return ft::irc::message(RPL_TIME) << server_name << local_time_str;
            }

            static inline ft::irc::message users_start()
            {
                return ft::irc::message(RPL_USERSSTART) << "UserID   Terminal  Host";
            }

            static inline ft::irc::message users(param_t utmp_name, param_t utmp_line, param_t utmp_host)
            {
                // NOTE: utmp.h
                std::ostringstream oss;
                oss << std::left << std::setw(8) << utmp_name << ' ' // "%-8s "
                    << std::left << std::setw(9) << utmp_line << ' ' // "%-9s "
                    << std::left << std::setw(8) << utmp_host;       // "%-8s"
                return ft::irc::message(RPL_USERS) << oss.str();
            }

            static inline ft::irc::message end_of_users()
            {
                return ft::irc::message(RPL_ENDOFUSERS) << "End of users";
            }

            static inline ft::irc::message no_users()
            {
                return ft::irc::message(RPL_NOUSERS) << "Nobody logged in";
            }

            static inline ft::irc::message trace_link(param_t version, int debug_level, param_t destination_server_name, param_t next_server_name)
            {
                std::ostringstream oss;
                oss << version << debug_level;
                return ft::irc::message(RPL_TRACELINK) << "Link" << oss.str() << destination_server_name << next_server_name;
            }

            static inline ft::irc::message trace_connecting(int client_class, param_t client_name)
            {
                return ft::irc::message(RPL_TRACECONNECTING) << "Try." << client_class << client_name;
            }

            static inline ft::irc::message trace_handshake(int client_class, param_t client_name)
            {
                return ft::irc::message(RPL_TRACEHANDSHAKE) << "H.S." << client_class << client_name;
            }

            static inline ft::irc::message trace_unknown(int client_class, param_t client_name)
            {
                return ft::irc::message(RPL_TRACEUNKNOWN) << "????" << client_class << client_name;
            }

            static inline ft::irc::message trace_operator(int client_class, param_t client_name)
            {
                return ft::irc::message(RPL_TRACEOPERATOR) << "Oper" << client_class << client_name;
            }

            static inline ft::irc::message trace_user(int client_class, param_t client_name)
            {
                return ft::irc::message(RPL_TRACEUSER) << "User" << client_class << client_name;
            }

            static inline ft::irc::message trace_server(int client_class, int server_count, int client_count, param_t client_name, param_t by, param_t username, param_t host)
            {
                std::ostringstream oss_s, oss_c, oss;
                oss_s << server_count << 'S';
                oss_c << client_count << 'C';
                oss << by << '!' << username << '@' << host; // ME: <by or '*'>!*@<my name>
                return ft::irc::message(RPL_TRACESERVER) << "Serv" << client_class << oss_s.str() << oss_c.str() << client_name << oss.str();
            }

            static inline ft::irc::message trace_new_type(param_t new_type, param_t client_name)
            {
                return ft::irc::message(RPL_TRACENEWTYPE) << new_type << "0" << client_name;
            }

            static inline ft::irc::message trace_log(param_t log_filename, int debug_level)
            {
                return ft::irc::message(RPL_TRACELOG) << "File" << log_filename << debug_level;
            }

            static inline ft::irc::message stats_link_info(param_t linkname, int sendq, param_t sent_messages, int sent_bytes, param_t received_messages, int received_bytes, int time_open)
            {
                return ft::irc::message(RPL_STATSLINKINFO) << linkname << sendq << sent_messages << sent_bytes << received_messages << received_bytes << time_open;
            }

            static inline ft::irc::message stats_commands(param_t command, unsigned count)
            {
                return ft::irc::message(RPL_STATSCOMMANDS) << command << count;
            }

            static inline ft::irc::message stats_c_line(param_t host, param_t pass, param_t name, int port, int conf_class)
            {
                return ft::irc::message(RPL_STATSCLINE) << 'C' << host << (!pass.empty() ? "*" : "<NULL>") << name << port << conf_class;
            }

            static inline ft::irc::message stats_n_line(param_t host, param_t pass, param_t name, int port, int conf_class)
            {
                return ft::irc::message(RPL_STATSNLINE) << 'N' << host << (!pass.empty() ? "*" : "<NULL>") << name << port << conf_class;
            }

            static inline ft::irc::message stats_i_line(param_t host, param_t pass, param_t name, int port, int conf_class)
            {
                return ft::irc::message(RPL_STATSILINE) << 'I' << host << (!pass.empty() ? "*" : "<NULL>") << name << port << conf_class;
            }

            static inline ft::irc::message stats_k_line(param_t host, param_t pass, param_t name, int port, int conf_class)
            {
                return ft::irc::message(RPL_STATSKLINE) << 'K' << host << (!pass.empty() ? "*" : "<NULL>") << name << port << conf_class;
            }

            static inline ft::irc::message stats_y_line(int class_class, int ping_freq, int conn_freq, int max_sendq)
            {
                return ft::irc::message(RPL_STATSYLINE) << 'Y' << class_class << ping_freq << conn_freq << max_sendq;
            }

            static inline ft::irc::message end_of_stats(char stats_letter)
            {
                return ft::irc::message(RPL_ENDOFSTATS) << stats_letter << "End of /STATS report";
            }

            static inline ft::irc::message stats_l_line(param_t host, param_t pass, param_t name, int max_depth)
            {
                return ft::irc::message(RPL_STATSLLINE) << 'L' << host << (!pass.empty() ? "*" : "<NULL>") << name << max_depth;
            }

            static inline ft::irc::message stats_uptime(int days, int hours, int minutes, int seconds)
            {
                std::ostringstream oss;
                oss << "Server Up " << days << " days "
                    << hours << ":"
                    << std::setfill('0') << std::setw(2) << std::dec << minutes << ":" // "%02d:"
                    << std::setfill('0') << std::setw(2) << std::dec << seconds;       // "%02d"
                return ft::irc::message(RPL_STATSUPTIME) << oss.str();
            }

            static inline ft::irc::message stats_o_line(param_t host, param_t pass, param_t name)
            {
                return ft::irc::message(RPL_STATSOLINE) << 'O' << host << (!pass.empty() ? "*" : "<NULL>") << name;
            }

            static inline ft::irc::message stats_h_line(param_t host, param_t pass, param_t name)
            {
                return ft::irc::message(RPL_STATSHLINE) << 'H' << host << (!pass.empty() ? "*" : "<NULL>") << name;
            }

            static inline ft::irc::message user_mode_is(param_t user_mode)
            {
                return ft::irc::message(RPL_UMODEIS) << user_mode;
            }

            static inline ft::irc::message luser_client(int user_count, int invisible_count, int server_count)
            {
                std::ostringstream oss;
                oss << "There are " << user_count << " users and " << invisible_count << " invisible on " << server_count << " servers";
                return ft::irc::message(RPL_LUSERCLIENT) << oss.str();
            }

            static inline ft::irc::message luser_operator(int op_count)
            {
                return ft::irc::message(RPL_LUSEROP) << op_count << "operator(s) online";
            }

            static inline ft::irc::message luser_unknown(int unknown_count)
            {
                return ft::irc::message(RPL_LUSERUNKNOWN) << unknown_count << "unknown connection(s)";
            }

            static inline ft::irc::message luser_channels(int channel_count)
            {
                return ft::irc::message(RPL_LUSERCHANNELS) << channel_count << "channels formed";
            }

            static inline ft::irc::message luser_me(int client_count, int server_count)
            {
                std::ostringstream oss;
                oss << "I have " << client_count << " clients and " << server_count << " servers";
                return ft::irc::message(RPL_LUSERME) << oss.str();
            }

            static inline ft::irc::message admin_me(param_t server_name)
            {
                return ft::irc::message(RPL_ADMINME) << server_name << ":Administrative info";
            }

            static inline ft::irc::message admin_loc1(param_t location)
            {
                return ft::irc::message(RPL_ADMINLOC1) << location;
            }

            static inline ft::irc::message admin_loc2(param_t location_detail)
            {
                return ft::irc::message(RPL_ADMINLOC2) << location_detail;
            }

            static inline ft::irc::message admin_email(param_t email_address)
            {
                return ft::irc::message(RPL_ADMINEMAIL) << email_address;
            }
        };
    }
}
