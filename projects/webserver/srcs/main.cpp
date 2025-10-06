/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:30:52 by asacchin          #+#    #+#             */
/*   Updated: 2025/10/04 19:22:32 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"
#include "../includes/Server.hpp"
#include "../includes/ConfigParser.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <fstream>

int signal_pipe[2] = {-1, -1};

void signal_handler(int signum) {
    (void)signum;
    ssize_t result = write(signal_pipe[1], "X", 1);
    if (result == -1) {
        std::cerr << "Error writing to signal pipe" << std::endl;
        return;
    }
    if (result == 0) {
        std::cerr << "No byte written to signal pipe" << std::endl;
        return;
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " path_to_config_file" << std::endl;
            return 1;
        }

        if (pipe(signal_pipe) != 0) {
            std::cerr << "Failed to create signal pipe" << std::endl;
            return 1;
        }

        struct sigaction sa;
        sa.sa_handler = signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);
		
		struct sigaction sa_pipe;
		sa_pipe.sa_handler = SIG_IGN;
		sigemptyset(&sa_pipe.sa_mask);
		sa_pipe.sa_flags = 0;
		sigaction(SIGPIPE, &sa_pipe, NULL);

        const char* config_path = argv[1];
        std::ifstream f(config_path);
        if (!f.good()) {
            std::cerr << "Cannot open config file: " << config_path << std::endl;
            return 1;
        }
        f.close();

        std::cout << "Parsing configuration from " << config_path << " ..." << std::endl;

        ConfigParser parser;
        GlobalConfig config = parser.parseConfigFile(config_path);

        Server server(config, signal_pipe[0]);

        std::cout << "Starting server..." << std::endl;
        server.start();

		close(signal_pipe[0]);
		close(signal_pipe[1]);
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
