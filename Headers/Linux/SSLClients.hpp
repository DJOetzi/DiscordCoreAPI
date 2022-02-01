/// SSLClents.hpp - Header file for the "SSL Client" stuff.
/// Dec 12, 2021
/// Chris M.
/// https://github.com/RealTimeChris

#ifndef SSL_CLIENTS
#define SSL_CLIENTS

#ifndef OPENSSL_NO_DEPRECATED
#define OPENSSL_NO_DEPRECATED
#endif

#include "FoundationEntities.hpp"
#include <openssl/x509v3.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

namespace DiscordCoreInternal {

	using SOCKET = int;

	struct BIOWrapper {

		struct BIODeleter {
			void operator()(BIO* other) {
				if (other != nullptr) {
					BIO_free(other);
					other = nullptr;
				}
			}
		};

		BIOWrapper& operator=(BIO* other) {
			this->bioPtr.reset(other);
			if (BIO_up_ref(other) != 1) {
				std::cout << "BIO_up_ref() Error: ";
				ERR_print_errors_fp(stdout);
				std::cout << std::endl;
			};
			return *this;
		}

		operator BIO* () {
			return this->bioPtr.get();
		}

		BIOWrapper(nullptr_t) {};

	protected:
		std::unique_ptr<BIO, BIODeleter> bioPtr{ nullptr, BIODeleter{} };
	};

	struct addrinfoWrapper {

		struct addrinfoDeleter {
			void operator()(addrinfo* other) {
				if (other != nullptr) {
					freeaddrinfo(other);
					other = nullptr;
				}
			}
		};

		addrinfo* operator->() {
			return this->addrinfoPtrTwo;
		}

		operator addrinfo** () {
			return &this->addrinfoPtrTwo;
		}

		operator addrinfo* () {
			return this->addrinfoPtrTwo;
		}

		addrinfoWrapper(nullptr_t) {
			this->addrinfoPtrTwo = this->addrinfoPtr.get();
		};

	protected:
		std::unique_ptr<addrinfo, addrinfoDeleter> addrinfoPtr{ new addrinfo{}, addrinfoDeleter{} };
		addrinfo* addrinfoPtrTwo{ nullptr };
	};

	struct SSL_CTXWrapper {

		struct SSL_CTXDeleter {
			void operator()(SSL_CTX* other) {
				if (other != nullptr) {
					SSL_CTX_free(other);
					other = nullptr;
				}
			}
		};

		SSL_CTXWrapper& operator=(SSL_CTX* other) {
			this->sslCTXPtr.reset(other);
			if (SSL_CTX_up_ref(other) != 1) {
				std::cout << "SSL_CTX_up_ref() Error: ";
				ERR_print_errors_fp(stdout);
				std::cout << std::endl;
			}
			return *this;
		}

		operator SSL_CTX* () {
			return this->sslCTXPtr.get();
		}

		SSL_CTXWrapper(nullptr_t) {};

	protected:
		std::unique_ptr<SSL_CTX, SSL_CTXDeleter> sslCTXPtr{ nullptr , SSL_CTXDeleter{} };
	};

	struct SSLWrapper {

		struct SSLDeleter {
			void operator()(SSL* other) {
				if (other != nullptr) {
					SSL_shutdown(other);
					SSL_free(other);
					other = nullptr;
				}
			}
		};

		SSLWrapper& operator=(SSL* other) {
			this->sslPtr.reset(other);
			if (SSL_up_ref(other) != 1) {
				std::cout << "SSL_up_ref() Error: ";
				ERR_print_errors_fp(stdout);
				std::cout << std::endl;
			}
			return *this;
		}

		operator SSL* () {
			return this->sslPtr.get();
		}

		SSLWrapper(nullptr_t) {};

	protected:
		std::unique_ptr<SSL, SSLDeleter> sslPtr{ nullptr , SSLDeleter{} };
	};

	struct SOCKETWrapper {

		struct SOCKETDeleter {
			void operator()(SOCKET* other) {
				if (other != nullptr) {
					close(*other);
					other = nullptr;
				}
			}
		};

		SOCKETWrapper& operator=(SOCKET other) {
			*this->socketPtr = other;
			return *this;
		}

		operator SOCKET() {
			return *this->socketPtr;
		}

		SOCKETWrapper(nullptr_t) {}

	protected:
		std::unique_ptr<SOCKET, SOCKETDeleter> socketPtr{ new SOCKET{}, SOCKETDeleter{} };
	};

	class HttpSSLClient {
	public:

		HttpSSLClient(std::string* theVector);

		HttpSSLClient(nullptr_t);

		bool connect(std::string baseUrl, std::string portNew = "443");

		bool writeData(std::string& theData);

		bool readData();

		virtual ~HttpSSLClient() = default;

	protected:

		std::string soundcloudCertPath{ "C:/SSL/certs/SoundCloudCert.pem" };
		std::string defaultCertPath{ "C:/SSL/certs/DiscordCert.pem" };
		std::string googleCertPath{ "C:/SSL/certs/GoogleCert.pem" };
		std::string* inputBufferPtr{ nullptr };
		BIOWrapper connectionBio{ nullptr };
		int32_t maxBufferSize{ 16 * 1024 };
		SSL_CTXWrapper context{ nullptr };
		SSLWrapper ssl{ nullptr };
	};

	template <typename ObjectType>
	concept StringOrVector = requires(ObjectType v)
	{
		{v.data() }->std::convertible_to<char*>;
	} || requires(ObjectType v)
	{
		{v.data()}->std::convertible_to<uint8_t*>;
	};

	class WebSocketSSLClient {
	public:

		WebSocketSSLClient(std::string baseUrl, std::string port, std::vector<uint8_t>* inputBuffer, int64_t maxBufferSize = 16 * 1024);

		WebSocketSSLClient(nullptr_t);

		template<StringOrVector TypeName>
		bool writeData(TypeName& data) {
			size_t writtenBytes{ 0 };
			if (this->ssl == nullptr) {
				return false;
			}
			int32_t returnValue = SSL_write_ex(this->ssl, data.data(), static_cast<uint32_t>(data.size()), &writtenBytes);
			if (returnValue != 1) {
				std::cout << "SSL_write_ex() Error: " << SSL_get_error(this->ssl, returnValue) << std::endl;
				ERR_print_errors_fp(stdout);
				std::cout << std::endl;
				return false;
			};
			data.clear();
			return true;
		}

		std::vector<uint8_t> getData();

		int64_t getBytesRead();

		bool readData();

	protected:

		const int64_t maxBufferSize{ 1024 * 16 };
		std::vector<uint8_t>* inputBufferPtr{};
		SOCKETWrapper theSocket{ nullptr };
		SSL_CTXWrapper context{ nullptr };
		SSLWrapper ssl{ nullptr };
		int64_t bytesRead{ 0 };
	};

	class DatagramSocketSSLClient {
	public:

		DatagramSocketSSLClient(std::string hostName, std::string port, std::vector<uint8_t>*);

		DatagramSocketSSLClient(nullptr_t);

		bool writeData(std::string& dataToWrite);

		std::vector<uint8_t> getData();

		void readData(bool doWeClear);

	protected:

		const int32_t maxBufferSize{ 1024 * 16 };
		std::vector<uint8_t>* inputBufferPtr{};
		BIOWrapper connectionBio{ nullptr };
		SOCKETWrapper theSocket{ nullptr };
	};
}
#endif