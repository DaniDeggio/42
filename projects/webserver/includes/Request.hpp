/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:02:21 by dde-giov          #+#    #+#             */
/*   Updated: 2025/10/04 11:19:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "utils.hpp"

class Request {
	public:
		struct MultipartPart {
			std::map<std::string, std::string> headers;
			std::string name;
			std::string filename;
			std::string contentType;
			std::string data;

			bool isFile() const { return !filename.empty(); }
		};

		std::string method;
		std::string uri;
		std::string version;
		std::map<std::string, std::string> headers;
		std::string queryString;
		std::string pathInfo;
		std::string body;

		const std::vector<MultipartPart>& getMultipartParts() const;
		const MultipartPart* getPartByName(const std::string& name) const;
		const MultipartPart* getFirstFilePart() const;
		std::string getFormField(const std::string& name) const;
		bool isMultipart() const;

		void parseFromRaw(const std::string& raw);

		Request();
		Request(const std::string& raw);

		bool hasHeader(const std::string& key) const;
		std::string getHeader(const std::string& key) const;
	
	private:
		static std::string ltrim(std::string s);
		static std::string rtrim(std::string s);
		static std::string trim(std::string s);

		static int tolower_int(int c);
		static std::string toLower(std::string s);

		static bool isTokenChar(unsigned char c);
		static void splitStartLine(const std::string& line, std::string& outMethod,
									std::string& outTarget, std::string& outVersion);
		void parseHeaders(const std::string& headersBlock);
		size_t parseBodyFraming(const std::string& raw, size_t posAfterHeaders);
		size_t parseChunked(const std::string& raw, size_t startPos, std::string& OutBody);
		void parseMultipartBody(const std::string& contentType);
		std::string extractBoundary(const std::string& contentType) const;
		void resetMultipart();

		std::pair<std::string, size_t> readCRLFLine(const std::string& raw, size_t from) const;

		std::string multipartBoundary;
		std::vector<MultipartPart> multipartParts;
		std::map<std::string, std::string> formFields;
};

#endif