#ifndef __SFTP_CXX__
#define __SFTP_CXX__
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <functional>

class ssh_cxx;

class sftp_cxx
{
friend class ssh_cxx;
friend class std::hash<sftp_cxx>;
private:
	ssh_cxx& _ssh;
	sftp_session _s;
private:
	sftp_cxx(ssh_cxx& ssh);
public:
	~sftp_cxx();
public:
	bool operator == (const sftp_cxx& sftp) const;
public:
	void close();
public:
	sftp_cxx(const sftp_cxx&) = delete;
	sftp_cxx& operator= (const sftp_cxx&) = delete;
	sftp_cxx(sftp_cxx&& sftp);
	sftp_cxx& operator= (sftp_cxx&& sftp);
	operator bool() const;
};

namespace std
{
    template<> struct hash<sftp_cxx>
    {
        std::size_t operator()(sftp_cxx const& sftp) const noexcept
        {
		return  std::hash<sftp_session>{}(sftp._s);
        }
    };
}
#endif //__SFTP_CXX__
