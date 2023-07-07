#include "header.hpp"

metaResponse handleResponse(const metaRequest &request) {
    metaResponse response(200, "OK", "text/plain", "Hello, World!");

    //reponse handling methods
    return response;
}

int main (int ac, char **av) {

	metaRequest parsedreq;

	parsedreq._method = "GET";
	parsedreq._url = "/path";
    parsedreq._version = "HTTP/1.1";
    parsedreq._headers.push_back(std::make_pair("contet-Type", "application/json"));
	std::string _req_raw = "raw req li ba9i ma3arefch lach msifetha liya zakaria";
    parsedreq._body = "Request body";

	metaResponse response = handleResponse(parsedreq);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////

// addrinfo hints;
	// memset(&hints, 0, sizeof(hints));
	// hints.ai_family = AF_INET;
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;
	// addrinfo *bind_address;
	// getaddrinfo(0, "8080", &hints, &bind_address);
	// std::cout << "Creating socket..." << std::endl;
	// int socket_listen;
	// socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
	// if (socket_listen < 0) {
	// 	std::cerr << "Error While Creating Socket..!" << std::endl;
	// 	return 1;
	// }
	// std::cout << "Binding Created Socket..." << std::endl;
	// if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
	// 	std::cerr << "Error While Binding Socket..!" << std::endl;
	// 	return 1;
	// }
	// freeaddrinfo(bind_address);
	// std::cout << "Waiting for Connection..." << std::endl;
	// if (listen(socket_listen, 1)) {
	// 	std::cerr << "Error While Listening..!" << std::endl;
	// 	return 1;
	// }
	// fd_set master;
	// FD_ZERO(&master);
	// FD_SET(socket_listen, &master);
	// int max_socket = socket_listen;
	// while (1) {
	// 	fd_set copy_reads;
	// 	copy_reads = master;
	// 	if (select(max_socket + 1, &copy_reads, 0, 0, 0) < 0) {
	// 		std::cerr << "Select() Fail..!" << std::endl;
	// 		return 1;
	// 	}
	// 	for (int i = 1; i <= max_socket; i++){
	// 		if (FD_ISSET(i, &copy_reads)) {
	// 			if (i == socket_listen) {
	// 				sockaddr_storage client_address;
	// 				socklen_t client_lenght = sizeof(client_address);
	// 				int client_socket = accept(socket_listen, (sockaddr *) &client_address,&client_lenght); //creayina sockaddrr dyal l client west accept() call
	// 				if (client_socket < 0) {
	// 					std::cerr << "Accept() Error..!" << std::endl;
	// 					return 1;
	// 				}
	// 				FD_SET(client_socket, &master);
	// 				if (client_socket > socket_listen) {max_socket = client_socket;}
	// 				char address_buffer[100];
	// 				getnameinfo((sockaddr*) &client_address, client_lenght, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
	// 				std::cout << "New Connection From: " << address_buffer << std:: endl;
	// 			}
	// 			else {
	// 				char read[1024];
	// 				int bytes_received = recv(i, read, 1024, 0);
	// 				if (bytes_received < 1) {
	// 					FD_CLR(i, &master);
	// 					close(i);
	// 					continue;
	// 				}
	// 				for (int j = 0; j < bytes_received; j++){read[j] = std::toupper(read[j]);}
	// 				send(i, read, bytes_received, 0);
	// 			}
	// 		}
	// 	}
	// }
	// std::cout << "Closing Listen_Socket..." << std::endl;
	// close(socket_listen);
	// std::cout << "finished." << std::endl;
	// return 0;