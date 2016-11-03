#pragma once
#include <unordered_map>
#include <thread>
#include <regex>
#include <map>
#include <functional>
#include <boost/asio.hpp>
#include <vector>
#include <ostream>

namespace WebServerBase{
	
	struct Request {
		// ���󷽷�(post, get), ����·��, http�汾
		std::string method, path, http_version;
		
		std::shared_ptr<std::istream> content;

		std::unordered_map<std::string, std::string> header;
		// ������ʽ����·��ƥ��
		std::smatch path_match;

	};

	typedef std::map < std::string, std::unordered_map < std::string,
		std::function<void(std::ostream&, Request& )> > > resource_type;


	// http or https
	template<typename socket_type>
	class ServerBase
	{
	public:
		explicit ServerBase(unsigned short port, size_t num_threads = 1);

		virtual ~ServerBase();
		// ����������
		void start();
		void hehehe() = delete;

	protected:

		virtual void accept();
		// implemention request and reponse
		void process_request_and_responce(std::shared_ptr<socket_type> socket) const;
	
		Request prase_Request(std::istream& stream) const;
	public:
		// ���ڷ�����������Դ����ʽ
		resource_type resource;
		// ���ڱ���Ĭ����Դ�Ĵ���ʽ
		resource_type default_resource;

	protected:
		// ʵ�ֶ��ڲ�������Դ�Ĵ�����Դ����start�д���
		std::vector<resource_type::iterator> all_resources;
		/*
		asio ���е� io_service �ǵ����������е��첽 IO �¼���Ҫͨ�������ַ�����
		��Ҫ IO �Ķ���Ĺ��캯��������Ҫ����һ�� io_service ����
		*/
		boost::asio::io_service m_io_service;
		// IP ��ַ���˿ںš�Э��汾����һ�� endpoint����ͨ����� endpoint �ڷ��������
		boost::asio::ip::tcp::endpoint endpoint;
		// tcp::acceptor ���󣬲���ָ���˿��ϵȴ����ӣ� ������Ҫio_service ��endpoing��������
		boost::asio::ip::tcp::acceptor acceptor;

		size_t num_threads;

		std::vector<std::thread> threads;
		
	};

	
}


