/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 02:42:53 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/04 19:40:04 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::string to_lower(const std::string& str) {
	std::string lower_str = str;
	for (size_t i = 0; i < lower_str.size(); ++i) {
		lower_str[i] = std::tolower(lower_str[i]);
	}
	return lower_str;
}

std::string to_upper(const std::string& str) {
	std::string upper_str = str;
	for (size_t i = 0; i < upper_str.size(); ++i) {
		upper_str[i] = std::toupper(upper_str[i]);
	}
	return upper_str;
}

std::string has_cgi(const Request& request, const ServerConfig* server_config) {
	const RouteConfig* route = server_config->get_route(request.uri);

	if (route == NULL || route->cgi_methods.empty()) {
		return "";
	}
	if (std::find(route->cgi_methods.begin(), route->cgi_methods.end(), to_upper(request.method)) == route->cgi_methods.end()) {
		return "";
	}

	size_t pos = request.uri.find_last_of('.');
	if (pos == std::string::npos || pos == 0 || pos == request.uri.size() - 1) {
		return ""; 
	}
	if (route == NULL || route->cgi_extension.empty() || route->cgi_path.empty()) {
		return ""; 
	}
	bool match = false;
	
	for (size_t i = 0; i < route->cgi_extension.size(); ++i) {
		if (to_lower(request.uri.substr(pos)) == to_lower(route->cgi_extension[i])) {
			match = true;
			return to_lower(route->cgi_extension[i]);
		}
	}
	if (!match) {
		return ""; 
	}

	std::string extension = to_lower(request.uri.substr(pos + 1));
	
	return extension;
}

bool is_subpath(const std::string& path, const std::string& root) {
    std::string abs_path = canon_path(path);
    std::string abs_root = canon_path(root);

    if (abs_root.size() > 1 && abs_root[abs_root.size() - 1] == '/')
        abs_root.erase(abs_root.size() - 1);

    if (abs_path == abs_root)
        return true;

    if (abs_path.size() > abs_root.size() &&
        abs_path.compare(0, abs_root.size(), abs_root) == 0 &&
        abs_path[abs_root.size()] == '/')
        return true;

    return false;
}


std::string canon_path(const std::string& path) {
    char resolved[PATH_MAX];
    
    std::string absolute_path = path;
    if (path[0] != '/') {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            absolute_path = std::string(cwd) + "/" + path;
        }
    }
    
    if (realpath(absolute_path.c_str(), resolved) != NULL) {
        return std::string(resolved);
    } else {
        return normalize_path(absolute_path);
    }
}

std::string normalize_path(const std::string& path) {
	std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string part;
    
    while (std::getline(ss, part, '/')) {
		if (part == "..") {
            if (!parts.empty()) {
				parts.pop_back();
            }
        } else if (part != "." && !part.empty()) {
			parts.push_back(part);
        }
    }
    
    std::string normalized;
    for (size_t i = 0; i < parts.size(); i++) {
        normalized += "/" + parts[i];
    }
    
    if (normalized.empty()) {
		normalized = "/";
    }
    
    return normalized;
}

Response serve_file(const std::string& path) {
    std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
    std::string body((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
    Response r;
    r.stock_status(200);
    r.set_status_text("OK");
    r.set_body(body);

    std::string mime = get_mime_type(path);
    r.add_header("Content-Type", mime);
    if (mime == "text/html" || mime == "text/css" || mime == "text/javascript" || mime == "text/plain")
        r.add_header("Content-Type", mime + "; charset=utf-8");

    r.add_header("X-Content-Type-Options", "nosniff");

    return r;
}


Response serve_autoindex(const std::string& dir,const std::string& uri)
{
	DIR* d=opendir(dir.c_str());
	std::string html="<html><body><h1>Index of "+uri+"</h1><ul>";
	if (d) {
		struct dirent* e;
		while ((e=readdir(d))) {
			if (!strcmp(e->d_name,".")||!strcmp(e->d_name,"..")) continue;
			html+="<li><a href=\""+uri+e->d_name+"\">"+e->d_name+"</a></li>";
		}
		closedir(d);
	}
	html+="</ul></body></html>";
	Response r;
	r.stock_status(200);
	r.set_status_text("OK");
	r.set_body(html);
	r.add_header("Content-Type","text/html");
	return r;
}

Response error_response(int code, const ServerConfig* server_config) {
	Response r;
	r.stock_status(code);

	std::map<int, std::string>::const_iterator it = server_config->error_pages.find(code);
	if (it != server_config->error_pages.end()) {
		std::string error_page_path = it->second;
		struct stat st;
		if (stat(error_page_path.c_str(), &st) == 0 && S_ISREG(st.st_mode) && access(error_page_path.c_str(), R_OK) == 0) {
			std::ifstream ifs(error_page_path.c_str(), std::ios::in|std::ios::binary);
			std::string body((std::istreambuf_iterator<char>(ifs)),
							  std::istreambuf_iterator<char>());
			r.set_body(body);
			r.add_header("Content-Type", "text/html");
		}
	}

	return r;
}

std::string get_mime_type(const std::string& path) {
    std::string::size_type dot = path.find_last_of('.');
    std::string ext = (dot == std::string::npos) ? "" : to_lower(path.substr(dot + 1));

    static std::pair<std::string, std::string> mime_array[] = {
        std::make_pair("html", "text/html"),
        std::make_pair("htm",  "text/html"),
        std::make_pair("css",  "text/css"),
        std::make_pair("js",   "text/javascript"),
        std::make_pair("mjs",  "text/javascript"),
        std::make_pair("json", "application/json"),
        std::make_pair("txt",  "text/plain"),
        std::make_pair("xml",  "application/xml"),
        std::make_pair("svg",  "image/svg+xml"),
        std::make_pair("png",  "image/png"),
        std::make_pair("jpg",  "image/jpeg"),
        std::make_pair("jpeg", "image/jpeg"),
        std::make_pair("gif",  "image/gif"),
        std::make_pair("webp", "image/webp"),
        std::make_pair("bmp",  "image/bmp"),
        std::make_pair("ico",  "image/vnd.microsoft.icon"),
        std::make_pair("mp3",  "audio/mpeg"),
        std::make_pair("wav",  "audio/wav"),
        std::make_pair("ogg",  "audio/ogg"),
        std::make_pair("oga",  "audio/ogg"),
        std::make_pair("mp4",  "video/mp4"),
        std::make_pair("webm", "video/webm"),
        std::make_pair("ogv",  "video/ogg"),
        std::make_pair("woff",  "font/woff"),
        std::make_pair("woff2", "font/woff2"),
        std::make_pair("ttf",   "font/ttf"),
        std::make_pair("otf",   "font/otf"),
        std::make_pair("pdf",  "application/pdf"),
        std::make_pair("zip",  "application/zip"),
        std::make_pair("gz",   "application/gzip"),
        std::make_pair("tar",  "application/x-tar"),
        std::make_pair("7z",   "application/x-7z-compressed"),
        std::make_pair("bin",  "application/octet-stream")
    };
    static std::map<std::string, std::string> mime(
        mime_array,
        mime_array + sizeof(mime_array) / sizeof(mime_array[0])
    );

    std::map<std::string, std::string>::const_iterator it = mime.find(ext);
    if (it != mime.end()) return it->second;
    return "application/octet-stream";
}

bool validate_cgi(const std::string& out) {
	CgiValidation result;
	result.ok = false;
	result.has_sep = false;
	result.has_ct = false;
	result.has_loc = false;
	result.has_status = false;

	size_t sep_pos = out.find("\r\n\r\n");
	if (sep_pos == std::string::npos) {
		sep_pos = out.find("\n\n");
	}
	if (sep_pos == std::string::npos) {
		return result.ok;
	}
	result.has_sep = true;

	std::string header_block = out.substr(0, sep_pos);
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
		if (!line.empty() && line[line.size() - 1] == '\r') {
			line.erase(line.size() - 1);
		}
		if (line.empty())
			break;

		size_t colon = line.find(':');
		if (colon == std::string::npos) {
			continue;
		}

		std::string key = line.substr(0, colon);
		std::string value = line.substr(colon + 1);
		size_t val_start = value.find_first_not_of(" \t");
		if (val_start != std::string::npos) {
			value = value.substr(val_start);
		} else {
			value.clear();
		}

		if (to_lower(key) == "Content-Type" || to_lower(key) == "content-type") {
			result.has_ct = true;
		} else if (to_lower(key) == "Location" || to_lower(key) == "location") {
			result.has_loc = true;
		} else if (to_lower(key) == "Status" || to_lower(key) == "status") {
			result.has_status = true;
		}
	}
	bool has_any_cgi = result.has_ct || result.has_loc || result.has_status;
	if (!has_any_cgi)
		return result.ok; // result.ok=false
	if (!out.substr(sep_pos + 4).empty() && !result.has_ct && !result.has_loc)
		return result.ok; // result.ok=false
	
	result.ok = true;
	return result.ok;
}
