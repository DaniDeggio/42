/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiState.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:18:07 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/04 18:34:27 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGISTATE_HPP
#define CGISTATE_HPP

#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

// Forward declarations per evitare dipendenze circolari
class Request;
struct ServerConfig;

class CgiState {
	public:
		int client_fd;          // File descriptor del client
		pid_t pid;              // PID del processo CGI
		int stdin_pipe[2];      // Pipe per stdin (scrittura dal server, lettura dal CGI)
		int stdout_pipe[2];     // Pipe per stdout (lettura dal server, scrittura dal CGI)
		std::string output;     // Output accumulato dal CGI
		bool headers_parsed;    // Flag per indicare se gli header sono stati parsati
		std::string headers;    // Headers ricevuti dal CGI
		std::string body;       // Body ricevuto dal CGI
		bool completed;         // Flag per indicare se il CGI ha completato

	    std::string in_buf;   // buffer da inviare (request.body)
	    size_t      in_off;   // offset corrente nel buffer
    	bool        in_closed; // true quando abbiamo chiuso stdin_pipe[1]
		time_t      start_time; // tempo di inizio esecuzione CGI	
	    std::string tmp_filename; // nome del file temporaneo
	    
	    // Memorizza Request e ServerConfig per evitare accesso alle mappe dopo la chiusura
	    const Request* saved_request;
	    const ServerConfig* saved_server_config;
	    
	    int cgi_id; // ID univoco per questo CGI request

		CgiState();
		~CgiState();
};

#endif