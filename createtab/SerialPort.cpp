#include "SerialPort.h"
#include <windows.h>

COMMUNICATION_NS_BEGIN

class CSerialPortPrivate
{
public:
	explicit CSerialPortPrivate();
	explicit CSerialPortPrivate(const char * portName);
	virtual ~CSerialPortPrivate();

	void init();

	bool open(CSerialPort::OpenMode openMode);
	bool close();
	bool write(const char * pBuffer, long size, long msecs);
	bool read(char * pBuffer, long size, long msecs);

	bool clearError();
	bool clear(CSerialPort::Direction direction);
	bool flush();

	bool setBaudRate(CSerialPort::BaudRate baudRate);
	bool setDataBits(CSerialPort::DataBits dataBits);
	bool setParity(CSerialPort::Parity parity);
	bool setStopBits(CSerialPort::StopBits stopBits);
	bool setReadBufferSize(long size);
	bool setWriteBufferSize(long size);
public:
	HANDLE							m_hComm;				//端口文件句柄
	char							m_szPortName[16];		//端口号
	CSerialPort::BaudRate			m_baudRate;				//波特率
	CSerialPort::DataBits			m_dataBits;				//数据位
	CSerialPort::Parity				m_parity;				//奇偶校验
	CSerialPort::StopBits			m_stopBits;				//停止位
	CSerialPort::SerialPortError	m_error;				//错误
	long							m_readBufferSize;		//读缓冲区大小
	long							m_writeBufferSize;		//写缓冲区大小				
};

CSerialPortPrivate::CSerialPortPrivate()
{
	init();
}

CSerialPortPrivate::CSerialPortPrivate(const char * portName)
{
	init();
	strcpy(m_szPortName, portName);
}

void CSerialPortPrivate::init()
{
	m_hComm = INVALID_HANDLE_VALUE;
	strcpy(m_szPortName, "COM1");
	m_baudRate = CSerialPort::Baud9600;
	m_dataBits = CSerialPort::Data8;
	m_parity = CSerialPort::NoneParity;
	m_stopBits = CSerialPort::OneStop;
	m_error = CSerialPort::NoError;
	m_readBufferSize = 512;
	m_writeBufferSize = 1;
}

CSerialPortPrivate::~CSerialPortPrivate()
{
	m_hComm = INVALID_HANDLE_VALUE;
}

bool CSerialPortPrivate::open(CSerialPort::OpenMode openMode)
{
	DWORD dwDesiredAccess;
	if (openMode == CSerialPort::ReadOnly)
	{
		dwDesiredAccess = GENERIC_READ;
	}
	else if (openMode == CSerialPort::WriteOnly)
	{
		dwDesiredAccess = GENERIC_WRITE;
	}
	else
	{
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	}
	m_hComm = CreateFile(m_szPortName, dwDesiredAccess, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		m_error = CSerialPort::OpenError;
		return false;
	}
	else
	{
		//设置I/O缓冲区的大小
		SetupComm(m_hComm, m_readBufferSize, 1);
		//设置I/O超时
		COMMTIMEOUTS timeouts;
		timeouts.ReadIntervalTimeout = 100;
		timeouts.ReadTotalTimeoutConstant = 50;
		timeouts.ReadTotalTimeoutMultiplier = 500;
		timeouts.WriteTotalTimeoutConstant = 50;
		timeouts.WriteTotalTimeoutMultiplier = 200;
		SetCommTimeouts(m_hComm, &timeouts);
		return true;
	}
}

bool CSerialPortPrivate::close()
{
	if (CloseHandle(m_hComm))
	{
		m_hComm = INVALID_HANDLE_VALUE;
		return true;
	}
	else
	{
		m_error = CSerialPort::CloseError;
		return false;
	}
}

bool CSerialPortPrivate::write(const char * pBuffer, long size, long msecs)
{
	OVERLAPPED ol;
	memset(&ol, 0, sizeof(OVERLAPPED));
	ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == ol.hEvent)
	{
		m_error = CSerialPort::WriteError;
		return false;
	}
	DWORD nBytesWritten = 0;
	if(!WriteFile(m_hComm, pBuffer, size, &nBytesWritten, &ol))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_PENDING)
		{
			DWORD dwCode = WaitForSingleObject(ol.hEvent, msecs);
			switch (dwCode)
			{
			case WAIT_OBJECT_0:
				return true;
				break;
			case WAIT_FAILED:
				m_error = CSerialPort::UnknownError;
				return false;
				break;
			case WAIT_TIMEOUT:
				m_error = CSerialPort::TimeoutError;
				return false;
				break;
			}
		}
		else
		{
			m_error = CSerialPort::UnknownError;
			return false;
		}
	}
	flush();
	return true;
}

bool CSerialPortPrivate::read(char * pBuffer, long size, long msecs)
{
	OVERLAPPED ol;
	memset(&ol, 0, sizeof(OVERLAPPED));
	ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == ol.hEvent)
	{
		m_error = CSerialPort::ReadError;
		return false;
	}
	DWORD nBytesRead = 0;
	if (!ReadFile(m_hComm, pBuffer, size, &nBytesRead, &ol))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_PENDING)
		{
			DWORD dwCode = WaitForSingleObject(ol.hEvent, msecs);
			switch (dwCode)
			{
			case WAIT_OBJECT_0:
				return true;
				break;
			case WAIT_FAILED:
				m_error = CSerialPort::UnknownError;
				return false;
				break;
			case WAIT_TIMEOUT:
				m_error = CSerialPort::TimeoutError;
				return false;
				break;
			}
		}
		else
		{
			m_error = CSerialPort::UnknownError;
			return false;
		}
	}
	return true;
}

bool CSerialPortPrivate::clearError()
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DWORD dwError;
		COMSTAT comStat;
		if (ClearCommError(m_hComm, &dwError, &comStat))
		{
			m_error = CSerialPort::NoError;
			return true;
		}
		else
		{
			m_error = CSerialPort::UnknownError;
			return false;
		}
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::clear(CSerialPort::Direction direction)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DWORD dwFlags;
		switch (direction)
		{
		case CSerialPort::Input:
			dwFlags = PURGE_RXABORT | PURGE_RXCLEAR;
			break;
		case CSerialPort::Output:
			dwFlags = PURGE_TXABORT|PURGE_TXCLEAR;
			break;
		case CSerialPort::AllDirections:
			dwFlags = PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT|PURGE_TXCLEAR;
			break;
		default:
			;
		}
		if (PurgeComm(m_hComm, dwFlags))
		{
			return true;
		}
		else
		{
			m_error = CSerialPort::UnknownError;
			return false;
		}
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::flush()
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		if (FlushFileBuffers(m_hComm))
		{
			return true;
		}
		else
		{
			m_error = CSerialPort::UnknownError;
			return false;
		}
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setBaudRate(CSerialPort::BaudRate baudRate)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DCB dcb;
		if (!GetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		dcb.BaudRate = baudRate;
		if (!SetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_baudRate = baudRate;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setDataBits(CSerialPort::DataBits dataBits)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DCB dcb;
		if (!GetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		dcb.ByteSize = dataBits;
		if (!SetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_dataBits = dataBits;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setParity(CSerialPort::Parity parity)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DCB dcb;
		if (!GetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		dcb.Parity = parity;
		if (!SetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_parity = parity;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setStopBits(CSerialPort::StopBits stopBits)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		DCB dcb;
		if (!GetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		dcb.StopBits = stopBits;
		if (!SetCommState(m_hComm, &dcb))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_stopBits = stopBits;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setReadBufferSize(long size)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		if(!SetupComm(m_hComm, size, m_writeBufferSize))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_readBufferSize = size;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

bool CSerialPortPrivate::setWriteBufferSize(long size)
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		if(!SetupComm(m_hComm, m_readBufferSize, size))
		{
			m_error = CSerialPort::PermissionError;
			return false;
		}
		m_writeBufferSize = size;
		return true;
	}
	else
	{
		m_error = CSerialPort::NotOpenError;
		return false;
	}
}

CSerialPort::CSerialPort() 
	: d_ptr(new CSerialPortPrivate)
{

}

CSerialPort::CSerialPort(char * portName)
	: d_ptr(new CSerialPortPrivate(portName))
{
	
}

CSerialPort::~CSerialPort(void)
{
	if (d_ptr)
	{
		delete d_ptr;
	}
}

bool CSerialPort::open(CSerialPort::OpenMode openMode)
{
	return d_ptr->open(openMode);
}

bool CSerialPort::close()
{
	return d_ptr->close();
}

bool CSerialPort::write(const char * pBuffer, long size, long msecs)
{
	return d_ptr->write(pBuffer, size, msecs);
}

bool CSerialPort::read(char * pBuffer, long size, long msecs)
{
	return d_ptr->read(pBuffer, size, msecs);
}

void CSerialPort::setPortName(const char * portName)
{
	strcpy(d_ptr->m_szPortName, portName);
}

char * CSerialPort::portName() const
{
	return d_ptr->m_szPortName;
}

bool CSerialPort::setBaudRate(BaudRate baudRate)
{
	return d_ptr->setBaudRate(baudRate);
}

CSerialPort::BaudRate CSerialPort::baudRate() const
{
	return d_ptr->m_baudRate;
}

bool CSerialPort::setDataBits(DataBits dataBits)
{
	return d_ptr->setDataBits(dataBits);
}

CSerialPort::DataBits CSerialPort::dataBits() const
{
	return d_ptr->m_dataBits;
}

bool CSerialPort::setParity(Parity parity)
{
	return d_ptr->setParity(parity);
}

CSerialPort::Parity CSerialPort::parity() const
{
	return d_ptr->m_parity;
}

bool CSerialPort::setStopBits(StopBits stopBits)
{
	return d_ptr->setStopBits(stopBits);
}

CSerialPort::StopBits CSerialPort::stopBits() const
{
	return d_ptr->m_stopBits;
}

bool CSerialPort::setReadBufferSize(long size)
{
	return d_ptr->setReadBufferSize(size);
}

long CSerialPort::readBufferSize() const
{
	return d_ptr->m_readBufferSize;
}

bool CSerialPort::setWriteBufferSize(long size)
{
	return d_ptr->setWriteBufferSize(size);
}

long CSerialPort::writeBufferSize() const
{
	return d_ptr->m_writeBufferSize;
}

CSerialPort::SerialPortError CSerialPort::error()
{
	return d_ptr->m_error;
}

bool CSerialPort::clearError()
{
	return d_ptr->clearError();
}

bool CSerialPort::clear(Direction direction)
{
	return d_ptr->clear(direction);
}

bool CSerialPort::flush()
{
	return d_ptr->flush();
}

COMMUNICATION_NS_END