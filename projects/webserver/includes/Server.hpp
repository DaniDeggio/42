/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:55:05 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/01 05:07:42 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "utils.hpp"
#include "CgiState.hpp"
#include <vector>
#include <poll.h>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sys/stat.h>
#include <ctime>
#include <signal.h>
#include <sys/wait.h>

class Server {
	private:
		GlobalConfig _config;
		std::map<int, const ServerConfig*> _listen_fds;
		std::vector<struct pollfd> _poll_fds;
		std::map<int, const ServerConfig*> _client_servers;
		std::map<int, std::string> _client_data;
		std::map<int, Request> _requests;
		std::map<int, Response> _responses;
		std::map<int, CgiState*> _cgi_map; // keyed by stdout_pipe fd
		std::map<int, int> _cgi_client_map; // client_fd -> stdout_pipe fd
		std::map<int, int> _in_cgi_client_map; // client_fd -> stdin_pipe fd
	    std::map<int, CgiState*> _cgi_in_map; // keyed by stdin_pipe fd
		std::map<int, size_t> _send_progress;
		
		bool _running;
		int _signal_fd;
		
		static int _cgi_request_counter; // Counter for CGI requests to implement delay for even requests

		void _setup_listening_sockets();

		void _handle_new_connection(int listen_fd);
		void _handle_client_data(size_t index);
		void _handle_client_send(size_t index);		
		void _close_connection(size_t index);
		
		void controlSpace(std::string& uri);
		void merge_uri(std::string& uri);
		void _process_http_request(int fd);
		void get_req(int fd, Request& request, const ServerConfig* server_config);
		void post_req(int fd, Request& request, const ServerConfig* server_config);
		void delete_req(int fd, Request& request, const ServerConfig* server_config);
		
		void cgi_req(int fd, Request& request, const ServerConfig* server_config);
		void exec_cgi(int fd, const Request& request, const ServerConfig* server_config, CgiState* cgi_state);
		void _handle_cgi_output(size_t index);
	    void _handle_cgi_input(size_t index);
		void _check_cgi_timeouts();

		bool is_listen_fd(int fd) const;
		bool request_is_complete(const std::string& data);
		std::string get_resource_path(const Request& request, const RouteConfig* route,
									  const ServerConfig* server, Response& out_response);
	
	public:
		explicit Server(const GlobalConfig& config, int signal_fd);
		void start();
		void stop();
};

#endif