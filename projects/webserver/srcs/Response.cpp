/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:35:35 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/04 19:27:40 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"

Response::Response() : status_code(-1), status_text("") {}
Response::Response(int code, const std::string& text) : status_code(code), status_text(text) {}

void Response::stock_status(int code) {
	status_code = code;
	if (code == 200) {
		status_text = "OK";
		body = "<html><body><h1>200 OK</h1></body></html>";
	}else if (code == 201) {
		status_text = "Created";
		body = "<html><body><h1>201 Created</h1></body></html>";
	}else if (code == 204) {
		status_text = "No Content";
		body = "<html><body><h1>204 No Content</h1></body></html>";
	} else if (code == 301) {
		status_text = "Moved Permanently";
		body = "<html><body><h1>301 Moved Permanently</h1></body></html>";
	} else if (code == 302) {
		status_text = "Found";
		body = "<html><body><h1>302 Found</h1></body></html>";
	} else if (code == 400) {
		status_text = "Bad Request";
		body = "<html><body><h1>400 Bad Request</h1></body></html>";
	} else if (code == 401) {
		status_text = "Unauthorized";
		body = "<html><body><h1>401 Unauthorized</h1></body></html>";
	} else if (code == 403) {
		status_text = "Forbidden";
		body = "<html><body><h1>403 Forbidden</h1></body></html>";
	} else if (code == 404) {
		status_text = "Not Found";
		body = "<html><body><h1>404 Not Found</h1></body></html>";
	} else if (code == 405) {
		status_text = "Method Not Allowed";
		body = "<html><body><h1>405 Method Not Allowed</h1></body></html>";
	} else if (code == 413) {
		status_text = "Payload Too Large";
		body = "<html><body><h1>413 Payload Too Large</h1></body></html>";
	} else if (code == 500) {
		status_text = "Internal Server Error";
		body = "<html><body><h1>500 Internal Server Error</h1></body></html>";
	} else {
		status_text = "Unknown Status";
		body = "<html><body><h1>Unknown Status</h1></body></html>";
	}
}

void Response::set_status(int code) {
	status_code = code;
}

void Response::set_status_text(const std::string& text) {
	status_text = text;
}

void Response::add_header(const std::string& key, const std::string& value) {
	headers[key] = value;
}

void Response::set_body(const std::string& content) {
	body = content;
}

std::string Response::get_header(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = headers.find(key);
	if (it != headers.end())
		return it->second;
	return "";
}

int Response::get_code() const {
	return status_code;
}

std::string Response::get_status_line() const {
	std::ostringstream oss;
	oss << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
	return oss.str();
}

std::string Response::to_string() {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << status_code << " " << (status_text.empty() ? "OK" : status_text) << "\r\n";

    std::map<std::string, std::string>::iterator itCL = headers.find("Content-Length");
    if (itCL != headers.end()) headers.erase(itCL);
    itCL = headers.find("content-length");
    if (itCL != headers.end()) headers.erase(itCL);

    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
        const std::string& k = it->first;
        const std::string& v = it->second;
        if (k.empty() || k[0] == ' ' || k[0] == '\t') continue;
        if (k == "Status" || k == "status" || k == "STATUS") continue;
        oss << k << ": " << v << "\r\n";
    }

    oss << "Content-Length: " << body.size() << "\r\n";

    oss << "\r\n";
    oss << body;
    return oss.str();
}


static inline void strip_trailing_cr(std::string& s) {
    if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
}

static inline void trim_sp_ht(std::string& s) {
    size_t a = 0;
    while (a < s.size() && (s[a] == ' ' || s[a] == '\t')) ++a;
    size_t b = s.size();
    while (b > a && (s[b - 1] == ' ' || s[b - 1] == '\t')) --b;
    s.assign(s, a, b - a);
}

static inline void sanitize_header_value(std::string& v) {
    for (size_t i = 0; i < v.size(); ) {
        unsigned char c = static_cast<unsigned char>(v[i]);
        if ((c < 0x20 && c != '\t') || c == 0x7f) v.erase(i, 1);
        else ++i;
    }
}


void Response::parse_cgi_response(const std::string& cgi_output, const ServerConfig* /*server_config*/) {
    size_t sep_pos = cgi_output.find("\r\n\r\n");
    size_t sep_len = 4;
    if (sep_pos == std::string::npos) {
        sep_pos = cgi_output.find("\n\n");
        sep_len = (sep_pos == std::string::npos) ? 0 : 2;
    }

    std::string header_block;
    if (sep_pos == std::string::npos) {
        status_code = 200;
        status_text = "OK";
        body = cgi_output;
        headers.clear();
        headers["Content-Type"] = "text/html; charset=utf-8";
        return;
    } else {
        header_block = cgi_output.substr(0, sep_pos);
        body = cgi_output.substr(sep_pos + sep_len);
    }

    headers.clear();
    int parsed_status = -1;
    std::string parsed_reason;

    size_t pos = 0;
    while (pos <= header_block.size()) {
        size_t line_end = header_block.find('\n', pos);
        std::string line;
        if (line_end == std::string::npos) {
            line = header_block.substr(pos);
            pos = header_block.size() + 1;
        } else {
            line = header_block.substr(pos, line_end - pos);
            pos = line_end + 1;
        }
        strip_trailing_cr(line);
        if (line.empty()) break;

        if (!line.empty() && (line[0] == ' ' || line[0] == '\t')) {
            continue;
        }

        size_t colon = line.find(':');
        if (colon == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, colon);
        std::string value = line.substr(colon + 1);
        trim_sp_ht(value);
        sanitize_header_value(value);

        if (key == "Status" || key == "status" || key == "STATUS") {
            std::istringstream ss(value);
            int code = -1;
            ss >> code;
            if (code >= 100 && code < 600) {
                parsed_status = code;
                std::string reason;
                std::getline(ss, reason);
                trim_sp_ht(reason);
                parsed_reason = reason.empty() ? "" : reason;
            }
            continue; 
        }

        if (key == "Content-Length" || key == "content-length" || key == "TRANSFER-ENCODING" ||
            key == "Transfer-Encoding" || key == "transfer-encoding") {
            continue;
        }

        headers[key] = value;
    }

    if (parsed_status == -1) {
        status_code = 200;
        status_text = "OK";
    } else {
        status_code = parsed_status;
        status_text = !parsed_reason.empty() ? parsed_reason : "OK";
    }

    if (headers.find("Content-Type") == headers.end() &&
        headers.find("content-type") == headers.end()) {
        headers["Content-Type"] = "text/html; charset=utf-8";
    }

}
