/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:54:54 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/05 22:56:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int Server::_cgi_request_counter = 0;

Server::Server(const GlobalConfig& config, int signal_fd) : _config(config), _running(true), _signal_fd(signal_fd) {
    _setup_listening_sockets();
}

void Server::_setup_listening_sockets() {
    for (size_t i = 0; i < _config.servers.size(); ++i) {
        int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_fd < 0) {
            throw std::runtime_error("socket() failed");
        }

        int tmp = 1;
        if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) < 0) {
            close(listen_fd);
            throw std::runtime_error("setsockopt() failed");
        }

        if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) < 0) {
            close(listen_fd);
            throw std::runtime_error("fcntl() failed");
        }
        

        struct sockaddr_in server_addr;
        std::memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        if (_config.servers[i].host == "localhost")
            server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        else if (_config.servers[i].host == "0.0.0.0" || _config.servers[i].host.empty())
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        else 
            server_addr.sin_addr.s_addr = inet_addr(_config.servers[i].host.c_str());
        server_addr.sin_port = htons(_config.servers[i].port);

        if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            close(listen_fd);
            std::cerr << "Bind failed on " << _config.servers[i].host << ":" << _config.servers[i].port << "\n";
            throw std::runtime_error("bind() failed");
        }


        if (listen(listen_fd, 128) < 0) {
            close(listen_fd);
            throw std::runtime_error("listen() failed");
        }

        _listen_fds[listen_fd] = &_config.servers[i];

        struct pollfd listen_pfd;
        listen_pfd.fd = listen_fd;
        listen_pfd.events = POLLIN;
        listen_pfd.revents = 0;
        _poll_fds.push_back(listen_pfd);

        std::cout << "Server listening on " << _config.servers[i].host << ":" << _config.servers[i].port << std::endl;
    }
	struct pollfd signal_pfd;
	signal_pfd.fd = _signal_fd;
	signal_pfd.events = POLLIN;
	signal_pfd.revents = 0;
	_poll_fds.push_back(signal_pfd);
}

bool Server::is_listen_fd(int fd) const {
    return _listen_fds.find(fd) != _listen_fds.end();
}

void Server::start() {
    while (_running) {
        _check_cgi_timeouts();
        
        int ret = poll(&_poll_fds[0], _poll_fds.size(), 100); // 100ms timeout
        if (ret < 0) {
            std::cerr << "poll error: " << std::endl;
            continue;
        }
        if (ret == 0) continue;
        for (size_t i = 0; i < _poll_fds.size();) {
            bool should_increment = true;
            if (_poll_fds[i].fd == _signal_fd) {
                if (_poll_fds[i].revents & POLLIN) {
                    char buf;
                    ssize_t bytes_read = read(_signal_fd, &buf, 1);
                    if (bytes_read < 0) {
                        std::cerr << "Error reading from signal fd" << std::endl;
                        ++i;
                        continue;
                    }
                    if (bytes_read == 0) {
                        std::cerr << "Signal fd closed unexpectedly" << std::endl;
                        ++i;
                        continue;
                    }
                    std::cout << "Received shutdown signal" << std::endl;
                    stop();
                    return;
                }
                ++i;
                continue;
            }

            if (_cgi_in_map.count(_poll_fds[i].fd)) {
				if (_poll_fds[i].revents & (POLLOUT | POLLHUP | POLLERR)) {
                    _handle_cgi_input(i);
                    continue;
                }
                ++i;
                continue;
            }
			
            if (_cgi_map.count(_poll_fds[i].fd)) {
				if (_poll_fds[i].revents & (POLLIN | POLLHUP | POLLERR)) {
					_handle_cgi_output(i);
                    continue;
                }
                ++i;
                continue;
            }

			if (_poll_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				_close_connection(i);
				should_increment = false;
				continue;
			}
			
            if (_poll_fds[i].revents & POLLIN) {
                if (is_listen_fd(_poll_fds[i].fd)) {
                    _handle_new_connection(_poll_fds[i].fd);
                } else {
                    _handle_client_data(i);
                }
            }

            if (_poll_fds[i].revents & POLLOUT) {
                _handle_client_send(i);
            }

            if (should_increment) {
                ++i;
            }
        }
    }
}

void Server::_handle_new_connection(int listen_fd) {
    int client_fd = accept(listen_fd, NULL, NULL);
    if (client_fd < 0) {
        std::cerr << "accept error" << std::endl;
        return;
    }

    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "fcntl client error" << std::endl;
        close(client_fd);
        return;
    }

    std::map<int, const ServerConfig*>::iterator it = _listen_fds.find(listen_fd);
    if (it != _listen_fds.end()) {
        _client_servers[client_fd] = it->second;
    } else {
        std::cerr << "No ServerConfig found for listen_fd: " << listen_fd << std::endl;
        close(client_fd);
        return;
    }

    struct pollfd new_pfd;
    new_pfd.fd = client_fd;
    new_pfd.events = POLLIN;
    new_pfd.revents = 0;
    _poll_fds.push_back(new_pfd);

    _client_data[client_fd] = "";
    // std::cout << std::endl << "Accepted new connection: " << client_fd << std::endl; //DEBUG
}

void Server::_handle_client_data(size_t index) {
    char buffer[8192];
    ssize_t bytes = recv(_poll_fds[index].fd, buffer, sizeof(buffer), 0);

    // std::cout << "Received data from fd: " << _poll_fds[index].fd << ", bytes: " << bytes << std::endl; //DEBUG
    if (bytes > 0) {
        _client_data[_poll_fds[index].fd] += std::string(buffer, bytes);
        if (request_is_complete(_client_data[_poll_fds[index].fd])) {
            // std::cout << "Request complete for fd: " << _poll_fds[index].fd << std::endl; //DEBUG
            // std::cout << "Request data: " << _client_data[_poll_fds[index].fd] << std::endl; //DEBUG
            try {
                Request request = Request(_client_data[_poll_fds[index].fd]);
                _requests[_poll_fds[index].fd] = request;
                _process_http_request(_poll_fds[index].fd);
                // std::cout << "Processed request for fd: " << _poll_fds[index].fd << std::endl; //DEBUG
            }
            catch (std::runtime_error& e) {
                std::cout << "Error processing request for fd: " << _poll_fds[index].fd << " - " << e.what() << std::endl;
                int req_code = std::atoi(e.what());
                std::cout << "Generating error response code: " << req_code << std::endl;
                _responses[_poll_fds[index].fd] = error_response(req_code, _client_servers[_poll_fds[index].fd]);
            }
            if (_cgi_client_map.count(_poll_fds[index].fd) == 0 && _in_cgi_client_map.count(_poll_fds[index].fd) == 0) {
                // std::cout << "Switching fd to POLLOUT: " << _poll_fds[index].fd << std::endl; //DEBUG
                _poll_fds[index].events = POLLOUT;
            }
			// std::cout << "End of request handling for fd: " << _poll_fds[index].fd << std::endl; //DEBUG
        }
    } else {
        _close_connection(index);
    }
}

void Server::_handle_client_send(size_t index) {
    int fd = _poll_fds[index].fd;

    Response& respp = this->_responses[fd];

    if (respp.get_code() == -1) {
        std::cout << "NO RESPONSE GENERATED FOR FD: " << fd << std::endl;
        respp = error_response(500, _client_servers[fd]);
    }
    
    std::string resp = respp.to_string();

    // std::cout << "Sending response to fd: " << fd << ", total bytes: " << resp.size() << std::endl; //DEBUG
	// std::cout << "Response:" << std::endl << resp << std::endl << "END OF RESPONSE" << std::endl; //DEBUG
	
	// std::cout << "Response content:\n" << resp << std::endl; //DEBUG
    if (_send_progress.count(fd) == 0)
        _send_progress[fd] = 0;  

    const char* data = resp.c_str() + _send_progress[fd];
    size_t remaining = resp.size() - _send_progress[fd];

    ssize_t sent = send(fd, data, remaining, 0);
	if (sent < 0) {
        _close_connection(index);
        return;
    }

    _send_progress[fd] += sent;

    if (_send_progress[fd] >= resp.size()) {
        // std::cout << "Response fully sent to fd " << fd << std::endl; //DEBUG
        _close_connection(index);
    }
}

void Server::_close_connection(size_t index) {
    // std::cout << std::endl << "Closing connection for fd: " << _poll_fds[index].fd << std::endl; //DEBUG
    int fd = _poll_fds[index].fd;
    
    std::map<int,int>::iterator itm = _cgi_client_map.find(fd);
    if (itm != _cgi_client_map.end()) {
        int pipe_fd = itm->second;
        std::map<int,CgiState*>::iterator itc = _cgi_map.find(pipe_fd);
        if (itc != _cgi_map.end()) {
            if (itc->second->pid > 0) {
                kill(itc->second->pid, SIGTERM);
                int status;
                waitpid(itc->second->pid, &status, WNOHANG);
            }
            
            close(pipe_fd);
            itc->second->stdout_pipe[0] = -1;
            --_cgi_request_counter;
            
            if (!itc->second->tmp_filename.empty()) {
                unlink(itc->second->tmp_filename.c_str());
            }
            
            delete itc->second;
            _cgi_map.erase(itc);
            
            for (size_t j = 0; j < _poll_fds.size(); ++j) {
                if (_poll_fds[j].fd == pipe_fd) {
                    _poll_fds.erase(_poll_fds.begin() + j);
                    break;
                }
            }
        }
        _cgi_client_map.erase(itm);
    }
    
    std::map<int,int>::iterator itm_in = _in_cgi_client_map.find(fd);
    if (itm_in != _in_cgi_client_map.end()) {
        int pipe_fd_in = itm_in->second;
        std::map<int,CgiState*>::iterator itc_in = _cgi_in_map.find(pipe_fd_in);
        if (itc_in != _cgi_in_map.end()) {
            close(pipe_fd_in);
            if (!itc_in->second->tmp_filename.empty()) {
                unlink(itc_in->second->tmp_filename.c_str());
            }
            
            bool shared_with_output = false;
            for (std::map<int, CgiState*>::iterator it = _cgi_map.begin(); it != _cgi_map.end(); ++it) {
                if (it->second == itc_in->second) {
                    shared_with_output = true;
                    break;
                }
            }
            
            if (!shared_with_output) {
                delete itc_in->second;
            }
            
            _cgi_in_map.erase(itc_in);
            
            for (size_t j = 0; j < _poll_fds.size(); ++j) {
                if (_poll_fds[j].fd == pipe_fd_in) {
                    _poll_fds.erase(_poll_fds.begin() + j);
                    break;
                }
            }
        }
        _in_cgi_client_map.erase(itm_in);
    }
    
    close(fd);
    _client_data.erase(fd);
    _requests.erase(fd);
    _responses.erase(fd);
    _client_servers.erase(fd);
    _send_progress.erase(fd);
    _poll_fds.erase(_poll_fds.begin() + index);
    
    // std::cout << "Connection closed for fd: " << fd << std::endl; //DEBUG
}

bool Server::request_is_complete(const std::string& data) {
    size_t headers_end = data.find("\r\n\r\n");
    if (headers_end == std::string::npos)
        return false;

    size_t body_start = headers_end + 4;
    std::string headers_str = data.substr(0, headers_end);

    std::string search = "content-length:";
    size_t cl_val_pos = std::string::npos;

    size_t line_start = 0;
    while (line_start < headers_str.size()) {
        size_t line_end = headers_str.find("\r\n", line_start);
        if (line_end == std::string::npos)
            line_end = headers_str.size();
        std::string line = headers_str.substr(line_start, line_end - line_start);
        std::string lcline = to_lower(line);
        if (lcline.find(search) == 0) {
            cl_val_pos = line.find(':');
            if (cl_val_pos != std::string::npos) {
                size_t val_start = cl_val_pos + 1;
                while (val_start < line.size() && line[val_start] == ' ') val_start++;
                std::string len_str = line.substr(val_start);
                int content_length = std::atoi(len_str.c_str());
                if (data.size() >= body_start + (size_t)content_length)
                    return true;
                else
                    return false;
            }
        }
        line_start = line_end + 2;
    }

    if (to_lower(headers_str).find("transfer-encoding: chunked") != std::string::npos) {
        size_t pos = data.find("0\r\n\r\n", body_start);
        if (pos != std::string::npos)
            return true;
        else
            return false;
    }

    return true;
}

void Server::controlSpace(std::string& uri) {
	size_t pos = 0;
	while ((pos = uri.find("%20", pos)) != std::string::npos) {
		uri.replace(pos, 3, " ");
		pos += 1;
	}
}

void Server::merge_uri(std::string& uri) {
	size_t pos = 0;
	while ((pos = uri.find("//", pos)) != std::string::npos) {
		uri.replace(pos, 2, "/");
	}
}
	
void Server::_process_http_request(int fd) {
	Request& request = _requests[fd];
    const ServerConfig* server_config = _client_servers[fd];

	controlSpace(request.uri);
	merge_uri(request.uri);

	if (has_cgi(request, server_config) != "") {
		// std::cout << "Request has CGI for URI: " << request.uri << std::endl; //DEBUG 
		cgi_req(fd, request, server_config);
	} // CHECK IF IS NEEDED THE ELSE
	else if (request.method == "GET") {
		// std::cout << "Handling GET request for URI: " << request.uri << std::endl; //DEBUG
		get_req(fd, request, server_config);
		// Logica per gestire la richiesta GET
	} else if (request.method == "POST") {
		// std::cout << "Handling POST request for URI: " << request.uri << std::endl; //DEBUG
		post_req(fd, request, server_config);
		// Logica per gestire la richiesta POST
	} else if (request.method == "DELETE") {
		// std::cout << "Handling DELETE request for URI: " << request.uri << std::endl; //DEBUG
		delete_req(fd, request, server_config);
		// Logica per gestire la richiesta DELETE
	} else {
		_responses[fd] = error_response(405, server_config);
		std::cout << "Unsupported HTTP method: " << request.method << std::endl;
	}	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					METHOD HANDLING							////////////////////////////////////////////////////////////////
//					METHOD HANDLING							////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//					GET REQUEST HANDLING					//
//					GET REQUEST HANDLING					//
//////////////////////////////////////////////////////////////

void Server::get_req(int fd, Request& request, const ServerConfig* server_config) {
	const RouteConfig* route = server_config->get_route(request.uri);
	std::string path;
	
	if (route == NULL) {
		std::cerr << "No route found for URI: " << request.uri << std::endl;
		//replacing stock status whit error_response()
		_responses[fd] = error_response(404, server_config);
		return;
	}
	if (std::find(route->methods.begin(), route->methods.end(), "GET") == route->methods.end()) {
		std::cerr << "GET method not allowed for URI: " << request.uri << std::endl;
		_responses[fd] = error_response(405, server_config);
		return;
	}
	path = get_resource_path(request, route, server_config, _responses[fd]);
	if (_responses[fd].get_code() != -1){
		std::cout << "Error " << _responses[fd].get_code() << " GET for fd:" << fd << std::endl;
		return;
	}
	struct stat st;
	if (stat(path.c_str(), &st) != 0) {
		std::cerr << "Failed to stat path: " << path << std::endl;
		_responses[fd] = error_response(500, server_config);
		return;
	}

	if (S_ISDIR(st.st_mode)) {
		std::string index_path = path + "/" + route->default_file;
        if (!route->default_file.empty() && access(index_path.c_str(), R_OK) == 0) {
            _responses[fd] = serve_file(index_path);
        }
		else if (route->directory_listing) {
            _responses[fd] = serve_autoindex(path, request.uri);
		} else {
			std::cout << "Error 404 GET for fd:" << fd << std::endl;
			_responses[fd] = error_response(404, server_config);
		}
	}
	else {
		_responses[fd] = serve_file(path);
	}
	
}


//////////////////////////////////////////////////////////////
//					POST REQUEST HANDLING					//
//					POST REQUEST HANDLING					//
//////////////////////////////////////////////////////////////

void Server::post_req(int fd, Request& request, const ServerConfig* server_config) {
    const RouteConfig* route = server_config->get_route(request.uri);
    
    if (route == NULL) {
        std::cerr << "No route found for URI: " << request.uri << std::endl;
        _responses[fd] = error_response(404, server_config);
        return;
    }
    if (std::find(route->methods.begin(), route->methods.end(), "POST") == route->methods.end()) {
        std::cerr << "POST method not allowed for URI: " << request.uri << std::endl;
        _responses[fd] = error_response(405, server_config);
        return;
    }
    if (request.body.size() > route->client_max_body_size) {
        std::cerr << "Request body too large for URI: " << request.uri << std::endl;
        _responses[fd] = error_response(413, server_config);
        return;
    }

    if (route->upload_path.empty()) {
        std::cerr << "No upload path configured for URI: " << request.uri << std::endl;
        _responses[fd] = error_response(403, server_config);
        return;
    }

	std::string absolute_root = canon_path(route->root);
    if (absolute_root.empty()) {
        _responses[fd] = error_response(500, server_config);
        return;
    }
	
    std::string upload_dir = canon_path(route->upload_path);
    
    if (!is_subpath(upload_dir, absolute_root)) {
        std::cout << "Upload path is outside of root: " << upload_dir << std::endl;
		std::cout << "Root path: " << absolute_root << std::endl;
        _responses[fd] = error_response(403, server_config);
        return;
    }

    struct stat st;
    if (stat(upload_dir.c_str(), &st) != 0) {
        if (mkdir(upload_dir.c_str(), 0755) != 0) {
            std::cerr << "Failed to create upload directory: " << upload_dir << std::endl;
            _responses[fd] = error_response(500, server_config);
            return;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        std::cerr << "Upload path is not a directory: " << upload_dir << std::endl;
        _responses[fd] = error_response(500, server_config);
        return;
    }

    std::string filename;
    const std::string* fileContent = &request.body;

    if (request.isMultipart()) {
        const Request::MultipartPart* part = request.getPartByName("file");
        if (part == NULL)
            part = request.getFirstFilePart();
        if (part == NULL) {
            std::cerr << "No file part found in multipart request for URI: " << request.uri << std::endl;
            _responses[fd] = error_response(400, server_config);
            return;
        }
        fileContent = &part->data;
        if (!part->filename.empty())
            filename = part->filename;

        if (filename.empty()) {
            std::string provided = request.getFormField("filename");
            if (!provided.empty())
                filename = provided;
        }
    } else {
        std::string content_disposition = request.getHeader("Content-Disposition");
        if (!content_disposition.empty()) {
            size_t filename_pos = content_disposition.find("filename=");
            if (filename_pos != std::string::npos) {
                filename = content_disposition.substr(filename_pos + 9);
                if (!filename.empty() && filename[0] == '"' && filename[filename.size()-1] == '"') {
                    filename = filename.substr(1, filename.size()-2);
                }
            }
        }
    }

    if (filename.empty()) {
        filename = "upload_" + to_string(time(NULL)) + "_" + to_string(fd) + ".dat";
    }

    size_t slashPos = filename.find_last_of("/\\");
    if (slashPos != std::string::npos) {
        filename = filename.substr(slashPos + 1);
    }
    
    std::string upload_file = upload_dir + "/" + filename;
    std::string normalized_upload_file = normalize_path(upload_file);
    
    if (!is_subpath(normalized_upload_file, upload_dir)) {
		std::cout << "Upload file path is outside of upload directory: " << normalized_upload_file << std::endl;
		std::cout << "Upload directory: " << upload_dir << std::endl;
		_responses[fd] = error_response(403, server_config);
        return;
    }

    std::ofstream ofs(normalized_upload_file.c_str(), std::ios::out | std::ios::binary);
    if (ofs) {
        ofs.write(fileContent->c_str(), fileContent->size());
        if (ofs.fail() || ofs.bad()) {
            std::cerr << "Failed to write to upload file: " << normalized_upload_file << std::endl;
            ofs.close();
            _responses[fd] = error_response(500, server_config);
            return;
        }
        ofs.close();
        _responses[fd].stock_status(201);
        _responses[fd].set_body("File uploaded successfully to: " + filename);
    } else {
        std::cerr << "Failed to open upload file: " << normalized_upload_file << std::endl;
        _responses[fd] = error_response(500, server_config);
   }
}


//////////////////////////////////////////////////////////////
//					DELETE REQUEST HANDLING					//
//					DELETE REQUEST HANDLING					//
//////////////////////////////////////////////////////////////

void Server::delete_req(int fd, Request& request, const ServerConfig* server_config) {
	const RouteConfig* route = server_config->get_route(request.uri);
	std::string path;
	
	if (route == NULL) {
		std::cerr << "No route found for URI: " << request.uri << std::endl;
		_responses[fd] = error_response(404, server_config);
		return;
	}
	if (std::find(route->methods.begin(), route->methods.end(), "DELETE") == route->methods.end()) {
		std::cerr << "DELETE method not allowed for URI: " << request.uri << std::endl;
		_responses[fd] = error_response(405, server_config);
		return;
	}
	
	path = get_resource_path(request, route, server_config, _responses[fd]);
	if (_responses[fd].get_code() != -1){
		return;
	}

	if (unlink(path.c_str()) == 0) {
		_responses[fd].stock_status(200); // OK
		_responses[fd].set_body("File deleted successfully.");
	} else {
		if (access(path.c_str(), W_OK) != 0) {
			std::cerr << "Permission denied to delete file: " << path << std::endl;
			_responses[fd] = error_response(403, server_config);
		} else {
			std::cerr << "Failed to delete file: " << path << std::endl;
			_responses[fd] = error_response(500, server_config);
		}
	}
}


//////////////////////////////////////////////////////////////
//					RESOURCE PATH HANDLING					//
//					RESOURCE PATH HANDLING					//
//////////////////////////////////////////////////////////////

std::string Server::get_resource_path(const Request& request,
                                      const RouteConfig* route,
                                      const ServerConfig* server,
                                      Response& out_response)
{
    if (!route->redirect.empty()) {
        out_response = error_response(301, server);
		out_response.add_header("Location", route->redirect);
        return "";
    }

    std::string absolute_root = canon_path(route->root);
    if (absolute_root.empty()) {
        out_response = error_response(500, server);
        return "";
    }

    std::string rel_uri = request.uri.substr(route->path.length());
    std::string full_path = absolute_root;

    if (full_path[full_path.size() - 1] != '/') {
        full_path += '/';
    }
    
    full_path += rel_uri;
    full_path = canon_path(full_path);

    // std::cout << "Full path: " << full_path << std::endl; //DEBUG
    // std::cout << "Absolute root: " << absolute_root << std::endl; //DEBUG

    if (!is_subpath(full_path, absolute_root)) {
        std::cout << "Directory traversal attempt detected: " << full_path << std::endl;
        out_response = error_response(403, server);
        return "";
    }

    struct stat st;
    if (stat(full_path.c_str(), &st) < 0) {
        std::cout << "File not found: " << full_path << std::endl;
        out_response = error_response(404, server);
        return "";
    }

    if (S_ISDIR(st.st_mode)) {

        std::string index_path = full_path + "/" + route->default_file;
        if (!route->default_file.empty() && access(index_path.c_str(), R_OK) == 0) {
            return canon_path(index_path);
        }

        return full_path;
    }

    if (S_ISREG(st.st_mode) && access(full_path.c_str(), R_OK) == 0) {
        return full_path;
    }

    out_response = error_response(404, server);
	(void)server;
    return "";
}

//////////////////////////////////////////////////////////////
//					CGI REQUEST HANDLING					//
//					CGI REQUEST HANDLING					//
//////////////////////////////////////////////////////////////

void Server::cgi_req(int fd, Request& request, const ServerConfig* server_config){
	const RouteConfig* route = server_config->get_route(request.uri);
	
	// std::cout << std::endl << "Starting CGI request handling for fd: " << fd << ", URI: " << request.uri << std::endl; //DEBUG
	
	if (route == NULL) {
		std::cout << "No route found for URI: " << request.uri << std::endl;
		_responses[fd] = error_response(404, server_config);
		return;
	}

	// std::cout << "Request body size: " << request.body.size() << ", Max allowed: " << route->client_max_body_size << std::endl; //DEBUG
	if (request.body.size() > route->client_max_body_size) {
		std::cerr << "Request body too large for CGI on URI: " << request.uri << std::endl;
		_responses[fd] = error_response(413, server_config);
		return;
	}
	
	if (std::find(route->cgi_methods.begin(), route->cgi_methods.end(), request.method) == route->cgi_methods.end()) {
		std::cout << "CGI method not allowed for URI: " << request.uri << std::endl;
		std::cout << "Method: " << request.method << std::endl;
		_responses[fd] = error_response(405, server_config);
		return;
	}
	
	++_cgi_request_counter;
	int current_cgi_id = _cgi_request_counter;
	// std::cout << "CGI request #" << current_cgi_id << " for fd: " << fd << std::endl; //DEBUG

	std::string absolute_root = canon_path(route->root);
	if (absolute_root.empty()) {
		--_cgi_request_counter;
		_responses[fd] = error_response(500, server_config);
		return;
	}
	
	std::string rel_uri = request.uri.substr(route->path.length());
	std::string script_path = absolute_root + rel_uri;
	
	CgiState* cgi_state = new CgiState();
	cgi_state->cgi_id = current_cgi_id;
	cgi_state->client_fd = fd;

	struct stat st;
	if (stat("./tmp", &st) != 0) {
		if (mkdir("./tmp", 0755) != 0) {
			std::cerr << "Failed to create ./tmp directory" << std::endl;
			--_cgi_request_counter;
			delete cgi_state;
			_responses[fd] = error_response(500, server_config);
			return;
		}
	}

	int file_fd = -1;
	std::string tmp_filename;
	
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	long unique_code = ts.tv_sec * 1000000000LL + ts.tv_nsec + fd * 1000000 + getpid();

	tmp_filename = "./tmp/cgi_in_" + to_string(unique_code);
	file_fd = open(tmp_filename.c_str(), O_CREAT | O_EXCL | O_WRONLY | O_NONBLOCK, 0644);
	
	if (file_fd == -1) {
		std::cerr << "Failed to create temp file: " << tmp_filename << " - " << strerror(errno) << std::endl;
		--_cgi_request_counter;
		delete cgi_state;
		_responses[fd] = error_response(500, server_config);
		return;
	}

	cgi_state->in_buf = request.body;
	cgi_state->in_off = 0;
	cgi_state->in_closed = false;
	cgi_state->tmp_filename = tmp_filename;
	cgi_state->saved_request = &request;
	cgi_state->saved_server_config = server_config;
	
	struct pollfd tmp_pfd;
	tmp_pfd.fd = file_fd;
	tmp_pfd.events = POLLOUT;
	tmp_pfd.revents = 0;
	_poll_fds.push_back(tmp_pfd);
	
	_cgi_in_map[file_fd] = cgi_state;
	_in_cgi_client_map[fd] = file_fd;
	
}

void Server::exec_cgi(int fd, const Request& request, const ServerConfig* server_config, CgiState* cgi_state) {
	const RouteConfig* route = server_config->get_route(request.uri);
	
	CgiState* existing_cgi_state = cgi_state;
	
	std::string tmp_filename = existing_cgi_state->tmp_filename;
	if (tmp_filename.empty()) {
		std::cerr << "No temporary filename found in CgiState for fd: " << fd << std::endl;
		_responses[fd] = error_response(500, server_config);
		return;
	}
	
	std::string absolute_root = canon_path(route->root);	
	std::string rel_uri = request.uri.substr(route->path.length());
	std::string script_path = absolute_root + rel_uri;
	std::string query_string = "";
	std::string path_info = "/";

	if (request.queryString != "") {
		query_string = request.queryString;
	}

	// std::cout << std::endl << "Executing CGI for fd: " << fd << std::endl; //DEBUG
	// std::cout << "CGI Script path: " << script_path << std::endl; //DEBUG
	// std::cout << "CGI Query string: " << query_string << std::endl; //DEBUG

	std::map<std::string, std::string> env;
	env["REQUEST_METHOD"] = request.method;
	// env["SCRIPT_NAME"] = rel_uri;
	// env["QUERY_STRING"] = query_string;
	env["PATH_INFO"] = path_info;
	// env["PATH_TRANSLATED"] = script_path;
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	// env["GATEWAY_INTERFACE"] = "CGI/1.1";
	// env["REDIRECT_STATUS"] = "200";
	// env["SERVER_SOFTWARE"] = "Webserv/1.0";
	// env["SERVER_NAME"] = server_config->host;
	// env["SERVER_PORT"] = to_string(server_config->port);

	for (std::map<std::string, std::string>::const_iterator it = request.headers.begin(); it != request.headers.end(); ++it) {
		std::string env_name = "HTTP_" + to_upper(it->first);
		std::replace(env_name.begin(), env_name.end(), '-', '_');
		env[env_name] = it->second;
	}

	if (!request.body.empty()) {
		env["CONTENT_LENGTH"] = to_string(request.body.size());
	}
    if (!request.body.empty()) {
        env["CONTENT_LENGTH"] = to_string(request.body.size());
    }
    
    std::map<std::string, std::string>::const_iterator content_type_it = request.headers.end();
    for (std::map<std::string, std::string>::const_iterator it = request.headers.begin(); it != request.headers.end(); ++it) {
        if (to_lower(it->first) == "content-type") {
            content_type_it = it;
            break;
        }
    }
    
    if (content_type_it != request.headers.end()) {
        env["CONTENT_TYPE"] = content_type_it->second;
    }

	int stdout_pipe[2];
	if (pipe(stdout_pipe) != 0) {
		_responses[fd] = error_response(500, server_config);
		return;
	}

	fcntl(stdout_pipe[0], F_SETFL, O_NONBLOCK);

	existing_cgi_state->start_time = time(NULL);

	// std::cout << "Forking process for CGI execution..." << std::endl; //DEBUG

	pid_t pid = fork();
	if (pid == 0) {
		close(stdout_pipe[0]);

		fflush(NULL);
		std::cout.flush();
		std::cerr.flush();
		std::clog.flush();

		int tmp_input_fd = open(tmp_filename.c_str(), O_RDONLY);
		if (tmp_input_fd < 0) {
			perror("Failed to open temporary file for CGI input");
			_exit(1);
		}
		dup2(tmp_input_fd, STDIN_FILENO);
		dup2(stdout_pipe[1], STDOUT_FILENO);

		close(tmp_input_fd);
		close(stdout_pipe[1]);
		
		for (int i = 3; i < 1024; ++i) {
			if (i != STDIN_FILENO && i != STDOUT_FILENO && i != STDERR_FILENO) {
				close(i);
			}
		}
		
		unlink(tmp_filename.c_str());

		for (std::map<std::string, std::string>::const_iterator it = env.begin(); it != env.end(); ++it) {
			setenv(it->first.c_str(), it->second.c_str(), 1);
		}

		std::string cgi_ext = has_cgi(request, server_config);
		std::string cgi_patth = "";

		for (int i = 0; route->cgi_extension[i] != ""; i++) {
			if (cgi_ext == route->cgi_extension[i]) {
				cgi_patth = route->cgi_path[i];
				break;
			}
		}

		char* args[3];
		args[0] = const_cast<char*>(cgi_patth.c_str());
		args[1] = const_cast<char*>(script_path.c_str());
		args[2] = NULL;

		execve(cgi_patth.c_str(), args, environ);

		perror("execve failed");
		_exit(1);
	} else if (pid > 0) {
        close(stdout_pipe[1]);

		existing_cgi_state->pid = pid;
		existing_cgi_state->stdout_pipe[0] = stdout_pipe[0];
        existing_cgi_state->stdout_pipe[1] = -1;
		existing_cgi_state->stdin_pipe[0] = -1;
		existing_cgi_state->stdin_pipe[1] = -1;

		_cgi_map[stdout_pipe[0]] = existing_cgi_state;
		_cgi_client_map[fd] = stdout_pipe[0];

		struct pollfd pfd_out;
		pfd_out.fd = stdout_pipe[0];
		pfd_out.events = POLLIN;
		pfd_out.revents = 0;
		_poll_fds.push_back(pfd_out);


		// std::cout << "CGI process forked with PID: " << pid << " for client fd: " << fd << std::endl; //DEBUG
		// std::cout << "CGI reading from file: " << tmp_filename << ", stdout pipe: " << stdout_pipe[0] << std::endl; //DEBUG
	} else {
		close(stdout_pipe[0]); close(stdout_pipe[1]);
		_responses[fd] = error_response(500, server_config);
		delete existing_cgi_state;
		
		for (size_t j = 0; j < _poll_fds.size(); ++j) {
			if (_poll_fds[j].fd == fd) {
				_poll_fds[j].events = POLLOUT;
				_poll_fds[j].revents = 0;
				break;
			}
		}
	}
}

void Server::_handle_cgi_output(size_t index) {
    int pipe_fd = _poll_fds[index].fd;
    std::map<int, CgiState*>::iterator it = _cgi_map.find(pipe_fd);
    if (it == _cgi_map.end()) {
		std::cout << "Unexpected CGI output fd: " << pipe_fd << ", removing from poll." << std::endl;
        _poll_fds.erase(_poll_fds.begin() + index);
        return;
    }
    CgiState* cgi_state = it->second;

    if (_poll_fds[index].revents & POLLERR) {
		std::cout << "Error on CGI output fd: " << pipe_fd << ", sending 500 to client fd: " << cgi_state->client_fd << std::endl;
        int client_fd = cgi_state->client_fd;
        close(pipe_fd);
        cgi_state->stdout_pipe[0] = -1;
        _poll_fds.erase(_poll_fds.begin() + index);
        _responses[client_fd] = error_response(500, _client_servers[client_fd]);
        _cgi_map.erase(it);
        _cgi_client_map.erase(client_fd);
        
        --_cgi_request_counter;
        std::cout << "CGI request #" << cgi_state->cgi_id << " failed with error. Active CGI requests: " << _cgi_request_counter << std::endl;
        
        delete cgi_state;
        return;
    }

    char buffer[4096];
    ssize_t n = read(pipe_fd, buffer, sizeof(buffer));
    if (n > 0) {
        cgi_state->output.append(buffer, n);
		// std::cout << "Accumulated CGI output size: " << cgi_state->output.size() << " bytes." << std::endl; //DEBUG
        return;
    }

    if (n == 0 || (_poll_fds[index].revents & POLLHUP)) {
		// std::cout << "CGI output fd: " << pipe_fd << " closed (EOF or POLLHUP)." << std::endl; //DEBUG
		// std::cout << "Final CGI output: " << std::endl << cgi_state->output << std::endl << "End of CGI output." << std::endl; //DEBUG
        int client_fd = cgi_state->client_fd;

        close(pipe_fd);
        cgi_state->stdout_pipe[0] = -1;
        _poll_fds.erase(_poll_fds.begin() + index);

		if (!validate_cgi(cgi_state->output)) {
			std::cout << "Invalid CGI output for client fd: " << client_fd << ", sending 500." << std::endl;
			_responses[client_fd] = error_response(500, _client_servers[client_fd]);
		} else {
			_responses[client_fd].parse_cgi_response(
				cgi_state->output, _client_servers[client_fd]
			);
		}

        for (size_t j = 0; j < _poll_fds.size(); ++j) {
            if (_poll_fds[j].fd == client_fd) {
                _poll_fds[j].events = POLLOUT;
                _poll_fds[j].revents = 0;
                break;
            }
        }

        _cgi_map.erase(it);
        _cgi_client_map.erase(client_fd);

        --_cgi_request_counter;

        delete cgi_state;
        return;
    }

    return;
}

void Server::_handle_cgi_input(size_t index) {
	int pipe_fd = _poll_fds[index].fd;
	std::map<int, CgiState*>::iterator it = _cgi_in_map.find(pipe_fd);
	if (it == _cgi_in_map.end()) {
		std::cout << "Unexpected CGI input fd: " << pipe_fd << ", removing from poll." << std::endl;
		_poll_fds.erase(_poll_fds.begin() + index);
		return;
	}
	CgiState* cs = it->second;

	if (_poll_fds[index].revents & (POLLERR | POLLHUP)) {
		std::cout << "Error or hangup on CGI input fd: " << pipe_fd << ", closing input." << std::endl;
		close(pipe_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		_cgi_in_map.erase(it);
		_in_cgi_client_map.erase(cs->client_fd);
		cs->in_closed = true;
		return;
	}

	if (cs->in_closed) {
		// std::cout << "CGI input already closed for fd: " << pipe_fd << ", removing from poll." << std::endl; //DEBUG
		close(pipe_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		_cgi_in_map.erase(it);
		_in_cgi_client_map.erase(cs->client_fd);
		return;
	}

	if (cs->in_off >= cs->in_buf.size()) {
		// std::cout << "File writing completed for fd: " << pipe_fd << ", starting CGI execution." << std::endl; //DEBUG
		close(pipe_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		_cgi_in_map.erase(it);
		_in_cgi_client_map.erase(cs->client_fd);
		cs->in_closed = true;
		
		int client_fd = cs->client_fd;
		if (cs->saved_request == NULL || cs->saved_server_config == NULL) {
			std::cerr << "Saved request or server config is NULL for fd: " << client_fd << std::endl;
			delete cs;
			return;
		}
		exec_cgi(client_fd, *cs->saved_request, cs->saved_server_config, cs);
		return;
	}

	// std::cout << "Sending data to CGI input fd: " << pipe_fd << ", offset: " << cs->in_off << ", total size: " << cs->in_buf.size() << std::endl; //DEBUG
	const size_t kChunk = 4096;
	size_t remaining = cs->in_buf.size() - cs->in_off;
	size_t to_write = remaining < kChunk ? remaining : kChunk;

	// std::cout << "Attempting to write " << to_write << " bytes to CGI input." << std::endl; //DEBUG
	// std::cout << "Data buff: " << cs->in_buf << std::endl;//DEBUG
	// std::cout << "Data buff size: " << cs->in_buf.size() << std::endl; //DEBUG
	// std::cout << "Data chunk: " << cs->in_buf.substr(cs->in_off, to_write) << std::endl; //DEBUG
	ssize_t n = write(pipe_fd, cs->in_buf.data() + cs->in_off, to_write); 
	// std::cout << "Wrote " << n << " bytes to CGI input." << std::endl; //DEBUG
	if (n > 0) {
		cs->in_off += static_cast<size_t>(n);
		if (cs->in_off >= cs->in_buf.size()) {
			// std::cout << std::endl << "File writing completed for fd: " << pipe_fd << ", starting CGI execution." << std::endl; //DEBUG
			cs->in_closed = true;
			
			int client_fd = cs->client_fd;
			if (cs->saved_request == NULL || cs->saved_server_config == NULL) {
				std::cerr << "Saved request or server config is NULL for fd: " << client_fd << std::endl;
				delete cs;
				return;
			}
			exec_cgi(client_fd, *cs->saved_request, cs->saved_server_config, cs);
		}
		return;
	} else if (n < 0) {
		std::cout << std::endl << "Error writing to CGI input fd: " << pipe_fd << " - " << strerror(errno) << std::endl;
		std::cout << "Closing CGI input and sending 500 to client fd: " << cs->client_fd << std::endl;
		std::cout << "Data alredy sent: " << cs->in_off << " bytes out of " << cs->in_buf.size() << " bytes." << std::endl;
		close(pipe_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		_cgi_in_map.erase(it);
		_in_cgi_client_map.erase(cs->client_fd);
		cs->in_closed = true;
		
		int client_fd = cs->client_fd;
		_responses[client_fd] = error_response(500, _client_servers[client_fd]);
		for (size_t j = 0; j < _poll_fds.size(); ++j) {
			if (_poll_fds[j].fd == client_fd) {
				_poll_fds[j].events = POLLOUT;
				_poll_fds[j].revents = 0;
				break;
			}
		}
		
		--_cgi_request_counter;
		std::cout << "CGI request #" << cs->cgi_id << " failed on input error. Active CGI requests: " << _cgi_request_counter << std::endl;
		
		delete cs;
		return;
	}
	else {
		std::cout << "Write returned 0 on CGI input fd: " << pipe_fd << ", treating as error." << std::endl;
		return;
	}
}

void Server::stop() {
	std::cout << "Shutting down server gracefully..." << std::endl;

	// Chiudi tutti i file descriptor aperti
	for (size_t i = 0; i < _poll_fds.size(); ++i) {
		if (_poll_fds[i].fd != _signal_fd) { // Non chiudere il pipe dei segnali
			close(_poll_fds[i].fd);
		}
	}
	_poll_fds.clear();

	// Chiudi i socket in ascolto
	for (std::map<int, const ServerConfig*>::iterator it = _listen_fds.begin(); it != _listen_fds.end(); ++it) {
		close(it->first);
	}
	_listen_fds.clear();

	// Termina tutti i processi CGI
	for (std::map<int, CgiState*>::iterator it = _cgi_map.begin(); it != _cgi_map.end(); ++it) {
		kill(it->second->pid, SIGTERM);
		waitpid(it->second->pid, NULL, 0);
		close(it->first); // Chiudi la pipe
		delete it->second;
	}
	_cgi_map.clear();
	
	// Reset CGI counter on shutdown
	_cgi_request_counter = 0;
	
	// Pulisci anche le pipe di input CGI
	for (std::map<int, CgiState*>::iterator it = _cgi_in_map.begin(); it != _cgi_in_map.end(); ++it) {
		close(it->first); // Chiudi la pipe di input
		// Non fare delete del CgiState qui perché già fatto sopra
	}
	_cgi_in_map.clear();

	// Pulisci tutte le mappe
	_client_data.clear();
	_requests.clear();
	_responses.clear();
	_client_servers.clear();
	_send_progress.clear();
	_cgi_client_map.clear();
	_in_cgi_client_map.clear();

	// Elimina la directory ./tmp e tutti i suoi file
	DIR* dir = opendir("./tmp");
	if (dir) {
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				std::string file_path = std::string("./tmp/") + entry->d_name;
				unlink(file_path.c_str());
			}
		}
		closedir(dir);
		rmdir("./tmp");
	}

	std::cout << "Server stopped" << std::endl;
}

void Server::_check_cgi_timeouts() {
    time_t current_time = time(NULL);
    std::vector<int> timed_out_clients;
    
    for (std::map<int, CgiState*>::iterator it = _cgi_map.begin(); it != _cgi_map.end(); ++it) {
        CgiState* cgi_state = it->second;
        int client_fd = cgi_state->client_fd;
        
        const ServerConfig* server_config = _client_servers[client_fd];
        if (!server_config) continue;
        
        const Request* request = cgi_state->saved_request;
        if (!request) continue;
        
        const RouteConfig* route = server_config->get_route(request->uri);
        if (!route) continue;
        
        time_t elapsed = current_time - cgi_state->start_time;
        if (elapsed >= route->cgi_timeout) {
            std::cout << "CGI timeout exceeded for client fd: " << client_fd 
                     << ", elapsed: " << elapsed << "s, timeout: " << route->cgi_timeout << "s" << std::endl;
            
            if (cgi_state->pid > 0) {
                kill(cgi_state->pid, SIGKILL);
                int status;
                waitpid(cgi_state->pid, &status, WNOHANG);
                std::cout << "Killed CGI process with PID: " << cgi_state->pid << std::endl;
            }
            
            timed_out_clients.push_back(client_fd);
        }
    }
    
    for (std::vector<int>::iterator it = timed_out_clients.begin(); it != timed_out_clients.end(); ++it) {
        int client_fd = *it;
        const ServerConfig* server_config = _client_servers[client_fd];
        
        _responses[client_fd] = error_response(500, server_config);
        
        for (size_t j = 0; j < _poll_fds.size(); ++j) {
            if (_poll_fds[j].fd == client_fd) {
                _poll_fds[j].events = POLLOUT;
                _poll_fds[j].revents = 0;
                break;
            }
        }
        
        // Pulisci le pipe CGI dalle strutture dati
        std::map<int, int>::iterator cgi_client_it = _cgi_client_map.find(client_fd);
        if (cgi_client_it != _cgi_client_map.end()) {
            int pipe_fd = cgi_client_it->second;
            std::map<int, CgiState*>::iterator cgi_it = _cgi_map.find(pipe_fd);
            if (cgi_it != _cgi_map.end()) {
                // Chiudi la pipe e rimuovi dai poll_fds
                close(pipe_fd);
                cgi_it->second->stdout_pipe[0] = -1;
                for (size_t j = 0; j < _poll_fds.size(); ++j) {
                    if (_poll_fds[j].fd == pipe_fd) {
                        _poll_fds.erase(_poll_fds.begin() + j);
                        break;
                    }
                }
                
                // Elimina il file temporaneo se esiste
                if (!cgi_it->second->tmp_filename.empty()) {
                    unlink(cgi_it->second->tmp_filename.c_str());
                }
                
                // Decrement CGI counter on timeout
                --_cgi_request_counter;
                std::cout << "CGI request #" << cgi_it->second->cgi_id << " timed out. Active CGI requests: " << _cgi_request_counter << std::endl;
                
                delete cgi_it->second;
                _cgi_map.erase(cgi_it);
            }
            _cgi_client_map.erase(cgi_client_it);
        }
        
        std::map<int, int>::iterator in_cgi_client_it = _in_cgi_client_map.find(client_fd);
        if (in_cgi_client_it != _in_cgi_client_map.end()) {
            int pipe_fd_in = in_cgi_client_it->second;
            std::map<int, CgiState*>::iterator cgi_in_it = _cgi_in_map.find(pipe_fd_in);
            if (cgi_in_it != _cgi_in_map.end()) {
                close(pipe_fd_in);
                for (size_t j = 0; j < _poll_fds.size(); ++j) {
                    if (_poll_fds[j].fd == pipe_fd_in) {
                        _poll_fds.erase(_poll_fds.begin() + j);
                        break;
                    }
                }
                _cgi_in_map.erase(cgi_in_it);
            }
            _in_cgi_client_map.erase(in_cgi_client_it);
        }
        
        std::cout << "CGI timeout handled for client fd: " << client_fd << std::endl;
    }
}