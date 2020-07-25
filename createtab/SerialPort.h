#pragma once
#include "communication_global.h"

COMMUNICATION_NS_BEGIN

class CSerialPortPrivate;
class COMMUNICATION_API CSerialPort
{
public:
	enum BaudRate {
		Baud1200 = 1200,
		Baud2400 = 2400,
		Baud4800 = 4800,
		Baud9600 = 9600,
		Baud19200 = 19200,
		Baud38400 = 38400,
		Baud57600 = 57600,
		Baud115200 = 115200,
		UnknownBaud = -1
	};

	enum DataBits {
		Data5 = 5,
		Data6 = 6,
		Data7 = 7,
		Data8 = 8,
		UnknownDataBits = -1
	};

	enum Parity {
		NoneParity = 0,
		OddParity = 1,
		EvenParity = 2,
		MarkParity = 3,
		SpaceParity = 4,
		UnknownParity = -1
	};

	enum StopBits {
		OneStop = 0,
		OneAndHalfStop = 1,
		TwoStop = 2,
		UnknownStopBits = -1
	};

	enum Direction  {
		Input			=	0x0001,
		Output			=	0x0002,
		AllDirections	=	Input | Output,
	};

	enum OpenMode {
		ReadOnly	=	0x0001,
		WriteOnly	=	0x0002,
		ReadWrite	=	ReadOnly | WriteOnly,
	};

	enum SerialPortError {
		NoError,
		DeviceNotFoundError,
		PermissionError,
		OpenError,
		CloseError,
		ParityError,
		FramingError,
		BreakConditionError,
		WriteError,
		ReadError,
		ResourceError,
		UnsupportedOperationError,
		UnknownError,
		TimeoutError,
		NotOpenError
	};
public:
	explicit CSerialPort();
	explicit CSerialPort(char * portName);
	virtual ~CSerialPort(void);

	bool open(OpenMode openMode);
	bool close();
	
	bool write(const char * pBuffer, long size, long msecs = 1000);
	bool read(char * pBuffer, long size, long msecs = 1000);

	void setPortName(const char * portName);
	char * portName() const;

	bool setBaudRate(BaudRate baudRate);
	BaudRate baudRate() const;

	bool setDataBits(DataBits dataBits);
	DataBits dataBits() const;

	bool setParity(Parity parity);
	Parity parity() const;

	bool setStopBits(StopBits stopBits);
	StopBits stopBits() const;

	bool setReadBufferSize(long size);
	long readBufferSize() const;

	bool setWriteBufferSize(long size);
	long writeBufferSize() const;


	SerialPortError error();
	bool clearError();
	bool clear(Direction direction = AllDirections);
	bool flush();

private:
	CSerialPortPrivate *  const d_ptr;
};

COMMUNICATION_NS_END
