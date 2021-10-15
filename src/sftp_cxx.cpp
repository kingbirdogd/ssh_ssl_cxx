#include <ssh_cxx.hpp>
#include <sftp_cxx.hpp>

sftp_cxx::sftp_cxx(ssh_cxx& ssh):
	_ssh(ssh),
	_s(sftp_new(_ssh._s))
{
}

sftp_cxx::~sftp_cxx()
{
	sftp_free(_s);
	_s = nullptr;
}

bool sftp_cxx::operator == (const sftp_cxx& sftp) const
{
	return _s == sftp._s;
}

void sftp_cxx::close()
{
	if (_s)
	{
		_ssh._sftp.erase(*this);
	}
}

sftp_cxx::sftp_cxx(sftp_cxx&& sftp):
	_ssh(sftp._ssh),
	_s(sftp._s)
{
	sftp._s = nullptr;
}

sftp_cxx& sftp_cxx::operator= (sftp_cxx&& sftp)
{
	_s = sftp._s;
	sftp._s = nullptr;
	return *this;
}

sftp_cxx::operator bool() const
{
	return _s != nullptr;
}

