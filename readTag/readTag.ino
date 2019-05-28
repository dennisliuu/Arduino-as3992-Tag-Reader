//#include <SoftSerial.h>
//#define  DEBUG
#define   LOCAT_EPC 6      //扫描标签，标签的EPC数据在接收到数据的起始位置
#define   EPC_len   12      //EPC长度
#define   reserved_membank   0
#define   EPC_membank        1
#define   TID_membank        2
#define   USER_membank       3
#define  WordsofData  6
//#define TimeInterval    10000
//unsigned long time;
//NewSoftSerial as3992(2,3);
char  COMMAND[30];     //保存命令数据
char  sta[30];
char  ReceBuffer[30];
char EPC[20];    //保存扫描到的标签的EPC数据
//char EPC_A[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88};
char char_in;
int NumofRece = 0; //rfid返回的数据的个数
char data[20];
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  //  as3992.begin(115200);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

//String num[52];



int point[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
String temp = "";
String num[] = {"5018114480-300539996-674448-26-10688-80",
                "5018114480-300539996-70-72112-26-10678-31",
                "5018114480-300539996-70-72-80-26-10678-30",
                "5018114480-300539996-7610748-26-10653-84",
                "5018114480-300539996-76106-16-26-10653-85",
                "5018114480-300539996-58121-16-26-106125-25",
                "5018114480-300539996-6126112-26-106112105",
                "5018114480-300539996-75-8148-26-10658-68",
                "5018114480-300539996-75-82-16-26-10658-69",
                "5018114480-300539996-6126-80-26-106112106",
                "5018114480-300539996-6698-16-26-10693-117",
                "5018114480-300539996-599548-26-106121124",
                "5018114480-300539996-65-10648-26-1069888"
               };

void loop()
{
  SearchForTag(EPC, 0x01);
}
void ReceData(char * buffer)    //接收数据
{
  NumofRece = 0;
  int index = 0;
  while (Serial.available() > 0)
  {
    char_in = Serial.read();
    NumofRece++;
    *(buffer + index) = char_in;
    index++;
  }
}

char SearchForTag(char *epc, char start)  //扫描标签
{
  COMMAND[0] = 0x31;
  COMMAND[1] = 0x03;
  COMMAND[2] = start;
  char i;
  for (i = 0; i < COMMAND[1]; i++) {
    Serial.print(COMMAND[i]);
    delay(50);    //延迟很重要
  }
  ReceData(ReceBuffer);
  if (ReceBuffer[0] == 0x32  && ReceBuffer[2] > 0)
  {
    temp = "";
    for (char j = LOCAT_EPC, k = 0; j < NumofRece; j++, k++) {//保存EPC
      epc[k] = ReceBuffer[j];
    }

    for (i = 0; i < NumofRece; i++) {
      temp = temp + int(*(ReceBuffer + i));
    }
//    Serial.println(temp);
        for (int j = 0; j < 13; j++) {
    //      Serial.println(num[j]);
    //      Serial.println(temp);
          if (num[j] == temp)
          {
            Serial.println();
            Serial.print(num[j]);
            Serial.print(" = ");
            Serial.print(j + 1);
            Serial.println();
          }
        }
    return ReceBuffer[2];
  }
  else
    return 0;
}
