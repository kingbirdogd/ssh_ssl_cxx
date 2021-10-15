#ifndef __SSH_CXX__
#define __SSH_CXX__
#include <libssh/libssh.h>
#include <string>
#include <unordered_set>
#include <sftp_cxx.hpp>


class ssh_cxx
{
friend class sftp_cxx;
private:
	ssh_session _s;
	std::unordered_set<sftp_cxx> _sftp;
public:
	ssh_cxx();
	ssh_cxx(const std::string& host, const std::string& user, const std::string& pass, unsigned short int port = 22);
	~ssh_cxx();
	sftp_cxx& get_sftp();
	bool login(const std::string& host, const std::string& user, const std::string& pass, unsigned short int port = 22);
	void close();
public:
	ssh_cxx(const ssh_cxx&) = delete;
	ssh_cxx& operator= (const ssh_cxx&) = delete;
	ssh_cxx(ssh_cxx&& ssh);
	ssh_cxx& operator= (ssh_cxx&& ssh);
	operator bool() const;
};
#endif //__SSH_CXX__
