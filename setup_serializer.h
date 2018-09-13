// setup_serializer.h

#ifndef _SETUP_SERIALIZER_h
#define _SETUP_SERIALIZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define SETUP_VERIFICATION_ADDRESS 0
#define SETUP_START_ADDRESS 1
#define EEPROM_SIZE 1024 


class SetupSeializer
{
public:
	bool WriteString(String in);

	bool Open();
	void Close();
	bool ValueOfField(String field, int* val);
	bool ValueOfField(String field, String* val);
	String GetInMemSetup();


private:
	String* inMemSetup;
};
#endif

