/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 08:58:05 by asacchin          #+#    #+#             */
/*   Updated: 2025/10/04 19:26:05 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <utility>

Request::Request() : method(""), uri(""), version(""), body("") {
    resetMultipart();
}

Request::Request(const std::string& raw) {
    parseFromRaw(raw);
	// std::cout << " URI: " << uri << " queryString: " << queryString << " " << std::endl; //DEBUG
}

std::string Request::ltrim(std::string s) {
    size_t i = 0;
    while (i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'))
        ++i;
    return s.substr(i);
}

std::string Request::rtrim(std::string s) {
    size_t i = s.size();
    while (i > 0 && (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\r' || s[i - 1] == '\n'))
        --i;
    s.resize(i);
    return s;
}

std::string Request::trim(std::string s) {
    return rtrim(ltrim(s));
}

int Request::tolower_int(int c) { return std::tolower(c); }

std::string Request::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), tolower_int);
    return s;
}

bool Request::isTokenChar(unsigned char c) {
    const std::string tchars = "!#$%&'*+-.^_`|~";
    return std::isalnum(c) || (tchars.find(c) != std::string::npos);
}

void Request::splitStartLine(const std::string& line,
                             std::string& outMethod,
                             std::string& outTarget,
                             std::string& outVersion) {
    size_t sp1 = line.find(' ');
    if (sp1 == std::string::npos)
        throw std::runtime_error("400");
    size_t sp2 = line.find(' ', sp1 + 1);
    if (sp2 == std::string::npos)
        throw std::runtime_error("400");

    outMethod = line.substr(0, sp1);
    outTarget = line.substr(sp1 + 1, sp2 - sp1 - 1);
    outVersion = line.substr(sp2 + 1);

    if (outMethod.empty() || outTarget.empty() || outVersion.empty())
        throw std::runtime_error("400");

    for (size_t i = 0; i < outMethod.size(); ++i) {
        if (!isTokenChar(static_cast<unsigned char>(outMethod[i])))
            throw std::runtime_error("400");
    }

    if (outVersion.rfind("HTTP/", 0) != 0)
        throw std::runtime_error("400");

    if (outVersion != "HTTP/1.1")
        throw std::runtime_error("505");
}


void Request::parseHeaders(const std::string& headersBlock) {
    std::istringstream iss(headersBlock);
    std::string line;
    size_t headerCount = 0;

    while (std::getline(iss, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        if (line.empty())
            break;

        if (!line.empty() && (line[0] == ' ' || line[0] == '\t'))
            throw std::runtime_error("400");

        size_t colon = line.find(':');
        if (colon == std::string::npos)
            throw std::runtime_error("400");

        std::string name = toLower(trim(line.substr(0, colon)));
        std::string value = trim(line.substr(colon + 1));

        if (name.empty())
            throw std::runtime_error("400");

        headers[name] = value;

        if (++headerCount > 1000)
            throw std::runtime_error("431");
    }

    bool absoluteForm = false;
    if (uri.size() >= 7 &&
        (uri.rfind("http://", 0) == 0 || uri.rfind("https://", 0) == 0))
        absoluteForm = true;

    if (!absoluteForm) {
        if (headers.find("host") == headers.end())
            throw std::runtime_error("400");
    }
}

std::pair<std::string, size_t> Request::readCRLFLine(const std::string& raw, size_t from) const {
    size_t end = raw.find("\r\n", from);
    if (end == std::string::npos)
        throw std::runtime_error("400");
    return std::make_pair(raw.substr(from, end - from), end + 2);
}

size_t Request::parseChunked(const std::string& raw, size_t pos, std::string& outBody) {
    while (true) {
        std::pair<std::string, size_t> p = readCRLFLine(raw, pos);
        std::string sizeLine = p.first;
        pos = p.second;

        size_t sc = sizeLine.find(';');
        std::string hexSize = (sc == std::string::npos) ? sizeLine : sizeLine.substr(0, sc);
        hexSize = trim(hexSize);
        if (hexSize.empty())
            throw std::runtime_error("400");

        unsigned long long sizeVal = 0;
        for (size_t i = 0; i < hexSize.size(); ++i) {
            unsigned char hc = static_cast<unsigned char>(hexSize[i]);
            unsigned int v;
            if (hc >= '0' && hc <= '9') v = hc - '0';
            else if (hc >= 'a' && hc <= 'f') v = hc - 'a' + 10;
            else if (hc >= 'A' && hc <= 'F') v = hc - 'A' + 10;
            else throw std::runtime_error("400");
            if (sizeVal > (std::numeric_limits<unsigned long long>::max() >> 4))
                throw std::runtime_error("413");
            sizeVal = (sizeVal << 4) + v;
        }

        if (sizeVal > 0) {
            if (pos + sizeVal + 2 > raw.size())
                throw std::runtime_error("400");
            outBody.append(raw, pos, static_cast<size_t>(sizeVal));
            pos += static_cast<size_t>(sizeVal);
            if (raw.compare(pos, 2, "\r\n") != 0)
                throw std::runtime_error("400");
            pos += 2;
        } else {
            while (true) {
                std::pair<std::string, size_t> t = readCRLFLine(raw, pos);
                pos = t.second;
                if (t.first.empty())
                    break;
            }
            break;
        }
    }
    return pos;
}

size_t Request::parseBodyFraming(const std::string& raw, size_t posAfterHeaders) {
    std::string te;
    if (headers.find("transfer-encoding") != headers.end())
        te = toLower(headers["transfer-encoding"]);

    if (!te.empty()) {
        if (te.find("chunked") == std::string::npos)
            throw std::runtime_error("501");
        size_t endPos = parseChunked(raw, posAfterHeaders, body);
        return endPos;
    }

    if (headers.find("content-length") != headers.end()) {
        const std::string clStrTmp = headers["content-length"];
        const std::string clStr = trim(clStrTmp);
        if (clStr.empty())
            throw std::runtime_error("400");

        unsigned long long len = 0;
        for (size_t i = 0; i < clStr.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(clStr[i]);
            if (!std::isdigit(c))
                throw std::runtime_error("400");
            len = len * 10 + (c - '0');
            if (len > static_cast<unsigned long long>(std::numeric_limits<size_t>::max()))
                throw std::runtime_error("413");
        }

        size_t n = static_cast<size_t>(len);
        if (posAfterHeaders + n > raw.size())
            throw std::runtime_error("400");

        body.assign(raw, posAfterHeaders, n);
        return posAfterHeaders + n;
    }

    body.clear();
    return posAfterHeaders;
}

void Request::parseFromRaw(const std::string& raw) {
    method.clear(); uri.clear(); version.clear();
    headers.clear(); body.clear();
    resetMultipart();

    size_t headerEnd = raw.find("\r\n\r\n");
    if (headerEnd == std::string::npos)
        throw std::runtime_error("400");

    size_t lineEnd = raw.find("\r\n");
    if (lineEnd == std::string::npos || lineEnd > headerEnd)
        throw std::runtime_error("400");

    std::string startLine = raw.substr(0, lineEnd);
    splitStartLine(startLine, method, uri, version);
	size_t qmark = uri.find('?');
	if (qmark != std::string::npos) {
		queryString = uri.substr(qmark + 1);
		uri = uri.substr(0, qmark);
	} else
		queryString.clear();

    std::string headersBlock = raw.substr(lineEnd + 2, headerEnd - (lineEnd + 2));
    parseHeaders(headersBlock);

    size_t bodyStart = headerEnd + 4;
    parseBodyFraming(raw, bodyStart);

    std::string contentType = getHeader("Content-Type");
    if (!contentType.empty()) {
        std::string lowered = toLower(contentType);
        if (lowered.find("multipart/form-data") != std::string::npos) {
            parseMultipartBody(contentType);
        }
    }
}

bool Request::hasHeader(const std::string& key) const {
	return headers.find(toLower(key)) != headers.end();
}

std::string Request::getHeader(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = headers.find(toLower(key));
	if (it != headers.end()) {
		return it->second;
	}
	return "";
}

void Request::parseMultipartBody(const std::string& contentType) {
    multipartBoundary = extractBoundary(contentType);
    multipartParts.clear();
    formFields.clear();

    if (multipartBoundary.empty())
        throw std::runtime_error("400");

    if (body.empty())
        return;

    std::string delimiter = "--" + multipartBoundary;
    size_t searchPos = 0;

    while (true) {
        size_t boundaryPos = body.find(delimiter, searchPos);
        if (boundaryPos == std::string::npos)
            break;
        size_t sectionStart = boundaryPos + delimiter.size();
        if (sectionStart > body.size())
            break;

        if (sectionStart + 2 <= body.size() && body.compare(sectionStart, 2, "--") == 0)
            break;

        if (sectionStart + 2 <= body.size() && body.compare(sectionStart, 2, "\r\n") == 0)
            sectionStart += 2;
        else if (sectionStart < body.size() && body[sectionStart] == '\n')
            ++sectionStart;
        else if (sectionStart < body.size() && body[sectionStart] == '\r') {
            ++sectionStart;
            if (sectionStart < body.size() && body[sectionStart] == '\n')
                ++sectionStart;
        }

        size_t headerEnd = body.find("\r\n\r\n", sectionStart);
        if (headerEnd == std::string::npos)
            throw std::runtime_error("400");
        std::string headersBlock = body.substr(sectionStart, headerEnd - sectionStart);
        size_t contentStart = headerEnd + 4;

        size_t nextBoundary = body.find(delimiter, contentStart);
        if (nextBoundary == std::string::npos)
            throw std::runtime_error("400");

        size_t contentEnd = nextBoundary;
        if (contentEnd >= 2 && body.compare(contentEnd - 2, 2, "\r\n") == 0)
            contentEnd -= 2;

        MultipartPart part;
        std::istringstream headerStream(headersBlock);
        std::string headerLine;
        while (std::getline(headerStream, headerLine)) {
            if (!headerLine.empty() && headerLine[headerLine.size() - 1] == '\r')
                headerLine.erase(headerLine.size() - 1);
            if (headerLine.empty())
                continue;

            size_t colon = headerLine.find(':');
            if (colon == std::string::npos)
                continue;

            std::string name = toLower(trim(headerLine.substr(0, colon)));
            std::string value = trim(headerLine.substr(colon + 1));
            if (!name.empty())
                part.headers[name] = value;
        }

        part.data.assign(body, contentStart, contentEnd - contentStart);

        std::map<std::string, std::string>::const_iterator cdIt = part.headers.find("content-disposition");
        if (cdIt != part.headers.end()) {
            std::string disposition = cdIt->second;
            size_t tokenPos = 0;
            while (tokenPos < disposition.size()) {
                size_t semi = disposition.find(';', tokenPos);
                std::string token = (semi == std::string::npos) ? disposition.substr(tokenPos) : disposition.substr(tokenPos, semi - tokenPos);
                token = trim(token);
                size_t eq = token.find('=');
                if (eq != std::string::npos) {
                    std::string key = toLower(trim(token.substr(0, eq)));
                    std::string value = trim(token.substr(eq + 1));
                    if (value.size() >= 2 && value[0] == '"' && value[value.size() - 1] == '"')
                        value = value.substr(1, value.size() - 2);
                    if (key == "name")
                        part.name = value;
                    else if (key == "filename")
                        part.filename = value;
                }
                if (semi == std::string::npos)
                    break;
                tokenPos = semi + 1;
            }
        }

        std::map<std::string, std::string>::const_iterator ctIt = part.headers.find("content-type");
        if (ctIt != part.headers.end())
            part.contentType = ctIt->second;

        if (!part.name.empty() && !part.isFile())
            formFields[part.name] = part.data;

        multipartParts.push_back(part);

        searchPos = nextBoundary;
    }
}

std::string Request::extractBoundary(const std::string& contentType) const {
    std::string lowered = toLower(contentType);
    size_t pos = lowered.find("boundary=");
    if (pos == std::string::npos)
        return "";
    pos += 9;
    std::string boundary = contentType.substr(pos);
    size_t semi = boundary.find(';');
    if (semi != std::string::npos)
        boundary = boundary.substr(0, semi);
    boundary = trim(boundary);
    if (!boundary.empty() && boundary[0] == '"' && boundary[boundary.size() - 1] == '"')
        boundary = boundary.substr(1, boundary.size() - 2);
    return boundary;
}

void Request::resetMultipart() {
    multipartBoundary.clear();
    multipartParts.clear();
    formFields.clear();
}

const std::vector<Request::MultipartPart>& Request::getMultipartParts() const {
    return multipartParts;
}

const Request::MultipartPart* Request::getPartByName(const std::string& name) const {
    for (std::vector<MultipartPart>::const_iterator it = multipartParts.begin(); it != multipartParts.end(); ++it) {
        if (it->name == name)
            return &(*it);
    }
    return NULL;
}

const Request::MultipartPart* Request::getFirstFilePart() const {
    for (std::vector<MultipartPart>::const_iterator it = multipartParts.begin(); it != multipartParts.end(); ++it) {
        if (it->isFile())
            return &(*it);
    }
    return NULL;
}

std::string Request::getFormField(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator it = formFields.find(name);
    if (it != formFields.end())
        return it->second;
    return "";
}

bool Request::isMultipart() const {
    return !multipartBoundary.empty();
}
