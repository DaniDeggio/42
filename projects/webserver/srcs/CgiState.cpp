/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiState.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:33:14 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/02 18:00:49 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CgiState.hpp"

CgiState::CgiState() :
	client_fd(-1),
	pid(-1),
	headers_parsed(false),
	completed(false),
	in_off(0),
	in_closed(false),
	start_time(0),
	saved_request(NULL),
	saved_server_config(NULL),
	cgi_id(-1) {
	stdin_pipe[0] = -1;
	stdin_pipe[1] = -1;
	stdout_pipe[0] = -1;
	stdout_pipe[1] = -1;
}

CgiState::~CgiState() {
    if (stdin_pipe[0] != -1) close(stdin_pipe[0]);
    if (stdin_pipe[1] != -1) close(stdin_pipe[1]);
    if (stdout_pipe[0] != -1) close(stdout_pipe[0]);
    if (stdout_pipe[1] != -1) close(stdout_pipe[1]);
    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) != 0)
				std::cout << "CGI process exited with status: " << WEXITSTATUS(status) << std::endl;
        } else if (WIFSIGNALED(status)) {
            std::cout << "CGI process killed by signal: " << WTERMSIG(status) << std::endl;
        }
    }
}