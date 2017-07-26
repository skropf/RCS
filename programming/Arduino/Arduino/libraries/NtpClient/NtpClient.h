#ifndef NtpClient_h
#define NtpClient_h


struct DateTime
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int seconds;
};

class NtpClient
{
  public:
  	NtpClient();
    DateTime getTimefromDefaultServer();
    DateTime getTimefromServer(byte[]);
  private:
  	unsigned long sendNTPpacket(byte *);
};

#endif