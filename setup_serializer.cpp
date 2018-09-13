// 
// 
// 

#include <EEPROM.h>
#include "setup_serializer.h"




bool SetupSeializer::WriteString(String in)
{
	EEPROM.update('0', SETUP_VERIFICATION_ADDRESS); // Invalidating any setup in EEPROM before attempting new write

	// Assuming 1024 bytes of EEPROM
	if (in.length() > EEPROM_SIZE - SETUP_START_ADDRESS) // Setup will always be placed after the verification byte
		return false;
		
	int writeAddress = SETUP_START_ADDRESS; 
	for (int readAddress = 0; readAddress < in.length(); readAddress++)
	{
		if (in[readAddress] == '\n')
			continue; // Skipping newlines.
		EEPROM.update(writeAddress, in[readAddress]);
		writeAddress++;
	}
	

	EEPROM.update(writeAddress, '\0');
	EEPROM.update('1', SETUP_VERIFICATION_ADDRESS);
	return true;
}

bool SetupSeializer::Open()
{
	if (EEPROM.read(SETUP_VERIFICATION_ADDRESS) == '0')
		return false;
	if (inMemSetup != NULL)
		delete inMemSetup;
	inMemSetup = new String();

	int address = SETUP_START_ADDRESS;

	char b = (char) EEPROM.read(address);
	while (b != '\0')
	{
		inMemSetup += b;
		address++;
		if (address >= EEPROM_SIZE)
		{
			delete inMemSetup;
			return false;
		}
		b = (char) EEPROM.read(address);
	}
	return true;
}

void SetupSeializer::Close()
{
	if (inMemSetup != NULL)
		delete inMemSetup;
}





bool SetupSeializer::ValueOfField(String field, int * val)
{
	String tempVal;
	if (!ValueOfField(field, &tempVal))
		return false;
	(*val) = (int) tempVal.toInt();
	return true;
}

bool SetupSeializer::ValueOfField(String field, String * val)
{
	if (EEPROM.read(SETUP_VERIFICATION_ADDRESS) == '0')
		return false;
	if (inMemSetup == NULL)
		return false;

	int index = inMemSetup->indexOf(field);
	if (index < 0)
		return false;

	int valueStartIndex = inMemSetup->indexOf(":", index) + 1;
	int entryEndIndex = inMemSetup->indexOf(";", index);
	(*val) = inMemSetup->substring(valueStartIndex, entryEndIndex);
	return true;
}

String SetupSeializer::GetInMemSetup()
{
	return *inMemSetup;
}






