#include <serials/serials.h>
 
int main(int argc, char** argv)
{
	int iSetOpt = 0;//SetOpt 的增量i
 
	//serialInit();
	//send_data_tty(SerFd, "hello series\n", sizeof("hello series\n"));
 
	int fdSerial = 0;
 
	//openPort
	if ((fdSerial = openPort(fdSerial, 4))<0)//1--"/dev/ttyS0",2--"/dev/ttyS1",3--"/dev/ttyS2",4--"/dev/ttyUSB0，5--"/dev/ttyUSB1,6--"/dev/ttyUSB2 以此类推" 小电脑上是2--"/dev/ttyS1"
	{
		perror("open_port error");
		return -1;
	}
	//setOpt(fdSerial, 9600, 8, 'N', 1)
	if ((iSetOpt = setOpt(fdSerial, 9600, 8, 'N', 1))<0)
	{
		perror("set_opt error");
		return -1;
	}
	printf("Serial fdSerial=%d\n", fdSerial);
 
	tcflush(fdSerial, TCIOFLUSH);//清掉串口缓存
	fcntl(fdSerial, F_SETFL, 0);
 
 
	char buffRcvData[buffLen] = { 0 };
	unsigned int readDataNum = 0;
	//发送类型1
 	char* str = "send-data-sucessful-!";

	  ros::init(argc, argv, "serials");
	  ros::NodeHandle n;
	  //ros::Subscriber sub = n.subscribe("/imu_message", 1000, alubiCallback);
	 // ros::spin();
	  ros::Rate loop_rate(5);


	//发送数据类型2
	buffRcvData[0] = 's';
	buffRcvData[1] = 't';
	buffRcvData[2] = 'a';
	buffRcvData[3] = 'r';
	buffRcvData[4] = 't';

	
	//sendDataTty(fdSerial, buffRcvData, 5);第一次发送测试
	  while (ros::ok()){
		
		readDataNum = readDataTty(fdSerial, buffRcvData, rcvTimeOut, buffLen);//收
		if(readDataNum>0)
		{
		sendDataTty(fdSerial, buffRcvData, readDataNum);//发2
		}
		readDataNum=0;
		//sendDataTty(fdSerial, buffRcvData, 5);
		//printf("------------\n");


		sendDataTty(fdSerial, str, 22);//发1
		ros::spinOnce();
       		loop_rate.sleep();
	}
	
	
	return 0;
}

